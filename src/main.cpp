#include "../include/Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

static  OpenTrainer breakdownOpen(const std::string& str){
    std::vector<Customer *> customers;

}

static Order breakdownOrder(const std::string& str){

}

static MoveCustomer breakdownMove(const std::string& str){

}

static Close breakdownClose(const std::string& str){

}

static PrintWorkoutOptions breakdownWorkout_options(const std::string& str){

}

static PrintTrainerStatus breakdownStatus(const std::string& str){
    PrintTrainerStatus printTrainerStatus = PrintTrainerStatus(static_cast<int>(str.back()));
    return printTrainerStatus;
}

static PrintActionsLog breakdownLog(const std::string& str){
    PrintActionsLog actionsLog = PrintActionsLog();
    return actionsLog;
}

static BackupStudio breakdownBackup(const std::string& str){
    BackupStudio backupStudio = BackupStudio();
    return backupStudio;
}

static RestoreStudio breakdownRestore(const std::string& str){
    RestoreStudio restoreStudio = RestoreStudio();
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
            OpenTrainer action = breakdownOpen(str);
            action.act(studio);
        }
        if (str.substr(0,5) == "order"){
            Order action = breakdownOrder(str);
            action.act(studio);
        }
        if (str.substr(0,4) == "move"){
            MoveCustomer action = breakdownMove(str);
            action.act(studio);
        }
        if (str.substr(0,5) == "close"){
            Close action = breakdownClose(str);
            action.act(studio);
        }
        if (str.substr(0,4) == "work"){
            PrintWorkoutOptions action = breakdownWorkout_options(str);
            action.act(studio);
        }
        if (str.substr(0,4) == "stat"){
            PrintTrainerStatus action = breakdownStatus(str);
            action.act(studio);
        }
        if (str.substr(0,3) == "log"){
            PrintActionsLog action = breakdownLog(str);
            action.act(studio);
        }
        if (str.substr(0,4) == "back"){
            BackupStudio action = breakdownBackup(str);
            action.act(studio);
        }
        if (str.substr(0,4) == "rest"){
            RestoreStudio action = breakdownRestore(str);
            action.act(studio);
        }
        std::cin >> str;
    }



    CloseAll closeAll = CloseAll();
    closeAll.act(studio);

    return 0;
}
