#include "Exercise.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructors
Exercise::Exercise() : exercise(""), name(""), muscleGroup(""), equipment(""), ratingsPtr(nullptr) {}

Exercise::Exercise(string exercise, string name, string muscleGroup, string equipment)
    : exercise(exercise), name(name), muscleGroup(muscleGroup), equipment(equipment), ratingsPtr(nullptr) {}

// Deep copy constructor
Exercise::Exercise(const Exercise& other)
    : exercise(other.exercise), name(other.name),
      muscleGroup(other.muscleGroup), equipment(other.equipment) {
    if (other.ratingsPtr != nullptr) {
        ratingsPtr = new int;
        *ratingsPtr = *(other.ratingsPtr);
    } else {
        ratingsPtr = nullptr;
    }
}

// Deep copy assignment operator
Exercise& Exercise::operator=(const Exercise& other) {
    if (this != &other) {
        // Free existing memory
        delete ratingsPtr;
        
        // Copy primitive members
        exercise = other.exercise;
        name = other.name;
        muscleGroup = other.muscleGroup;
        equipment = other.equipment;
        
        // Deep copy pointer member
        if (other.ratingsPtr != nullptr) {
            ratingsPtr = new int;
            *ratingsPtr = *(other.ratingsPtr);
        } else {
            ratingsPtr = nullptr;
        }
    }
    return *this;
}

// Destructor
Exercise::~Exercise() {
    delete ratingsPtr;
    ratingsPtr = nullptr;
}

// Getter methods
string Exercise::getExercise() const { return exercise; }
string Exercise::getName() const { return name; }
string Exercise::getMuscleGroup() const { return muscleGroup; }
string Exercise::getEquipment() const { return equipment; }

int Exercise::getRating() const {
    if (ratingsPtr != nullptr) {
        return *ratingsPtr;
    }
    return 0;
}

// Setter methods
void Exercise::setExercise(string exercise) { this->exercise = exercise; }
void Exercise::setName(string name) { this->name = name; }
void Exercise::setMuscleGroup(string muscleGroup) { this->muscleGroup = muscleGroup; }
void Exercise::setEquipment(string equipment) { this->equipment = equipment; }


void Exercise::setRating(int rating) {
    if (ratingsPtr == nullptr) {
        ratingsPtr = new int;
    }
    *ratingsPtr = rating;
}

// Exercise specific methods
void Exercise::getInstructions() const {
    cout << "Instructions for " << name << endl;
}

void Exercise::getMuscleGroups() const {
    cout << "Muscle group: " << muscleGroup << endl;
}

// Operator overloading for comparison
bool Exercise::operator==(const Exercise& other) const {
    return (exercise == other.exercise && name == other.name);
}

bool Exercise::operator!=(const Exercise& other) const {
    return !(*this == other);
}

bool Exercise::operator<(const Exercise& other) const {
    return (name < other.name);
}

// Friend function for output operator
ostream& operator<<(ostream& out, const Exercise& ex) {
    out << ex.name << " (Muscle Group: " << ex.muscleGroup << ", Equipment: " << ex.equipment << ")";
    return out;
}

// Display
void Exercise::displayAllExercise()
{
    clearScreen();
    line();
    cout << "          EXERCISE DETAILS" << endl;
    line();
    cout  << name << endl;
    line();
    cout << "Muscle Group: " << muscleGroup << endl;
    cout << "Equipment:    " << equipment << endl;
    line();
}

// UI
void Exercise::clearScreen() 
{ 
    for(int i = 0; i < 40; i++) 
    cout << endl; 
}

void Exercise::line() 
{ 
    cout << "========================================\n"; 
}

void Exercise::title(string t) 
{ 
    line(); 
    cout << "          " << t << endl; 
    line(); 
}
