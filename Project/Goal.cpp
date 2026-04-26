#include "Goal.h"
#include <algorithm>

int Goal::nextGoalId = 1;
vector<Goal> Goal::goalList;

int Goal::goalIndex(int goalId) {
    for (int i = 0; i < static_cast<int>(goalList.size()); i++) {
        if (goalList[i].id == goalId) {
            return i;
        }
    }
    return -1;
}

Goal::Goal() : id(0), currentPR(0), days(0), months(0), years(0), timePeriod(),
               goal(), type(), target(0), deadline(), newPR(0), status("Not Started"),
               improvement(0), percentage(0)
{
    setType("Strength");
}
Goal::Goal(int gid, double currentPR, int days, int months, int years, char timePeriod, double percentage, string goal, string type, double target, string deadline, double newPR, double improvement, string status)
    : id(gid), currentPR(currentPR), days(days), months(months), years(years), timePeriod(timePeriod),
      goal(goal), type(type), target(target), deadline(deadline), newPR(newPR), status(status),
      improvement(improvement), percentage(percentage)
{}

double Goal::getValidPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Please enter a number.\n";
        }
        else if (value < 0) {
            cout << "Error: Value cannot be negative.\n";
        }
        else {
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
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Please enter a whole number.\n";
        }
        else if (value <= 0) {
            cout << "Error: Please enter a positive number (greater than 0).\n";
        }
        else {
            return value;
        }
    }
}

char Goal::getValidCharInput(const string& prompt, const string& validOptions) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin >> ws, input);
        
        if (input.empty()) {
            cout << "Error: Input cannot be empty.\n";
            continue;
        }
        
        char choice = toupper(input[0]);
        
        bool valid = false;
        for (size_t i = 0; i < validOptions.length(); i++) {
            if (choice == validOptions[i]) {
                valid = true;
                break;
            }
        }
        
        if (valid) {
            return choice;
        } else {
            cout << "Error: Invalid option. Please enter one of: ";
            for (size_t i = 0; i < validOptions.length(); i++) {
                cout << validOptions[i] << " ";
            }
            cout << endl;
        }
    }
}

