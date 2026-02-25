#include "User.h"

User::User() {
    age = 0;
    height = 0;
    weight = 0;
    fitnessLevel = "Not Set";
    fitnessGoal = "Not Set";
}

string User::getEmail() { return email; }
string User::getPassword() { return password; }
string User::getName() { return name; }
int User::getAge() { return age; }
double User::getHeight() { return height; }
double User::getWeight() { return weight; }
string User::getFitnessLevel() { return fitnessLevel; }
string User::getFitnessGoal() { return fitnessGoal; }

void User::setEmail(string e) { email = e; }
void User::setPassword(string p) { password = p; }
void User::setName(string n) { name = n; }
void User::setAge(int a) { age = a; }
void User::setHeight(double h) { height = h; }
void User::setWeight(double w) { weight = w; }
void User::setFitnessLevel(string f) { fitnessLevel = f; }
void User::setFitnessGoal(string g) { fitnessGoal = g; }