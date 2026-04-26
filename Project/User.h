#ifndef USER_H
#define USER_H

#include <iostream>
#include <stdexcept>
using namespace std;

class User {
    protected:
        static int nextUserId;
        int id;
        string name, email;
        int phone, dobDay, dobMonth, dobYear;
        string password;

    public:
        // Constructors & Destructors
        User();                             // Default Constructor
        User(int i, string n, string e, int ph, int dd, int dm, int dy, string p);    // Overloaded Constructor
        virtual ~User();                    // Destructor


        // Getters
        int getId(){return id;}                     // ID
        string getName(){return name;}              // First Name
        string getEmail(){return email;}            // Email
        int getPhone(){return phone;}               // Phone
        int getDobDay(){return dobDay;}             // DOB Day
        int getDobMonth(){return dobMonth;}         // DOB Month
        int getDobYear(){return dobYear;} 
        string getPassword(){return password;}      // Password


        // Setters
        void setId(int i){id = i;}                      // ID
        void setName(string n){name = n;}               // First Name
        void setEmail(string e){email = e;}             // Email
        void setPhone(int ph){phone = ph;}              // Phone
        void setDobDay(int dd){dobDay = dd;}            // DOB Day
        void setDobMonth(int dm){dobMonth = dm;}        // DOB Month
        void setDobYear(int dy){dobYear = dy;}   
        void setPassword(string p){password = p;}       // Password


        // Functions
        void mainMenu();
        virtual void displayDetails();
        virtual void registerAccount();
        bool verifyUser(int i, string p);
        void logIn(int &i, string &p);
        bool getValidDate(int& dd, int& dm, int& dy);

        // Menus
        virtual void displayMenu();
        virtual void goalMenu();
        virtual void workoutMenu();

        // UI
        void clearScreen();
        void line();
        void lineLong();
        void dashedLine(); 
};

#endif 
