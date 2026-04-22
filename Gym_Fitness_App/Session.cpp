#include "Session.h"
#include <vector>
#include <limits>

int Session::nextSessionId = 1;
vector<Session> Session::sessionList;

int Session::sessionIndex(int sessionId) {
    for (int i = 0; i < static_cast<int>(sessionList.size()); i++) {
        if (sessionList[i].id == sessionId) {
            return i;
        }
    }
    return -1;
}

// Constructors & Destructor
Session::Session()
    : id(0), sessionName("N/A"), trainerName("N/A"),
      sessionDay(0), sessionMonth(0), sessionYear(0),
      time("00:00"), spacesAvailable(0) {
}

Session::Session(int i, string sn, string tn, int sd, int sm, int sy, string t, int sa)
    : id(i), sessionName(sn), trainerName(tn),
      sessionDay(sd), sessionMonth(sm), sessionYear(sy),
      time(t), spacesAvailable(sa) {
}

Session::~Session() {
}

Session& Session::operator--() {
    if (spacesAvailable <= 0) {
        throw runtime_error("No spaces available for this session.");
    }

    --spacesAvailable;
    return *this;
}

Session Session::operator--(int) {
    Session original(*this);
    --(*this);
    return original;
}

Session& Session::operator++() {
    ++spacesAvailable;
    return *this;
}

Session Session::operator++(int) {
    Session original(*this);
    ++(*this);
    return original;
}

bool Session::operator==(const Session& other) const {
    return id == other.id
        && sessionName == other.sessionName
        && sessionDay == other.sessionDay
        && sessionMonth == other.sessionMonth
        && sessionYear == other.sessionYear
        && time == other.time;
}

ostream& operator<<(ostream& os, const Session& session) {
    os << " ID:               " << session.id << '\n'
       << " Session Name:     " << session.sessionName << '\n'
       << " Trainer:          " << session.trainerName << '\n'
       << " Date:             ";
    if (session.sessionDay < 10) os << '0';
    os << session.sessionDay << '/';
    if (session.sessionMonth < 10) os << '0';
    os << session.sessionMonth << '/' << session.sessionYear << '\n'
       << " Time:             " << session.time << '\n'
       << " Spaces Available: " << session.spacesAvailable << '\n';
    return os;
}

// Getters
int Session::getId() const {
    return id;
}

string Session::getSessionName() const {
    return sessionName;
}

string Session::getTrainerName() const {
    return trainerName;
}

int Session::getSessionDay() const {
    return sessionDay;
}

int Session::getSessionMonth() const {
    return sessionMonth;
}

int Session::getSessionYear() const {
    return sessionYear;
}

string Session::getTime() const {
    return time;
}

int Session::getSpacesAvailable() const {
    return spacesAvailable;
}

// Setters
void Session::setId(int sid) {
    id = sid;
}

void Session::setSessionName(string sn) {
    sessionName = sn;
}

void Session::setTrainerName(string tn) {
    trainerName = tn;
}

void Session::setSessionDay(int sd) {
    sessionDay = sd;
}

void Session::setSessionMonth(int sm) {
    sessionMonth = sm;
}

void Session::setSessionYear(int sy) {
    sessionYear = sy;
}

void Session::setTime(string st) {
    time = st;
}

void Session::setSpacesAvailable(int sa) {
    spacesAvailable = sa;
}

// Create Session
void Session::createSession() {
    try {
        Session newSession;

        line();
        cout << "           CREATE SESSION" << endl;
        line();
        newSession.id = nextSessionId++;
        cout << "Session ID: " << newSession.id << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Session Name: ";
        getline(cin, newSession.sessionName);

        cout << "Enter Trainer Name: ";
        getline(cin, newSession.trainerName);

        cout << "Enter Session Date\n";
        getValidDate(newSession.sessionDay, newSession.sessionMonth, newSession.sessionYear);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Session Time: ";
        getline(cin, newSession.time);

        cout << "Enter Number of Spaces: ";
        cin >> newSession.spacesAvailable;
        if (cin.fail() || newSession.spacesAvailable < 0) {
            throw invalid_argument("Available spaces cannot be negative.");
        }

        newSession.validateSession();
        sessionList.push_back(newSession);
        cout << "\nSession Created Successfully!\n";
        clearScreen();
        displaySession();
    }
    catch (const exception& ex) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nERROR: " << ex.what() << "\n";
    }
}

void Session::addSession(const Session& session) {
    if (sessionIndex(session.getId()) != -1) {
        return;
    }

    sessionList.push_back(session);

    if (session.getId() >= nextSessionId) {
        nextSessionId = session.getId() + 1;
    }
}

// Remove Session
void Session::removeSession()
{
    if (sessionList.empty())
    {
        cout << "\nNo sessions have been created yet.\n";
        return;
    }

    displaySession();

    int sessionId;
    cout << "\nEnter the Session ID to remove: ";
    cin >> sessionId;

    int index = sessionIndex(sessionId);
    if (index == -1)
    {
        cout << "\nERROR: Session not found.\n";
        return;
    }

    char confirm;
    cout << "\nAre you sure you want to remove this session? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        sessionList.erase(sessionList.begin() + index);
        clearScreen();
        cout << "\nSession removed successfully.\n\n";
        displaySession();
    }
    else
    {
        cout << "\nSession removal cancelled.\n";
    }
}

