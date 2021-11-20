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
    trainer = nullptr;
}

Order::Order(int id): trainerId(id) {
    //act(&studi)};//TODO: same
}

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
        std:: cout <<"order "<< trainerId << "\n";
        for(const OrderPair& pair : trainer->getOrders()){
            std:: cout << trainer->getCustomer(pair.first)->getName()<< " Is Doing " << pair.second.getName() <<"\n";
        }
    }
    //TODO:figure out if vectors need to be deleted
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src), dstTrainer(dst),id(customerId) {
    //act(&studi)};//TODO: same
}

void MoveCustomer::act(Studio &studio) {
    Trainer *trainerDst = studio.getTrainer(dstTrainer);
    Trainer *trainerSrc = studio.getTrainer(srcTrainer);
    if(trainerSrc == nullptr ||!trainerSrc->isOpen() || trainerSrc->getCustomer(id) == nullptr|| trainerDst == nullptr || !trainerDst->isOpen() || trainerDst->availableCapacity() < 1)
        error( "Cannot move customer");

    else{

        //TODO:finish this
        std::vector<OrderPair>::iterator itr;
        for(itr = trainerSrc->getOrders().begin(); itr < trainerSrc->getOrders().end(); itr ++){
            if (itr->first == id)
                trainerDst->getOrders().emplace_back(trainerSrc->getOrders().pop)
        }
        trainerDst->addCustomer(trainerSrc->getCustomer(id));
        trainerSrc->removeCustomer(id);
        if (trainerSrc->getCapacity() == trainerSrc->availableCapacity())
            trainerSrc->closeTrainer();
    }
}

