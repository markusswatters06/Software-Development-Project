#ifndef WORKOUTEXERCISE_H
#define WORKOUTEXERCISE_H

#include "WorkoutPlan.h"
#include "Exercise.h"

using namespace std;

// This class demonstrates aggregation between WorkoutPlan and Exercise
class WorkoutExercise {
private:
    WorkoutPlan* workoutPlan;
    Exercise* exercise;
    int sets;
    int reps;
    int restTime; // in seconds

public:
    // Constructor
    WorkoutExercise();
    WorkoutExercise(WorkoutPlan* plan, Exercise* ex, int sets, int reps, int restTime);
    
    // Getter methods
    WorkoutPlan* getWorkoutPlan() const;
    Exercise* getExercise() const;
    int getSets() const;
    int getReps() const;
    int getRestTime() const;
    
    // Setter methods
    void setWorkoutPlan(WorkoutPlan* plan);
    void setExercise(Exercise* ex);
    void setSets(int sets);
    void setReps(int reps);
    void setRestTime(int restTime);
    
    // Display method
    void display() const;
};

#endif