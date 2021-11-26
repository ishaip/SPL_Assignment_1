#ifndef WORKOUT_H_
#define WORKOUT_H_

#include <string>

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
    static bool comparePrice (const Workout& thisWorkout, const Workout& otherWorkout);
    static bool compareId(const Workout &thisWorkout, const Workout &otherWorkout);
    std::string toString();
    std::string typeToString();
    virtual ~Workout(); //destructor
    Workout(const Workout &w);
    virtual Workout *clone();
private:
	const int id;
    const std::string name;
    const int price;
    const WorkoutType type;
};


#endif