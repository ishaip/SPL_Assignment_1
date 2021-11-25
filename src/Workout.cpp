//
// Created by spl211 on 13/11/2021.
//

#include "../include/Workout.h"

//constructor
Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
id(w_id), name(w_name),price(w_price), type(w_type){};

//destructor
Workout::~Workout() = default;

//copy constructor
Workout::Workout(const Workout &w): //TODO: check
    id(w.id), name(w.name),price(w.price), type(w.type){}{};

int Workout::getId() const {
    return id;
}

std::string Workout::getName() const {
    return name;
}

int Workout::getPrice() const {
    return price;
}

WorkoutType Workout::getType() const {
    return type;
}

bool Workout::comparePrice(const Workout &thisWorkout, const Workout &otherWorkout) {
    return thisWorkout.getPrice() < otherWorkout.getPrice();
}

bool Workout::compareId(const Workout &thisWorkout, const Workout &otherWorkout) {
    return thisWorkout.getId() < otherWorkout.getId();
}

std::string Workout::toString() {
    return name + ", " +typeToString()+", " + std::to_string(price) ;
}

std::string Workout::typeToString() {
    if (type == ANAEROBIC)
        return  "ANAEROBIC";
    if (type == MIXED)
        return "MIXED";
    if (type == CARDIO)
        return "CARDIO";
    return "ALL";
}





