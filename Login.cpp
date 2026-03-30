#include "Login.h"

Login::Login() : User() {}

Login::Login(int i, string p) {
    setId(i);
    setPassword(p);
} 

bool Login::loginUser(int i, string p) {
    if (i == getId() && p == getPassword()) {
        cout << "\nLogin Successful!" << endl;
        return true;
    } else {
        cout << "\nInvalid ID or Password!" << endl;
        return false;
    }
}

void Login::loggingIn(int &i, string &p) {
    cout << "\nEnter ID: ";
    cin >> i;
    cout << "Enter Password: ";
    cin >> p;
}
