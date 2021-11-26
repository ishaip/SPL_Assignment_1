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
//    buffer << file.rdbuf(); //??
    int trainerCount = 0;
    int numOfTrainers;
    int workoutIds = 0;
    std::string line;
    int index = 0;

    while (std::getline(file, line)){
        //the conditions we wish to skip
        if ( line[0] == '#' || line[0] == '\0' )
            continue;
        else if ( index == 0 ) { //reading the number of trainers in the studio
            numOfTrainers = std::stoi(line);
        }
        else if ( index == 1 ){ //reading the respective spots of the trainers
            int start = 0;
            while ( line[start] != '\n' && trainerCount < numOfTrainers){
                int end;
                end = line.find(",", start);
                std::string str = line.substr(start, end - start);
                int spot = stoi(str);
                makeTrainer(trainerCount, &spot);
                trainerCount ++;
                start = end + 1;
            }
        }
        else{
            makeWorkout(line, workoutIds);
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
    workout_options.emplace_back(Workout(id, workoutName, price, type));
}

//destructor
Studio::~Studio() {
    for (int i=0; i< trainers.size();i++)
        delete trainers[i];
    for (int i =0; i< actionsLog.size(); i++)
        delete actionsLog[i];

    actionsLog.clear();
    workout_options.clear();
    trainers.clear();
}

//copy constructor
Studio:: Studio(const Studio& other):
        open(other.open), nextCustomerId(other.nextCustomerId){
    for (int i = 0; i < static_cast<int>(other.workout_options.size()); ++i) {
        workout_options.emplace_back(other.workout_options[i].clone());
    }
    for (Trainer* t : other.trainers){
        Trainer* trainer = new Trainer(*t);
        trainers.emplace_back(trainer);
    }
    for (int i = 0; i < static_cast<int>(other.actionsLog.size()); i++)
        actionsLog.emplace_back(other.actionsLog[i]->clone());
}

//copy assignment operator
Studio &Studio::operator=(Studio &other){
    //check for self assignment
    if ( this == &other)
        return *this;

    //freeing the pointers
    for (int i = 0; i < static_cast<int>(trainers.size()); i++) //TODO: check casting necessity
        delete trainers[i];
    for (int i = 0; i < static_cast<int>(actionsLog.size()); i++)
        delete actionsLog[i];

    trainers.clear();
    actionsLog.clear();
    workout_options.clear();

    //duplicate the resources
    for (int i = 0; i < static_cast<int>(other.trainers.size()); i++){
        Trainer* trainer = new Trainer(*other.trainers[i]);
        trainers.emplace_back(trainer);
    }
    actionsLog.clear();
    for (int i = 0; i < static_cast<int>(other.actionsLog.size()); i++)
        actionsLog.emplace_back(other.actionsLog[i]->clone());

    //copy the rest of the data
    workout_options.clear();
    for(int i = 0; i < static_cast<int>(other.workout_options.size()); i++){
        workout_options.emplace_back(other.workout_options[i].clone());
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
    trainers = std::vector<Trainer*>{};
    actionsLog = std::vector<BaseAction*>{};
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
    for (int i = 0; i < static_cast<int>(other.trainers.size()); i++){
        Trainer* t = new Trainer(*other.trainers[i]);
        trainers.emplace_back(t);
    }

    workout_options.clear();
    for(Workout workout : other.workout_options){
        workout_options.emplace_back(workout);
    }
    other.workout_options.clear();
    for (BaseAction* action : other.actionsLog)
        actionsLog.emplace_back(action);

    //detach other's resources
    trainers = std::vector<Trainer*>{};
    actionsLog = std::vector<BaseAction*>{};

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
    if ( tid >= 0 && tid < static_cast<int>(trainers.size()) )
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
