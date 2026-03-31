#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>

using namespace std;

class Exercise {
private:
    string exercise;
    string name;
    string description;
    string muscleGroup;
    string equipment;
    string techDifficulty;
    
    int* ratingsPtr; // Pointer to dynamically allocated memory for demonstration

public:
    // Constructors
    Exercise();
    Exercise(string exercise, string name, string description, string muscleGroup, string equipment, string techDifficulty);
    
    // Deep copy constructor
    Exercise(const Exercise& other);
    
    // Deep copy assignment operator
    Exercise& operator=(const Exercise& other);
    
    // Destructor
    ~Exercise();
    
    // Getter methods
    string getExercise() const;
    string getName() const;
    string getDescription() const;
    string getMuscleGroup() const;
    string getEquipment() const;
    string getTechDifficulty() const;
    int getRating() const;
    
    // Setter methods
    void setExercise(string exercise);
    void setName(string name);
    void setDescription(string description);
    void setMuscleGroup(string muscleGroup);
    void setEquipment(string equipment);
    void setTechDifficulty(string techDifficulty);
    void setRating(int rating);
    
    // Exercise specific methods
    void getInstructions() const;
    void getMuscleGroups() const;
    
    // Operator overloading for comparison (required for STL algorithms)
    bool operator==(const Exercise& other) const;
    bool operator!=(const Exercise& other) const;
    bool operator<(const Exercise& other) const;
    
    // Friend function for output operator
    friend ostream& operator<<(ostream& out, const Exercise& ex);
};

#endif