#include "Login.h"

Login::Login() : User(){}

Login::Login(int i, string u, string p) : User(i,u,p){}

bool Login::loginUser(string u, string p)
{
    if (u == getUsername() && p == getPassword())
    {
        cout << "\nLogin Successful!" << endl;
        return true;
    }
    else{
        cout <<"\nInvalid Username or Password!" << endl;
        return false;
    }
}

void Login::displayLogin(string &u, string &p)
{
    cout << "\nEnter Username: ";
    cin >> u;
    cout << "\nEnter Password: ";
    cin >> p;
}
