//
// Created by spl211 on 09/11/2021.
//

#include <vector>
#include <string>
#include "../include/Studio.h"

void start() {
    std::cout << "Studio is now open!" << std:: endl;
    std::string x = "";
    while ( x != "closeall" ){
        std::cin >> x;
        if (x.substr(0,4) == "open"){

        }
    }

}

// gets number of trainer to init and a pointer to an array of spots for each trainer
// update the number of trainers in the studio
void Studio:: makeTrainer(int trainerCount, int *spots){
    _numOfTrainers = trainerCount;
    std::vector<Trainer*> trainers;
    for (int i = 0; i < trainerCount; i++){

    }

}

int Studio::getNumOfTrainers() const{
    return (int) trainers.size(); // TODO: fix the casting
}

Trainer *Studio::getTrainer(int tid) {
    if (tid >= 0 && tid < trainers.size())
        return trainers[tid];
    return nullptr;
}

std::vector<Workout> &Studio::getWorkoutOptions() { return workout_options; }


