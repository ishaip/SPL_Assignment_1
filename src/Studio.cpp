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


void Studio :: makeTrainer(int numOfTrainers, int *spotArray ){
    _numOfTrainers = numOfTrainers;
    for(int i = 0; i < numOfTrainers; i++){

    }
}

int Studio::getNumOfTrainers() const {
    return _numOfTrainers;
}

Trainer *Studio::getTrainer(int tid) {
    if (trainers.size() > tid && tid >= 0){ //vector size isn't big enough prevents an error
        return trainers[tid];
    }
    return nullptr;
}

