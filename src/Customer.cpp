//
// Created by spl211 on 13/11/2021.
//

#include "../include/Customer.h"
#include <bits/stdc++.h>

#include <utility>

Customer::Customer(std::string c_name, int c_id): name(std::move(c_name)),  id(c_id){}

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

std::string SweatyCustomer::toString() const {
    return getName() + ",swt";
}

Customer * SweatyCustomer::clone() {
    return new SweatyCustomer(this->getName(), this->getId());
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

std::string CheapCustomer::toString() const {
    return getName() +",chp";
}

Customer *CheapCustomer::clone() {
    return new CheapCustomer(this->getName(), this->getId());
}


HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    std::vector<int> workoutOrder;
    //if it is an ANAEROBIC type of workout save the location of the workout
    for (int i = 0; i < workout_options.size(); i++){
        if (workout_options[i].getType() == ANAEROBIC){
            workoutOrder.emplace_back(i);
        }
    }
    //stable sorting
    for (int i = 0; i < workoutOrder.size(); ++i) {
        for (int j = i + 1; j < workoutOrder.size(); ++j) {
            if(workout_options[workoutOrder[i]].getPrice() < workout_options[workoutOrder[j]].getPrice()) {
                int temp = workoutOrder[i];
                workoutOrder[i] = workoutOrder[j];
                workoutOrder[j] = temp;
            }
        }
    }
    return workoutOrder;
}

std::string HeavyMuscleCustomer::toString() const {
    return getName() + ",mcl";
}

Customer *HeavyMuscleCustomer::clone() {
    return new HeavyMuscleCustomer(this->getName(), this->getId());
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

std::string FullBodyCustomer::toString() const {
    return getName() + ",fbd";
}

Customer *FullBodyCustomer::clone() {
    return new FullBodyCustomer(this->getName(), this->getId());
}
