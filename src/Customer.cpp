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

int Customer::selectOrder(const std::vector<Workout> &workout_options, WorkoutType workoutType, bool lookingForCheap) {
    int index=-1;
    if (!workout_options.empty() ) {
        for (int i = 0; i < workout_options.size(); i++) {
            if (workout_options[i].getType() == workoutType || workoutType == ALL) {
                if (index == -1)
                    //first time wanted workout appears
                    index = i;
                //using a compare function to choose the cheapest if that is what we are looking for
                if (Workout::comparePrice(workout_options[i], workout_options[index]) && lookingForCheap) {
                    index = i;
                }
                //using a compare function to choose the most expensive if that is what we are looking for
                if (!Workout::comparePrice(workout_options[i], workout_options[index]) && !lookingForCheap) {
                    index = i;
                }
                //if prices are the same chose the smallest id
                if (Workout::compareId(workout_options[i], workout_options[index]) &&
                    workout_options[i].getPrice() == workout_options[index].getPrice())
                    index = i;
            }
        }
    }
    return index;
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
    //we don't care about the workout type, so we added the enum ALL and we are looking for the cheapest workout
    int cheapest = selectOrder(workout_options, ALL, true);
    if (cheapest != -1)
        workoutOrder.emplace_back(cheapest);
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
    //we wrote a comprator that compares prices
    return workoutOrder;
}


FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    int index = selectOrder(workout_options, CARDIO, true);
    if (index != -1)
        workoutOrder.emplace_back(index);
    index = selectOrder(workout_options, MIXED, false);
    if (index != -1)
        workoutOrder.emplace_back(index);
    index = selectOrder(workout_options, ANAEROBIC, true);
    if (index != -1)
        workoutOrder.emplace_back(index);
    return workoutOrder;
}