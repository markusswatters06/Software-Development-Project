#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
    protected:
        int id;
        string username;
        string password;

    public:
        // Constructors/Destructors
        User();    // Default Constructor
        User(int i, string u, string p);  // Overloaded Constructor
        ~User();   // Destructor

        // Getters
        int getId(){return id;}                 // ID
        string getUsername(){return username;}  // Username
        string getPassword(){return password;}  // Password

        // Setters
        void setId(int i){id = i;}                  // ID
        void setUsername(string u){username = u;}   // Username
        void setPassword(string p){password = p;}   // Password

        // Functions
        void displayDetails();
};
#endif 
