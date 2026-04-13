#include "User.h"
#include "Client.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "WorkoutPlan.h"
#include "Exercise.h"
#include "WorkoutExercise.h"

using namespace std; 

int x;

int main()
{

//Testing Goal Class 
//Goal benchPR("Bench 100kg", "Strength", 100, "1st of January 2027"); 
    Goal benchPR; 
    Goal(); 
    benchPR.startingPoint();
    benchPR.setType();
    
    cin.get(); 
    benchPR.checkProgress(); 
    cin.get(); 
    benchPR.updateProgress(); 
    cin.get(); 
    benchPR.checkProgress(); 

    benchPR.updateDeadline();
    cin.get();
    benchPR.displayDetails(); 

    cout << endl;

    // Cardio sub20("Run a sub 20min 5k", "Cardio", 20, "31st of December 2026"); 
    // sub20.checkProgress(20);
    // sub20.displayDetails();

    
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
