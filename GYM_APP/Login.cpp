#include "Login.h"

Login::Login() {
    currentUser = NULL;
    
    // Add sample user
    User sample;
    sample.setEmail("user@example.com");
    sample.setPassword("password123");
    sample.setName("John Doe");
    sample.setAge(25);
    sample.setHeight(175.5);
    sample.setWeight(70.2);
    sample.setFitnessLevel("Intermediate");
    sample.setFitnessGoal("Build Muscle");
    users.push_back(sample);
}

Login::~Login() {
    if (currentUser != NULL) {
        delete currentUser;
    }
}

User* Login::getCurrentUser() {
    return currentUser;
}

void Login::addUser(User newUser) {
    users.push_back(newUser);
}

bool Login::findUser(string email, User &foundUser) {
    for(int i = 0; i < users.size(); i++) {
        if(users[i].getEmail() == email) {
            foundUser = users[i];
            return true;
        }
    }
    return false;
}

void Login::setCurrentUser(User* user) {
    if(currentUser != NULL) {
        delete currentUser;
    }
    currentUser = user;
}

void Login::logout() {
    if(currentUser != NULL) {
        delete currentUser;
        currentUser = NULL;
    }
}