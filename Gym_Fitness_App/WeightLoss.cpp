#include "WeightLoss.h"

WeightLoss::WeightLoss() : Goal(), startWeight(0), targetWeight(0), currentWeight(0), unit("kg")
{
    setType("Weight Loss");
    setStatus("Not Started");
    setGoal("Weight Loss");          // Auto‑generated, no user prompt
}

std::string WeightLoss::getValidUnit() {
    char choice = getValidCharInput("Unit: [K] Kilograms  [L] Pounds: ", "KL");
    return (choice == 'K') ? "kg" : "lbs";
}

void WeightLoss::addGoal() {
    cout << "\n=== NEW WEIGHT LOSS GOAL SETUP ===\n";

    // Unit selection
    unit = getValidUnit();

    // Starting weight
    startWeight = getValidPositiveDouble("Current weight (" + unit + "): ");

    // Target weight (must be less than starting weight)
    while (true) {
        targetWeight = getValidPositiveDouble("Target weight (" + unit + "): ");
        if (targetWeight >= startWeight) {
            cout << "Error: Target weight must be less than current weight (" 
                 << startWeight << " " << unit << ").\n";
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
    cout << "\n=== WEIGHT LOSS SUMMARY ===\n";
    cout << "Starting weight: " << startWeight << " " << unit << "\n";
    cout << "Target weight: " << targetWeight << " " << unit << "\n";
    cout << "Weight to lose: " << (startWeight - targetWeight) << " " << unit << "\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "============================\n\n";
    cin.ignore();
}

void WeightLoss::updateProgress() {
    cout << "\n=== UPDATE WEIGHT LOSS PROGRESS ===\n";
    double newWeight;
    while (true) {
        newWeight = getValidPositiveDouble("Enter current weight (" + unit + "): ");
        if (newWeight >= startWeight) {
            cout << "Error: New weight must be less than starting weight ("
                 << startWeight << " " << unit << ").\n";
        } else if (newWeight >= currentWeight && currentWeight > 0) {
            cout << "Error: No weight loss since last update (current: "
                 << currentWeight << " " << unit << ").\n";
        } else {
            break;
        }
    }
    currentWeight = newWeight;
    cout << "Progress updated!\n";
    cin.ignore();
}

void WeightLoss::checkProgress() {
    if (currentWeight == 0) {
        cout << "\nNo progress recorded yet. Please update your progress first.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    double lost = startWeight - currentWeight;
    double totalToLose = startWeight - targetWeight;

    if (lost > 0) {
        improvement = lost;
        if (totalToLose > 0) {
            percentage = (lost / totalToLose) * 100.0;
            if (percentage > 100) percentage = 100;
        } else {
            percentage = 100;
        }
    } else {
        improvement = 0;
        percentage = 0;
    }

    cout << "\n=== WEIGHT LOSS PROGRESS CHECK ===\n";
    cout << "Starting weight: " << startWeight << " " << unit << "\n";
    cout << "Current weight: " << currentWeight << " " << unit << "\n";
    cout << "Target weight: " << targetWeight << " " << unit << "\n";
    cout << "Weight lost: " << lost << " " << unit << "\n";

    if (percentage >= 100) {
        cout << "✓ GOAL ACHIEVED! Congratulations!\n";
    } else if (percentage > 0) {
        cout << "✓ Progress: " << percentage << "% toward goal\n";
    } else {
        cout << "⚠ No weight loss yet. Keep going!\n";
    }

    updateStatus();
    cout << "Status: " << getStatus() << "\n";
    cout << "==================================\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void WeightLoss::updateStatus() {
    if (percentage >= 100) setStatus("Achieved");
    else if (percentage > 0) setStatus("In Progress");
    else setStatus("Not Started");
}

void WeightLoss::displayGoal() {
    cout << "\n=== WEIGHT LOSS GOAL DETAILS ===\n";
    cout << "Goal: " << getGoal() << "\n";
    cout << "Type: " << getType() << "\n";
    cout << "Starting weight: " << startWeight << " " << unit << "\n";
    cout << "Target weight: " << targetWeight << " " << unit << "\n";
    cout << "Current weight: ";
    if (currentWeight > 0)
        cout << currentWeight << " " << unit << "\n";
    else
        cout << "Not recorded\n";
    cout << "Weight lost: " << improvement << " " << unit << "\n";
    cout << "Deadline: " << getDeadline() << "\n";
    cout << "Progress: " << percentage << "%\n";
    cout << "Status: " << getStatus() << "\n";
    cout << "==============================\n";

    int choice;
    cout << "  1) Edit Goal\n  2) Update Progress\n  0) Return\n  Choice: ";
    cin >> choice; cin.ignore();
    if (choice == 1) editGoal();
    else if (choice == 2) updateProgress();
}

void WeightLoss::editGoal() {
    int choice;
    do {
        clearScreen();
        line();
        cout << "           EDIT WEIGHT LOSS GOAL\n";
        line();
        cout << "1) Unit\n2) Starting Weight\n3) Target Weight\n4) Current Weight\n5) Deadline\n0) Back\nChoice: ";
        cin >> choice; cin.ignore();
        switch(choice) {
            case 1: {
                unit = getValidUnit();
                break;
            }
            case 2: {
                startWeight = getValidPositiveDouble("New starting weight (" + unit + "): ");
                break;
            }
            case 3: {
                while (true) {
                    targetWeight = getValidPositiveDouble("New target weight (" + unit + "): ");
                    if (targetWeight >= startWeight)
                        cout << "Error: Target must be less than starting weight.\n";
                    else break;
                }
                break;
            }
            case 4: {
                currentWeight = getValidPositiveDouble("New current weight (" + unit + "): ");
                break;
            }
            case 5: {
                char tp = getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
                int val = getValidPositiveInt("Number: ");
                string unitStr;
                if (tp == 'D') unitStr = (val == 1) ? " day" : " days";
                else if (tp == 'M') unitStr = (val == 1) ? " month" : " months";
                else unitStr = (val == 1) ? " year" : " years";
                setDeadline(to_string(val) + unitStr);
                break;
            }
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

string WeightLoss::getSummary() const {
    ostringstream ss;
    ss << getGoal() << " [" << startWeight << " -> " << targetWeight << " " << unit << "] - "
       << getStatus() << " (" << percentage << "%)";
    return ss.str();
}