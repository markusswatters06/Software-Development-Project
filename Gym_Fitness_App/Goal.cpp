#include "Goal.h"
#include <algorithm>

Goal::Goal() : currentPR(0), days(0), months(0), years(0), timePeriod(), 
               percentage(0), target(0), newPR(0), improvement(0), status("Not Started")
{
    setType("Strength");
}
Goal::Goal(double currentPR, int days, int months, int years, char timePeriod, double percentage, string goal, string type, double target, string deadline, double newPR, double improvement, string status)
    : currentPR(currentPR), days(days), months(months), years(years), timePeriod(timePeriod), 
      percentage(percentage), goal(goal), type(type), target(target), deadline(deadline), 
      newPR(newPR), improvement(improvement), status(status)
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

void Goal::addGoal(){
    int choice;
    type = "Strength";
    clearInputStream();
    clearScreen();
    line();
    cout << "           NEW STRENGTH GOAL\n";
    line();
    
    while (true) {
        cout << "Exercise Name: ";
        getline(cin, goal);
        
        if (goal.empty()) {
            cout << "\n\nERROR: Exercise name cannot be empty.\n\n";
        }
        else {
            break;
        }
    }
    
    currentPR = getValidPositiveDouble("Current Personal best [kg]: ");
    
    while (true) {
        target = getValidPositiveDouble("Target [kg]: ");
        if (target <= currentPR) {
            cout << "\n\nERROR: Target must be greater than current PR (" << currentPR << " kg).\n\n";
        }
        else {
            break;
        }
    }
    
    cout << "Time to Accomplish:\n";
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

    clearScreen();
    line();
    cout << "           GOAL CREATED\n";
    line();

    cout << "Goal: Improve " << goal << "\n";
    cout << "Current: " << currentPR << " kg\n";
    cout << "Target: " << target << " kg\n";
    cout << "Deadline: " << deadline << "\n";
    cout << "Type: Strength (kg-based)\n";

    line();
    cout << "  1) Edit Goal" <<endl;
    cout << "  0) Return to Menu" << endl;
    cout << "  Choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1: editGoal(); break;
        case 0: break;
    }
}

void Goal::editGoal()
{
    int choice;

    clearScreen();
    do
    {
    line();
    cout << "           GOAL DETAILS\n";
    line();
    cout << "Goal: " << goal << "\n";
    cout << "Type: " << type << "\n";
    cout << "Starting PR: " << currentPR << " kg\n";
    cout << "Target: " << target << " kg\n";
    cout << "Latest PR: ";
    if (newPR > 0)
        cout << newPR << " kg\n";
    else
        cout << "Not recorded\n";
    cout << "Deadline: " << deadline << endl;
    cout << "Progress: +" << improvement << " kg (" << percentage << "%)\n";
    cout << "Status: " << status << "\n";
    line();
    
        cout << "           EDIT GOAL" << endl;
        line();

        cout << "  1) Goal" << endl;
        cout << "  2) Type" << endl;
        cout << "  3) Starting PR" << endl;
        cout << "  4) Target" << endl;
        cout << "  5) Latest PR" << endl;
        cout << "  6) Deadline" << endl;
        cout << "  0) Return to Goal Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;   

        switch(choice)
        {
            case 1: 
            {
                string g;
                cout << "\nEnter a New Goal: ";
                cin >> g;
                setGoal(g);
                clearScreen();
                break;
            }
            case 2: 
            {
                string t;
                cout << "\nEnter a New Type: ";
                cin >> t;
                setType(t);
                clearScreen();
                break;
            }
            case 3: 
            {
                double pr;
                cout << "\nEnter a New Starting PR [kg]: ";
                cin >> pr;
                setCurrentPR(pr);
                clearScreen();
                break;
            }
            case 4: 
            {
                double t;
                cout << "\nEnter a New Target [kg]: ";
                cin >> t;
                setTarget(t);
                clearScreen();
                break;
            }
            case 5: 
            {
                double pr;
                cout << "\nEnter a New Latest PR [kg]: ";
                cin >> pr;
                setNewPR(pr);
                clearScreen();
                break;
            }
            case 6: 
            {
                cout << "\nEnter a New Deadline\n";
            

                timePeriod = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");

                days = 0;
                months = 0;
                years = 0;

        switch(timePeriod)
        {
            case 'D':
            days = getValidPositiveInt("Enter number of day(s): ");
            break;

            case 'M':
            months = getValidPositiveInt("Enter number of month(s): ");
            break;

            case 'Y':
            years = getValidPositiveInt("Enter number of year(s): ");
            break;
    }

    updateDeadline();
    clearScreen();
    break;
    }
            case 0: break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        } 

    } 
    while (choice != 6);
}

void Goal::updateProgress() {
    cout << "\n=== UPDATE PROGRESS ===\n";
    double newVal;
    while (true) {
        newVal = getValidPositiveDouble("Enter New Personal Best [kg]: ");
        if (newVal <= currentPR) {
            cout << "Error: New PR must be greater than current PR (" 
                 << currentPR << " kg). Please try again.\n";
        } else {
            break;
        }
    }
    newPR = newVal;
    cout << "Progress updated successfully!\n";
    cout << "Press Enter to Return to Goal Menu...";
    cin.get();
}

string Goal::setType(){
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
    line();
    cout << "           PROGRESS CHECK\n";
    line();
    
    if (percentage >= 100) {
        cout << "GOAL ACHIEVED! Congratulations!\n";
        line();
    }
    else if (percentage >= 90){
        cout << "Nearly there! Keep up the great work!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "% toward goal)\n";
        line();
    }
    else if (percentage >= 75){
        cout << "Excellent progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
        line();
    }
    else if (percentage >= 50){
        cout << "Good progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
        line();
    }
    else if (percentage >= 25){
        cout << "Making progress!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
        line();
    }
    else if (percentage > 0){
        cout << "Just getting started!\n";
        cout << "  Improved by: " << improvement << " kg (" << percentage << "%)\n";
        line();
    }
    else {
        cout << "No improvement yet. Don't give up!\n";
        line();
    }
    
    updateStatus();
    cout << "Status: " << status << "\n";
    line();
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

void Goal::displayGoal(){
    int choice;
    line();
    cout << "           GOAL DETAILS\n";
    line();
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
    line();
    cout << "  1) Edit Goal\n";
    cout << "  2) Update Progress\n";
    cout << "  3) Remove Goal\n";
    cout << "  0) Return to Goal Menu\n";
    cout << "  Choice: ";
    cin >> choice;
    switch(choice)
    {
        case 1: editGoal(); break;
        case 2: updateProgress(); break;
        case 3: break;
        case 4: break;
        case 0: break;
        default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
    }
}


// UI
void Goal::clearScreen() {
    for (int i = 0; i < 40; i++) {
        cout << endl;
    }
}

void Goal::line() const {
    cout << "========================================\n";
}

string Goal::getSummary() const {
    ostringstream ss;
    ss << goal << " (" << type << ") - " << status << " (" << percentage << "%)";
    return ss.str();
}
