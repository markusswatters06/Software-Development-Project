#include "WorkoutPlan.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>

using namespace std;

namespace {
bool getValidWorkoutDate(int& d, int& m, int& y)
{
    while (true) {
        cout << "(DD): ";
        cin >> d;
        cout << "(MM): ";
        cin >> m;
        cout << "(YYYY): ";
        cin >> y;

        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) {
            cout << "\n-ERROR: Invalid date.-\n";
            cout << "\nEnter a Valid Date" << endl;
            continue;
        }

        int maxDays;

        if (m == 2)
            maxDays = 28;
        else if (m == 4 || m == 6 || m == 9 || m == 11)
            maxDays = 30;
        else
            maxDays = 31;

        if (d > maxDays) {
            cout << "ERROR: Invalid day for that month.\n";
            continue;
        }

        return true;
    }
}

string formatWorkoutDate(int d, int m, int y)
{
    string day = (d < 10 ? "0" : "") + to_string(d);
    string month = (m < 10 ? "0" : "") + to_string(m);
    return day + "/" + month + "/" + to_string(y);
}
}

// Static constant for maximum exercises (if using array instead of vector)
const int MAX_EXERCISES = 50;
int WorkoutPlan::nextPlanId = 1;
vector<WorkoutPlan> WorkoutPlan::workoutPlanList;

int WorkoutPlan::workoutPlanIndex(int planId)
{
    for (int i = 0; i < static_cast<int>(workoutPlanList.size()); i++ ) {
        if (workoutPlanList[i].id == planId){
            return i;
        }
    }
    return -1;
}

// Constructors
WorkoutPlan::WorkoutPlan() : id(nextPlanId++), plan(""), name(""), startDate(""), endDate("") {}

WorkoutPlan::WorkoutPlan(string plan, string name, string startDate, string endDate)
    : id(nextPlanId++), plan(plan), name(name), startDate(startDate), endDate(endDate) {}

// Deep copy constructor
WorkoutPlan::WorkoutPlan(const WorkoutPlan& other)
    : id(other.id), plan(other.plan), name(other.name), startDate(other.startDate), endDate(other.endDate) {
    // Deep copy the vector of Exercise pointers
    for (int i = 0; i < other.exercises.size(); i++) {
        exercises.push_back(new Exercise(*other.exercises[i]));
    }
}

// Deep copy assignment operator
WorkoutPlan& WorkoutPlan::operator=(const WorkoutPlan& other) {
    if (this != &other) { // Self-assignment check
        // Free existing memory
        for (int i = 0; i < exercises.size(); i++) {
            delete exercises[i];
        }
        exercises.clear();
        
        
        id = other.id;
        plan = other.plan;
        name = other.name;
        startDate = other.startDate;
        endDate = other.endDate;
        
        // Deep copy exercises
        for (int i = 0; i < other.exercises.size(); i++) {
            exercises.push_back(new Exercise(*other.exercises[i]));
        }
    }
    return *this;
}

// Destructor
WorkoutPlan::~WorkoutPlan() {
    for (int i = 0; i < exercises.size(); i++) {
        delete exercises[i];
    }
    exercises.clear();
}

// Getter methods
string WorkoutPlan::getPlan() const { return plan; }
string WorkoutPlan::getName() const { return name; }
string WorkoutPlan::getStartDate() const { return startDate; }
string WorkoutPlan::getEndDate() const { return endDate; }

// Setter methods
void WorkoutPlan::setPlan(string plan) { this->plan = plan; }
void WorkoutPlan::setName(string name) { this->name = name; }
void WorkoutPlan::setStartDate(string startDate) { this->startDate = startDate; }
void WorkoutPlan::setEndDate(string endDate) { this->endDate = endDate; }

// Aggregation relationship methods
bool WorkoutPlan::addExercise(const Exercise& newExercise) {
    if (exercises.size() < MAX_EXERCISES) {
        exercises.push_back(new Exercise(newExercise));
        return true;
    }
    cout << "Error: Workout plan " << name << " is full!" << endl;
    return false;
}

bool WorkoutPlan::removeExercise(string exerciseName) {
    for (int i = 0; i < exercises.size(); i++) {
        if (exercises[i]->getName() == exerciseName) {
            delete exercises[i];
            exercises.erase(exercises.begin() + i);
            return true;
        }
    }
    return false;
}

Exercise* WorkoutPlan::findExercise(string exerciseName) {
    for (int i = 0; i < exercises.size(); i++) {
        if (exercises[i]->getName() == exerciseName) {
            return exercises[i];
        }
    }
    return nullptr;
}

int WorkoutPlan::getExerciseCount() const {
    return exercises.size();
}

void WorkoutPlan::displayAllExercises() const {
    for (int i = 0; i < exercises.size(); i++) {
        cout << "  " << *exercises[i] << endl;
    }
}

