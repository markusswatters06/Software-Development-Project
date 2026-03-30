#include "User.h"

User::User()
    : id(0), firstName("N/A"), surname("N/A"), email("N/A"), phone(0), dobDay(0), dobMonth(0), dobYear(0), password("N/A"){}

User::User(int i, string fn, string sn, string e, int ph, int dd, int dm, int dy, string p)
    : id(i), firstName(fn), surname(sn), email(e), phone(ph), dobDay(dd), dobMonth(dm), dobYear(dy), password(p){} 

User::~User(){}

void User::displayDetails()
{
    cout << "ID: " << id << endl;
    cout << "Email Address: " << email << endl;
    cout << "Password: " << password << endl;
    cout << "Name: " << firstName << " " << surname << endl;
    cout << "Phone Number: 0" << phone << endl;
    cout << "Date Of Birth: " << dobDay << "/" << dobMonth << "/" << dobYear << endl;
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
