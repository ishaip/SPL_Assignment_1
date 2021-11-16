#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>
#include <vector>

enum WorkoutType{
    ANAEROBIC, MIXED, CARDIO, ALL
};

class Workout{
public:
    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    WorkoutType getType() const;

    static bool comparePrice(const Workout &w1, const Workout &w2); // compare two workouts by price
    static bool compareID(const Workout &w1, const Workout &w2); // compare two workouts by id

    virtual ~Workout(); //destructor
private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};


#endif