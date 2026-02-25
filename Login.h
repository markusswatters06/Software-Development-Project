#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
using namespace std;

class Login {
    private:
        int id;
        string username;
        string password;

    public:
        // Constructors/Destructors
        Login();    // Default Constructor
        Login(int i, string u, string p);  // Overloaded Constructor
        ~Login();   // Destructor

        // Getters
        string getUsername(){return username;}  // Username
        string getPassword(){return password;}  // Password
        int getId(){return id;} // ID

        // Setters
        void setUsername(string u){username = u;}   // Username
        void setPassword(string p){password = p;}   // Password
        void setId(int i){id = i;}  // ID

};
#endif 