//
// Created by spl211 on 09/11/2021.
//

#include "../include/Trainer.h"
#include <vector>

Trainer::Trainer(int t_capacity):
    capacity(t_capacity), open(false), customersList(0), orderList(0), salary(0){}

    Trainer::~Trainer(){
        for (int i = 0; i < customersList.size(); i++){
            delete &customersList[i];
            customersList[i] = nullptr;
        }
        customersList.clear(); // important?
        for (int i = 0; i < orderList.size(); i++){
            delete orderList[i]; //
        }
        orderList.clear();
    }
;

int Trainer::getCapacity() const{ return capacity; }

void Trainer::addCustomer(Customer *customer) {
    customersList.emplace_back(customer);
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
    for (int i = 0; i < workout_ids.size(); i++)
        orderList.emplace_back(customer_id, workout_options[i]);
}

void Trainer::openTrainer(){ open = true; }

void Trainer::closeTrainer(){ open = false; }

int Trainer::getSalary() { return salary; }

void Trainer::setSalary(int salary) { this->salary = salary; }

bool Trainer::isOpen(){ return open; }

std::vector<Customer *> &Trainer::getCustomers() { return customersList; }





