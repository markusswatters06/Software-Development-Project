#include "User.h"
#include "Client.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "WorkoutPlan.h"
#include "Exercise.h"
#include "WorkoutExercise.h"
#include "Goal.h"
#include "Cardio.h"

using namespace std; 

int x;

int main()
{
cout << "=== FITNESS GOAL TRACKER ===\n\n";
    
    int choice;
    cout << "Select goal type:\n";
    cout << "1. Strength Goal (kg-based)\n";
    cout << "2. Cardio Goal (distance & pace-based)\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        Goal strengthGoal;
        strengthGoal.startingPoint();
        strengthGoal.setType();
        
        strengthGoal.updateProgress();
        strengthGoal.checkProgress();
        
        cout << "\n--- Updating strength progress again ---\n";
        strengthGoal.updateProgress();
        strengthGoal.checkProgress();
        
        strengthGoal.displayDetails();
    }
    else if (choice == 2) {
        Cardio cardioGoal;
        cardioGoal.startingPoint();
        
        cardioGoal.updateProgress();
        cardioGoal.checkProgress();
        
        cout << "\n--- Updating cardio progress again ---\n";
        cardioGoal.updateProgress();
        cardioGoal.checkProgress();
        
        cardioGoal.displayDetails();
    }
    else {
        cout << "Invalid choice. Exiting program.\n";
    }
    
    cout << "\nProgram completed successfully.\n";
    cin.get();
    return 0;
    
//Testing User
    cout << "---Testing User Constructor---" << endl;
    User u1(1, "name1", "user1@email.com", 891, 30 , 03, 2026, "pass1");
    u1.displayMenu();

// Testing Signup
    User s;
    s.registerAccount();
    s.displayDetails();


// Testing Login
    User l;
    cout << "\n---Testing Login---" << endl;
    l.setId(s.getId());
    l.setName(s.getName());
    l.setPhone(s.getPhone());
    l.setEmail(s.getEmail());
    l.setPassword(s.getPassword());
    l.setDobDay(s.getDobDay());
    l.setDobMonth(s.getDobMonth());
    l.setDobYear(s.getDobYear());

    int i;
    string p;
    
    cout << "\n---Testing Logging In---" << endl;
    l.logIn(i,p);
    // l.loginUser(i,p);
    cout << "\n---Test Successful---" << endl; 
    l.displayDetails();


// Testing Client
    User u4(1, "name1", "user1@email.com", 891, 30 , 03, 2026, "pass1");
    Client c1(1, "name1", "email1@email.com", 1234567890, 1, 1, 2000, "pass", 192.1, 90, "Gym", "Goal 1", 1, 4, 2026);
    c1.displayMenu();
    //c1.displayDetails();
    //c1.membershipMenu();
    //c1.progressMenu();
    //c1.workoutMenu();
    //c1.sessionMenu();

    
    cout << "=== Workout Plan System Demonstration ===" << endl;
    
    // Create exercises
    try {
        Exercise benchPress("BP001", "Bench Press", "Lie on bench and push bar upward", "Chest", "Barbell", "Intermediate");
        Exercise squat("SQ001", "Squat", "Lower body with bar on shoulders", "Legs", "Barbell", "Advanced");
        Exercise pullUp("PU001", "Pull Up", "From a hanging position, pull yourself up until chin is above bar", "Chest", "Bodyweight", "Intermediate");
        
        // Set ratings (demonstrating pointer member)
        benchPress.setRating(5);
        squat.setRating(4);
        pullUp.setRating(4);
        
        // Create workout plan
        WorkoutPlan strengthPlan("WP001", "Strength Training", "2024-01-01", "2024-03-31", "Increase strength", "Advanced");
        
        // Add exercises to plan 
        strengthPlan.addExercise(benchPress);
        strengthPlan.addExercise(squat);
        strengthPlan.addExercise(pullUp);
        
        // Display workout plan
        strengthPlan.createPlan();
        cout << "\nExercises in plan:" << endl;
        strengthPlan.displayAllExercises();

        cout << endl; 
        
        benchPress.getInstructions(); 
        squat.getInstructions(); 
        pullUp.getInstructions(); 
        
        // Demonstrate operator overloading
        cout << "\n=== Operator Overloading Demo ===" << endl;
        cout << "Workout Plan: " << strengthPlan << endl;
        
        Exercise benchPress2("BP001", "Bench Press", "Lie on bench and push bar upward", "Chest", "Barbell", "Intermediate");
        
        if (benchPress == benchPress2) {
            cout << "Bench press exercises are equal" << endl;
        }
        
        // Demonstrate STL algorithms 
        vector<Exercise> exerciseList;
        exerciseList.push_back(squat);
        exerciseList.push_back(benchPress);
        exerciseList.push_back(pullUp);
        
        sort(exerciseList.begin(), exerciseList.end());
        cout << "\nSorted exercises by name:" << endl;
        for (Exercise ex : exerciseList) {
            cout << ex << endl;
        }
        
        // Demonstrate find algorithm (requires operator==)
        auto it = find(exerciseList.begin(), exerciseList.end(), benchPress);
        if (it != exerciseList.end()) {
            cout << "\nFound: " << *it << endl;
        }
        
        // Demonstrate copy constructor (deep copy)
        WorkoutPlan copiedPlan = strengthPlan;
        cout << "\nCopied plan: " << copiedPlan << endl;
        
        // Demonstrate exception handling
        try {
            Exercise invalidEx("INV001", "", "", "", "", "");
        } catch (const invalid_argument& e) {
            cerr << "Exception caught: " << e.what() << endl;
        }
        
        // Demonstrate WorkoutExercise (aggregation between WorkoutPlan and Exercise)
        cout << "\n=== WorkoutExercise Aggregation Demo ===" << endl;
        WorkoutExercise workoutEx(&strengthPlan, &benchPress, 3, 10, 120);
        workoutEx.display();
        
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    cin.get();
    return 0; 
};
