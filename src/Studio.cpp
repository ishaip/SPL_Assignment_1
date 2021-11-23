//
// Created by spl211 on 09/11/2021.
//

#include "../include/Studio.h"

Studio::Studio(){}

void Studio:: start(){
    std:: cout<< "Studio is now open!\n";
    std:: string x = "";
    while(x != "closeall"){
        std:: cin >> x;
        if(x.substr(0,4) == "open"){

        }
    }
}



Trainer *Studio::getTrainer(int tid) {
    if (trainers.size() > tid && tid >= 0){ //vector size isn't big enough prevents an error
        return trainers[tid];
    }
    return nullptr;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

void Studio::addAction(BaseAction *action) {
actionsLog.emplace_back(action);
}

