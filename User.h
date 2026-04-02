#include "User.h"


User::User()
    : id(0), name("N/A"), email("N/A"), phone(0), dobDay(0), dobMonth(0), dobYear(0), password("N/A"){}

User::User(int i, string n, string e, int ph, int dd, int dm, int dy, string p)
    : id(i), name(n), email(e), phone(ph), dobDay(dd), dobMonth(dm), dobYear(dy), password(p){} 


User::~User(){}


// Main Menu
void User::displayMenu()
{
    int choice;
    do
    {
    cout << "-----Welcome To The Gym App-----\n" << endl;
    cout << "Please Select One of The Following\n";
    cout << "1) Login" << endl;
    cout << "2) Signup" << endl;
    cout << "3) Logout" << endl;
    cout << "Choice: ";
    cin >> choice;
    
    int i;
    string p;
    switch(choice)
    {
        case 1: logIn(i, p); verifyUser(i, p); break;
        case 2: registerAccount(); break;
    }
    }
    while (choice != 3);
}


// Account Details
void User::displayDetails()
{
    cout << "\n-----Account Details-----" << endl;
    cout << "-Member ID:     " << id << endl;
    cout << "-Name:          " << name << endl;
    cout << "-Password:      " << password << endl;
    cout << "-Email Address: " << email << endl;
    cout << "-Phone Number:  0" << phone << endl;
    cout << "-Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
    cout << "-------------------------\n" << endl;
}


// Sign Up
void User::registerAccount()
{
    int i, ph, dd, dm, dy;
    string n, e, p;

    cout << "\nEnter Name: ";
    cin >> n;

    cout << "\nEnter Email Address: ";
    cin >> e;

    cout << "\nEnter Phone Number: ";
    cin >> ph;
    
    cout << "Enter Date of Birth\n";
    getValidDate(dd, dm, dy);

    cout << "\nEnter ID: ";
    cin >> i;

    cout << "\nEnter Password: "; 
    cin >> p;
    
    setId(i);
    setName(n);
    setEmail(e);
    setPhone(ph);
    setDobDay(dd);
    setDobMonth(dm);
    setDobYear(dy);
    setPassword(p);

    cout << "\nSignup Successful!" << endl;
}


// Verify Login
bool User::verifyUser(int i, string p) {
    if (i == getId() && p == getPassword()) {
        cout << "\nLogin Successful!" << endl;
        return true;
    } else {
        cout << "\nInvalid ID or Password!\n" << endl;
        return false;
    }
}


// Log In
void User::logIn(int &i, string &p) {
    cout << "\nEnter ID: ";
    cin >> i;
    cout << "Enter Password: ";
    cin >> p;
}


// Valid Date Function
bool User::getValidDate(int& d, int& m, int& y) {
    while (true) {
        cout << "(DD): ";
        cin >> d;
        cout << "(MM): ";
        cin >> m;
        cout << "(YYYY): ";
        cin >> y;

        // Basic Checks
        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) {
            cout << "\n-ERROR: Invalid date.-\n";
            cout << "\nEnter a Valid Date" << endl;
            continue;
        }

        // Days in a Month
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

        return true; // only returns when valid
    }
}


// UI
void User::clearScreen() 
{ 
    for(int i=0;i<40;i++) 
    cout << endl; 
}

void User::line() 
{ 
    cout << "========================================\n"; 
}

void User::title(string t) 
{ 
    line(); 
    cout << "          " << t << endl; 
    line(); 
}
