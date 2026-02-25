#include "Login.h"

Login::Login()
{
    id = 0;
    username = "N/A";
    password = "N/A";
    cout << "Default Constructor Called." << endl;
}

Login::Login(int i, string u, string p)
{
    id = i;
    username = u;
    password = p;
    cout << i << " constructed." << endl;
}

Login::~Login()
{
    cout << " destroyed." << endl;
}