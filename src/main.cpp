#include "../include/Studio.h"
#include <iostream>
#include <algorithm>

using namespace std;

Studio* backup = nullptr;

static  OpenTrainer *breakdownOpen(const std::string& str, Studio &studio){
    std::vector<Customer *> customers;
    int idStart = (int) str.find(' ') + 1;
    int idEnd = (int) str.find(' ', idStart);
    if (idEnd == -1){
        //there are no customers
        OpenTrainer *openTrainer = new OpenTrainer(std::stoi(str.substr(idStart)), customers);
        return openTrainer;
    }
    int id = std::stoi(str.substr(idStart,idEnd-idStart));
    int nameStart = idEnd;
    int nameEnd;
    std::string name;
    for (int i = 0; i < std::count(str.begin(),str.end(), ','); ++i) {
        nameStart +=1;
        nameEnd = (int) str.find(',', nameStart);
        name = str.substr(nameStart,nameEnd-nameStart);
        Customer *customer;
        if (str[nameEnd + 1] == 's')
            customer = new SweatyCustomer(name,studio.getNextCustomerId());
        if (str[nameEnd + 1] == 'c')
            customer = new CheapCustomer(name,studio.getNextCustomerId());
        if (str[nameEnd + 1] == 'm')
            customer = new HeavyMuscleCustomer(name,studio.getNextCustomerId());
        if (str[nameEnd + 1] == 'f')
            customer = new FullBodyCustomer(name,studio.getNextCustomerId());
        customers.emplace_back(customer);
        nameStart = (int) str.find(' ', nameStart);
    }
    OpenTrainer *openTrainer = new OpenTrainer(id, customers);
    return openTrainer;
}

static Order *breakdownOrder(const std::string& str){
    int id =(int) str.find(' ') + 1;
    Order *order = new Order(static_cast<int>(std::stoi(str.substr(id))));
    return order;
}

static MoveCustomer *breakdownMove(const std::string& str){
    int srcStart = (int) str.find(' ') + 1;
    int srcEnd = (int) str.find(' ', srcStart);
    int src = std::stoi(str.substr(srcStart,srcEnd-srcStart));
    int dstStart = srcEnd + 1;
    int dstEnd =(int) str.find(' ', srcEnd);
    int dst = std::stoi(str.substr(dstStart,dstEnd-dstStart));
    int idStart = srcEnd + 1;
    int id = std::stoi(str.substr(idStart));
    MoveCustomer *moveCustomer = new MoveCustomer(dst,src,id);
    return moveCustomer;

}

static Close *breakdownClose(const std::string& str){
    int id =(int) str.find(' ') + 1;
    Close *close = new Close(static_cast<int>(std::stoi(str.substr(id))));
    return close;
}

static PrintWorkoutOptions *breakdownWorkout_options(const std::string& str){
    PrintWorkoutOptions *workoutOptions = new PrintWorkoutOptions();
    return workoutOptions;
}

static PrintTrainerStatus *breakdownStatus(const std::string& str){
    int id =(int) str.find(' ') + 1;
    PrintTrainerStatus *printTrainerStatus = new PrintTrainerStatus(static_cast<int>(std::stoi(str.substr(id))));
    return printTrainerStatus;
}

static PrintActionsLog *breakdownLog(const std::string& str){
    PrintActionsLog *actionsLog = new PrintActionsLog();
    return actionsLog;
}

static BackupStudio *breakdownBackup(const std::string& str){
    BackupStudio * backupStudio = new BackupStudio();
    return backupStudio;
}

static RestoreStudio *breakdownRestore(const std::string& str){
    RestoreStudio * restoreStudio = new RestoreStudio();
    return restoreStudio;
}

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    std::string str;
    std::cin >> str;
    while(str !="closeall"){
        if (str.substr(0,4) == "open"){
            OpenTrainer *action = breakdownOpen(str, studio);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,5) == "order"){
            Order *action = breakdownOrder(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,4) == "move"){
            MoveCustomer *action = breakdownMove(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,5) == "close"){
            Close *action = breakdownClose(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,4) == "work"){
            PrintWorkoutOptions *action = breakdownWorkout_options(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,4) == "stat"){
            PrintTrainerStatus *action = breakdownStatus(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,3) == "log"){
            PrintActionsLog *action = breakdownLog(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,4) == "back"){
            BackupStudio *action = breakdownBackup(str);
            studio.addAction(action);
            action->act(studio);
        }
        if (str.substr(0,4) == "rest"){
            RestoreStudio *action = breakdownRestore(str);
            studio.addAction(action);
            action->act(studio);
        }
        std::cin >> str;
    }



    CloseAll closeAll = CloseAll();
    closeAll.act(studio);

    return 0;
}
