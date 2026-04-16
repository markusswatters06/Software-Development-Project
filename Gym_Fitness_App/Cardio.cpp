#include "Cardio.h"
#include <iomanip>
#include <cmath>

Cardio::Cardio() : Goal(), cardioType("Unknown"), distance(0), 
                   currentPaceMin(0), currentPaceSec(0), 
                   targetPaceMin(0), targetPaceSec(0),
                   newPaceMin(0), newPaceSec(0),
                   improvementMin(0), improvementSec(0), percentage(0)
{
    setType("Cardio");
}

double Cardio::convertToSeconds(double minutes, double seconds) const {
    return minutes * 60 + seconds;
}

void Cardio::convertToMinSec(double totalSeconds, double& minutes, double& seconds) const {
    minutes = floor(totalSeconds / 60);
    seconds = totalSeconds - (minutes * 60);
}

void Cardio::displayTime(double minutes, double seconds) const {
    if (minutes >= 60) {
        int hours = (int)minutes / 60;
        int remainingMins = (int)minutes % 60;
        cout << hours << "h " << remainingMins << "m " << (int)seconds << "s";
    }
    else if (minutes > 0) {
        cout << (int)minutes << "m " << (int)seconds << "s";
    }
    else {
        cout << (int)seconds << "s";
    }
}

void Cardio::displayTotalTime(double totalSeconds) const {
    double minutes, seconds;
    convertToMinSec(totalSeconds, minutes, seconds);
    displayTime(minutes, seconds);
}

void Cardio::getValidPaceInput(const string& prompt, double& minutes, double& seconds) {
    while (true) {
        cout << prompt << " (minutes seconds):\n";
        cout << "Minutes: ";
        cin >> minutes;
        cout << "Seconds: ";
        cin >> seconds;
        
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter numbers.\n";
            clearInputStream();
        }
        else if (minutes < 0 || seconds < 0) {
            cout << "Error: Pace values cannot be negative.\n";
        }
        else if (seconds >= 60) {
            cout << "Error: Seconds must be between 0 and 59.\n";
        }
        else if (minutes == 0 && seconds == 0) {
            cout << "Error: Pace cannot be zero.\n";
        }
        else {
            clearInputStream();
            return;
        }
    }
}

void Cardio::startingPoint(){
    cout << "\n=== NEW CARDIO GOAL SETUP ===\n";
    
    while (true) {
        cout << "Activity (e.g., Run, Swim, Cycle): ";
        getline(cin, cardioType);
        
        if (cardioType.empty()) {
            cout << "Error: Activity cannot be empty.\n";
        }
        else {
            setGoal("Improve " + cardioType + " pace");
            break;
        }
    }
    
    cout << "\nEnter distance for this activity:\n";
    distance = getValidPositiveDouble("Distance (km): ");
    
    cout << "\nCurrent pace per km:\n";
    getValidPaceInput("Enter current pace", currentPaceMin, currentPaceSec);
    
    cout << "\nTarget pace per km:\n";
    while (true) {
        getValidPaceInput("Enter target pace", targetPaceMin, targetPaceSec);
        
        double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
        double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
        
        if (targetSec <= 0) {
            cout << "Error: Target pace must be positive.\n";
        }
        else if (targetSec >= currentSec) {
            cout << "Error: Target pace must be faster (lower number) than current pace.\n";
            cout << "Current pace: " << (int)currentPaceMin << "m " << (int)currentPaceSec << "s\n";
        }
        else {
            break;
        }
    }
    
    cout << "\nTime period to accomplish this goal:\n";
    char tp = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
    
    switch(tp){
        case 'D': 
            setDeadline(to_string(getValidPositiveInt("Number of day(s): ")) + " days");
            break;
        case 'M': 
            setDeadline(to_string(getValidPositiveInt("Number of month(s): ")) + " months");
            break;
        case 'Y': 
            setDeadline(to_string(getValidPositiveInt("Number of year(s): ")) + " years");
            break;
    }
    
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    double currentTotalSec = currentSec * distance;
    double targetTotalSec = targetSec * distance;
    
    cout << "\n=== CARDIO SUMMARY ===\n";
    cout << "Activity: " << cardioType << "\n";
    cout << "Distance: " << distance << " km\n";
    cout << "Current pace: " << (int)currentPaceMin << "m " << (int)currentPaceSec << "s per km\n";
    cout << "Current total time: ";
    displayTotalTime(currentTotalSec);
    cout << "\n";
    cout << "Target pace: " << (int)targetPaceMin << "m " << (int)targetPaceSec << "s per km\n";
    cout << "Target total time: ";
    displayTotalTime(targetTotalSec);
    cout << "\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "======================\n\n";
    
    cin.ignore();
}

