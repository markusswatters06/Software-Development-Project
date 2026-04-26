#include "Trainer.h"
#include "Client.h"
#include <limits>

namespace {
void printTrainerGoalTable(const vector<Goal>& goals)
{
    cout << "=====================================================================================\n";
    cout << "                                      TRAINER GOALS\n";
    cout << "=====================================================================================\n";
    cout << " ID | Goal Name            | Type      | Target      | Deadline        | Status\n";
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
        cout << "  " << goal.getStatus() << endl;
    }

    cout << "=====================================================================================\n";
}
}

Trainer::Trainer()
    : bio("N/A"), cert("N/A"), rating(0.0), yearsExp(0), clients(0), sessionsPerWeek(0), sessionRate(0.0), availablility("N/A"),
      trainerGoal(new Goal()), trainerWorkout(new WorkoutPlan())
{}

Trainer::Trainer(string b, string c, double r, int ye, int cl, int spw, double sr, string a)
    : bio(b), cert(c), rating(r), yearsExp(ye), clients(cl), sessionsPerWeek(spw), sessionRate(sr), availablility(a),
      trainerGoal(new Goal()), trainerWorkout(new WorkoutPlan())
{}

Trainer::~Trainer()
{
    for (int i = 0; i < static_cast<int>(ownedClients.size()); i++)
    {
        delete ownedClients[i];
    }

    delete trainerGoal;
    delete trainerWorkout;
}

bool Trainer::isClientAssigned(int clientId) const
{
    for (int i = 0; i < static_cast<int>(assignedClients.size()); i++)
    {
        if (assignedClients[i] != nullptr && assignedClients[i]->getId() == clientId)
        {
            return true;
        }
    }

    return false;
}

void Trainer::printAvailableClientsTable() const
{
    cout << "==========================================================================\n";
    cout << "                            AVAILABLE CLIENTS\n";
    cout << "==========================================================================\n";

    bool hasAvailableClients = false;

    for (int i = 0; i < static_cast<int>(ownedClients.size()); i++)
    {
        if (ownedClients[i] != nullptr && !isClientAssigned(ownedClients[i]->getId()))
        {
            hasAvailableClients = true;
            break;
        }
    }

    if (!hasAvailableClients)
    {
        cout << " No available clients.\n";
    }
    else
    {
        cout << " ID | Name                 | Goal\n";
        cout << "--------------------------------------------------------------------------\n";

        for (int i = 0; i < static_cast<int>(ownedClients.size()); i++)
        {
            if (ownedClients[i] != nullptr && !isClientAssigned(ownedClients[i]->getId()))
            {
                Client* client = ownedClients[i];

                if (client->getId() < 10) cout << "  ";
                else if (client->getId() < 100) cout << ' ';
                cout << client->getId() << " | ";

                cout << client->getName();
                for (int j = static_cast<int>(client->getName().length()); j < 20; j++)
                {
                    cout << ' ';
                }
                cout << "| ";

                cout << client->getGoal() << endl;
            }
        }
    }

    cout << "==========================================================================\n";
}

Trainer& Trainer::operator+=(Client& client)
{
    assignClients(client);
    return *this;
}

bool Trainer::operator==(const Trainer& other) const
{
    return id == other.id;
}

ostream& operator<<(ostream& os, const Trainer& trainer)
{
    os << "Trainer[" << trainer.id << "] " << trainer.name
       << " | Experience: " << trainer.yearsExp << " years"
       << " | Clients: " << trainer.clients
       << " | Rate: " << trainer.sessionRate;
    return os;
}

void Trainer::setCurrentGoal(const Goal &newGoal)
{
        *trainerGoal = newGoal;

    for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
    {
        if (trainGoals[i].getId() == newGoal.getId())
        {
            trainGoals[i] = newGoal;
            return;
        }
    }

    trainGoals.push_back(newGoal);
}