bool Goal::isValidExercise(const string& exercise) {
    string lowerExercise = exercise;
    for (size_t i = 0; i < lowerExercise.length(); i++) {
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

void Goal::addGoal(const Goal& goal) {
    if (!goal.getGoal().empty()) {
        if (goalIndex(goal.getId()) != -1) {
            return;
        }

        goalList.push_back(goal);

        if (goal.getId() >= nextGoalId) {
            nextGoalId = goal.getId() + 1;
        }
        return;
    }

    int choice;
    Goal newGoal;

    clearScreen();
    line();
    cout << "           NEW GOAL\n";
    line();

    newGoal.id = nextGoalId++;
    cout << "Goal ID: " << newGoal.id << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Exercise Name: ";
        getline(cin, newGoal.goal);

        if (newGoal.goal.empty()) {
            cout << "\nERROR: Exercise name cannot be empty.\n";
        }
    } while (newGoal.goal.empty());

    newGoal.type = newGoal.setType();

    const string unit = (newGoal.type == "Cardio") ? "minutes" : "kg";

    newGoal.currentPR = getValidPositiveDouble("Current Personal Best [" + unit + "]: ");

    while (true) {
        newGoal.target = getValidPositiveDouble("Target [" + unit + "]: ");
        if (newGoal.target <= newGoal.currentPR) {
            cout << "\nERROR: Target must be greater than the current value (" << newGoal.currentPR
                 << ' ' << unit << ").\n";
        } else {
            break;
        }
    }

    cout << "Time to Accomplish:\n";
    newGoal.timePeriod = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");

    switch (newGoal.timePeriod) {
        case 'D':
            newGoal.days = getValidPositiveInt("Enter number of day(s): ");
            break;
        case 'M':
            newGoal.months = getValidPositiveInt("Enter number of month(s): ");
            break;
        case 'Y':
            newGoal.years = getValidPositiveInt("Enter number of year(s): ");
            break;
    }

    newGoal.updateDeadline();
    goalList.push_back(newGoal);
    *this = newGoal;

    clearScreen();
    line();
    cout << "           GOAL CREATED\n";
    line();
    cout << "Goal: Improve " << newGoal.goal << "\n";
    cout << "Current: " << newGoal.currentPR << ' ' << unit << "\n";
    cout << "Target: " << newGoal.target << ' ' << unit << "\n";
    cout << "Deadline: " << newGoal.deadline << "\n";
    cout << "Type: " << newGoal.type << "\n";
    line();
    cout << "  Enter 0 to return to Goal Menu" << endl;
    cout << "  Choice: ";
    cin >> choice;

    switch (choice) {
        case 0:  break;
        default: break;
    }
}

void Goal::editGoal()
{
    if (goalList.empty()) {
        cout << "\nNo Goals Available to Edit.\n";
        return;
    }

    int goalId;
    int choice;

    displayGoals();
    cout << "  Enter Goal ID to edit (0 to return): ";
    cin >> goalId;

    if (goalId == 0) {
        clearScreen();
        return;
    }

    const int index = goalIndex(goalId);
    if (index == -1) {
        cout << "\nERROR: Goal not found.\n";
        return;
    }

    Goal& selectedGoal = goalList[index];

    do {
        clearScreen();
        line();
        cout << "           EDIT GOAL\n";
        line();
        selectedGoal.displayGoal();
        cout << "  1) Goal Name" << endl;
        cout << "  2) Starting PR" << endl;
        cout << "  3) Target" << endl;
        cout << "  4) Latest PR" << endl;
        cout << "  5) Deadline" << endl;
        cout << "  0) Return to Goal Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string g;
                do {
                    cout << "\nEnter a New Goal: ";
                    getline(cin, g);
                } while (g.empty());
                selectedGoal.setGoal(g);
                selectedGoal.setType(selectedGoal.setType());
                break;
            }
            case 2:
            {
                const string unit = (selectedGoal.getType() == "Cardio") ? "minutes" : "kg";
                double pr = getValidPositiveDouble("\nEnter a New Starting PR [" + unit + "]: ");
                selectedGoal.setCurrentPR(pr);
                break;
            }
            case 3:
            {
                const string unit = (selectedGoal.getType() == "Cardio") ? "minutes" : "kg";
                double targetValue;
                do {
                    targetValue = getValidPositiveDouble("\nEnter a New Target [" + unit + "]: ");
                    if (targetValue <= selectedGoal.getCurrentPR()) {
                        cout << "ERROR: Target must be greater than the starting PR.\n";
                    }
                } while (targetValue <= selectedGoal.getCurrentPR());
                selectedGoal.setTarget(targetValue);
                break;
            }
            case 4:
            {
                const string unit = (selectedGoal.getType() == "Cardio") ? "minutes" : "kg";
                double pr = getValidPositiveDouble("\nEnter a New Latest PR [" + unit + "]: ");
                selectedGoal.setNewPR(pr);
                selectedGoal.checkProgress();
                break;
            }
            case 5:
            {
                cout << "\nEnter a New Deadline\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                selectedGoal.timePeriod = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
                selectedGoal.days = 0;
                selectedGoal.months = 0;
                selectedGoal.years = 0;

                switch (selectedGoal.timePeriod) {
                    case 'D':
                        selectedGoal.days = getValidPositiveInt("Enter number of day(s): ");
                        break;
                    case 'M':
                        selectedGoal.months = getValidPositiveInt("Enter number of month(s): ");
                        break;
                    case 'Y':
                        selectedGoal.years = getValidPositiveInt("Enter number of year(s): ");
                        break;
                }

                selectedGoal.updateDeadline();
                break;
            }
            case 0:
                break;
            default:
                cout << "\n\n*ERROR: Invalid Choice*\n\n";
                break;
        }

        if (choice != 0) {
            *this = selectedGoal;
        }
    } while (choice != 0);
}

void Goal::removeGoal()
{
    if (goalList.empty()) {
        clearScreen();
        cout << "\nNo goals available to remove.\n";
        return;
    }

    clearScreen();
    displayGoals();

    int goalId;
    cout << "Enter the Goal ID to remove: ";
    cin >> goalId;

    int index = goalIndex(goalId);
    if (index == -1) {
        clearScreen();
        cout << "\nERROR: Goal not found.\n";
        return;
    }

    char confirm;
    cout << "\nAre you sure you want to remove this goal? (Y/N): ";
    cin >> confirm;


    if (confirm == 'Y' || confirm == 'y')
    {
        goalList.erase(goalList.begin() + index);
        clearScreen();
        cout << "\nGoal removed successfully.\n\n";
        if (!goalList.empty()) {
            displayGoals();
        }
    }
    else
    {
        cout << "\nGoal removal cancelled.\n";
    }
}

