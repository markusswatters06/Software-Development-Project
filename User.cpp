#include "User.h"

User::User(): id(0), username("N/A"), password("N/A"){}

User::User(int i, string u, string p): id(i), username(u), password(p){} 

User::~User(){}

void User::displayDetails()
{
    cout << "\nID: " << id << endl;
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
}