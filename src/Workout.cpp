//
// Created by spl211 on 13/11/2021.
//

#include "../include/Workout.h"

#include <utility>


Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id), name(std::move(w_name)), price(w_price), type(w_type){};

Workout::~Workout() { // TODO: complete the destructor

}

int Workout::getId() const { return id; }

std::string Workout::getName() const { return name; }

int Workout::getPrice() const { return price; }

WorkoutType Workout::getType() const { return type; }

bool Workout::comparePrice(const Workout &w1, const Workout &w2) {
    return w1.getPrice() < w2.getPrice();
}

bool Workout::compareID(const Workout &w1, const Workout &w2) {
    return w1.getId() < w2.getId();
}










