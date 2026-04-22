#include "Trainer.h"
#include "Client.h"
#include <limits>

Trainer::Trainer()
    : bio("N/A"), cert("N/A"), rating(0.0), yearsExp(0), clients(0), sessionsPerWeek(0), sessionRate(0.0), availablility("N/A")
{}

Trainer::Trainer(string b, string c, double r, int ye, int cl, int spw, double sr, string a)
    : bio(b), cert(c), rating(r), yearsExp(ye), clients(cl), sessionsPerWeek(spw), sessionRate(sr), availablility(a)
{}

Trainer::~Trainer()
{
    for (int i = 0; i < ownedClients.size(); i++)
    {
        delete ownedClients[i];
    }
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
        cout << " ID | Name                 | Membership      | Goal\n";
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

                cout << client->getMembershipType();
                for (int j = static_cast<int>(client->getMembershipType().length()); j < 15; j++)
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
    int choice;
    do
    {
        line();
        cout << "           TRAINER MENU" << endl;

        line();
        cout << "  1) Profile" << endl;
        cout << "  2) Client Menu" << endl;
        cout << "  3) Session Menu" << endl;
        cout << "  4) Workout Menu" << endl;
        cout << "  5) Progress Menu" << endl;
        cout << "  0) Logout" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();

        switch (choice)
        {
        case 1: displayDetails(); break;
        case 2: clientMenu(); break;
        case 3: sessionMenu(); break;
        case 4: workoutMenu(); break;
        case 5: progressMenu(); break;
        case 0: displayMenu(); break;
        default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    } while (choice != 5); 
}

// Profile Menu
void Trainer::displayDetails()
{
    int choice;
    do
    {
        line();
        cout << "           ACCOUNT DETAILS\n";
        line();

        //cout << "  Member ID:     " << id << endl;
        cout << "  Name:          " << name << endl;
        cout << "  Password:      " << password << endl;
        cout << "  Email Address: " << email << endl;
        cout << "  Phone Number:  0" << phone << endl;
        cout << "  Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
        line();
        cout << "  Years of Experience: " << yearsExp << endl;
        cout << "  Certificates: " << cert << endl;
        cout << "  Rating: " << rating << endl;
        cout << "  Availability Per Week: " << sessionsPerWeek << endl;
        line();
        cout << bio << endl;

        line();
        cout << "  1) Edit Profile" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();

        switch(choice){
            case 1: editProfile(); break;
            case 0: displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
        while (choice != 2);
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
            case 0: clearScreen(); break;
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
    line();
    cout << "           WORKOUT MENU" << endl;
    line();

    do
    {
        cout << "  1) View Workouts" << endl;
        cout << "  2) Create Workout" << endl;
        cout << "  3) Remove Workout" << endl;
        cout << "  4) Edit Workout" << endl;
        cout << "  5) Assign Workout to Client" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 0: clearScreen(); displayMenu(); break;
        }  
    }
    while (choice != 5);
}

// Progress Menu
void Trainer::progressMenu()
{
    int choice;
    line();
    cout << "           PROGRESS MENU" << endl;
    line();

    do
    {
        cout << "  1) View Client Progress" << endl;
        cout << "  2) Create Goal" << endl;
        cout << "  3) Remove Goal" << endl;
        cout << "  4) Edit Goals" << endl;
        cout << "  5) Assign Goals to Clients" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 0: clearScreen(); displayMenu(); break;
        }  
    }
    while (choice != 5);
}


// Edit Profile
void Trainer::editProfile()
{
    int choice;

    do
    {
        line();
        cout << "           ACCOUNT DETAILS\n";
        line();

        cout << "  Member ID:     " << id << endl;
        cout << "  Name:          " << name << endl;
        cout << "  Password:      " << password << endl;
        cout << "  Email Address: " << email << endl;
        cout << "  Phone Number:  0" << phone << endl;
        cout << "  Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
        line();
        cout << "  Years of Experience: " << yearsExp << endl;
        cout << "  Certificates: " << cert << endl;
        cout << "  Rating: " << rating << endl;
        cout << "  Availability Per Week: " << sessionsPerWeek << endl;
        line();
        cout << bio << endl;

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
        cout << " 11) Return to Profile Menu" << endl;
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
                clearScreen();
                break;
            }
            case 2: 
            {
                string p;
                cout << "\nEnter a New Password: ";
                cin >> p;
                setPassword(p);
                clearScreen();
                break;
            }
            case 3: 
            {
                string e;
                cout << "\nEnter a New Email Address: ";
                cin >> e;
                setEmail(e);
                clearScreen();
                break;
            }
            case 4: 
            {
                int ph;
                cout << "\nEnter a New Phone Number: ";
                cin >> ph;
                setPhone(ph);
                clearScreen();
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
                clearScreen();
                break;
            }
            case 6: 
            {   
                int y;
                cout << "\nEnter New Year: ";
                cin >> y;
                setYearsExp(y);
                clearScreen();
                break;
            }
            case 7:
            {
                string c;
                cout << "\nEnter New Certificate: ";
                cin >> c;
                setCert(c);
                clearScreen();
                break;
            }
            case 8:
            {
                double r;
                cout << "\nEnter New Rating: ";
                cin >> r;
                setRating(r);
                clearScreen();
                break;
            }
            case 9:
            {
                int swp;
                cout << "\nEnter New Availability: ";
                cin >> swp;
                setSessionsPerWeek(swp);
                clearScreen();
                break;
            }
            case 10:
            {
                string b;
                cout << "\n Enter New Bio: ";
                cin >> b;
                setBio(b);
                clearScreen();
                break;
            }
            case 11:
            {
                cout <<"\nReturning to Profile Menu...." << endl;
                clearScreen();
                displayDetails();
                break;
            }
            case 0: 
            {
                clearScreen();
                displayMenu();  
                break;
            }

            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        } 

    } 
    while (choice != 11);
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
        cout << " ID | Name                 | Membership      | Goal\n";
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

                cout << client->getMembershipType();
                for (int j = static_cast<int>(client->getMembershipType().length()); j < 15; j++)
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
        case 0: clearScreen(); break;
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
