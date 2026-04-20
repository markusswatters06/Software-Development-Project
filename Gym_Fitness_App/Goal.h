#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

#ifndef _GOAL_
#define _GOAL_

class Goal
{
    private: 
    double currentPR; 
    int days;
    int months; 
    int years; 
    char timePeriod; 
    double percentage;
    string goal; 
    string type; 
    double target; 
    string deadline; 
    double newPR;
    double improvement;
    string status; 

    public: 
    Goal(); 
    Goal(double currentPR, int days, int months, int years, char timePeriod, double percentage, string goal, string type, double target, string deadline, double newPR, double improvement, string status);
    virtual ~Goal() {}


    virtual void checkProgress();
    virtual void updateStatus();
    virtual void updateProgress(); 
    virtual void addGoal();
    virtual void editGoal();
    virtual void displayGoal(); 
    virtual void updateDeadline();
    void setType(); 
    
    bool isValidExercise(const string& exercise);
    
    // Input validation helper functions
    double getValidPositiveDouble(const string& prompt);
    int getValidPositiveInt(const string& prompt);
    char getValidCharInput(const string& prompt, const string& validOptions);
    void clearInputStream();

    // Getters 
    string getGoal() const { return goal; }
    string getType() const { return type; }
    double getTarget() const { return target; }
    string getDeadline() const { return deadline; } 
    string getStatus() const { return status; } 
    double getCurrentPR() const { return currentPR; }
    double getNewPR() const { return newPR; }
    double getImprovement() const { return improvement; }
    double getPercentage() const { return percentage; }
    
    // Setters
    void setGoal(string g) { goal = g; }
    void setType(string t) { type = t; }
    void setTarget(double t) { target = t; }
    void setDeadline(string d) { deadline = d; }
    void setStatus(string s) { status = s; }
    void setCurrentPR(double pr) { currentPR = pr; }
    void setNewPR(double pr) { newPR = pr; }

    // UI
    void clearScreen();
    void line() const;
};

#endif
