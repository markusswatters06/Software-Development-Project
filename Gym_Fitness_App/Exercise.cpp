#include "Exercise.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructors
Exercise::Exercise() : exercise(""), name(""), description(""), muscleGroup(""), equipment(""), techDifficulty(""), ratingsPtr(nullptr) {}

Exercise::Exercise(string exercise, string name, string description, string muscleGroup, string equipment, string techDifficulty)
    : exercise(exercise), name(name), description(description), muscleGroup(muscleGroup), equipment(equipment), techDifficulty(techDifficulty), ratingsPtr(nullptr) {
    if (techDifficulty.empty()) {
        throw invalid_argument("Technical difficulty cannot be empty");
    }
}

// Deep copy constructor
Exercise::Exercise(const Exercise& other)
    : exercise(other.exercise), name(other.name), description(other.description),
      muscleGroup(other.muscleGroup), equipment(other.equipment), 
      techDifficulty(other.techDifficulty) {
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
        description = other.description;
        muscleGroup = other.muscleGroup;
        equipment = other.equipment;
        techDifficulty = other.techDifficulty;
        
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
string Exercise::getDescription() const { return description; }
string Exercise::getMuscleGroup() const { return muscleGroup; }
string Exercise::getEquipment() const { return equipment; }
string Exercise::getTechDifficulty() const { return techDifficulty; }

int Exercise::getRating() const {
    if (ratingsPtr != nullptr) {
        return *ratingsPtr;
    }
    return 0;
}

// Setter methods
void Exercise::setExercise(string exercise) { this->exercise = exercise; }
void Exercise::setName(string name) { this->name = name; }
void Exercise::setDescription(string description) { this->description = description; }
void Exercise::setMuscleGroup(string muscleGroup) { this->muscleGroup = muscleGroup; }
void Exercise::setEquipment(string equipment) { this->equipment = equipment; }

void Exercise::setTechDifficulty(string techDifficulty) {
    if (techDifficulty.empty()) {
        throw invalid_argument("Technical difficulty cannot be empty");
    }
    this->techDifficulty = techDifficulty;
}

void Exercise::setRating(int rating) {
    if (ratingsPtr == nullptr) {
        ratingsPtr = new int;
    }
    *ratingsPtr = rating;
}

// Exercise specific methods
void Exercise::getInstructions() const {
    cout << "Instructions for " << name << ": " << description << endl;
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