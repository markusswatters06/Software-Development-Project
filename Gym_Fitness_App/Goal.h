
#include <iostream> 
#include <limits>
using namespace std; 
//#include <chrono> // helps you measure time, store dates/times, and calculate differences between times

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
    //chrono::system_clock::time_point deadline; 
    // system_clock = Real-world wall clock time (like your watch)
    // time_point = Represents a specific date and time. Example: "December 31, 2024 at 3:00 PM"
    string status; 

    public: 
    //constructor 
    Goal(); 
    //Goal(string goal, string type, double target, string deadline, int day, int, int month, int year,  ); 

    //functions 
    void checkProgress();
    void updateStatus();
    void updateProgress(); 
    void startingPoint();
    void displayDetails(); 
    void updateDeadline();
    void setType(); 

    // Getters 
    string getGoal()const{return goal;}
    string getType() const{return type;}
    double getTarget() const{return target;}
    string getDeadline() const{return deadline;} 
    string getStatus() const{return status;} 
    

};


#endif
