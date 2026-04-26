#include "Client.h"
#include <limits>
#include <stdexcept>

namespace {
void printClientGoalTable(const vector<Goal>& goals)
{
    if (goals.empty())
    {
        cout << " No goals available.\n\n";
        return;
    }

    cout << "=====================================================================================\n";
    cout << "                                     MY GOALS\n";
    cout << "=====================================================================================\n";
    cout << " ID | Goal Name            | Type      | Target      | Deadline        | Progress | Status\n";
    cout << "-------------------------------------------------------------------------------------\n";

    for (int i = 0; i < static_cast<int>(goals.size()); i++)
    {
        const Goal& goal = goals[i];

        if (goal.getId() < 10) cout << "  ";
        else if (goal.getId() < 100) cout << ' ';
        cout << goal.getId() << "  ";

        cout << goal.getGoal();
        for (int j = static_cast<int>(goal.getGoal().length()); j < 20; j++) cout << ' ';
        cout << "  ";

        cout << goal.getType();
        for (int j = static_cast<int>(goal.getType().length()); j < 9; j++) cout << ' ';
        cout << "  ";

        string unit = (goal.getType() == "Cardio") ? " minutes" : " kg";
        string targetValue = to_string(static_cast<int>(goal.getTarget())) + unit;
        cout << targetValue;
        for (int j = static_cast<int>(targetValue.length()); j < 11; j++) cout << ' ';
        cout << "  ";

        cout << goal.getDeadline();
        for (int j = static_cast<int>(goal.getDeadline().length()); j < 15; j++) cout << ' ';
        cout << "  ";

        string percent = to_string(static_cast<int>(goal.getPercentage())) + "%";
        cout << percent;
        for (int j = static_cast<int>(percent.length()); j < 8; j++) cout << ' ';
        cout << "  " << goal.getStatus() << endl;
    }

    cout << "=====================================================================================\n";
}
}


// Constructors
Client::Client()
    : User(), height(0.0), weight(0.0), goal("N/A"),
        bookedSession(new Session()), currentGoal(new Goal())
{
    initializeWorkoutData();
}

Client::Client(double h, double w, string g)    
    : User(), height(h), weight(w), goal(g),
        bookedSession(new Session()), currentGoal(new Goal())
{
    initializeWorkoutData();
}

Client::Client(int i, string n, string e, int ph, int dd, int dm, int dy, string p,
               double h, double w, string g)
    : User(i, n, e, ph, dd, dm, dy, p), height(h), weight(w), goal(g),
        bookedSession(new Session()), currentGoal(new Goal())
{
    initializeWorkoutData();
}

Client::Client(const Client& other)
    : User(other.id, other.name, other.email, other.phone, other.dobDay, other.dobMonth, other.dobYear, other.password),
        height(other.height), weight(other.weight), goal(other.goal),
      bookedSessionIds(other.bookedSessionIds), clientGoals(other.clientGoals),
      bookedSession(new Session(*other.bookedSession)), currentGoal(new Goal(*other.currentGoal)),
      cardioWorkout(other.cardioWorkout), currentExercise(other.currentExercise),
      currentWorkoutPlan(other.currentWorkoutPlan), currentWorkoutExercise(other.currentWorkoutExercise)
{
    syncWorkoutLinks();
}

Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        email = other.email;
        phone = other.phone;
        dobDay = other.dobDay;
        dobMonth = other.dobMonth;
        dobYear = other.dobYear;
        password = other.password;
        height = other.height;
        weight = other.weight;
        goal = other.goal;
        bookedSessionIds = other.bookedSessionIds;
        clientGoals = other.clientGoals;
        cardioWorkout = other.cardioWorkout;
        currentExercise = other.currentExercise;
        currentWorkoutPlan = other.currentWorkoutPlan;
        currentWorkoutExercise = other.currentWorkoutExercise;

        *bookedSession = *other.bookedSession;
        *currentGoal = *other.currentGoal;
        syncWorkoutLinks();
    }

    return *this;
}

Client::~Client()
{
    delete bookedSession;
    delete currentGoal;
}

bool Client::operator==(const Client& other) const
{
    return id == other.id;
}

ostream& operator<<(ostream& os, const Client& client)
{
    os << "Client[" << client.id << "] " << client.name
       << " | Goal: " << client.goal;
    return os;
}

