//
// Created by spl211 on 13/11/2021.
//

#include <vector>
#include <string>
#include <algorithm>
#include "../include/Workout.h"
#include "../include/Customer.h"
#include <bits/stdc++.h>

Customer::Customer(std::string c_name, int c_id):
        name(c_name), id(c_id){};

int Customer::getId() const { return id; }

std::string Customer::getName() const { return name; }


SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id){}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
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

    if ( !workout_options.empty() ){
        int index = 0;
        for (int i = 1; i < workout_options.size(); i++){
            // updating the index of the cheaper workout
            if (workout_options[index].getPrice() > workout_options[i].getPrice())
                index = i;
            // if the workouts have the same price, we want to take the one with the smaller id
            else if (workout_options[index].getPrice() == workout_options[i].getPrice() && workout_options[index].getId() > workout_options[i].getId())
                index = i;
        }
        workoutOrder.emplace_back(index);
    }
    return workoutOrder;
};

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    for (int i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == ANAEROBIC){
            workoutOrder.emplace_back(i);
        }
    }
    std::sort(workoutOrder.begin(), workoutOrder.end(),Workout::comparePrice);
    return workoutOrder;
};






std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
}
