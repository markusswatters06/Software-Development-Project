#include "Cardio.h"

//Cardio::Cardio(string g, string t, double tar, string d) : goal(g), type("Cardio"), deadline(d), status(){}


void Cardio :: displayCardio(){
    cout << "Goal: " << getGoal() << endl; 
    cout << "Type:  " << getType() << endl; 
    cout << "Target: " << getTarget() << endl; 
    cout << "Deadline: " << getDeadline() << endl; 
    cout << "Status: " << getStatus() << endl; 

}