void Client::setBookedSession(const Session& session)
{
    *bookedSession = session;
}

void Client::setCurrentGoal(const Goal& newGoal)
{
    *currentGoal = newGoal;

    for (int i = 0; i < static_cast<int>(clientGoals.size()); i++)
    {
        if (clientGoals[i].getId() == newGoal.getId())
        {
            clientGoals[i] = newGoal;
            return;
        }
    }

    clientGoals.push_back(newGoal);
}

void Client::setWorkoutTester(const WorkoutPlan& workoutPlan, string exerciseName, int sets, int reps, int restTime)
{
    currentWorkoutPlan = workoutPlan;

    Exercise* linkedExercise = currentWorkoutPlan.findExercise(exerciseName);
    if (linkedExercise != nullptr)
    {
        currentExercise = *linkedExercise;
        currentWorkoutExercise.setExercise(linkedExercise);
    }

    currentWorkoutExercise.setWorkoutPlan(&currentWorkoutPlan);
    currentWorkoutExercise.setSets(sets);
    currentWorkoutExercise.setReps(reps);
    currentWorkoutExercise.setRestTime(restTime);
}

bool Client::hasBookedSession(int sessionId) const
{
    for (int i = 0; i < static_cast<int>(bookedSessionIds.size()); i++)
    {
        if (bookedSessionIds[i] == sessionId)
        {
            return true;
        }
    }

    return false;
}

void Client::initializeWorkoutData()
{
    cardioWorkout.setGoal("5km Run");
    cardioWorkout.setType("Cardio");
    cardioWorkout.setTarget(25);
    cardioWorkout.setDeadline("31/12/2026");
    cardioWorkout.setStatus("In Progress");

    currentExercise.setExercise("Strength");
    currentExercise.setName("Bench Press");
    currentExercise.setMuscleGroup("Chest");
    currentExercise.setEquipment("Barbell");
    currentExercise.setRating(5);

    currentWorkoutPlan.setPlan("WP101");
    currentWorkoutPlan.setName("Upper Body Builder");
    currentWorkoutPlan.setStartDate("22/04/2026");
    currentWorkoutPlan.setEndDate("22/06/2026");
    currentWorkoutPlan.addExercise(currentExercise);

    currentWorkoutExercise.setSets(4);
    currentWorkoutExercise.setReps(10);
    currentWorkoutExercise.setRestTime(90);
    syncWorkoutLinks();
}

void Client::syncWorkoutLinks()
{
    currentWorkoutExercise.setWorkoutPlan(&currentWorkoutPlan);

    Exercise* linkedExercise = currentWorkoutPlan.findExercise(currentExercise.getName());
    if (linkedExercise == nullptr)
    {
        if (currentWorkoutPlan.getExerciseCount() == 0)
        {
            currentWorkoutPlan.addExercise(currentExercise);
        }
        linkedExercise = currentWorkoutPlan.findExercise(currentExercise.getName());
    }

    if (linkedExercise != nullptr)
    {
        currentExercise = *linkedExercise;
        currentWorkoutExercise.setExercise(linkedExercise);
    }
}


// Registeration
void Client::registerAccount()
{
    bool validInput = false;

    while (!validInput)
    {
        try
        {
            line();
            cout << "           CLIENT REGISTRATION" << endl;
            line();

            User::registerAccount();

            cout << "Enter Height (cm): ";
            cin >> height;
            if (cin.fail() || height <= 0)
            {
                throw invalid_argument("Height must be a positive number.");
            }

            cout << "Enter Weight (kg): ";
            cin >> weight;
            if (cin.fail() || weight <= 0)
            {
                throw invalid_argument("Weight must be a positive number.");
            }

            cout << "Enter Goal: ";
            cin >> goal;
            if (goal.empty())
            {
                throw invalid_argument("Goal cannot be empty.");
            }

            validInput = true;
            cout << "\nAccount Successfully Created." << endl;
        }
        catch (const exception& ex)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nERROR: " << ex.what() << "\nPlease try again.\n\n";
        }
    }
}

