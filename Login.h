#ifndef LOGIN_H
#define LOGIN_H

#include "User.h"

#include <iostream>
using namespace std;

class Login : public User{
    public:
        // Constructors
        Login();
        Login(int i, string u, string p);

        // Functions
        bool loginUser(string u, string p);
        void loggingIn(string &u, string &p);
};
#endif