// Register Account
void Trainer::registerAccount()
{
    bool validInput = false;

    while (!validInput)
    {
        try
        {
            line();
            cout << "           TRAINER REGISTRATION" << endl;
            line();

            User::registerAccount();

            cout << "Enter Bio: ";
            cin >> bio;
            if (bio.empty()) {
                throw invalid_argument("Bio cannot be empty.");
            }

            cout << "Enter Certification: ";
            cin >> cert;
            if (cert.empty()) {
                throw invalid_argument("Certification cannot be empty.");
            }

            cout << "Enter Years Experience: ";
            cin >> yearsExp;
            if (cin.fail() || yearsExp < 0) {
                throw invalid_argument("Years of experience cannot be negative.");
            }

            cout << "Enter Session Rate: ";
            cin >> sessionRate;
            if (cin.fail() || sessionRate < 0) {
                throw invalid_argument("Session rate cannot be negative.");
            }

            cout << "Enter Availability: ";
            cin >> availablility;
            if (availablility.empty()) {
                throw invalid_argument("Availability cannot be empty.");
            }

            rating = 0.0;
            clients = 0;
            sessionsPerWeek = 0;
            validInput = true;

            cout << "\nTrainer Account Created Successfully!\n";
        }
        catch (const exception& ex)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nERROR: " << ex.what() << "\nPlease try again.\n\n";
        }
    }
}

// Menu
// Main Menu
void Trainer::displayMenu()
{
    User::displayMenu();
    cout << "  5) Client Menu" << endl;
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
            case 5: clientMenu(); break;
            case 0: return; break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }

    } 
    while (choice != 0);
}

// Profile Menu
void Trainer::displayDetails()
{
    int choice;
    do
    {
        clearScreen();
        printProfileDetails();

        line();
        cout << "  1) Edit Profile" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice){
            case 1: editProfile(); break;
            case 0: clearScreen();displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
    while (choice != 0);
}


// Client Menu
void Trainer::clientMenu()
{
    int choice;

    do
    {
        line();
        cout << "           CLIENT MENU" << endl;
        line();

        cout << "  1) View Available Clients" << endl;
        cout << "  2) View Assigned Clients" << endl;
        cout << "  3) Assign Clients" << endl;
        cout << "  4) Remove Clients" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); displayClients(); break;
            case 2: clearScreen(); displayAssignedClients(); break;
            case 3: clearScreen(); assignClients(); break;
            case 4: clearScreen(); removeClients(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n"; break;
        }
    }
    while (choice != 0);
}

// Session Menu
void Trainer::sessionMenu()
{
    int choice;
    do
    {
        line();
        cout << "           SESSION MENU" << endl;
        line();

        cout << "  1) View Sessions" << endl;
        cout << "  2) Create Session" << endl;
        cout << "  3) Remove Session" << endl;
        cout << "  4) Edit Session" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); displaySession(); break;
            case 2: clearScreen(); createSession(); break;
            case 3: clearScreen(); removeSession(); break;
            case 4: clearScreen(); editSession(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n"; break;
        }  
    }
    while (choice != 0);
}

// Workout Menu
void Trainer::workoutMenu()
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
        cout << "  5) View Client Workouts" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); displayWorkouts(); break;
            case 2: clearScreen(); createWorkout(); break;
            case 3: clearScreen(); editWorkout(); break;
            case 4: clearScreen(); removeWorkout(); break;
            case 5: clearScreen(); displayClientWorkouts(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n"; break;
        }  
    }
    while (choice != 0);
}

// Progress Menu
void Trainer::goalMenu()
{
    int choice;

    do
    {
        User::goalMenu();
        cout << "  5) View Client Goals" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();
        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); displayGoals(); break;
            case 2:
            {
                clearScreen();
                Goal newGoal;
                addGoal(newGoal);
                break;
            }
            case 3: clearScreen(); editGoal(); break;
            case 4: clearScreen(); removeGoal(); break;
            case 5: clearScreen(); displayClientGoals(); break;
            case 0: clearScreen(); displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n"; break;
        }  
    }
    while (choice != 0);
}


