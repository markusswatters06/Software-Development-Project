#ifndef SIGNUP_H
#define SIGNUP_H

#include "User.h"

#include <iostream>
using namespace std;

class Signup : public User{
    public:
        // Constructors
        Signup();
        Signup(int i,string fn, string sn, string e, int ph, int dd, int dm, int dy, string p);

        // Functions
        void registerAccount();
};
#endif
