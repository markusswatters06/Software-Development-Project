#include "WorkoutExercise.h"
#include <iostream>

using namespace std;

WorkoutExercise::WorkoutExercise() : workoutPlan(nullptr), exercise(nullptr), sets(0), reps(0), restTime(0) {
    
}

WorkoutExercise::WorkoutExercise(WorkoutPlan* plan, Exercise* ex, int sets, int reps, int restTime) : workoutPlan(plan), exercise(ex), sets(sets), reps(reps), restTime(restTime) {}

WorkoutPlan* WorkoutExercise::getWorkoutPlan() const { return workoutPlan; }
Exercise* WorkoutExercise::getExercise() const { return exercise; }
int WorkoutExercise::getSets() const { return sets; }
int WorkoutExercise::getReps() const { return reps; }
int WorkoutExercise::getRestTime() const { return restTime; }

void WorkoutExercise::setWorkoutPlan(WorkoutPlan* plan) { workoutPlan = plan; }
void WorkoutExercise::setExercise(Exercise* ex) { exercise = ex; }
void WorkoutExercise::setSets(int sets) { this->sets = sets; }
void WorkoutExercise::setReps(int reps) { this->reps = reps; }
void WorkoutExercise::setRestTime(int restTime) { this->restTime = restTime; }

void WorkoutExercise::display() const {
    cout << "Workout: " << workoutPlan->getName() << endl;
    cout << "-Exercise: " << exercise->getName() << " (" << sets << " sets x " << reps << " reps, " << restTime << "s rest)" << endl;
}