void Cardio::updateProgress(){
    cout << "\n=== UPDATE CARDIO PROGRESS ===\n";
    cout << "Distance: " << distance << " km\n";
    
    getValidPaceInput("Enter new personal best pace", newPaceMin, newPaceSec);
    cout << "Progress updated!\n";
    cin.ignore();
}

void Cardio::checkProgress(){
    if(newPaceMin == 0 && newPaceSec == 0){
        cout << "\nNo progress recorded yet. Please update your progress first.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double newSec = convertToSeconds(newPaceMin, newPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    
    if(newSec < currentSec){
        double improvementTotalSec = currentSec - newSec;
        convertToMinSec(improvementTotalSec, improvementMin, improvementSec);
        
        double totalNeeded = currentSec - targetSec;
        if(totalNeeded > 0){
            percentage = (improvementTotalSec / totalNeeded) * 100;
            if(percentage > 100) percentage = 100;
        } else {
            percentage = 100;
        }
    } else {
        improvementMin = 0;
        improvementSec = 0;
        percentage = 0;
    }
    
    cout << "\n=== CARDIO PROGRESS CHECK ===\n";
    cout << "Distance: " << distance << " km\n";
    
    double newTotalSec = newSec * distance;
    double targetTotalSec = targetSec * distance;
    
    if (percentage >= 100) {
        cout << "✓ GOAL ACHIEVED! New best pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  New total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else if (percentage >= 90){
        cout << "✓ Nearly there! Keep up the great work!\n";
        cout << "  Improved pace by: " << (int)improvementMin << "m " << (int)improvementSec << "s";
        cout << " (" << percentage << "% toward goal)\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else if (percentage >= 75){
        cout << "✓ Excellent progress!\n";
        cout << "  Improved pace by: " << (int)improvementMin << "m " << (int)improvementSec << "s";
        cout << " (" << percentage << "%)\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else if (percentage >= 50){
        cout << "✓ Good progress!\n";
        cout << "  Improved pace by: " << (int)improvementMin << "m " << (int)improvementSec << "s";
        cout << " (" << percentage << "%)\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else if (percentage >= 25){
        cout << "✓ Making progress!\n";
        cout << "  Improved pace by: " << (int)improvementMin << "m " << (int)improvementSec << "s";
        cout << " (" << percentage << "%)\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else if (percentage > 0){
        cout << "✓ Just getting started!\n";
        cout << "  Improved pace by: " << (int)improvementMin << "m " << (int)improvementSec << "s";
        cout << " (" << percentage << "%)\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    else {
        cout << "⚠ No improvement yet. Keep training!\n";
        cout << "  Current pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
        cout << "  Current total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    
    updateStatus();
    cout << "Status: " << getStatus() << "\n";
    cout << "============================\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void Cardio::updateStatus(){
    if (percentage >= 100) {
        setStatus("Achieved");
    }
    else if (percentage > 0) {
        setStatus("In Progress");
    }
    else {
        setStatus("Not Started");
    }
}

void Cardio::displayDetails(){
    double currentSec = convertToSeconds(currentPaceMin, currentPaceSec);
    double targetSec = convertToSeconds(targetPaceMin, targetPaceSec);
    double newSec = convertToSeconds(newPaceMin, newPaceSec);
    double currentTotalSec = currentSec * distance;
    double targetTotalSec = targetSec * distance;
    double newTotalSec = newSec * distance;
    
    cout << "\n=== CARDIO GOAL DETAILS ===\n";
    cout << "Activity: " << cardioType << "\n";
    cout << "Distance: " << distance << " km\n";
    
    cout << "\n--- Pace Information ---\n";
    cout << "Starting pace: " << (int)currentPaceMin << "m " << (int)currentPaceSec << "s per km\n";
    cout << "Target pace: " << (int)targetPaceMin << "m " << (int)targetPaceSec << "s per km\n";
    if (newPaceMin > 0 || newPaceSec > 0) {
        cout << "Latest pace: " << (int)newPaceMin << "m " << (int)newPaceSec << "s per km\n";
    } else {
        cout << "Latest pace: Not recorded\n";
    }
    
    cout << "\n--- Total Time Information ---\n";
    cout << "Starting total time: ";
    displayTotalTime(currentTotalSec);
    cout << "\n";
    cout << "Target total time: ";
    displayTotalTime(targetTotalSec);
    cout << "\n";
    if (newPaceMin > 0 || newPaceSec > 0) {
        cout << "Latest total time: ";
        displayTotalTime(newTotalSec);
        cout << "\n";
    }
    
    cout << "\n--- Goal Progress ---\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "Progress: " << percentage << "% toward goal\n";
    cout << "Status: " << getStatus() << "\n";
    cout << "===========================\n";
}

void Cardio::setCardioType(string ct){
    cardioType = ct;
    setGoal("Improve " + ct + " pace");
}

string Cardio::getCardioType() const {
    return cardioType;
}