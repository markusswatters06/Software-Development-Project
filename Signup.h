#ifndef SIGNUP_H
#define SIGNUP_H

#include "User.h"

#include <iostream>
using namespace std;

class Signup : public User{
    public:
        Signup();
        Signup(int i, string u, string p);

        void registerAccount();
};
#endif