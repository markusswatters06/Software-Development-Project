#include "Client.h"
#include <limits>
#include <stdexcept>


// Constructors
Client::Client()
    : User(), height(0.0), weight(0.0), membershipType("N/A"), goal("N/A"),
        expiryDay(1), expiryMonth(1), expiryYear(2026),
        bookedSession(new Session()), currentGoal(new Goal())
{}

Client::Client(double h, double w, string mt, string g, int ed, int em, int ey)
    : User(), height(h), weight(w), membershipType(mt), goal(g),
        expiryDay(ed), expiryMonth(em), expiryYear(ey),
        bookedSession(new Session()), currentGoal(new Goal())
{}

Client::Client(int i, string n, string e, int ph, int dd, int dm, int dy, string p,
               double h, double w, string mt, string g, int ed, int em, int ey)
    : User(i, n, e, ph, dd, dm, dy, p), height(h), weight(w), membershipType(mt), goal(g),
        expiryDay(ed), expiryMonth(em), expiryYear(ey),
        bookedSession(new Session()), currentGoal(new Goal())
{}

Client::Client(const Client& other)
    : User(other.id, other.name, other.email, other.phone, other.dobDay, other.dobMonth, other.dobYear, other.password),
        height(other.height), weight(other.weight), membershipType(other.membershipType), goal(other.goal),
      expiryDay(other.expiryDay), expiryMonth(other.expiryMonth), expiryYear(other.expiryYear),
      bookedSessionIds(other.bookedSessionIds),
      bookedSession(new Session(*other.bookedSession)), currentGoal(new Goal(*other.currentGoal))
{}

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
        membershipType = other.membershipType;
        goal = other.goal;
        expiryDay = other.expiryDay;
        expiryMonth = other.expiryMonth;
        expiryYear = other.expiryYear;
        bookedSessionIds = other.bookedSessionIds;

        *bookedSession = *other.bookedSession;
        *currentGoal = *other.currentGoal;
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
       << " | Membership: " << client.membershipType
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

            cout << "Enter Membership Type: ";
            cin >> membershipType;
            if (membershipType != "Basic" && membershipType != "Premium" && membershipType != "basic" && membershipType != "premium")
            {
                throw invalid_argument("Membership type must be Basic or Premium.");
            }

            cout << "Enter Expiry Date:" << endl;
            getValidDate(expiryDay, expiryMonth, expiryYear);

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
    int choice;
    do
    { 
        line();
        cout << "           CLIENT MENU" << endl;

        line();
        cout << "  1) Profile" << endl;
        cout << "  2) Membership Menu" << endl;
        cout << "  3) Progress Menu" << endl;
        cout << "  4) Workout Menu" << endl;
        cout << "  5) Session Menu" << endl;
        cout << "  0) Logout" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();
    
        switch(choice) {
            case 1: displayDetails(); break;
            case 2: membershipMenu(); break;
            case 3: goalMenu(); break;
            case 4: workoutMenu(); break;
            case 5: sessionMenu(); break;
            case 0: displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }

    } 
    while (choice != 5);
    
}


// Profile Menu
void Client::displayDetails()
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
        cout << "  Height:        " << height << "cm" << endl;
        cout << "  Weight:        " << weight << "kg" << endl;

        line();
        cout << "  1) Edit Profile" << endl;
        cout << "  0) Return to Client Menu" << endl;
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

void Client::displayClients() const
{
    cout << "===============================================================================\n";
    cout << "                                CLIENT DETAILS\n";
    cout << "===============================================================================\n";
    cout << " ID | Name                 | Membership      | Goal\n";
    cout << "-------------------------------------------------------------------------------\n";

    if (id < 10) cout << "  ";
    else if (id < 100) cout << ' ';
    cout << id << "  ";

    cout << name;
    for (int i = static_cast<int>(name.length()); i < 20; i++)
    {
        cout << ' ';
    }
    cout << ' ';

    cout << membershipType;
    for (int i = static_cast<int>(membershipType.length()); i < 15; i++)
    {
        cout << ' ';
    }
    cout << ' ';

    cout << goal << endl;
    cout << "===============================================================================\n";
}


