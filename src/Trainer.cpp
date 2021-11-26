//
// Created by spl211 on 09/11/2021.
//

#include "../include/Trainer.h"
#include <vector>

Trainer::Trainer(int t_capacity):
        capacity(t_capacity), open(false), customersList({}),
        orderList({}), salary(0){};

//destructor
Trainer::~Trainer(){
    clear();
}

void Trainer::clear(){
    for (int i = 0; i < customersList.size(); i++){
        customersList[i]->~Customer();
//        customersList[i] = nullptr;
    }
    customersList.clear(); //TODO: check memory leak
    orderList.clear();
}
//copy constructor
Trainer::Trainer(const Trainer &trainer):
    capacity(trainer.capacity), open(trainer.open),salary(trainer.salary){
    for (Customer * customer : trainer.customersList)
        this->customersList.emplace_back(customer->clone());
    for (OrderPair orderPair : trainer.orderList)
        this->orderList.emplace_back(orderPair);
}

//copy assignment operator
Trainer &Trainer::operator=(const Trainer &other) {
    //check for self assignment
    if (this == &other)
        return *this;
    //free the pointers
    for (int i = 0; i < customersList.size(); i++) {
        if (customersList[i] != nullptr){
            delete &customersList[i];
            customersList[i] = nullptr;
        }
    }
    for (int i = 0; i < orderList.size(); i++)
        delete &orderList[i];

    orderList.clear(); //TODO: check memory leak
    customersList.clear();
//    customersList.erase(customersList.begin(),customersList.end()); // TODO: check whether it is important when compiling

    for (OrderPair orderPair : other.orderList) {
        orderList.emplace_back(orderPair);
    }
    for (int i = 0; i < other.customersList.size(); i++) {
        customersList.emplace_back(other.customersList[i]->clone());
    }
    //copy the rest of the data
    capacity = other.capacity;
    open = other.open;
    salary = other.salary;
}

int Trainer::getCapacity() const{ return capacity; }

void Trainer::addCustomer(Customer *customer) {
    customersList.emplace_back(customer);
}

void Trainer::removeCustomer(int id) { //TODO: check when compiling
    //create new vector of orderList
    std::vector<OrderPair> tempOrder;
    for (int i = 0; i < orderList.size(); i++){
        if ( orderList[i].first != id )
            tempOrder.emplace_back(orderList[i]);
    }
    orderList.clear();
    //reassign to our vector
    for (int i = 0; i < tempOrder.size(); i++)
        orderList.emplace_back(tempOrder[i]);

    //create new vector of customersList
    std::vector<Customer*> tempCustomer;
    for (int i = 0; i < customersList.size(); i++)
        tempCustomer.emplace_back(customersList[i]);

    customersList.clear();
    //reassign to our vector
    for (int i = 0; i < tempCustomer.size(); i++)
        customersList.emplace_back(tempCustomer[i]);
}

Customer *Trainer::getCustomer(int id) {
    std::vector<Customer*>::iterator itr;
    for (itr = customersList.begin(); itr < customersList.end(); itr++){
        if ((*itr)->getId() == id)
            return *itr;
    }
    return nullptr;
}

std::vector<Customer *> &Trainer::getCustomers() { return customersList; }

std::vector<OrderPair> &Trainer::getOrders() { return orderList; }

void Trainer::addOrder (const OrderPair& pair) {
    orderList.emplace_back(pair);
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int i = 0; i < workout_ids.size(); i++)
        orderList.emplace_back(customer_id, workout_options[workout_ids[i]]);
}

void Trainer::openTrainer(){ open = true; }

void Trainer::closeTrainer(){
    open = false;
    updateSalary();
    //removing the customers
    for (int i = 0; i < customersList.size(); i++) {
        delete customersList[i];
        customersList[i] = nullptr;
    }
    //clear orderList and customersList
    orderList.clear();
    customersList.clear();
//    customersList.erase(customersList.begin(), customersList.end());

}

int Trainer::getSalary() { return salary; }

void Trainer::updateSalary() {
    for (OrderPair pair : orderList)
        salary += pair.second.getPrice();
}

bool Trainer::isOpen() const{ return open; }

int Trainer::availableCapacity() { return capacity - customersList.size(); }