// Display Session
void Session::displaySession() const {
    if (sessionList.empty()) {
        line();
        cout << "           SESSION DETAILS" << endl;
        line();
        cout << " No sessions available.\n\n";
        line();
        return;
    }

    cout << "==========================================================================\n";
    cout << "                              ALL SESSIONS\n";
    cout << "==========================================================================\n";
    cout << " ID | Session Name         | Trainer              | Date       | Time  | Spaces\n";
    cout << "--------------------------------------------------------------------------\n";

    for (int i = 0; i < static_cast<int>(sessionList.size()); i++) {
        const Session& session = sessionList[i];
        if (session.id < 10) cout << "  ";
        else if (session.id < 100) cout << ' ';
        cout << session.id << "  ";

        cout << session.sessionName;
        for (int j = static_cast<int>(session.sessionName.length()); j < 20; j++) {
            cout << ' ';
        }
        cout << ' ';

        cout << session.trainerName;
        for (int j = static_cast<int>(session.trainerName.length()); j < 20; j++) {
            cout << ' ';
        }
        cout << ' ';

        if (session.sessionDay < 10) cout << '0';
        cout << session.sessionDay << '/';
        if (session.sessionMonth < 10) cout << '0';
        cout << session.sessionMonth << '/' << session.sessionYear << "  ";

        cout << session.time;
        for (int j = static_cast<int>(session.time.length()); j < 5; j++) {
            cout << ' ';
        }

        cout << "   ";
        if (session.spacesAvailable < 10) cout << ' ';
        cout << session.spacesAvailable << endl;
    }
    cout << "==========================================================================\n";
}

bool Session::hasSessions() {
    return !sessionList.empty();
}

bool Session::bookSessionById(int sessionId) {
    int index = sessionIndex(sessionId);
    if (index == -1) {
        clearScreen();
        cout << "\nERROR: Session not found.\n\n";
        return false;
    }

    try {
        --sessionList[index];
        *this = sessionList[index];
        clearScreen();
        cout << "\nSession Booked Successfully!\n";
        cout << "Booked: " << sessionList[index].getSessionName()
             << " at " << sessionList[index].getTime()
             << " | Spaces left: " << sessionList[index].getSpacesAvailable() << "\n\n";
        return true;
    } catch (const exception& ex) {
        clearScreen();
        cout << "\nERROR: " << ex.what() << "\n\n";
        return false;
    }
}

bool Session::unbookSessionById(int sessionId) {
    int index = sessionIndex(sessionId);
    if (index == -1) {
        clearScreen();
        cout << "\nERROR: Session not found.\n\n";
        return false;
    }

    ++sessionList[index];
    clearScreen();
    cout << "\nSession Unbooked Successfully!\n";
    cout << "Unbooked: " << sessionList[index].getSessionName()
         << " at " << sessionList[index].getTime()
         << " | Spaces now: " << sessionList[index].getSpacesAvailable() << "\n\n";
    return true;
}

// Edit Session
void Session::editSession() {
    if (sessionList.empty()) {
        cout << "\nNo sessions available to edit.\n";
        return;
    }

    int sessionId;
    displaySession();
    cout << "Enter Session ID to edit (0 to return): ";
    cin >> sessionId;

    if (sessionId == 0) {
        clearScreen();
        return;
    }

    int index = sessionIndex(sessionId);
    if (index == -1) {
        cout << "\nERROR: Session not found.\n";
        return;
    }

    Session& selectedSession = sessionList[index];
    int choice;

    do {
        clearScreen();
        line();
        cout << "        EDIT SESSION DETAILS" << endl;
        line();
        cout << selectedSession;
        line();
        cout << "1) Session Name" << endl;
        cout << "2) Trainer Name" << endl;
        cout << "3) Session Date" << endl;
        cout << "4) Session Time" << endl;
        cout << "5) Spaces Available" << endl;
        cout << "0) Return to Session Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "\nEnter New Session Name: ";
                getline(cin, selectedSession.sessionName);
                break;

            case 2:
                cout << "\nEnter New Trainer Name: ";
                getline(cin, selectedSession.trainerName);
                break;

            case 3:
                cout << "\nEnter New Session Date\n";
                getValidDate(selectedSession.sessionDay, selectedSession.sessionMonth, selectedSession.sessionYear);
                break;

            case 4:
                cout << "\nEnter New Session Time: ";
                getline(cin, selectedSession.time);
                break;

            case 5:
                cout << "\nEnter New Number of Spaces: ";
                cin >> selectedSession.spacesAvailable;
                break;

            case 0:
                clearScreen();
                break;

            default:
                cout << "\nERROR: Invalid Choice\n";
                break;
        }
    } while (choice != 0);
}

// Book Session
void Session::bookSession() {
    if (sessionList.empty()) {
        clearScreen();
        cout << "\nNo sessions available to book.\n\n";
        return;
    }

    displaySession();

    int sessionId;
    cout << "Enter Session ID to book: ";
    cin >> sessionId;
    bookSessionById(sessionId);
}

// Cancel Session
void Session::unbookSession(){
    if (sessionList.empty()) {
        clearScreen();
        cout << "\nNo sessions available to unbook.\n\n";
        displaySession();
        return;
    }

    displaySession();

    int sessionId;
    cout << "Enter Session ID to unbook: ";
    cin >> sessionId;

    unbookSessionById(sessionId);
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

        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) {
            cout << "\nERROR: Invalid date.\n";
            cout << "Enter a valid date.\n";
            continue;
        }

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

        return true;
    }
}

// UI
void Session::clearScreen() {
    for (int i = 0; i < 40; i++) {
        cout << endl;
    }
}

void Session::line() const {
    cout << "========================================\n";
}

void Session::validateSession() const {
    if (sessionName.empty()) {
        throw invalid_argument("Session name cannot be empty.");
    }

    if (trainerName.empty()) {
        throw invalid_argument("Trainer name cannot be empty.");
    }

    if (time.empty()) {
        throw invalid_argument("Session time cannot be empty.");
    }
}
