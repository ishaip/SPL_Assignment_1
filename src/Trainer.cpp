//
// Created by spl211 on 09/11/2021.
//

#include "../include/Trainer.h"
#include <vector>

Trainer::Trainer(int t_capacity):
    capacity(t_capacity), open(false), customersList(0), orderList(0){}
    ~virtual Trainer(){
        if(customerList) delete[] customerList;
        if(orderList) delete[] orderList;
}
;

int Trainer::getCapacity() const{ return capacity; }

bool Trainer::isOpen(){ return open; }

void Trainer::openTrainer(){ open = true; }

void Trainer::closeTrainer(){ open = false; }