// Edit Profile
void Trainer::editProfile()
{
    int choice;

    do
    {
        clearScreen();
        printProfileDetails();

        line();
        cout << "           EDIT PROFILE" << endl;
        line();

        cout << "  1) Name" << endl;
        cout << "  2) Password" << endl;
        cout << "  3) Email Address" << endl;
        cout << "  4) Phone Number" << endl;
        cout << "  5) Date of Birth" << endl;
        cout << "  6) Years of Experience" << endl;
        cout << "  7) Certificates" << endl;
        cout << "  8) Rating" << endl;
        cout << "  9) Availability Per Week" << endl;
        cout << " 10) Bio" << endl;
        cout << "  0) Return to Main Menu" << endl;
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
                int y;
                cout << "\nEnter New Year: ";
                cin >> y;
                setYearsExp(y);
                break;
            }
            case 7:
            {
                string c;
                cout << "\nEnter New Certificate: ";
                cin >> c;
                setCert(c);
                break;
            }
            case 8:
            {
                double r;
                cout << "\nEnter New Rating: ";
                cin >> r;
                setRating(r);
                break;
            }
            case 9:
            {
                int swp;
                cout << "\nEnter New Availability: ";
                cin >> swp;
                setSessionsPerWeek(swp);
                break;
            }
            case 10:
            {
                string b;
                cout << "\n Enter New Bio: ";
                cin >> b;
                setBio(b);
                break;
            }
            case 0: clearScreen(); displayDetails();

            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        } 

    } 
    while (choice != 0);
}

void Trainer::printProfileDetails() const
{
    const_cast<Trainer*>(this)->User::displayDetails();
    cout << "  Years of Experience: " << yearsExp << endl;
    cout << "  Certificates: " << cert << endl;
    cout << "  Rating: " << rating << endl;
    cout << "  Availability Per Week: " << sessionsPerWeek << endl;
    line();
    cout << bio << endl;
}

void Trainer::assignClients()
{
    bool hasAvailableClients = false;

    for (int i = 0; i < static_cast<int>(ownedClients.size()); i++)
    {
        if (ownedClients[i] != nullptr && !isClientAssigned(ownedClients[i]->getId()))
        {
            hasAvailableClients = true;
            break;
        }
    }

    if (!hasAvailableClients)
    {
        cout << "\nNo available clients to assign.\n\n";
        return;
    }

    printAvailableClientsTable();

    int clientId;
    cout << "Enter Client ID to assign (0 to return): ";
    cin >> clientId;

    if (clientId == 0)
    {
        clearScreen();
        return;
    }

    for (int i = 0; i < static_cast<int>(ownedClients.size()); i++)
    {
        if (ownedClients[i] != nullptr && ownedClients[i]->getId() == clientId)
        {
            if (isClientAssigned(clientId))
            {
                cout << "\nThat client is already assigned.\n\n";
                return;
            }

            try
            {
                *this += *ownedClients[i];
                cout << "\nClient assigned successfully." << endl;
                cout << "Total assigned clients: " << clients << "\n\n";
            }
            catch (const exception& ex)
            {
                cout << "\nERROR: " << ex.what() << "\n\n";
            }

            return;
        }
    }

    cout << "\nERROR: Client not found.\n\n";
}

void Trainer::assignClients(Client& client)
{
    string clientName = client.getName();

    if (clientName.empty())
    {
        throw invalid_argument("Client name cannot be empty.");
    }

    for (int i = 0; i < assignedClients.size(); i++)
    {
        if (assignedClients[i] != nullptr && assignedClients[i]->getName() == clientName)
        {
            throw runtime_error(clientName + " is already assigned to this trainer.");
        }
    }

    assignedClients.push_back(&client);
    clients = static_cast<int>(assignedClients.size());
}

void Trainer::displayClients()
{
    int choice;

    printAvailableClientsTable();
    cout << "  1) Assign Client\n";
    cout << "  0) Return to Client Menu\n";
    cout << "  Choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            clearScreen();
            assignClients();
            break;

        case 0:
            clearScreen();
            clientMenu();
            break;

        default:
            cout << "\n\n*ERROR: Invalid Choice*\n\n";
            break;
    }
}

