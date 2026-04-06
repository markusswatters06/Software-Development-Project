#include "Trainer.h"

Trainer::Trainer()
    : bio("N/A"), cert("N/A"), rating(0.0), yearsExp(0), clients(0), sessionsPerWeek(0), sessionRate(0.0), availablility("N/A")
{}

Trainer::Trainer(string b, string c, double r, int ye, int cl, int spw, double sr, string a)
    : bio(b), cert(c), rating(r), yearsExp(ye), clients(cl), sessionsPerWeek(spw), sessionRate(sr), availablility(a)
{}

Trainer::~Trainer()
{}


// Register Account
void Trainer::registerAccount()
{
    line();
    cout << "           TRAINER REGISTRATION" << endl;
    line();

    User::registerAccount();

        // Step 1: base user info
    User::registerAccount();

    cout << "Enter Bio: ";
    cin >> bio;

    cout << "Enter Certification: ";
    cin >> cert;

    cout << "Enter Years Experience: ";
    cin >> yearsExp;

    cout << "Enter Session Rate: ";
    cin >> sessionRate;

    cout << "Enter Availability: ";
    cin >> availablility;

    rating = 0.0;
    clients = 0;
    sessionsPerWeek = 0;

    cout << "\nTrainer Account Created Successfully!\n";
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
    line();
    cout << "           CLIENT MENU" << endl;
    line();

    do
    {
        cout << "  1) View Assigned Clients" << endl;
        cout << "  2) Assign Clients" << endl;
        cout << "  3) Remove Clients" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 0: clearScreen(); displayMenu(); break;
        }  
    }
    while (choice != 3); 
}

// Session Menu
void Trainer::sessionMenu()
{
    int choice;
    line();
    cout << "           SESSION MENU" << endl;
    line();

    do
    {
        cout << "  1) View Sessions" << endl;
        cout << "  2) Create Session" << endl;
        cout << "  3) Remove Session(LOCKED)" << endl;
        cout << "  4) Edit Session" << endl;
        cout << "  0) Return to Main Menu" << endl;
        line();

        cout << "  Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: displaySession(); break;
            case 2: createSession(); break;
            case 3: break;
            case 4: editSession(); break;
            case 0: clearScreen(); displayMenu(); break;
        }  
    }
    while (choice != 4);
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

// Create Session
void Trainer::createSession()
{
    trainerSession.createSession();
}

// View Session
void Trainer::displaySession()
{
    int choice;
    trainerSession.displaySession();
    cout << "  1) Edit Session" << endl;
    cout << "  0) Return to Menu" << endl;
    cout << "  Choice: ";
    do
    {
        cin >> choice;
        switch(choice)
        {
        case 1: editSession(); break;
        case 0: displayMenu(); break;
        } 
    }
    while (choice != 1);

    clearScreen();
    
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

void Trainer::line() 
{ 
    cout << "========================================\n"; 
}

