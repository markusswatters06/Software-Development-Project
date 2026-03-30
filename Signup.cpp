#include "Signup.h"

Signup::Signup() : User(){}

Signup::Signup(int i, string u, string p):
    User(i,u,p){}

void Signup::registerAccount()
{
    int i;
    string u,p;
    cout << "\nEnter ID: " << endl;
    cin >> i;
    cout << "\nEnter Username: " << endl;
    cin >> u;
    cout << "\nEnter password " << endl;
    cin >> p;
    
    setId(i);
    setUsername(u);
    setPassword(p);

    cout << "\n\nSignup Successful!" << endl;
}