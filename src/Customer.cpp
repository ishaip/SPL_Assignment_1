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

int Customer::selectOrder(const std::vector<Workout> &workout_options, WorkoutType workoutType, bool lookingForCheap) {
    if ( workout_options.empty() )
        return -1;

    int index = -1;

    for (int i = 0; i < workout_options.size(); i++){
        //first time wanted workout appeared
        if ( index == -1 && workoutType == workout_options[i].getType() )
            index = i;
        //checking the current workout type in 'workout_options', if 'workoutType' is ALL we go into as well
        if ( workout_options[i].getType() == workoutType || workoutType == ALL ){
            //if we want the cheapest workout
            if (lookingForCheap && Workout::comparePrice(workout_options[i], workout_options[index]) )
                index = i;
            //if we want the most expensive workout
            else if (!lookingForCheap && !Workout::comparePrice(workout_options[i], workout_options[index]) )
                index = i;
            //if the current workout has same price, we want to take the one with the lowest id
            else if ( workout_options[i].getPrice() == workout_options[index].getPrice() && Workout::compareID(workout_options[i], workout_options[index]))
                index = i;
        }
    }

    return index;
}

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
    int index = selectOrder(workout_options, ALL, true);
    if ( index >= 0 )
        return std::vector<int> {index};
    return std::vector<int> {};
};

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;

    for (int i = 0; i < workout_options.size(); i++){
        // adding to 'workoutOrder' all the workouts options which are ANAEROBIC
        if (workout_options[i].getType() == ANAEROBIC){
            workoutOrder.emplace_back(i);
        }
    }
    std::sort(workoutOrder.begin(), workoutOrder.end(), Workout::comparePrice);
    return workoutOrder;
};

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    int index = selectOrder(workout_options, CARDIO, true);
    if ( index != -1 )
        workoutOrder.emplace_back(index);
    index = selectOrder(workout_options, MIXED, false);
    if ( index != -1 )
        workoutOrder.emplace_back(index);
    index = selectOrder(workout_options, ANAEROBIC, true);
    if ( index != -1 )
        workoutOrder.emplace_back(index);
    return workoutOrder;
}