void WorkoutPlan::displayPlan() const {
    line();
    cout << "           WORKOUT PLAN DETAILS\n";
    line();
    cout << "Plan ID: " << id << endl;
    cout << "Plan Code: " << plan << endl;
    cout << "Name: " << name << endl;
    cout << "Start Date: " << startDate << endl;
    cout << "End Date: " << endDate << endl;
    cout << "Exercises:" << endl;
    if (exercises.empty()) {
        cout << " No exercises added.\n";
    } else {
        displayAllExercises();
    }
    line();
}

void WorkoutPlan::addPlan(const WorkoutPlan& workoutPlan)
{
    if (workoutPlanIndex(workoutPlan.id) != -1)
    {
        return;
    }

    workoutPlanList.push_back(workoutPlan);

    if (workoutPlan.id >= nextPlanId)
    {
        nextPlanId = workoutPlan.id + 1;
    }
}

void WorkoutPlan::displayPlans() const
{
    if(workoutPlanList.empty()){
        line();
        cout << "           WORKOUT PLAN DETAILS" << endl;
        line();
        cout << " No workout plans available.\n\n";
        line();
        return;
    }

    lineLong();
    cout << "                                      WORKOUT PLANS\n";
    lineLong();
    cout << " ID | Name                 | Start Date  | End Date\n";
    dashedLine();

    for (int i = 0; i < static_cast<int>(workoutPlanList.size()); i++) {
        const WorkoutPlan& plan = workoutPlanList[i];
        if (plan.id < 10) cout << "  ";
        else if (plan.id < 100) cout << ' ';
        cout << plan.id << " | ";

        cout << plan.name;
        for (int j = static_cast<int>(plan.name.length()); j < 20; j++) cout << ' ';
        cout << " | ";

        cout << plan.startDate;
        for (int j = static_cast<int>(plan.startDate.length()); j < 12; j++) cout << ' ';
        cout << " | ";

        cout << plan.endDate;
        for (int j = static_cast<int>(plan.endDate.length()); j < 12; j++) cout << ' ';
        cout << endl;
    }

    lineLong();
}

void WorkoutPlan::viewPlanDetails() const
{
    if (workoutPlanList.empty())
    {
        displayPlans();
        return;
    }

    displayPlans();

    int planId;
    cout << "Enter Workout Plan ID to view (0 to return): ";
    cin >> planId;

    if (planId == 0)
    {
        clearScreen();
        return;
    }

    const int index = workoutPlanIndex(planId);
    if (index == -1)
    {
        cout << "\nERROR: Workout plan not found.\n";
        return;
    }

    clearScreen();
    workoutPlanList[index].displayPlan();
    cout << "Press Enter to return...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// WorkoutPlan specific methods
void WorkoutPlan::createPlan() {
    WorkoutPlan newPlan;
    int exerciseCount = 0;

    clearScreen();
    line();
    cout << "           CREATE WORKOUT PLAN\n";
    line();

    newPlan.id = nextPlanId++;
    newPlan.plan = "WP" + to_string(newPlan.id);
    cout << "Plan ID: " << newPlan.id << endl;
    cout << "Plan Code: " << newPlan.plan << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << "Plan Name: ";
        getline(cin, newPlan.name);
        if (newPlan.name.empty())
        {
            cout << "ERROR: Plan name cannot be empty.\n";
        }
    }
    while (newPlan.name.empty());

    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;

    cout << "Enter Start Date\n";
    getValidWorkoutDate(startDay, startMonth, startYear);
    newPlan.startDate = formatWorkoutDate(startDay, startMonth, startYear);

    cout << "Enter End Date\n";
    getValidWorkoutDate(endDay, endMonth, endYear);
    newPlan.endDate = formatWorkoutDate(endDay, endMonth, endYear);

    cout << "How many exercises would you like to add now? ";
    cin >> exerciseCount;

    while (cin.fail() || exerciseCount < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Enter a valid number of exercises: ";
        cin >> exerciseCount;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < exerciseCount; i++)
    {
        Exercise exercise;
        string exerciseName;
        string muscleGroup;
        string equipment;

        cout << "\nExercise " << (i + 1) << endl;

        do
        {
            cout << "Name: ";
            getline(cin, exerciseName);
        }
        while (exerciseName.empty());

        do
        {
            cout << "Muscle Group: ";
            getline(cin, muscleGroup);
        }
        while (muscleGroup.empty());

        do
        {
            cout << "Equipment: ";
            getline(cin, equipment);
        }
        while (equipment.empty());

        exercise.setExercise("Workout");
        exercise.setName(exerciseName);
        exercise.setMuscleGroup(muscleGroup);
        exercise.setEquipment(equipment);
        newPlan.addExercise(exercise);
    }

    workoutPlanList.push_back(newPlan);
    *this = newPlan;

    clearScreen();
    line();
    cout << "           WORKOUT PLAN CREATED\n";
    line();
    newPlan.displayPlan();
    line();
    cout << "Press Enter to return...";
    cin.get();
}

