#include "Session.h"

// Constructors & Destructors
Session::Session()
: id(0), sessionName("N/A"), trainerName("N/A"), sessionDay(00), sessionMonth(00), sessionYear(0000), time("00:00"), spacesAvailable(0)
{}

Session::Session(int i, string sn, string tn, int sd, int sm, int sy, string t, int sa)
    : id(i), sessionName(sn), trainerName(tn), sessionDay(sd), sessionMonth(sm), sessionYear(sy), time(t), spacesAvailable(sa)
{}

Session::~Session()
{}


// Create Session
void Session::createSession()
{
    line();
    cout << "           CREATE SESSION" << endl;
    line();

    cout << "Enter Session ID: ";
    cin >> id;
    cout << "Enter Session Name: ";
    cin >> sessionName;
    cout << "Enter Trainer Name: ";
    cin >> trainerName;
    cout << "Enter Session Date\n";
    getValidDate(sessionDay, sessionMonth, sessionYear);
    cout << "Enter Session Time: ";
    cin >> time;
    cout << "Enter Number of Spaces: ";
    cin >> spacesAvailable;
    cout << "\nSession Created Successfully!\n";
    clearScreen();
    displaySession();
}


// Display Session
void Session::displaySession()
{   
    clearScreen();
    line();
    cout << "           SESSION DETAILS" << endl;
    line();

    cout << "ID: " << id << endl;
    cout << "Name: " << sessionName << endl;
    cout << "Trainer Name: " << trainerName << endl;
    cout << "Date: " << sessionDay << "/" << sessionMonth << "/" << sessionYear << endl;
    cout << "Time: " << time << endl;
    cout << "Available Spaces: " << spacesAvailable << endl;
    line();
}


// Edit Session
void Session::editSession()
{
    int choice;
    displaySession();
    cout << "      EDIT SESSION DETAILS" << endl;
    line();

        do
    {
        cout << "1) Session Name" << endl;
        cout << "2) Trainer Name" << endl;
        cout << "3) Session Date" << endl;
        cout << "4) Session Time" << endl;
        cout << "5) Spaces Available" << endl;
        cout << "0) Return to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "\nEnter New Session Name: ";
                cin >> sessionName;
                clearScreen();
                editSession();
                break;

            case 2:
                cout << "\nEnter New Trainer Name: ";
                cin >> trainerName;
                clearScreen();
                editSession();
                break;

            case 3:
                cout << "\nEnter New Session Date\n";
                getValidDate(sessionDay, sessionMonth, sessionYear);
                clearScreen();
                editSession();
                break;

            case 4:
                cout << "\nEnter New Session Time: ";
                cin >> time;
                clearScreen();
                editSession();
                break;

            case 5:
                cout << "\nEnter New Number of Spaces: ";
                cin >> spacesAvailable;
                clearScreen();
                editSession();
                break;

            case 0:
                break;

            default:
                cout << "\nERROR: Invalid Choice\n";
        }

    } while(choice != 5);
    
}


// Book Session
void Session::bookSession()
{
    if(spacesAvailable > 0)
    {
        spacesAvailable--;
        cout << "\nSession Booked Successfully!\n";
        cout << "Remaining Spaces: " << spacesAvailable << endl;
    }
    else
    {
        cout << "\nNo Spaces Available.\n";
    }
    
}


// Get Valid Date
bool Session::getValidDate(int& d, int& m, int& y) {
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
            cout << "\nERROR: Invalid day for that month.\n";
            continue;
        }

        return true; // only returns when valid
    }
}


// UI
void Session::clearScreen() 
{ 
    for(int i = 0; i < 40; i++) 
    cout << endl; 
}

void Session::line() 
{ 
    cout << "========================================\n"; 
}