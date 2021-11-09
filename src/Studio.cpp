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


void Studio :: makeTranier(int trainerCount, int *spotArray ){
    numOfTrainers = trainerCount;
    for(int i = 0; i < trainerCount; i++){

    }
}

int Studio::getNumOfTrainers() const {
    return numOfTrainers;
}

Trainer *Studio::getTrainer(int tid) {
    return trainers[tid];
}