void Trainer::addAvailableClient(const Client& client)
{
    Client* storedClient = new Client(client);
    ownedClients.push_back(storedClient);
}

void Trainer::displayAssignedClients() const
{
    cout << "==========================================================================\n";
    cout << "                            ASSIGNED CLIENTS\n";
    cout << "==========================================================================\n";

    if (assignedClients.empty())
    {
        cout << " No assigned clients.\n\n";
    }
    else
    {
        cout << " ID | Name                 | Goal\n";
        cout << "--------------------------------------------------------------------------\n";

        for (int i = 0; i < assignedClients.size(); i++)
        {
            if (assignedClients[i] != nullptr)
            {
                Client* client = assignedClients[i];

                if (client->getId() < 10) cout << "  ";
                else if (client->getId() < 100) cout << ' ';
                cout << client->getId() << " | ";

                cout << client->getName();
                for (int j = static_cast<int>(client->getName().length()); j < 20; j++)
                {
                    cout << ' ';
                }
                cout << "| ";

                cout << client->getGoal() << endl;
            }
        }
    }

    cout << "==========================================================================\n";
}

void Trainer::removeClients()
{
    if (assignedClients.empty())
    {
        cout << "\nNo assigned clients to remove.\n\n";
        return;
    }

    displayAssignedClients();

    int clientId;
    cout << "Enter Client ID to remove (0 to return): ";
    cin >> clientId;

    if (clientId == 0)
    {
        clearScreen();
        return;
    }

    for (int i = 0; i < static_cast<int>(assignedClients.size()); i++)
    {
        if (assignedClients[i] != nullptr && assignedClients[i]->getId() == clientId)
        {
            string clientName = assignedClients[i]->getName();
            assignedClients.erase(assignedClients.begin() + i);
            clients = static_cast<int>(assignedClients.size());

            cout << "\nClient removed successfully: " << clientName << endl;
            cout << "Total assigned clients: " << clients << "\n\n";
            return;
        }
    }

    cout << "\nERROR: Assigned client not found.\n\n";
}

// Create Session
void Trainer::createSession()
{
    trainerSession.createSession();
}

// Remove Session
void Trainer::removeSession()
{
    trainerSession.removeSession();
}

// View Session
void Trainer::displaySession()
{
    int choice;

    do
    {
        trainerSession.displaySession();
        cout << "  1) Edit Session" << endl;
        cout << "  0) Return to Session Menu" << endl;
        cout << "  Choice: ";
        cin >> choice;
        switch(choice)
        {
        case 1: clearScreen(); editSession(); break;
        case 0: clearScreen(); sessionMenu(); break;
        default: cout << "\n\n*ERROR: Invalid Choice*\n\n"; break;
        }
    }
    while (choice != 0);
}

// Edit Session
void Trainer::editSession()
{
    trainerSession.editSession();
}


// Goals
//Add Goal
void Trainer::addGoal(const Goal& goal)
{
    if (!goal.getGoal().empty())
    {
        setCurrentGoal(goal);
        return;
    }

    trainerGoal->addGoal(goal);

    if (!trainerGoal->getGoal().empty())
    {
        setCurrentGoal(*trainerGoal);
    }
}

