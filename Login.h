#ifndef LOGIN_H
#define LOGIN_H

#include "User.h"
#include <iostream>
using namespace std;

class Login : public User {
public:
    // Constructors
    Login();
    Login(int i, string p);

    
    // Functions
    bool loginUser(int i, string p);
    void loggingIn(int &i, string &p);
};
#endif
