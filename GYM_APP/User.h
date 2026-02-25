#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string email;
    string password;
    string name;
    int age;
    double height;
    double weight;
    string fitnessLevel;
    string fitnessGoal;

public:
    // Constructor
    User();
    
    // Getters
    string getEmail();
    string getPassword();
    string getName();
    int getAge();
    double getHeight();
    double getWeight();
    string getFitnessLevel();
    string getFitnessGoal();
    
    // Setters
    void setEmail(string e);
    void setPassword(string p);
    void setName(string n);
    void setAge(int a);
    void setHeight(double h);
    void setWeight(double w);
    void setFitnessLevel(string f);
    void setFitnessGoal(string g);
};

#endif