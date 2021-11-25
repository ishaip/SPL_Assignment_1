//
// Created by spl211 on 09/11/2021.
//

#include <vector>
#include <string>
#include "../include/Studio.h"
#include "../include/Workout.h"

#include <fstream>
#include <sstream>

Studio::Studio():
        open(false), nextCustomerId(0), trainers({}),
        workout_options({}), actionsLog({}){
};

Studio::Studio(const std::string &configFilePath):
        open(false), nextCustomerId(0){

    //reading the running file
    std::ifstream file;
    file.open(configFilePath);
    std::stringstream buffer;
//reinterpret_cast<const char *>(&configFilePath)
    buffer << file.rdbuf();
    int trainerCount = 0;
    int numOfTrainers;
    int workoutIds = 0;
    char line[256]; //should be a pointer??
    int index = 0;

    while (file.is_open()){
        file.getline(line, 256);
        if ( line[0] == '#' || line[0] == '\0' )
            continue;
        else if ( index == 0 ) //reading the number of trainers in the studio
            numOfTrainers = static_cast<int>(line[0]);
        else if ( index == 1 ){ //reading the respective spots of the trainers
            int i = 0;
            while ( line[i] != '\n' && trainerCount < numOfTrainers){
                if ( line[i] == ',' )
                    i ++;
                else{
                    int spot = static_cast<int>(line[index]);
                    makeTrainer(trainerCount, &spot);
                    trainerCount ++;
                    i ++;
                }
            }
        }
        else{
            int i = 0;
            std::string workout;
            while ( line[i] != '\n' ){
                workout.append(reinterpret_cast<const char *>(line[i]));
            }
            makeWorkout(workout, workoutIds);
            workoutIds ++;
        }
        index ++;
    }
    file.close();
    std::cout << buffer.str() << std::endl;
};

void Studio:: makeTrainer(int trainerCount, const int *spots){
    Trainer* newTrainer;
    newTrainer = new Trainer(*spots);
    trainers.emplace_back(newTrainer);
}

void Studio:: makeWorkout(std::string workout, int id){
    int start = 0;
    int end;
    end = workout.find(", ");

    std::string workoutName = workout.substr(start, end - start);
    start = end + 2;
    end = workout.find(", ", start);
    std::string workoutType = workout.substr(start, end - start);
    start = end + 2;
    std::string workoutPrice = workout.substr(start);
    int price = stoi(workoutPrice);

    WorkoutType type;
    if ( workoutType == "Anaerobic" )
        type = ANAEROBIC;
    else if ( workoutType == "Mixed" )
        type = MIXED;
    else if ( workoutType == "Cardio" )
        type = CARDIO;
    else
        type = ALL;
    Workout *newWorkout;
    newWorkout = new Workout(id, workoutName, price, type);
    workout_options.emplace_back(*newWorkout);
}

//destructor
Studio::~Studio() {
    for (Trainer* trainer : trainers){
        delete &trainer;
        trainer = nullptr;
    }
    workout_options.clear();
   // workout_options.erase(workout_options.begin(), workout_options.end());

    for (BaseAction* a : actionsLog){
        delete &a;
        a = nullptr;
    }
}

//copy constructor
Studio:: Studio(const Studio& other):
        open(other.open), nextCustomerId(other.nextCustomerId),workout_options(other.workout_options){
    for (Trainer* t : other.trainers){
        Trainer* trainer = new Trainer(*t);
        trainers.emplace_back(trainer);
    }

    for (BaseAction* action : other.actionsLog)
        actionsLog.emplace_back(action);
};

//copy assignment operator
Studio &Studio::operator=(Studio &other){
    //check for self assignment
    if ( this == &other)
        return *this;
    //freeing the pointers
    for (Trainer* t : trainers) {
        delete &t;
        t= nullptr;

    }
    for (BaseAction* a : actionsLog) {
        delete &a;
        a = nullptr;
    }

    //duplicate the resources
    for (Trainer* t : other.trainers){
        Trainer* trainer = new Trainer(*t);
        trainers.emplace_back(trainer);
    }
    for (BaseAction* action : other.actionsLog)
        actionsLog.emplace_back(action);

    //copy the rest of the data
    workout_options.clear();
    for(Workout workout : other.workout_options){
        workout_options.emplace_back(workout);
    }
    open = other.open;
    nextCustomerId = other.nextCustomerId;

    return *this;
}

//move constructor
Studio::Studio(Studio&& other) noexcept :
//taking other's arguments
        open(other.open), nextCustomerId(other.nextCustomerId),
        trainers(other.trainers),
        workout_options(other.workout_options),
        actionsLog(other.actionsLog){

    //destroying other's pointers
    //other.trainers = {};
    for (Trainer* t : other.trainers)
        t = nullptr;
    for (BaseAction* a : other.actionsLog)
        a = nullptr;
};

//move assignment operator
Studio &Studio::operator=(Studio &&other) noexcept {
    //check for self assignment
    if ( this == &other)
        return *this;

    //freeing the pointers
    for (Trainer* t : trainers)
        delete &t;
    for (BaseAction* a : actionsLog)
        delete &a;
    //workout_options.clear(); //important??

    //assigning
    for (Trainer* t : other.trainers){
        Trainer* trainer = new Trainer(*t);
        trainers.emplace_back(trainer);
    }
    workout_options.clear();
    for(Workout workout : other.workout_options){
        workout_options.emplace_back(workout);
    }
    other.workout_options.clear();
    for (BaseAction* action : other.actionsLog)
        actionsLog.emplace_back(action);

    //detach other's resources
    for (Trainer* t : other.trainers)
        t = nullptr;
    for (BaseAction* a : other.actionsLog)
        a = nullptr;

    return *this;
}

void Studio::start() {
    std::cout << "Studio is now open!" << std:: endl;
    open = true;
}

int Studio::getNumOfTrainers() const{
    return static_cast<int>(trainers.size());
}

Trainer *Studio::getTrainer(int tid) {
    if (tid >= 0 && tid < trainers.size())
        return trainers[tid];
    return nullptr;
}

std::vector<Workout> &Studio::getWorkoutOptions() { return workout_options; }

const std::vector<BaseAction *> &Studio::getActionsLog() const { return actionsLog; }

void Studio::addAction(BaseAction* action) {
    actionsLog.emplace_back(action);
}

int Studio::getNextCustomerId() {
    int output = nextCustomerId;
    nextCustomerId ++;
    return output;
}
