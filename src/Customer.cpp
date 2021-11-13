//
// Created by spl211 on 13/11/2021.
//

#include "../include/Customer.h"
#include <bits/stdc++.h>

Customer::Customer(std::string c_name, int c_id): name(c_name),  id(c_id){}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    //if it is a CARDIO type of workout save the location of the workout
    for (int i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == CARDIO){
            workoutOrder.emplace_back(i);
        }
    }
    return workoutOrder;
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    if (!workout_options.empty() ){
        int j=0;
        for (int i = 1; i < workout_options.size(); i++){
            //chose the cheapest
            if (workout_options[j].getPrice() > workout_options[i].getPrice()){
                j=i;
            }
            // if there are two with the same price chose the one with the smallest id
            else if (workout_options[j].getPrice() == workout_options[i].getPrice() && workout_options[j].getId() < workout_options[i].getId() ){
                j=i;
            }
        }
        workoutOrder.emplace_back(j);
    }
    return workoutOrder;
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    //if it is a ANAEROBIC type of workout save the location of the workout
    for (int i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == ANAEROBIC){
            workoutOrder.emplace_back(i);
        }
    }
    std::sort(workoutOrder.begin(),workoutOrder.end(),Workout::comparePrice());

    return workoutOrder;
}
