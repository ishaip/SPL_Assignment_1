//
// Created by spl211 on 09/11/2021.
//
#include "../include/Trainer.h"

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::openTrainer() {
    open = true;

}

void Trainer::closeTrainer() {
    open = false;
    for (int i = 0; i < customersList.size(); ++i) {
        delete customersList[i];
        customersList[i] = nullptr;
    }
    customersList.erase(customersList.begin(),customersList.end());
    orderList.erase(orderList.begin(),orderList.end());
}

bool Trainer::isOpen() {
    return open;
}

int Trainer::availableCapacity() {
    return capacity - customersList.size();
}

Trainer::Trainer(int t_capacity):
        capacity (t_capacity),open (false),customersList (0),orderList(0),salary(0){}



Trainer:: ~Trainer() {
    for (Customer *  customer : customersList) {
        delete &customer;
        customer = nullptr;
    }
    if (!orderList.empty()) {
        for (int i = 0; i < orderList.size(); ++i) {
            //delete orderList[i];
        }
    }
}

void Trainer::addCustomer(Customer *customer) {
    customersList.emplace_back(customer);
}

int Trainer::getSalary() {
    return salary;
}

void Trainer::setSalary(int salary) {
    this->salary = salary;
}

// a function to add all the orders made by a single custemer
void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int index : workout_ids) {
        orderList.emplace_back(customer_id,workout_options[index]);
    }
}

void Trainer::removeCustomer(int id) {
    std::vector<OrderPair>::iterator itr;
    for (itr = orderList.begin(); itr < orderList.end(); itr++) {
        if (itr->first == id) {
            orderList.erase(itr);
        }
    }
    std::vector<Customer*>::iterator cItr;
    for (cItr = customersList.begin(); cItr < customersList.end(); cItr++) {
        if ((*cItr)->getId() == id)
            orderList.erase(itr);
    }
}

void Trainer::addOrder(const OrderPair& orders) {
    orderList.emplace_back(orders);
}






