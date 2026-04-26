#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "User.h"

using namespace std;

#ifndef _GOAL_
#define _GOAL_

class Goal
{
    private: 
    static int nextGoalId;
    int id;
    double currentPR; 
    int days;
    int months; 
    int years; 
    char timePeriod; 
    
    string goal; 
    string type; 
    double target; 
    string deadline; 
    double newPR;
    
    string status; 

    static vector<Goal> goalList;
    static int goalIndex(int goalId);


    public: 
    double improvement;
    double percentage;
    Goal(); 
    Goal(int gid, double currentPR, int days, int months, int years, char timePeriod, double percentage, string goal, string type, double target, string deadline, double newPR, double improvement, string status);
    virtual ~Goal() {}


    virtual void checkProgress();
    virtual void updateStatus();
    virtual void updateProgress(); 
    virtual void addGoal(const Goal& goal);
    virtual void editGoal();
    virtual void removeGoal();
    virtual void displayGoals() const;
    virtual void displayGoal(); 
    virtual void updateDeadline();
    
    bool isValidExercise(const string& exercise);
    
    // Input validation helper functions
    double getValidPositiveDouble(const string& prompt);
    int getValidPositiveInt(const string& prompt);
    char getValidCharInput(const string& prompt, const string& validOptions);

    // Getters 
    int getId() const { return id; }
    string getGoal() const { return goal; }
    string getType() const { return type; }
    double getTarget() const { return target; }
    string getDeadline() const { return deadline; } 
    string getStatus() const { return status; } 
    double getCurrentPR() const { return currentPR; }
    double getNewPR() const { return newPR; }
    double getImprovement() const { return improvement; }
    double getPercentage() const { return percentage; }
    string setType(); 
    virtual string getSummary() const;

    // Setters
    void setId(int gid){ id = gid; }
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
    void lineLong() const;
    void dashedLine() const;
};

#endif
