//
// Created by spl211 on 09/11/2021.
//

#include "../include/Trainer.h"

Trainer(int t_capacity);
int getCapacity() const;
void addCustomer(Customer* customer);
void removeCustomer(int id);
Customer* getCustomer(int id);
