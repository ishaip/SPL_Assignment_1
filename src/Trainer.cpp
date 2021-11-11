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
}

bool Trainer::isOpen() {
    return open;
}

int Trainer::availableCapacity() {
    return capacity - customersList.size();
}

Trainer::Trainer(int t_capacity):
        capacity (t_capacity),open (false),customersList (0),orderList(0){}

Trainer:: ~Trainer() {
    if (!customersList.empty()){ delete customersList;}
    if (!orderList.empty()) { delete orderList; }


}



