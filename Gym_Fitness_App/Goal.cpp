#include "Goal.h"
#include <algorithm>

Goal::Goal() : currentPR(0), days(0), months(0), years(0), timePeriod(' '), 
               percentage(0), target(0), newPR(0), improvement(0), status("Not Started")
{}

void Goal::clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double Goal::getValidPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a number.\n";
            clearInputStream();
        }
        else if (value < 0) {
            cout << "Error: Value cannot be negative.\n";
        }
        else {
            clearInputStream();
            return value;
        }
    }
}

int Goal::getValidPositiveInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a whole number.\n";
            clearInputStream();
        }
        else if (value <= 0) {
            cout << "Error: Please enter a positive number (greater than 0).\n";
        }
        else {
            clearInputStream();
            return value;
        }
    }
}

char Goal::getValidCharInput(const string& prompt, const string& validOptions) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Error: Input cannot be empty.\n";
            continue;
        }
        
        char choice = toupper(input[0]);
        
        bool valid = false;
        for (int i = 0; i < validOptions.length(); i++) {
            if (choice == validOptions[i]) {
                valid = true;
                break;
            }
        }
        
        if (valid) {
            return choice;
        } else {
            cout << "Error: Invalid option. Please enter one of: ";
            for (int i = 0; i < validOptions.length(); i++) {
                cout << validOptions[i] << " ";
            }
            cout << endl;
        }
    }
}

bool Goal::isValidExercise(const string& exercise) {
    string lowerExercise = exercise;
    for (int i = 0; i < lowerExercise.length(); i++) {
        lowerExercise[i] = tolower(lowerExercise[i]);
    }
    
    string cardioExercises[] = {"swim", "run", "cycle", "row", "walk", "hike", 
                                 "jump", "throw", "climb", "running", "swimming", 
                                 "cycling", "rowing", "walking", "hiking", "jumping", 
                                 "throwing", "climbing"};
    
    for (int i = 0; i < 18; i++) {
        if (lowerExercise == cardioExercises[i]) {
            return true;
        }
    }
    return false;
}

void Goal::startingPoint(){
    cout << "\n=== NEW STRENGTH GOAL SETUP ===\n";
    
    while (true) {
        cout << "Exercise you would like to improve upon: ";
        getline(cin, goal);
        
        if (goal.empty()) {
            cout << "Error: Exercise name cannot be empty.\n";
        }
        else {
            break;
        }
    }
    
    currentPR = getValidPositiveDouble("Current personal best [kg]: ");
    
    while (true) {
        target = getValidPositiveDouble("Final target to reach [kg]: ");
        if (target <= currentPR) {
            cout << "Error: Target must be greater than current PR (" << currentPR << " kg).\n";
        }
        else {
            break;
        }
    }
    
    cout << "\nTime period to accomplish this goal:\n";
    timePeriod = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
    
    switch(timePeriod){
        case 'D': 
            days = getValidPositiveInt("Enter number of day(s): ");
            if (days == 1)
                deadline = to_string(days) + " day";
            else
                deadline = to_string(days) + " days";
            break;
        case 'M': 
            months = getValidPositiveInt("Enter number of month(s): ");
            if (months == 1)
                deadline = to_string(months) + " month";
            else
                deadline = to_string(months) + " months";
            break;
        case 'Y': 
            years = getValidPositiveInt("Enter number of year(s): ");
            if (years == 1)
                deadline = to_string(years) + " year";
            else
                deadline = to_string(years) + " years";
            break;
    }
    
    cout << "\n=== SUMMARY ===\n";
    cout << "Goal: improve " << goal << "\n";
    cout << "Current: " << currentPR << " kg\n";
    cout << "Target: " << target << " kg\n";
    cout << "Deadline: " << deadline << "\n";
    cout << "Type: Strength (kg-based)\n";
    cout << "===============\n\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void Goal::updateProgress(){
    cout << "\n=== UPDATE PROGRESS ===\n";
    newPR = getValidPositiveDouble("Enter new personal best [kg]: ");
    
    if (newPR <= currentPR) {
        cout << "Note: New PR (" << newPR << " kg) is not better than current PR (" 
             << currentPR << " kg). No progress recorded.\n";
    } else {
        cout << "Progress updated successfully!\n";
    }
    cout << "Press Enter to continue...";
    cin.get();
}

void Goal::setType(){
    if (isValidExercise(goal)) {
        type = "Cardio";
    } else {
        type = "Strength";
    }
}

void Goal::checkProgress(){
    if(newPR == 0){
        cout << "\nNo progress recorded yet. Please update your progress first.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    if (newPR > currentPR){
        improvement = newPR - currentPR;
        double needed = target - currentPR;
        if (needed > 0) {
            percentage = (improvement / needed) * 100;
            if(percentage > 100) percentage = 100;
        } else {
            percentage = 100;
        }
    } else {
        improvement = 0;
        percentage = 0;
    }
    
    cout << "\n=== PROGRESS CHECK ===\n";
    
    if (percentage >= 100) {
        cout << "✓ GOAL ACHIEVED! Congratulations!\n";
    }
    else if (percentage >= 90){
        cout << "✓ Nearly there! Keep up the great work!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "% toward goal)\n";
    }
    else if (percentage >= 75){
        cout << "✓ Excellent progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
    }
    else if (percentage >= 50){
        cout << "✓ Good progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
    }
    else if (percentage >= 25){
        cout << "✓ Making progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
    }
    else if (percentage > 0){
        cout << "✓ Just getting started!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
    }
    else {
        cout << "⚠ No improvement yet. Don't give up!\n";
    }
    
    updateStatus();
    cout << "Status: " << status << "\n";
    cout << "=====================\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void Goal::updateStatus(){
    if (percentage >= 100) {
        status = "Achieved";
    }
    else if (percentage > 0) {
        status = "In Progress";
    }
    else {
        status = "Not Started";
    }
}

void Goal::updateDeadline(){
    if(timePeriod == 'D') {
        if (days == 1)
            deadline = to_string(days) + " day";
        else
            deadline = to_string(days) + " days";
    }
    else if (timePeriod == 'M') {
        if (months == 1)
            deadline = to_string(months) + " month";
        else
            deadline = to_string(months) + " months";
    }
    else if (timePeriod == 'Y') {
        if (years == 1)
            deadline = to_string(years) + " year";
        else
            deadline = to_string(years) + " years";
    }
}

void Goal::displayDetails(){
    cout << "\n=== STRENGTH GOAL DETAILS ===\n";
    cout << "Goal: " << goal << "\n";
    cout << "Type: " << type << "\n";
    cout << "Starting PR: " << currentPR << " kg\n";
    cout << "Target: " << target << " kg\n";
    cout << "Latest PR: ";
    if (newPR > 0)
        cout << newPR << " kg\n";
    else
        cout << "Not recorded\n";
    cout << "Deadline: " << deadline << "\n";
    cout << "Progress: +" << improvement << " kg (" << percentage << "%)\n";
    cout << "Status: " << status << "\n";
    cout << "===========================\n";
}