// Membership Menu
void Client::membershipMenu()
{
    int choice;

    do{
        line();
        cout << "           MEMBERSHIP MENU" << endl;
        line();

        cout << " Type:    " << membershipType << endl;
        cout << " Expiry:  " << expiryDay << "/" << expiryMonth << "/" << expiryYear << endl;

        line();

        cout << "  Month Gym Membership ($50)" << endl;
        cout << "  Year Gym Membership ($450)" << endl;
        cout << "  Month Gym & Class Membership ($550)" << endl;
        line();
        cout << "  0) Return to Client Menu:";
        cin >> choice;
        
        clearScreen();

        switch(choice)
        {
            case 0: displayMenu(); break;
            default: cout << "\n*ERROR: Invalid Choice*\n\n";
        }

    } while(choice != 0); 
}


// Goal Menu
void Client::goalMenu()
{
    int choice;
    do
    {
        clearScreen();
        line();
        cout << "           GOAL MENU" << endl;
        line();

        cout << "  1) New Goal" << endl;
        cout << "  2) View Goals" << endl;
        cout << "  3) Remove Goal (LOCKED)" << endl;
        cout << "  4) View Progress (LOCKED)" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                clearScreen();
                addGoal();
                currentGoal->setType();
                currentGoal->updateDeadline();
                currentGoal->updateStatus();
                break;

            case 2:
                clearScreen();
                displayGoal();
                break;

            case 3:
                cout << "\nRemove Goal is currently locked.\n";
                cin.get();
                break;

            case 4:
                clearScreen();
                checkProgress();
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
    line();
    cout << "           WORKOUT MENU" << endl;
    line();

    do
    {
        cout << "  1) Log Workout (LOCKED)" << endl;
        cout << "  2) View Workouts (LOCKED)" << endl;
        cout << "  3) Edit Workouts (LOCKED)" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: " << endl;
        cin >> choice;

        clearScreen();

        switch(choice)
        {
            case 1: logWorkout(); break;
            case 2: displayWorkout(); break;
            case 3: editWorkout(); break;
            case 0: displayMenu(); break;
            default: cout << "\n\n*ERROR: Invalid Choice*\n\n";
        }
    }
        while(choice != 4);
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
                line();
        cout << "           ACCOUNT DETAILS\n";
        line();

        cout << "  Member ID:     " << id << endl;
        cout << "  Name:          " << name << endl;
        cout << "  Password:      " << password << endl;
        cout << "  Email Address: " << email << endl;
        cout << "  Phone Number:  0" << phone << endl;
        cout << "  Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
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
        cout << "  8) Return to Profile Menu" << endl;
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
                double h;
                cout << "\nEnter a New Height (cm): ";
                cin >> h;
                setHeight(h);
                clearScreen();
                break;
            }
            case 7: 
            {   
                double w;
                cout << "\nEnter a New Weight (kg): ";
                cin >> w;
                setWeight(w);
                clearScreen();
                break;
            }
            case 8: 
            {   
                cout << "\nReturning to Profile Menu...\n";
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
    while (choice != 6);
}


// Display Workouts
void Client::displayWorkout()
{

}


// Edit Workouts
void Client::editWorkout()
{
}


// Log Workouts
void Client::logWorkout()
{
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
                sessionMenu();
                break;

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
        cout << "\nYou do not have a booked session to unbook.\n\n";
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
    currentGoal->displayGoal();
}

void Client::updateProgress()
{
    currentGoal->updateProgress();
}

void Client::checkProgress()
{
    currentGoal->checkProgress();
}

void Client::addGoal()
{
    currentGoal->addGoal();
}

// UI
void Client::clearScreen() 
{ 
    for(int i = 0; i < 40; i++) 
    cout << endl; 
}

void Client::line() 
{ 
    cout << "========================================\n"; 
}

void Client::title(string t) 
{ 
    line(); 
    cout << "          " << t << endl; 
    line(); 
}
