#include "WorkoutPlan.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Static constant for maximum exercises (if using array instead of vector)
const int MAX_EXERCISES = 50;

// Constructors
WorkoutPlan::WorkoutPlan() : plan(""), name(""), startDate(""), endDate(""), goal(""), difficulty("") {}

WorkoutPlan::WorkoutPlan(string plan, string name, string startDate, string endDate, string goal, string difficulty)
    : plan(plan), name(name), startDate(startDate), endDate(endDate), goal(goal), difficulty(difficulty) {}

// Deep copy constructor
WorkoutPlan::WorkoutPlan(const WorkoutPlan& other)
    : plan(other.plan), name(other.name), startDate(other.startDate), endDate(other.endDate), goal(other.goal), difficulty(other.difficulty) {
    // Deep copy the vector of Exercise pointers
    for (int i = 0; i < other.exercises.size(); i++) {
        exercises.push_back(new Exercise(*other.exercises[i]));
    }
}

// Deep copy assignment operator
WorkoutPlan& WorkoutPlan::operator=(const WorkoutPlan& other) {
    if (this != &other) { // Self-assignment check
        // Free existing memory
        for (int i = 0; i < exercises.size(); i++) {
            delete exercises[i];
        }
        exercises.clear();
        
        
        plan = other.plan;
        name = other.name;
        startDate = other.startDate;
        endDate = other.endDate;
        goal = other.goal;
        difficulty = other.difficulty;
        
        // Deep copy exercises
        for (int i = 0; i < other.exercises.size(); i++) {
            exercises.push_back(new Exercise(*other.exercises[i]));
        }
    }
    return *this;
}

// Destructor
WorkoutPlan::~WorkoutPlan() {
    for (int i = 0; i < exercises.size(); i++) {
        delete exercises[i];
    }
    exercises.clear();
}

// Getter methods
string WorkoutPlan::getPlan() const { return plan; }
string WorkoutPlan::getName() const { return name; }
string WorkoutPlan::getStartDate() const { return startDate; }
string WorkoutPlan::getEndDate() const { return endDate; }
string WorkoutPlan::getGoal() const { return goal; }
string WorkoutPlan::getDifficulty() const { return difficulty; }

// Setter methods
void WorkoutPlan::setPlan(string plan) { this->plan = plan; }
void WorkoutPlan::setName(string name) { this->name = name; }
void WorkoutPlan::setStartDate(string startDate) { this->startDate = startDate; }
void WorkoutPlan::setEndDate(string endDate) { this->endDate = endDate; }
void WorkoutPlan::setGoal(string goal) { this->goal = goal; }
void WorkoutPlan::setDifficulty(string difficulty) { this->difficulty = difficulty; }

// Aggregation relationship methods
bool WorkoutPlan::addExercise(const Exercise& newExercise) {
    if (exercises.size() < MAX_EXERCISES) {
        exercises.push_back(new Exercise(newExercise));
        return true;
    }
    cout << "Error: Workout plan " << name << " is full!" << endl;
    return false;
}

bool WorkoutPlan::removeExercise(string exerciseName) {
    for (int i = 0; i < exercises.size(); i++) {
        if (exercises[i]->getName() == exerciseName) {
            delete exercises[i];
            exercises.erase(exercises.begin() + i);
            return true;
        }
    }
    return false;
}

Exercise* WorkoutPlan::findExercise(string exerciseName) {
    for (int i = 0; i < exercises.size(); i++) {
        if (exercises[i]->getName() == exerciseName) {
            return exercises[i];
        }
    }
    return nullptr;
}

int WorkoutPlan::getExerciseCount() const {
    return exercises.size();
}

void WorkoutPlan::displayAllExercises() const {
    for (int i = 0; i < exercises.size(); i++) {
        cout << *exercises[i] << endl;
    }
}

// WorkoutPlan specific methods
void WorkoutPlan::createPlan() {
    cout << "Creating workout plan: " << name << endl;
    cout << "Goal: " << goal << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << "Duration: " << startDate << " to " << endDate << endl;
}

void WorkoutPlan::updatePlan() {
    cout << "Updating workout plan: " << name << endl;
}

void WorkoutPlan::getProgress() const {
    cout << "Getting progress for plan: " << name << endl;
}

// Operator overloading
bool WorkoutPlan::operator==(const WorkoutPlan& other) const {
    return (plan == other.plan && name == other.name);
}

bool WorkoutPlan::operator!=(const WorkoutPlan& other) const {
    return !(*this == other);
}

// Friend function for output operator
ostream& operator<<(ostream& out, const WorkoutPlan& plan) {
    out << "Workout Plan: " << plan.name << " (Difficulty: " << plan.difficulty << ", Goal: " << plan.goal << ")";
    return out;
}