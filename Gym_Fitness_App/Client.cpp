#include "Client.h"


// Constructors
Client::Client()
    : User(), height(0.0), weight(0.0), membershipType("N/A"), goal("N/A"),
        expiryDay(1), expiryMonth(1), expiryYear(2026) 
{}

Client::Client(double h, double w, string mt, string g, int ed, int em, int ey)
    : User(), height(h), weight(w), membershipType(mt), goal(g),
        expiryDay(ed), expiryMonth(em), expiryYear(ey) 
{}

Client::Client(int i, string n, string e, int ph, int dd, int dm, int dy, string p,
               double h, double w, string mt, string g, int ed, int em, int ey)
    : User(i, n, e, ph, dd, dm, dy, p), height(h), weight(w), membershipType(mt), goal(g),
        expiryDay(ed), expiryMonth(em), expiryYear(ey) 
{}

Client::~Client() {}


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
            case 3: progressMenu(); break;
            case 4: workoutMenu(); break;
            case 5: sessionMenu(); break;
            case 0: ; break;
            default: cout << "\n\nERROR: Invalid Choice\n";
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
            default: cout << "\n\nERROR: Invalid Choice\n";
        }
    }
        while (choice != 2);
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
        cout << "  1) Renew Membership" << endl;
        cout << "  2) Upgrade Membership" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;
        
        clearScreen();

        switch(choice)
        {
            case 1: renewMembership(); break;
            case 2: upgradeMembership(); break;
            case 0: displayMenu();
            default: cout << "\nERROR: Invalid Choice\n";
        }

    } while(choice != 0); 
}


// Progress Menu
void Client::progressMenu()
{
    int choice;
    line();
    cout << "           PROGRESS MENU" << endl;
    line();

    do
    {
        cout << "  1) View Progress" << endl;
        cout << "  2) Edit Progress" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();

        switch(choice)
        {
            case 1: viewProgress(); break;
            case 2: editProgress(); break;
            case 0: displayMenu(); break;
            default: cout << "\n\nERROR: Invalid Choice\n";
        }
    }
    while(choice != 2);
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
        cout << "  1) Log Workout" << endl;
        cout << "  2) View Workouts" << endl;
        cout << "  3) Edit Workouts" << endl;
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
            default: cout << "\n\nERROR: Invalid Choice\n";
        }
    }
        while(choice != 4);
}


// Session Menu
void Client::sessionMenu()
{
    int choice;
    line();
    cout << "           SESSION MENU" << endl;
    line();

    do
    {
        cout << "  1) View Sessions" << endl;
        cout << "  2) Book Sessions" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        clearScreen();

        switch(choice)
        {
            case 1: viewSession(); break;
            case 2: bookSession(); break;
            case 0: displayMenu(); break;
            default: cout << "\n\nERROR: Invalid Choice\n";
        }
    }
    while(choice != 2);
}


// Edit Profile
void Client::editProfile()
{
    int choice;

    do
    {
        line();
        cout << "           EDIT PROFILE" << endl;
        line();

        cout << "  1) Name" << endl;
        cout << "  2) Password" << endl;
        cout << "  3) Email Address" << endl;
        cout << "  4) Phone Number" << endl;
        cout << "  5) Date of Birth" << endl;
        cout << "  6) Return to Profile Menu" << endl;
        cout << "  0) Return to Client Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;   
        
        clearScreen();

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
                clearScreen();
                break;
            }
            case 6: 
            {   
                cout << "\nReturning to Profile Menu...\n";
                break;
            }
            case 0: displayMenu(); break;
            default:
                cout << "\n\nERROR: Invalid Choice\n";
        } 

    } while (choice != 6);
}


void Client::displayWorkout()
{

}


void Client::editWorkout()
{
}


void Client::logWorkout()
{
}


void Client::viewSession()
{
}


void Client::bookSession()
{
}


void Client::viewProgress()
{
}


void Client::editProgress()
{
}


void Client::renewMembership()
{
}


void Client::upgradeMembership()
{
}


// UI
void Client::clearScreen() 
{ 
    for(int i=0;i<40;i++) 
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