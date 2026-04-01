#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
    protected:
        int id;
        string name;
        string email;
        int phone;
        int dobDay;
        int dobMonth;
        int dobYear;
        string password;

    public:
        // Constructors/Destructors
        User();                             // Default Constructor
        User(int i, string n, string e, int ph, int dd, int dm, int dy, string p);    // Overloaded Constructor
        ~User();                            // Destructor


        // Getters
        int getId(){return id;}                     // ID
        string getName(){return name;}              // First Name
        string getEmail(){return email;}            // Email
        int getPhone(){return phone;}               // Phone
        int getDobDay(){return dobDay;}             // DOB Day
        int getDobMonth(){return dobMonth;}         // DOB Month
        int getDobYear(){return dobYear;}           // DOB Year
        string getPassword(){return password;}      // Password


        // Setters
        void setId(int i){id = i;}                      // ID
        void setName(string n){name = n;}          // First Name
        void setEmail(string e){email = e;}             // Email
        void setPhone(int ph){phone = ph;}              // Phone
        void setDobDay(int dd){dobDay = dd;}            // DOB Day
        void setDobMonth(int dm){dobMonth = dm;}        // DOB Month
        void setDobYear(int dy){dobYear = dy;}          // DOB Year
        void setPassword(string p){password = p;}       // Password


        // Functions
        void displayDetails();
        void registerAccount();
        bool loginUser(int i, string p);
        void loggingIn(int &i, string &p);
        bool getValidDate(int& dobDay, int& dobMonth, int& dobYear);
};
#endif 