// Client Menu
void Client::displayMenu()
{     
    User::displayMenu(); 
    cout << "  0) Logout" << endl;
    line();
    cout << "  Choice: "; 
    int choice;
    do
    { 
        cin >> choice;

        clearScreen();
    
        switch(choice) {
            case 1: displayDetails(); break;
            case 2: goalMenu(); break;
            case 3: workoutMenu(); break;
            case 4: sessionMenu(); break;
            case 0: return; break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }

    } 
    while (choice != 0);
    
}


// Profile Menu
void Client::displayDetails()
{
    int choice;
    do
    {
        clearScreen();
        User::displayDetails();
        cout << "  Height:        " << height << "cm" << endl;
        cout << "  Weight:        " << weight << "kg" << endl;

        line();
        cout << "  1) Edit Profile" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice){
            case 1: editProfile(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
    while (choice != 0);
}

void Client::displayClients() const
{
    cout << "===============================================================================\n";
    cout << "                                CLIENT DETAILS\n";
    cout << "===============================================================================\n";
    cout << " ID | Name                 | Goal\n";
    cout << "---------------------------------------------------\n";

    if (id < 10) cout << "  ";
    else if (id < 100) cout << ' ';
    cout << id << "  ";

    cout << name;
    for (int i = static_cast<int>(name.length()); i < 20; i++)
    {
        cout << ' ';
    }
    cout << ' ';

    cout << goal << endl;
    cout << "===============================================================================\n";
}


// Goal Menu
void Client::goalMenu()
{
    int choice;
    do
    {
        User::goalMenu();
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                clearScreen();
                displayGoals();
                break;

            case 2:
                clearScreen();
                {
                    Goal newGoal;
                    addGoal(newGoal);
                }
                break;

            case 3:
                clearScreen();
                editGoal();
                cin.get();
                break;

            case 4:
                clearScreen();
                removeGoal();
                break;

            case 0:
                clearScreen();
                displayMenu();
                break;

            default:
                cout << "\n*ERROR: Invalid Choice*\n";
                cin.get();
        }

    } while(choice != 0);
}


// Workout Menu
void Client::workoutMenu()
{
    int choice;
    do
    {
        line();
        cout << "           WORKOUT MENU" << endl;
        line();
        cout << "  1) View Workout Plans" << endl;
        cout << "  2) Create Workout Plan" << endl;
        cout << "  3) Edit Workout Plan" << endl;
        cout << "  4) Remove Workout Plan" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); displayWorkouts(); break;
            case 2: clearScreen(); createWorkout(); break;
            case 3: clearScreen(); editWorkout(); break;
            case 4: clearScreen(); removeWorkout(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
    while(choice != 0);
}

// Session Menu
void Client::sessionMenu()
{
    int choice;

    do
    {
        line();
        cout << "           SESSION MENU" << endl;
        line();

        cout << "  1) View Sessions" << endl;
        cout << "  2) Book Sessions" << endl;
        cout << "  3) Unbook Sessions" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();

        switch(choice)
        {
            case 1: viewSession(); break;
            case 2: bookSession(); break;
            case 3: unbookSession(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
    while(choice != 0);
}


// Edit Profile
void Client::editProfile()
{
    int choice;
    do
    {
        clearScreen();
        User::displayDetails();
        cout << "  Height:        " << height << "cm" << endl;
        cout << "  Weight:        " << weight << "kg" << endl;

        line();
        cout << "           EDIT PROFILE" << endl;
        line();

        cout << "  1) Name" << endl;
        cout << "  2) Password" << endl;
        cout << "  3) Email Address" << endl;
        cout << "  4) Phone Number" << endl;
        cout << "  5) Date of Birth" << endl;
        cout << "  6) Height" << endl;
        cout << "  7) Weight" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;   

        switch(choice)
        {
            case 1: 
            {
                string n;
                cout << "\nEnter a New Name: ";
                cin >> n;
                setName(n);
                break;
            }
            case 2: 
            {
                string p;
                cout << "\nEnter a New Password: ";
                cin >> p;
                setPassword(p);
                break;
            }
            case 3: 
            {
                string e;
                cout << "\nEnter a New Email Address: ";
                cin >> e;
                setEmail(e);
                break;
            }
            case 4: 
            {
                int ph;
                cout << "\nEnter a New Phone Number: ";
                cin >> ph;
                setPhone(ph);
                break;
            }
            case 5: 
            {
                int dd, dm, dy;
                cout << "\nEnter a New Date of Birth" << endl;
                getValidDate(dd,dm,dy);
                setDobDay(dd);
                setDobMonth(dm);
                setDobYear(dy);
                break;
            }
            case 6: 
            {   
                double h;
                cout << "\nEnter a New Height (cm): ";
                cin >> h;
                setHeight(h);
                break;
            }
            case 7: 
            {   
                double w;
                cout << "\nEnter a New Weight (kg): ";
                cin >> w;
                setWeight(w);
                break;
            }
            case 0: clearScreen(); displayMenu();

            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        } 

    } 
    while (choice != 0);
}


// Display Workouts
void Client::displayWorkouts()
{
    currentWorkoutPlan.viewPlanDetails();
}

void Client::displayCurrentWorkout() const
{
    string exerciseName = currentExercise.getName();
    string muscleGroup = currentExercise.getMuscleGroup();
    string equipment = currentExercise.getEquipment();
    string planName = currentWorkoutPlan.getName();
    string workoutSummary = to_string(currentWorkoutExercise.getSets()) + "x" + to_string(currentWorkoutExercise.getReps());
    string restSummary = to_string(currentWorkoutExercise.getRestTime()) + "s rest";

    cout << "=====================================================================================\n";
    cout << "                              CURRENT CLIENT WORKOUT\n";
    cout << "=====================================================================================\n";
    cout << " TYPE             | NAME                 | FOCUS / DATES         | DETAILS\n";
    cout << "-------------------------------------------------------------------------------------\n";

    cout << " Exercise         | " << exerciseName;
    for (int i = static_cast<int>(exerciseName.length()); i < 20; i++) cout << ' ';
    cout << " | " << muscleGroup;
    for (int i = static_cast<int>(muscleGroup.length()); i < 21; i++) cout << ' ';
    cout << " | " << equipment << endl;

    cout << " Workout Plan     | " << planName;
    for (int i = static_cast<int>(planName.length()); i < 20; i++) cout << ' ';
    cout << " | " << currentWorkoutPlan.getStartDate() << " - " << currentWorkoutPlan.getEndDate();
    for (int i = static_cast<int>((currentWorkoutPlan.getStartDate() + " - " + currentWorkoutPlan.getEndDate()).length()); i < 21; i++) cout << ' ';
    cout << " | " << currentWorkoutPlan.getPlan() << endl;

    cout << " Workout Exercise | " << exerciseName;
    for (int i = static_cast<int>(exerciseName.length()); i < 20; i++) cout << ' ';
    cout << " | " << workoutSummary;
    for (int i = static_cast<int>(workoutSummary.length()); i < 21; i++) cout << ' ';
    cout << " | " << restSummary << endl;

    cout << "=====================================================================================\n";
}

void Client::createWorkout()
{
    currentWorkoutPlan.createPlan();
}

// Edit Workouts
void Client::editWorkout()
{
    currentWorkoutPlan.editPlan();
}

void Client::removeWorkout()
{
    currentWorkoutPlan.removePlan();
}

// View Sessions
void Client::viewSession()
{
    if (!Session::hasSessions())
    {
        bookedSession->displaySession();
        return;
    }

    int choice;
    do
    {
        bookedSession->displaySession();
        cout << "  1) Book Session" << endl;
        cout << "  2) Unbook Session" << endl;
        cout << "  0) Return to Session Menu" << endl;
        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                clearScreen();
                bookSession();
                break;
                
            case 2:
                clearScreen();
                unbookSession();
                break;

            case 0:
                clearScreen();
                return;

            default:
                cout << "\n\n*ERROR: Invalid Choice*\n\n";
                break;
        } 
    }   
    while (choice != 0);
    
    clearScreen();
}


// Book Sessions
void Client::bookSession()
{
    if (!Session::hasSessions())
    {
        bookedSession->displaySession();
        return;
    }

    bookedSession->displaySession();

    int sessionId;
    cout << "Enter Session ID to book: ";
    cin >> sessionId;

    if (hasBookedSession(sessionId))
    {
        cout << "\nYou have already booked this session.\n\n";
        return;
    }

    if (bookedSession->bookSessionById(sessionId))
    {
        bookedSessionIds.push_back(sessionId);
    }
}


// Unbook Sessions
void Client::unbookSession()
{
    if (bookedSessionIds.empty())
    {
        cout << "\nYou're not booked in a session'.\n\n";
        return;
    }

    bookedSession->displaySession();

    int sessionId;
    cout << "Enter Session ID to unbook: ";
    cin >> sessionId;

    if (!hasBookedSession(sessionId))
    {
        cout << "\nYou have not booked that session.\n\n";
        return;
    }

    if (bookedSession->unbookSessionById(sessionId))
    {
        for (int i = 0; i < static_cast<int>(bookedSessionIds.size()); i++)
        {
            if (bookedSessionIds[i] == sessionId)
            {
                bookedSessionIds.erase(bookedSessionIds.begin() + i);
                break;
            }
        }
    }
}

void Client::displayGoal()
{
    int choice;
    clearScreen();
    currentGoal->displayGoal();
    cout << "  1) Edit Goal\n";
    cout << "  2) Update Progress\n";
    cout << "  3) Remove Goal\n";
    cout << "  0) Return to Goal Menu\n";
    cout << "  Choice: ";
    cin >> choice;
    switch(choice)
    {
        case 1: clearScreen(); editGoal();         break;
        case 2: clearScreen(); updateProgress();   break;
        case 3: clearScreen(); removeGoal();       break;
        case 0: clearScreen(); goalMenu();         break;
        default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
    }
}

void Client::displayGoals()
{
    if (clientGoals.empty())
    {
        line();
        cout << "           GOAL DETAILS" << endl;
        line();
        cout << " No goals available.\n\n";
        line();
    }
    else
    {
        printClientGoalTable(clientGoals);
    }

    cout << "  1) Edit Goal\n";
    cout << "  2) Update Progress\n";
    cout << "  3) Remove Goal\n";
    cout << "  0) Return to Goal Menu\n";
    cout << "  Choice: ";
    int choice;
    cin >> choice;
    switch(choice)
    {
        case 1: clearScreen(); editGoal();          break;
        case 2: clearScreen(); updateProgress();    break;
        case 3: clearScreen(); removeGoal();        break;
        case 0: clearScreen(); return;
        default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
    }
}

void Client::updateProgress()
{
    if (clientGoals.empty())
    {
        cout << "\nNo goals available to update.\n";
        return;
    }

    int goalId;
    cout << "Enter Goal ID to update progress (0 to return): ";
    cin >> goalId;

    if (goalId == 0)
    {
        return;
    }

    for (int i = 0; i < static_cast<int>(clientGoals.size()); i++)
    {
        if (clientGoals[i].getId() == goalId)
        {
            const string unit = (clientGoals[i].getType() == "Cardio") ? "minutes" : "kg";
            double newValue;

            do
            {
                newValue = currentGoal->getValidPositiveDouble("Enter New Personal Best [" + unit + "]: ");
                if (newValue <= clientGoals[i].getCurrentPR())
                {
                    cout << "Error: New PR must be greater than current PR ("
                         << clientGoals[i].getCurrentPR() << ' ' << unit << "). Please try again.\n";
                }
            }
            while (newValue <= clientGoals[i].getCurrentPR());

            clientGoals[i].setNewPR(newValue);
            clientGoals[i].checkProgress();
            *currentGoal = clientGoals[i];
            return;
        }
    }

    cout << "\nERROR: Goal not found.\n";
}

void Client::updateDeadline()
{
    currentGoal->updateDeadline();
}

void Client::updateStatus()
{
    currentGoal->updateStatus();
}

void Client::checkProgress()
{
    currentGoal->checkProgress();
}

void Client::addGoal(const Goal& goal)
{
    if (!goal.getGoal().empty())
    {
        setCurrentGoal(goal);
        return;
    }

    currentGoal->addGoal(goal);
    setCurrentGoal(*currentGoal);
}

void Client::editGoal()
{
    if (clientGoals.empty())
    {
        cout << "\nNo goals available to edit.\n";
        return;
    }

    int goalId;
    printClientGoalTable(clientGoals);
    cout << "Enter Goal ID to edit (0 to return): ";
    cin >> goalId;

    if (goalId == 0)
    {
        return;
    }

    Goal* selectedGoal = nullptr;
    for (int i = 0; i < static_cast<int>(clientGoals.size()); i++)
    {
        if (clientGoals[i].getId() == goalId)
        {
            selectedGoal = &clientGoals[i];
            break;
        }
    }

    if (selectedGoal == nullptr)
    {
        cout << "\nERROR: Goal not found.\n";
        return;
    }

    int choice;
    do
    {
        clearScreen();
        selectedGoal->displayGoal();
        cout << "  1) Goal Name" << endl;
        cout << "  2) Starting PR" << endl;
        cout << "  3) Target" << endl;
        cout << "  4) Latest PR" << endl;
        cout << "  5) Deadline" << endl;
        cout << "  0) Return to Goal Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string newGoalName;
                do
                {
                    cout << "\nEnter a New Goal: ";
                    getline(cin, newGoalName);
                }
                while (newGoalName.empty());

                selectedGoal->setGoal(newGoalName);
                selectedGoal->setType(selectedGoal->setType());
                break;
            }
            case 2:
            {
                string unit = (selectedGoal->getType() == "Cardio") ? "minutes" : "kg";
                double pr = currentGoal->getValidPositiveDouble("\nEnter a New Starting PR [" + unit + "]: ");
                selectedGoal->setCurrentPR(pr);
                break;
            }
            case 3:
            {
                string unit = (selectedGoal->getType() == "Cardio") ? "minutes" : "kg";
                double targetValue;
                do
                {
                    targetValue = currentGoal->getValidPositiveDouble("\nEnter a New Target [" + unit + "]: ");
                    if (targetValue <= selectedGoal->getCurrentPR())
                    {
                        cout << "ERROR: Target must be greater than the starting PR.\n";
                    }
                }
                while (targetValue <= selectedGoal->getCurrentPR());
                selectedGoal->setTarget(targetValue);
                break;
            }
            case 4:
            {
                string unit = (selectedGoal->getType() == "Cardio") ? "minutes" : "kg";
                double pr = currentGoal->getValidPositiveDouble("\nEnter a New Latest PR [" + unit + "]: ");
                selectedGoal->setNewPR(pr);
                selectedGoal->checkProgress();
                break;
            }
            case 5:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                char timePeriod = currentGoal->getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
                int amount = 0;

                switch (timePeriod)
                {
                    case 'D': amount = currentGoal->getValidPositiveInt("Enter number of day(s): "); break;
                    case 'M': amount = currentGoal->getValidPositiveInt("Enter number of month(s): "); break;
                    case 'Y': amount = currentGoal->getValidPositiveInt("Enter number of year(s): "); break;
                }

                string deadline;
                if (timePeriod == 'D') deadline = to_string(amount) + (amount == 1 ? " day" : " days");
                if (timePeriod == 'M') deadline = to_string(amount) + (amount == 1 ? " month" : " months");
                if (timePeriod == 'Y') deadline = to_string(amount) + (amount == 1 ? " year" : " years");

                selectedGoal->setDeadline(deadline);
                break;
            }
            case 0:
                *currentGoal = *selectedGoal;
                return;
            default:
                cout << "\n\n*ERROR: Invalid Choice*\n\n";
                break;
        }
    }
    while (choice != 0);
}

void Client::removeGoal()
{
    if (clientGoals.empty())
    {
        cout << "\nNo goals available to remove.\n";
        return;
    }

    int goalId;
    printClientGoalTable(clientGoals);
    cout << "Enter the Goal ID to remove: ";
    cin >> goalId;

    for (int i = 0; i < static_cast<int>(clientGoals.size()); i++)
    {
        if (clientGoals[i].getId() == goalId)
        {
            char confirm;
            cout << "\nAre you sure you want to remove this goal? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                clientGoals.erase(clientGoals.begin() + i);
                if (clientGoals.empty())
                {
                    *currentGoal = Goal();
                }
                else
                {
                    *currentGoal = clientGoals.back();
                }
                cout << "\nGoal removed successfully.\n\n";
            }
            else
            {
                cout << "\nGoal removal cancelled.\n";
            }
            return;
        }
    }

    cout << "\nERROR: Goal not found.\n";
}
// UI
void Client::clearScreen() 
{ 
    User::clearScreen(); 
}

void Client::line() 
{ 
    User::line(); 
}

void Client::lineLong()
{
    User::lineLong();
}

void Client::dashedLine()
{
    User::dashedLine();
}

