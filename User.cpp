#include "User.h"

User::User()
    : id(0), name("N/A"), email("N/A"), phone(0), dobDay(0), dobMonth(0), dobYear(0), password("N/A"){}

User::User(int i, string n, string e, int ph, int dd, int dm, int dy, string p)
    : id(i), name(n), email(e), phone(ph), dobDay(dd), dobMonth(dm), dobYear(dy), password(p){} 

User::~User(){}

void User::displayDetails()
{
    cout << "ID: " << id << endl;
    cout << "Email Address: " << email << endl;
    cout << "Password: " << password << endl;
    cout << "Name: " << name << endl;
    cout << "Phone Number: 0" << phone << endl;
    cout << "Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
}

void User::registerAccount()
{
    int i, ph, dd, dm, dy;
    string n, n, e, p;

    cout << "\nEnter Name ";
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

bool User::loginUser(int i, string p) {
    if (i == getId() && p == getPassword()) {
        cout << "\nLogin Successful!" << endl;
        return true;
    } else {
        cout << "\nInvalid ID or Password!" << endl;
        return false;
    }
}

void User::loggingIn(int &i, string &p) {
    cout << "\nEnter ID: ";
    cin >> i;
    cout << "Enter Password: ";
    cin >> p;
}

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
            cout << "ERROR: Invalid date.\n";
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
