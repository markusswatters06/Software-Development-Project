#ifndef Login_H
#define Login_H

#include "User.h"
#include <vector>

class Login {
private:
    vector<User> users;
    User* currentUser;

public:
    Login();
    ~Login();
    
    User* getCurrentUser();
    void addUser(User newUser);
    bool findUser(string email, User &foundUser);
    void setCurrentUser(User* user);
    void logout();
};

#endif