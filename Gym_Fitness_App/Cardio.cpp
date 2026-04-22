#include "Cardio.h"
#include <iomanip>
#include <cmath>

double Cardio::convertToSeconds(double minutes, double seconds) const
{
    return minutes * 60.0 + seconds;
}

void Cardio::convertToMinSec(double totalSeconds, double &minutes, double &seconds) const
{
    minutes = floor(totalSeconds / 60.0);
    seconds = totalSeconds - (minutes * 60.0);
}

void Cardio::displayTime(double minutes, double seconds) const
{
    int mins = static_cast<int>(minutes);
    int secs = static_cast<int>(seconds);
    if (mins >= 60) {
        int hrs = mins / 60;
        mins %= 60;
        cout << hrs << "h " << mins << "m " << secs << "s";
    } else if (mins > 0) {
        cout << mins << "m " << secs << "s";
    } else {
        cout << secs << "s";
    }
}

void Cardio::displayTotalTime(double totalSeconds) const
{
    double mins, secs;
    convertToMinSec(totalSeconds, mins, secs);
    displayTime(mins, secs);
}

void Cardio::getValidPaceInput(const std::string &prompt, double &minutes, double &seconds)
{
    while (true) {
        cout << prompt << " (minutes seconds):\n";
        cout << "Minutes: ";
        cin >> minutes;
        cout << "Seconds: ";
        cin >> seconds;

        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter numbers.\n";
            clearInputStream();
        } else if (minutes < 0 || seconds < 0) {
            cout << "Error: Pace values cannot be negative.\n";
        } else if (seconds >= 60) {
            cout << "Error: Seconds must be between 0 and 59.\n";
        } else if (minutes == 0 && seconds == 0) {
            cout << "Error: Pace cannot be zero.\n";
        } else {
            clearInputStream();
            return;
        }
    }
}

void Cardio::setCardioType(string ct) {
    cardioType = ct;
    setGoal("Improve " + ct + " pace");
}

Cardio::Cardio() : Goal(), cardioType("Unknown"), distance(0),
                   currentPaceMin(0), currentPaceSec(0),
                   targetPaceMin(0), targetPaceSec(0),
                   newPaceMin(0), newPaceSec(0), improvementSec(0)
{
    setType("Cardio");
    setStatus("Not Started");
}

// Helper functions remain unchanged (convertToSeconds, convertToMinSec, displayTime, displayTotalTime, getValidPaceInput)

void Cardio::addGoal() {
    cout << "\n=== NEW CARDIO GOAL SETUP ===\n";
    
    // Activity
    while (true) {
        cout << "Activity (e.g., Run, Swim, Cycle): ";
        getline(cin, cardioType);
        if (cardioType.empty()) {
            cout << "Error: Activity cannot be empty.\n";
        } else {
            setGoal("Improve " + cardioType + " pace");
            break;
        }
    }
    
    // Distance
    distance = getValidPositiveDouble("Distance (km): ");
    
    // Current pace
    cout << "\nCurrent pace per km:\n";
    getValidPaceInput("Enter current pace", currentPaceMin, currentPaceSec);
    
    // Target pace (must be faster)
    cout << "\nTarget pace per km:\n";
    while (true) {
        getValidPaceInput("Enter target pace", targetPaceMin, targetPaceSec);
        double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
        double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
        if (targetSec >= currentSec) {
            cout << "Error: Target pace must be faster (lower time) than current pace.\n";
        } else {
            break;
        }
    }
    
    // Deadline
    cout << "\nTime period to accomplish this goal:\n";
    char tp = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
    switch(tp) {
        case 'D': setDeadline(to_string(getValidPositiveInt("Number of day(s): ")) + " days"); break;
        case 'M': setDeadline(to_string(getValidPositiveInt("Number of month(s): ")) + " months"); break;
        case 'Y': setDeadline(to_string(getValidPositiveInt("Number of year(s): ")) + " years"); break;
    }
    
    // Summary
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    double currentTotal = currentSec * distance;
    double targetTotal = targetSec * distance;
    cout << "\n=== CARDIO SUMMARY ===\n";
    cout << "Activity: " << cardioType << "\n";
    cout << "Distance: " << distance << " km\n";
    cout << "Current pace: "; displayTime(currentPaceMin, currentPaceSec); cout << " per km\n";
    cout << "Current total time: "; displayTotalTime(currentTotal); cout << "\n";
    cout << "Target pace: "; displayTime(targetPaceMin, targetPaceSec); cout << " per km\n";
    cout << "Target total time: "; displayTotalTime(targetTotal); cout << "\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "======================\n\n";
    cin.ignore();
}

void Cardio::updateProgress() {
    cout << "\n=== UPDATE CARDIO PROGRESS ===\n";
    cout << "Distance: " << distance << " km\n";
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    while (true) {
        getValidPaceInput("Enter new personal best pace", newPaceMin, newPaceSec);
        double newSec = convertToSeconds(newPaceMin, newPaceSec);
        if (newSec >= currentSec) {
            cout << "Error: New pace must be faster (lower time) than current best.\n";
        } else {
            break;
        }
    }
    cout << "Progress updated!\n";
    cin.ignore();
}

