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

void displayGoalList(const vector<Goal*>& goals) {
    if (goals.empty()) {
        cout << "\nNo goals yet. Add one first!\n";
        return;
    }
    cout << "\n=== YOUR GOALS ===\n";
    for (size_t i = 0; i < goals.size(); ++i) {
        cout << i+1 << ". " << goals[i]->getSummary() << "\n";
    }
    cout << "==================\n";
}

// Helper to get a valid integer from the user
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main()
{
    // Goal Classes
    vector<Goal*> goals;
    int choice;
    bool running = true;

    while (running) {
        cout << "\n=== FITNESS GOAL TRACKER ===\n";
        cout << "1. Add New Goal\n";
        cout << "2. View All Goals\n";
        cout << "3. Manage a Goal\n";
        cout << "4. Delete a Goal\n";
        cout << "0. Exit\n";
        
        choice = getValidInt("Enter choice: ");

        switch (choice) {
            case 1: {
                int type;
                cout << "\nSelect goal type:\n";
                cout << "1. Strength\n2. Cardio\n3. Weight Loss\n";
                type = getValidInt("Choice: ");

                Goal* newGoal = nullptr;
                if (type == 1)
                    newGoal = new Goal();
                else if (type == 2)
                    newGoal = new Cardio();
                else if (type == 3)
                    newGoal = new WeightLoss();
                else {
                    cout << "Invalid type. Please choose 1, 2, or 3.\n";
                    break;
                }

                newGoal->addGoal();
                goals.push_back(newGoal);
                cout << "Goal added!\n";
                break;
            }

            case 2:
                displayGoalList(goals);
                break;

            case 3: {
                if (goals.empty()) {
                    cout << "No goals to manage.\n";
                    break;
                }
                displayGoalList(goals);
                int idx = getValidInt("Enter goal number to manage: ");
                if (idx < 1 || idx > (int)goals.size()) {
                    cout << "Invalid number. Must be between 1 and " << goals.size() << ".\n";
                    break;
                }
                goals[idx - 1]->displayGoal();
                break;
            }

            case 4: {
                if (goals.empty()) {
                    cout << "No goals to delete.\n";
                    break;
                }
                displayGoalList(goals);
                int idx = getValidInt("Enter goal number to delete: ");
                if (idx < 1 || idx > (int)goals.size()) {
                    cout << "Invalid number. Must be between 1 and " << goals.size() << ".\n";
                    break;
                }
                delete goals[idx - 1];
                goals.erase(goals.begin() + (idx - 1));
                cout << "Goal deleted.\n";
                break;
            }

            case 0:
                running = false;
                break;

            default:
                cout << "Invalid choice. Please enter a number from 0 to 4.\n";
        }
    }

    // Clean up all remaining goals
    for (size_t i = 0; i < goals.size(); ++i)
        delete goals[i];

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
