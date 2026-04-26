#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
#include <vector>
#include "Exercise.h"

using namespace std;

class WorkoutPlan {
private:
    static int nextPlanId;
    int id;
    string plan;
    string name;
    string startDate;
    string endDate;
    vector<Exercise*> exercises; // 1:0..M aggregation relationship with Exercise objects

    static vector<WorkoutPlan> workoutPlanList;
    static int workoutPlanIndex(int planId);

public:
    // Constructor
    WorkoutPlan();
    WorkoutPlan(string plan, string name, string startDate, string endDate);
    
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
    
    // Setter methods
    void setPlan(string plan);
    void setName(string name);
    void setStartDate(string startDate);
    void setEndDate(string endDate);
    
    // Aggregation relationship methods
    bool addExercise(const Exercise& newExercise);
    bool removeExercise(string exerciseName);
    Exercise* findExercise(string exerciseName);
    int getExerciseCount() const;
    void displayAllExercises() const;
    
    // WorkoutPlan specific methods
    void addPlan(const WorkoutPlan& workoutPlan);
    void displayPlan() const;
    void displayPlans() const;
    void viewPlanDetails() const;
    void createPlan();
    void editPlan();
    void removePlan();
    void updatePlan();
    void getProgress() const;

    // UI
    void clearScreen() const;
    void line() const;
    void lineLong() const;
    void dashedLine() const;
    
    // Operator overloading
    bool operator==(const WorkoutPlan& other) const;
    bool operator!=(const WorkoutPlan& other) const;
    
    // Friend function for output operator
    friend ostream& operator<<(ostream& out, const WorkoutPlan& plan);
};

#endif
