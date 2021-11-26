//
// Created by spl211 on 16/11/2021.
//

#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Trainer.h"


extern Studio *backup;

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg ="Error: " + errorMsg;
    std:: cout << errorMsg <<"\n";
}

void BaseAction::complete() {
    status = COMPLETED;
    //this->errorMsg = nullptr;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):
        trainerId (id),customers(customersList){}

void OpenTrainer::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen())
        error( "Trainer does not exist or is not open");
    else{
        std::vector<Customer *> rightsize;
        for (int i = static_cast<int>(customers.size() - 1); i >= trainer->getCapacity(); i--) {
            delete customers[i];
            customers.pop_back();
        }
        trainer->openTrainer();
        for (Customer *c : customers) {
            Customer *customer = c->clone();
            trainer->addCustomer(customer);
        }
        complete();
    }
}

std::string OpenTrainer::toString() const {
    std::string str = "open ";
    str += std::to_string(trainerId);
    for (Customer* customer : customers) {
        str +=" ";
        str += customer->toString();
    }
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" " + getErrorMsg();
    return str;
}

BaseAction *OpenTrainer::clone() {
    std::vector<Customer *> cloneCustomerList;
    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        cloneCustomerList.emplace_back(customers[i]->clone());
    }
    return new OpenTrainer(trainerId,cloneCustomerList);
}

OpenTrainer::~OpenTrainer() {
    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        delete customers[i];
    }
    customers.clear();
}

Order::Order(int id): trainerId(id) {}

void Order::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || !trainer->isOpen())
        error( "Trainer does not exist or is not open");
    else{
        std::vector<Workout>& workoutOptions =  studio.getWorkoutOptions();
        //for all customers that the trainers has, add their preferred workout routine
        for (Customer *customer : trainer->getCustomers()) {
            trainer->order( customer->getId() , customer->order(workoutOptions), workoutOptions);
        }
        for(const OrderPair& pair : trainer->getOrders()){
            std:: cout << trainer->getCustomer(pair.first)->getName()<< " Is Doing " << pair.second.getName() <<"\n";
        }
        complete();
    }
}

std::string Order::toString() const {
    std::string str = "order ";
    str += std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *Order::clone() {
    return new Order(trainerId);
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src), dstTrainer(dst),id(customerId) {}

void MoveCustomer::act(Studio &studio) {
    Trainer *trainerDst = studio.getTrainer(dstTrainer);
    Trainer *trainerSrc = studio.getTrainer(srcTrainer);
    if (trainerSrc == nullptr || !trainerSrc->isOpen() || trainerSrc->getCustomer(id) == nullptr ||
        trainerDst == nullptr || !trainerDst->isOpen() || trainerDst->availableCapacity() < 1)
        error("Cannot move customer");

    else {
        std::vector<OrderPair> orderList = trainerSrc->getOrders();
        for (int i = 0; i < static_cast<int>(orderList.size()); i++) {
            if (orderList[i].first == id) {
                trainerDst->addOrder(orderList[i]);
            }
        }
        trainerDst->addCustomer(trainerSrc->getCustomer(id));
        trainerSrc->removeCustomer(id);
        if (trainerSrc->getCapacity() == trainerSrc->availableCapacity())
            trainerSrc->closeTrainer();
        complete();
    }
}

std::string MoveCustomer::toString() const {
    std::string str = "move ";
    str += std::to_string(srcTrainer);
    str +=" "+ std::to_string(dstTrainer);
    str += " " +std::to_string(id);
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *MoveCustomer::clone() {
    return new MoveCustomer(srcTrainer, dstTrainer,id);
}

Close::Close(int id): trainerId(id){}

void Close::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || !trainer->isOpen())
        error("Trainer does not exist or is not open");
    else{
        trainer->closeTrainer();
        std:: cout <<"Trainer "<< trainerId << "  closed. Salary "<< trainer-> getSalary() <<"NIS"<< "\n";
        complete();
    }
}

std::string Close::toString() const {
    std::string str = "close ";
    str += std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *Close::clone() {
    return new Close(trainerId);
}

CloseAll::CloseAll() {}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        Trainer *trainer = studio.getTrainer(i);
        if (trainer->isOpen()){
            Close close =  Close(i);
            close.act(studio);
        }
    }
    complete();
}

std::string CloseAll::toString() const {
    std::string str = "closeall";
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *CloseAll::clone() {
    return new CloseAll();
}

PrintWorkoutOptions::PrintWorkoutOptions() {}

void PrintWorkoutOptions::act(Studio &studio) {
    std::vector<Workout> workoutOptions =  studio.getWorkoutOptions();
    for (int i = 0; i < static_cast<int>(workoutOptions.size()); ++i) {
        std::cout << workoutOptions[i].toString()<< "\n";
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    std::string str = "workout_options";
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *PrintWorkoutOptions::clone() {
    return new PrintWorkoutOptions();
}

PrintTrainerStatus::PrintTrainerStatus(int id): trainerId(id) {}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer != nullptr && !(trainer->isOpen())){
        std::cout <<"Trainer " << trainerId<<" status: closed\n";
    }
    if (trainer != nullptr && trainer->isOpen()){
        std::cout <<"Trainer "<< trainerId<<" status: open\nCustomers: \n";
        std::vector<Customer *> customers = trainer->getCustomers();
        for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
            std::cout <<customers[i]->getId() << " "<<customers[i]->getName()<<"\n";
        }
        std::cout <<"Orders:\n";
        std::vector<OrderPair> orderList = trainer->getOrders();
        for (int i = 0; i < static_cast<int>(orderList.size()); ++i) {
            std::cout <<orderList[i].second.getName()<<" " <<std::to_string(orderList[i].second.getPrice())<<"NIS"<< " "<< std::to_string(orderList[i].first)<<"\n";
        }
        int sum =0;
        for(int i =0; i < static_cast<int>(orderList.size()); i++){
            sum = sum + orderList[i].second.getPrice();
        }
        std::cout <<"Current Trainer’s Salary: " << std::to_string(trainer->getSalary() + sum)<<"NIS"<< "\n";
    }
    complete();
}

std::string PrintTrainerStatus::toString() const {
    std::string str = "status ";
    str += std::to_string(trainerId);
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *PrintTrainerStatus::clone() {
    return new PrintTrainerStatus(trainerId);
}

PrintActionsLog::PrintActionsLog() = default;

void PrintActionsLog::act(Studio &studio) {
    const std::vector<BaseAction*>& actionLog = studio.getActionsLog();
    for (int i = 0; i < static_cast<int>(actionLog.size()); i++) {
        std::cout<< actionLog[i]->toString()<<"\n";
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    std::string str = "log";
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *PrintActionsLog::clone() {
    return new PrintActionsLog();
}

BackupStudio::BackupStudio() {}

void BackupStudio::act(Studio &studio) {
    if (backup != nullptr) {
        delete backup;
        backup = nullptr;
    }
    backup = new Studio(studio);
    complete();
}

std::string BackupStudio::toString() const {
    std::string str = "backup";
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *BackupStudio::clone() {
    return new BackupStudio;
}

RestoreStudio::RestoreStudio() {}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr)
        error("No backup available");
    else{
        studio = *backup;
        complete();
    }
}

std::string RestoreStudio::toString() const {
    std::string str = "restore";
    if (getStatus() == COMPLETED)
        str += " Completed";
    else
        str +=" "+ getErrorMsg();
    return str;
}

BaseAction *RestoreStudio::clone() {
    return new RestoreStudio();
}