//
// Created by spl211 on 16/11/2021.
//

#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Trainer.h"
BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const {
    return status;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
    std:: cout <<"Error: " << errorMsg <<"\n";
}

void BaseAction::complete() {
    status = COMPLETED;
    this->errorMsg = nullptr;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):
trainerId (id),customers(customersList){
    //act(&studio); //TODO:understand forward declartions
}

void OpenTrainer::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || trainer->isOpen()|| trainer->getCapacity() < customers.size())
        error( "Workout session does not exist or is already open.");
    else{
        trainer->openTrainer();
        for (int i = 0; i < customers.size(); i++) {
            trainer->addCustomer(customers[i]);
        }
    }
}