void Cardio::checkProgress() {
    if (newPaceMin == 0 && newPaceSec == 0) {
        cout << "\nNo progress recorded yet. Please update your progress first.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double newSec = convertToSeconds(newPaceMin, newPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    
    if (newSec < currentSec) {
        improvementSec = currentSec - newSec;
        double totalNeeded = currentSec - targetSec;
        if (totalNeeded > 0) {
            percentage = (improvementSec / totalNeeded) * 100.0;
            if (percentage > 100) percentage = 100;
        } else {
            percentage = 100;
        }
    } else {
        improvementSec = 0;
        percentage = 0;
    }
    
    cout << "\n=== CARDIO PROGRESS CHECK ===\n";
    cout << "Distance: " << distance << " km\n";
    double newTotal = newSec * distance;
    
    if (percentage >= 100) {
        cout << "✓ GOAL ACHIEVED! New best pace: ";
        displayTime(newPaceMin, newPaceSec); cout << " per km\n";
        cout << "  New total time: "; displayTotalTime(newTotal); cout << "\n";
    } else if (percentage > 0) {
        cout << "✓ Improved by: ";
        double impMin, impSec;
        convertToMinSec(improvementSec, impMin, impSec);
        displayTime(impMin, impSec);
        cout << " (" << percentage << "% toward goal)\n";
        cout << "  Current pace: "; displayTime(newPaceMin, newPaceSec); cout << " per km\n";
        cout << "  Current total time: "; displayTotalTime(newTotal); cout << "\n";
    } else {
        cout << " No improvement yet. Keep training!\n";
    }
    
    updateStatus();
    cout << "Status: " << getStatus() << "\n";
    cout << "============================\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void Cardio::updateStatus() {
    if (percentage >= 100) setStatus("Achieved");
    else if (percentage > 0) setStatus("In Progress");
    else setStatus("Not Started");
}

void Cardio::displayGoal() {
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    double newSec = convertToSeconds(newPaceMin, newPaceSec);
    
    cout << "\n=== CARDIO GOAL DETAILS ===\n";
    cout << "Goal: " << getGoal() << "\n";
    cout << "Type: " << getType() << "\n";
    cout << "Distance: " << distance << " km\n";
    cout << "Starting pace: "; displayTime(currentPaceMin, currentPaceSec); cout << " per km\n";
    cout << "Target pace: "; displayTime(targetPaceMin, targetPaceSec); cout << " per km\n";
    cout << "Latest pace: ";
    if (newPaceMin > 0 || newPaceSec > 0)
        displayTime(newPaceMin, newPaceSec);
    else
        cout << "Not recorded";
    cout << " per km\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "Progress: " << percentage << "%\n";
    cout << "Status: " << getStatus() << "\n";
    cout << "===========================\n";
    
    // Edit menu (optional – can be kept simple)
    int choice;
    cout << "  1) Edit Goal\n  2) Update Progress\n  0) Return\n  Choice: ";
    cin >> choice; cin.ignore();
    if (choice == 1) editGoal();
    else if (choice == 2) updateProgress();
    // else return
}

void Cardio::editGoal() {
    // Cardio-specific editing (activity, distance, paces, deadline)
    int choice;
    do {
        clearScreen();
        line();
        cout << "           EDIT CARDIO GOAL\n";
        line();
        cout << "1) Activity\n2) Distance\n3) Starting Pace\n4) Target Pace\n5) Latest Pace\n6) Deadline\n0) Back\nChoice: ";
        cin >> choice; cin.ignore();
        switch(choice) {
            case 1: {
                cout << "New activity: ";
                getline(cin, cardioType);
                setGoal("Improve " + cardioType + " pace");
                break;
            }
            case 2: distance = getValidPositiveDouble("New distance (km): "); break;
            case 3: getValidPaceInput("New starting pace", currentPaceMin, currentPaceSec); break;
            case 4: {
                while (true) {
                    getValidPaceInput("New target pace", targetPaceMin, targetPaceSec);
                    if (convertToSeconds(targetPaceMin, targetPaceSec) >= convertToSeconds(currentPaceMin, currentPaceSec))
                        cout << "Error: Target must be faster than starting pace.\n";
                    else break;
                }
                break;
            }
            case 5: getValidPaceInput("New latest pace", newPaceMin, newPaceSec); break;
            case 6: {
                char tp = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
                int val = getValidPositiveInt("Number: ");
                string unit;
                if (tp == 'D') unit = (val == 1) ? " day" : " days";
                else if (tp == 'M') unit = (val == 1) ? " month" : " months";
                else unit = (val == 1) ? " year" : " years";
                setDeadline(to_string(val) + unit);
                break;
            }
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

string Cardio::getSummary() const {
    ostringstream ss;
    ss << getGoal() << " [" << distance << " km] - " << getStatus() << " (" << percentage << "%)";
    return ss.str();
}