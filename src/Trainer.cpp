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
    for (Customer *customer: customersList){
        delete &customer;
        customer = nullptr;
    }
    customersList.erase(customersList.begin(),customersList.end());
    orderList.clear();
    //orderList.erase(orderList.begin(), orderList.end());
}

Trainer::Trainer(const Trainer &trainer):
    capacity(trainer.capacity), open(trainer.open),salary(trainer.salary){
    for (Customer * customer : trainer.customersList) {
        this->customersList.emplace_back(customer->clone());
    }
    for (OrderPair orderPair : trainer.orderList) {
        this->orderList.emplace_back(orderPair);
    }
}

//copy assignment operator
Trainer &Trainer::operator=(const Trainer &other) {
    if (this == &other)
        return *this;
    for (Customer * customer : customersList) {
        if (customer != nullptr){
            delete &customer;
            customer = nullptr;
        }
    }
    for (OrderPair orderPair  : orderList) {
        delete & orderPair;
    }
    orderList.clear();
    //orderList.erase(orderList.begin(),orderList.end());
    customersList.erase(customersList.begin(),customersList.end());
    for (OrderPair orderPair  : other.orderList) {
        orderList.emplace_back(orderPair);
    }
    for (Customer * customer : other.customersList) {
        customersList.emplace_back(customer->clone());
    }
    capacity = other.capacity;
    open = other.open;
    salary = other.salary;
}

int Trainer::getCapacity() const{ return capacity; }

void Trainer::addCustomer(Customer *customer) {
    customersList.emplace_back(customer);
}

void Trainer::removeCustomer(int id) { //TODO: check when compiling
    //removing the orders of the customer
    std::vector<OrderPair>::iterator itr;
    for (itr = orderList.begin(); itr < orderList.end(); itr++){
        if (itr->first == id)
            delete &itr;
            //orderList.erase(itr);
    }
    //removing the customer from the list
    std::vector<Customer*>::iterator cItr;
    for (cItr = customersList.begin(); cItr < customersList.end(); cItr++){
        if ((*cItr)->getId() == id)
            customersList.erase(cItr);
    }
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
        orderList.emplace_back(customer_id, workout_options[i]);
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
    //orderList.erase(orderList.begin(), orderList.end());
    //customersList.erase(customersList.begin(), customersList.end());
}

int Trainer::getSalary() { return salary; }

void Trainer::updateSalary() {
    for (OrderPair pair : orderList)
        salary += pair.second.getPrice();
}

bool Trainer::isOpen() const{ return open; }

int Trainer::availableCapacity() { return capacity - customersList.size(); }