void Goal::updateProgress() {
    displayGoals();
    const string unit = (type == "Cardio") ? "minutes" : "kg";
    double newVal;
    while (true) {
        newVal = getValidPositiveDouble("Enter New Personal Best [" + unit + "]: ");
        if (newVal <= currentPR) {
            cout << "Error: New PR must be greater than current PR (" 
                 << currentPR << ' ' << unit << "). Please try again.\n";
        } else {
            break;
        }
    }
    newPR = newVal;
    checkProgress();
    cout << "Progress updated successfully!\n";
}

string Goal::setType(){
    if (isValidExercise(goal)) {
        type = "Cardio";
    } else {
        type = "Strength";
    }

    return type;
}

void Goal::checkProgress(){
    const string unit = (type == "Cardio") ? "minutes" : "kg";

    if(newPR == 0){
        cout << "\nNo progress recorded yet. Please update your progress first.\n";
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout << "  Improved by: " << improvement << ' ' << unit << " (" << percentage << "% toward goal)\n";
        line();
    }
    else if (percentage >= 75){
        cout << "Excellent progress!\n";
        cout << "  Improved by: " << improvement << ' ' << unit << " (" << percentage << "%)\n";
        line();
    }
    else if (percentage >= 50){
        cout << "Good progress!\n";
        cout << "  Improved by: " << improvement << ' ' << unit << " (" << percentage << "%)\n";
        line();
    }
    else if (percentage >= 25){
        cout << "Making progress!\n";
        cout << "  Improved by: " << improvement << ' ' << unit << " (" << percentage << "%)\n";
        line();
    }
    else if (percentage > 0){
        cout << "Just getting started!\n";
        cout << "  Improved by: " << improvement << ' ' << unit << " (" << percentage << "%)\n";
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
void Goal::displayGoals() const{
    if (goalList.empty()) {
            line();
            cout << "           GOAL DETAILS" << endl;
            line();
            cout << " No goals available.\n\n";
            line();
            return;
        }

        lineLong();
        cout << "                                      ALL GOALS\n";
        lineLong();
        cout << " ID | Goal Name            | Type      | Target      | Deadline        | Progress | Status\n";
        dashedLine();

        for (int i = 0; i < static_cast<int>(goalList.size()); i++){
            const Goal& goal = goalList[i];
            if (goal.id < 10) cout << "  ";
            else if (goal.id < 100) cout << ' ';
            cout << goal.id << "  ";

        cout << goal.goal;
        for (int j = static_cast<int>(goal.goal.length()); j < 20; j++) cout << ' ';
        cout << "  ";

        cout << goal.type;
        for (int j = static_cast<int>(goal.type.length()); j < 9; j++) cout << ' ';
        cout << "  ";

        string unit = (goal.type == "Cardio") ? " minutes" : " kg";
        string targetValue = to_string(static_cast<int>(goal.target)) + unit;
        cout << targetValue;
        for (int j = static_cast<int>(targetValue.length()); j < 11; j++) cout << ' ';
        cout << "  ";

        cout << goal.deadline;
        for (int j = static_cast<int>(goal.deadline.length()); j < 15; j++) cout << ' ';
        cout << "  ";

        string percent = to_string(static_cast<int>(goal.percentage)) + "%";
        cout << percent;
        for (int j = static_cast<int>(percent.length()); j < 8; j++) cout << ' ';
        cout << "  " << goal.status << endl;
    }
    lineLong();
}
void Goal::displayGoal(){
    const string unit = (type == "Cardio") ? "minutes" : "kg";

    line();
    cout << "           GOAL DETAILS\n";
    line();
    cout << "Goal: " << goal << "\n";
    cout << "Starting PR: " << currentPR << ' ' << unit << "\n";
    cout << "Target: " << target << ' ' << unit << "\n";
    cout << "Latest PR: ";
    if (newPR > 0)
        cout << newPR << ' ' << unit << "\n";
    else
        cout << "Not recorded\n";
    cout << "Deadline: " << deadline << "\n";
    cout << "Progress: +" << improvement << ' ' << unit << " (" << percentage << "%)\n";
    cout << "Status: " << status << "\n";
    line();
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

void Goal::lineLong() const {
    cout << "=====================================================================================\n";
}
void Goal::dashedLine() const {
    cout << "-------------------------------------------------------------------------------------\n";
}

string Goal::getSummary() const {
    ostringstream ss;
    ss << goal << " (" << type << ") - " << status << " (" << percentage << "%)";
    return ss.str();
}