// Remove Goal
void Trainer::removeGoal()
{
    if (trainGoals.empty())
    {
        cout << "\nNo trainer goals available to remove.\n";
        return;
    }

    lineLong();
    cout << "                                      TRAINER GOALS\n";
    lineLong();
    cout << " ID | Goal Name            | Type      | Target      | Deadline        | Status\n";
    dashedLine();

    for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
    {
        const Goal& goal = trainGoals[i];

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
        cout << "  " << goal.getStatus() << endl;
    }

    lineLong();

    int goalId;
    cout << "Enter the Goal ID to remove: ";
    cin >> goalId;

    for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
    {
        if (trainGoals[i].getId() == goalId)
        {
            char confirm;
            cout << "\nAre you sure you want to remove this goal? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {
                trainGoals.erase(trainGoals.begin() + i);
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

// Display Goal
void Trainer::displayGoal()
{
    trainerGoal->displayGoal();
}

// Display Goals
void Trainer::displayGoals()
{
    int choice;

    do
    {
        clearScreen();
        if (trainGoals.empty())
        {
            line();
            cout << "           GOAL DETAILS" << endl;
            line();
            cout << " No trainer goals available.\n\n";
            line();
        }
        else
        {
            lineLong();
            cout << "                                      TRAINER GOALS\n";
            lineLong();
            cout << " ID | Goal Name            | Type      | Target      | Deadline        | Status\n";
            dashedLine();

            for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
            {
                const Goal& goal = trainGoals[i];

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
                cout << "  " << goal.getStatus() << endl;
            }

            lineLong();
        }
        cout << "  1) Edit Goal\n";
        cout << "  2) Remove Goal\n";
        cout << "  0) Return to Goal Menu\n";
        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: clearScreen(); editGoal();          break;
            case 2: clearScreen(); removeGoal();        break;
            case 0: clearScreen(); goalMenu();          break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
    while (choice != 0);
}

void Trainer::displayClientGoals()
{
    if (assignedClients.empty())
    {
        cout << "\nNo assigned clients available.\n\n";
        return;
    }

    displayAssignedClients();

    int clientId;
    cout << "Enter Client ID to view goals (0 to return): ";
    cin >> clientId;

    if (clientId == 0)
    {
        return;
    }

    Client* selectedClient = nullptr;
    for (int i = 0; i < static_cast<int>(assignedClients.size()); i++)
    {
        if (assignedClients[i] != nullptr && assignedClients[i]->getId() == clientId)
        {
            selectedClient = assignedClients[i];
            break;
        }
    }

    if (selectedClient == nullptr)
    {
        cout << "\nERROR: Assigned client not found.\n\n";
        return;
    }

    const vector<Goal>& clientGoals = selectedClient->getClientGoals();

    clearScreen();
    lineLong();
    cout << "                             GOALS FOR " << selectedClient->getName() << "\n";
    lineLong();

    if (clientGoals.empty())
    {
        clearScreen();
        cout << " No goals assigned to this client.\n\n";
        displayAssignedClients();
    }

    cout << " ID | Goal Name            | Type      | Target      | Deadline        | Status\n";
    dashedLine();

    for (int i = 0; i < static_cast<int>(clientGoals.size()); i++)
    {
        const Goal& goal = clientGoals[i];

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
        cout << "  " << goal.getStatus() << endl;
    }

    lineLong();
    cout << "\nPress Enter to return...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Update Progress
void Trainer::updateProgress()
{
    if (trainGoals.empty())
    {
        cout << "\nNo trainer goals available to update.\n";
        return;
    }

    int goalId;
    cout << "Enter Goal ID to update progress (0 to return): ";
    cin >> goalId;

    if (goalId == 0)
    {
        return;
    }

    for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
    {
        if (trainGoals[i].getId() == goalId)
        {
            const string unit = (trainGoals[i].getType() == "Cardio") ? "minutes" : "kg";
            double newValue;

            do
            {
                newValue = trainerGoal->getValidPositiveDouble("Enter New Personal Best [" + unit + "]: ");
                if (newValue <= trainGoals[i].getCurrentPR())
                {
                    cout << "Error: New PR must be greater than current PR ("
                         << trainGoals[i].getCurrentPR() << ' ' << unit << "). Please try again.\n";
                }
            }
            while (newValue <= trainGoals[i].getCurrentPR());

            trainGoals[i].setNewPR(newValue);
            trainGoals[i].checkProgress();
            cout << "Progress updated successfully!\n";
            return;
        }
    }

    cout << "\nERROR: Goal not found.\n";
}

// Update Deadline
void Trainer::updateDeadline(){trainerGoal->updateDeadline();}

// Update Status
void Trainer::updateStatus(){trainerGoal->updateStatus();}

// Check Progress
void Trainer::checkProgress(){trainerGoal->checkProgress();}

void Trainer::displayWorkouts(){trainerWorkout->viewPlanDetails();}

void Trainer::createWorkout(){trainerWorkout->createPlan();}

void Trainer::editWorkout(){trainerWorkout->editPlan();}

void Trainer::removeWorkout(){trainerWorkout->removePlan();}

void Trainer::displayClientWorkouts()
{
    if (assignedClients.empty())
    {
        cout << "\nNo assigned clients available.\n\n";
        return;
    }

    displayAssignedClients();

    int clientId;
    cout << "Enter Client ID to view workout (0 to return): ";
    cin >> clientId;

    if (clientId == 0)
    {
        return;
    }

    Client* selectedClient = nullptr;
    for (int i = 0; i < static_cast<int>(assignedClients.size()); i++)
    {
        if (assignedClients[i] != nullptr && assignedClients[i]->getId() == clientId)
        {
            selectedClient = assignedClients[i];
            break;
        }
    }

    if (selectedClient == nullptr)
    {
        cout << "\nERROR: Assigned client not found.\n\n";
        return;
    }

    clearScreen();
    cout << "Client: " << selectedClient->getName() << "\n";
    selectedClient->displayCurrentWorkout();
    cout << "Press Enter to return...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Edit Goal
void Trainer::editGoal()
{
    if (trainGoals.empty())
    {
        cout << "\nNo trainer goals available to edit.\n";
        return;
    }

    int goalId;
    printTrainerGoalTable(trainGoals);
    cout << "Enter Goal ID to edit (0 to return): ";
    cin >> goalId;

    if (goalId == 0)
    {
        return;
    }

    Goal* selectedGoal = nullptr;
    for (int i = 0; i < static_cast<int>(trainGoals.size()); i++)
    {
        if (trainGoals[i].getId() == goalId)
        {
            selectedGoal = &trainGoals[i];
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
                double pr = trainerGoal->getValidPositiveDouble("\nEnter a New Starting PR [" + unit + "]: ");
                selectedGoal->setCurrentPR(pr);
                break;
            }
            case 3:
            {
                string unit = (selectedGoal->getType() == "Cardio") ? "minutes" : "kg";
                double targetValue;
                do
                {
                    targetValue = trainerGoal->getValidPositiveDouble("\nEnter a New Target [" + unit + "]: ");
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
                double pr = trainerGoal->getValidPositiveDouble("\nEnter a New Latest PR [" + unit + "]: ");
                selectedGoal->setNewPR(pr);
                selectedGoal->checkProgress();
                break;
            }
            case 5:
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                char timePeriod = trainerGoal->getValidCharInput("[D] Day(s)  [M] Month(s)  [Y] Year(s): ", "DMY");
                int amount = 0;

                switch (timePeriod)
                {
                    case 'D': amount = trainerGoal->getValidPositiveInt("Enter number of day(s): "); break;
                    case 'M': amount = trainerGoal->getValidPositiveInt("Enter number of month(s): "); break;
                    case 'Y': amount = trainerGoal->getValidPositiveInt("Enter number of year(s): "); break;
                }

                string deadline;
                if (timePeriod == 'D') deadline = to_string(amount) + (amount == 1 ? " day" : " days");
                if (timePeriod == 'M') deadline = to_string(amount) + (amount == 1 ? " month" : " months");
                if (timePeriod == 'Y') deadline = to_string(amount) + (amount == 1 ? " year" : " years");

                selectedGoal->setDeadline(deadline);
                break;
            }
            case 0:
                return;
            default:
                cout << "\n\n*ERROR: Invalid Choice*\n\n";
                break;
        }
    }
    while (choice != 0);
}


// UI
void Trainer::clearScreen() 
{ 
    for(int i = 0; i < 40; i++) 
    cout << endl; 
}

void Trainer::line() const
{ 
    cout << "========================================\n"; 
}

void Trainer::lineLong(){User::lineLong();}

void Trainer::dashedLine(){User::dashedLine();}