void WorkoutPlan::editPlan()
{
    if (workoutPlanList.empty())
    {
        cout << "\nNo workout plans available to edit.\n";
        return;
    }

    int planId;
    int choice;

    displayPlans();
    cout << "Enter Workout Plan ID to edit (0 to return): ";
    cin >> planId;

    if (planId == 0)
    {
        clearScreen();
        return;
    }

    const int index = workoutPlanIndex(planId);
    if (index == -1)
    {
        cout << "\nERROR: Workout plan not found.\n";
        return;
    }
    WorkoutPlan& selectedPlan = workoutPlanList[index];
    do
    {
        clearScreen();
        line();
        cout << "           EDIT WORKOUT PLAN\n";
        line();
        selectedPlan.displayPlan();
        cout << "  1) Name" << endl;
        cout << "  2) Start Date" << endl;
        cout << "  3) End Date" << endl;
        cout << "  4) Manage Exercises" << endl;
        cout << "  0) Return to Workout Plan Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch(choice){
            case 1:
            {
                string newName;
                cout << "\nEnter New Name: ";
                cin >> newName;
                selectedPlan.setName(newName);
                break;
            }
            case 2:
            {
                int day, month, year;
                cout << "\nEnter New Start Date\n";
                getValidWorkoutDate(day, month, year);
                selectedPlan.setStartDate(formatWorkoutDate(day, month, year));
                break;
            }
            case 3:
            {
                int day, month, year;
                cout << "\nEnter New End Date\n";
                getValidWorkoutDate(day, month, year);
                selectedPlan.setEndDate(formatWorkoutDate(day, month, year));
                break;
            }
            case 4:
            {
                int exerciseChoice;
                do
                {
                    clearScreen();
                    line();
                    cout << "           MANAGE EXERCISES\n";
                    line();
                    selectedPlan.displayAllExercises();
                    line();
                    cout << "  1) Add Exercise" << endl;
                    cout << "  2) Remove Exercise" << endl;
                    cout << "  0) Return to Edit Workout Plan" << endl;
                    line();
                    cout << "  Choice: ";
                    cin >> exerciseChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (exerciseChoice)
                    {
                        case 1:
                        {
                            Exercise exercise;
                            string exerciseName;
                            string muscleGroup;
                            string equipment;

                            do { cout << "Name: "; getline(cin, exerciseName); } while (exerciseName.empty());
                            do { cout << "Muscle Group: "; getline(cin, muscleGroup); } while (muscleGroup.empty());
                            do { cout << "Equipment: "; getline(cin, equipment); } while (equipment.empty());

                            exercise.setExercise("Workout");
                            exercise.setName(exerciseName);
                            exercise.setMuscleGroup(muscleGroup);
                            exercise.setEquipment(equipment);
                            selectedPlan.addExercise(exercise);
                            break;
                        }
                        case 2:
                        {
                            string exerciseName;
                            cout << "Enter Exercise Name to remove: ";
                            getline(cin, exerciseName);
                            if (!selectedPlan.removeExercise(exerciseName))
                            {
                                cout << "ERROR: Exercise not found.\n";
                            }
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "\nERROR: Invalid Choice\n";
                            break;
                    }
                }
                while (exerciseChoice != 0);
                break;
            }
            case 0:
                clearScreen();
                break;
        }
        }while(choice != 0);
}

void WorkoutPlan::removePlan()
{
    if(workoutPlanList.empty())
    {
        cout << "\nNo workout plans available to remove.\n";
        return;
    }

    clearScreen();
    displayPlans();

    int planId;
    cout << "Enter Workout Plan ID to remove (0 to return): ";
    cin >> planId;

    if (planId == 0)
    {
        clearScreen();
        return;
    }

    int index = workoutPlanIndex(planId);
    if (index == -1)
    {
        clearScreen();
        cout << "\nERROR: Workout plan not found.\n";
        return;
    }

    char confirm;
    cout << "\nAre you sure you want to remove this workout plan? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        workoutPlanList.erase(workoutPlanList.begin() + index);
        clearScreen();
        cout << "\nWorkout plan removed successfully.\n\n";
        if (!workoutPlanList.empty()) {
            displayPlans();
        }
    }
    else
    {
        cout << "\nWorkout plan removal cancelled.\n";
    }
}

void WorkoutPlan::updatePlan() {
    cout << "Updating workout plan: " << name << endl;
}

void WorkoutPlan::getProgress() const {
    cout << "Getting progress for plan: " << name << endl;
}

void WorkoutPlan::clearScreen() const
{
    for (int i = 0; i < 40; i++) {
        cout << endl;
    }
}

void WorkoutPlan::line() const
{
    cout << "========================================\n";
}

void WorkoutPlan::lineLong() const
{
    cout << "=====================================================================================\n";
}

void WorkoutPlan::dashedLine() const
{
    cout << "-------------------------------------------------------------------------------------\n";
}

// Operator overloading
bool WorkoutPlan::operator==(const WorkoutPlan& other) const {
    return (plan == other.plan && name == other.name);
}

bool WorkoutPlan::operator!=(const WorkoutPlan& other) const {
    return !(*this == other);
}

// Friend function for output operator
ostream& operator<<(ostream& out, const WorkoutPlan& plan) {
    out << "Workout Plan: " << plan.name << " (" << plan.startDate << " to " << plan.endDate << ")";
    return out;
}
