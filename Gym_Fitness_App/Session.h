#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Session {
private:
    static int nextSessionId;
    int id;
    string sessionName;
    string trainerName;
    int sessionDay;
    int sessionMonth;
    int sessionYear;
    string time;
    int spacesAvailable;

    static vector<Session> sessionList;
    static int sessionIndex(int sessionId);

public:
    // Constructors & Destructor
    Session();
    Session(int i, string sn, string tn, int sd, int sm, int sy, string t, int sa);
    ~Session();

    // Operator Overloading
    Session& operator--();
    Session operator--(int);
    Session& operator++();
    Session operator++(int);
    bool operator==(const Session& other) const;
    friend ostream& operator<<(ostream& os, const Session& session);

    // Getters
    int getId() const;
    string getSessionName() const;
    string getTrainerName() const;
    int getSessionDay() const;
    int getSessionMonth() const;
    int getSessionYear() const;
    string getTime() const;
    int getSpacesAvailable() const;

    // Setters
    void setId(int sid);
    void setSessionName(string sn);
    void setTrainerName(string tn);
    void setSessionDay(int sd);
    void setSessionMonth(int sm);
    void setSessionYear(int sy);
    void setTime(string st);
    void setSpacesAvailable(int sa);

    // Functions
    void createSession();
    void addSession(const Session& session);
    void removeSession();
    void displaySession() const;
    static bool hasSessions();
    bool bookSessionById(int sessionId);
    bool unbookSessionById(int sessionId);
    void editSession();
    void bookSession();
    void unbookSession();
    bool getValidDate(int& d, int& m, int& y);
    void validateSession() const;

    // UI
    void clearScreen();
    void line() const;
};

#endif
