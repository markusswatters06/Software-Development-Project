#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
#include <vector>
#include "Exercise.h"

using namespace std;

class WorkoutPlan {
private:
    string plan;
    string name;
    string startDate;
    string endDate;
    string goal;
    string difficulty;
    vector<Exercise*> exercises; // 1:0..M aggregation relationship with Exercise objects

public:
    // Constructor
    WorkoutPlan();
    WorkoutPlan(string plan, string name, string startDate, 
                string endDate, string goal, string difficulty);
    
    // Copy constructor (deep copy)
    WorkoutPlan(const WorkoutPlan& other);
    
    // Assignment operator (deep copy)
    WorkoutPlan& operator=(const WorkoutPlan& other);
    
    // Destructor
    ~WorkoutPlan();
    
    // Getter methods
    string getPlan() const;
    string getName() const;
    string getStartDate() const;
    string getEndDate() const;
    string getGoal() const;
    string getDifficulty() const;
    
    // Setter methods
    void setPlan(string plan);
    void setName(string name);
    void setStartDate(string startDate);
    void setEndDate(string endDate);
    void setGoal(string goal);
    void setDifficulty(string difficulty);
    
    // Aggregation relationship methods
    bool addExercise(const Exercise& newExercise);
    bool removeExercise(string exerciseName);
    Exercise* findExercise(string exerciseName);
    int getExerciseCount() const;
    void displayAllExercises() const;
    
    // WorkoutPlan specific methods
    void createPlan();
    void updatePlan();
    void getProgress() const;
    
    // Operator overloading
    bool operator==(const WorkoutPlan& other) const;
    bool operator!=(const WorkoutPlan& other) const;
    
    // Friend function for output operator
    friend ostream& operator<<(ostream& out, const WorkoutPlan& plan);
};

#endif