//
// Created by spl211 on 16/11/2021.
//

#include "../include/Action.h"
#include "../include/Studio.h"
#include "../include/Trainer.h"
#include "../include/Workout.h"

BaseAction::BaseAction() {};

ActionStatus BaseAction::getStatus() const { return status; }

std::string BaseAction::getErrorMsg() const { return errorMsg; }

void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
    std::cout << "Error: " << errorMsg <<std::endl;
}

void BaseAction::complete() {
    status = COMPLETED;
    this->errorMsg = nullptr; // should be changed?
}


OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) :
        trainerId(id), customers(customersList){
}

void OpenTrainer::act(Studio &studio) {
    Trainer *trainer = studio.getTrainer(trainerId);

    if (trainer == nullptr || trainer->isOpen() || trainer->getCapacity() < customers.size() )
        error("Workout session does not exist or is already open.");
    else{
        trainer->openTrainer();
        for (Customer *customer : customers)
            trainer->addCustomer(customer);
    }
    trainer = nullptr;
}

Order::Order(int id): trainerId(id){};

void Order::act(Studio &studio){
    Trainer *trainer = studio.getTrainer(trainerId);

    if (trainer == nullptr || !trainer->isOpen() )
        error("Trainer does not exist or is not open.");
    else{
        //for all customers that the trainer has, we add their preferred workout to the trainer orderList
        for (Customer* customer : trainer->getCustomers())
            trainer->order(customer->getId(), customer->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());


        std::cout<< "order" << studio.getTrainer(trainerId) << std::endl;
        //printing all customers' order
        for (const OrderPair& pair : trainer->getOrders()){
            std::string name = trainer->getCustomer(pair.first)->getName();
            std::cout<< name << " Is Doing " << pair.second.getName() << std::endl;
        }
    }
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):
        srcTrainer(src), dstTrainer(dst), id(customerId){}
//act(*studio);
;

void MoveCustomer::act(Studio &studio) {
    Trainer *trainerSrc = studio.getTrainer(srcTrainer);
    Trainer *trainerDst = studio.getTrainer(dstTrainer);

    if ( trainerSrc == nullptr || !trainerSrc->isOpen() || trainerSrc->getCustomer(id) == nullptr )
        error("Cannot move customer");
    else if ( trainerDst == nullptr || !trainerDst->isOpen() || !trainerDst->availableCapacity() )
        error("Cannot move customer");
    else{
        Customer* customer = trainerSrc->getCustomer(id);

        std::vector<OrderPair> list = trainerSrc->getOrders();
        for (int i = 0; i < list.size(); i++){
            if (list[i].first == id) {
                trainerDst->addOrder(list[i]);
            }
        }
        trainerDst->addCustomer(customer);
        trainerSrc->removeCustomer(customer->getId());

        if ( trainerSrc->getCustomers().empty() )
            trainerSrc->closeTrainer();


        delete customer; //
    }
    delete trainerSrc;
    delete trainerDst;
}


Close::Close(int id):
        trainerId(id){}

void Close::act(Studio &studio) {
    Trainer* trainer = studio.getTrainer(trainerId);
    if ( trainer == nullptr || !trainer->isOpen() )
        error("Trainer does not exist or is not open");
    trainer->closeTrainer();
    trainer->updateSalary();

    std::cout << "Trainer " << trainerId << " closed. Salary "<<  trainer->getSalary() << "NIS" << std::endl;

};

