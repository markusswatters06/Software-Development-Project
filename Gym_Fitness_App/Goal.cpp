//C24466122 - Kevin Chen - Wednesday 8th of April near the end of the night 

#include "Goal.h"

Goal::Goal(){
    
}



void Goal::startingPoint(){

    cout << "Excerise you would like to improve upon: "; 
    getline(cin,goal); 
    cout << "\nCurrent personal best that you would like to improve upon [kg]: "; 
    cin >> currentPR;
    cout << "Enter final target to reach by the end of this goal [kg]:"; 
    cin >> target; 
    cout << "Time period you wish to accomplish this goal entering the following:"<< endl;
    cout << "[D] for Day(s)" << endl; 
    cout << "[M] for Month(s)" << endl;  
    cout << "[Y] for Year(s)" << endl;   

    cin >> timePeriod; 
    switch(timePeriod){

        default: 
        cout << "Please enter one of the following: " << endl;
        cout << "[D] for Day(s)" << endl; 
        cout << "[M] for Month(s)" << endl;  
        cout << "[Y] for Year(s)" << endl; 
        break; 
        
        case 'D': 
        cout << "Enter the No. of Day(s) have to accomplish your goal: "; 
        cin >> days; 
        cout << endl << endl; 
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << " kg" << endl; 
        cout << "-Completion date: " << days << " day(s)" << endl;
        break;

        case 'd': 
        cout << "Enter the No. of Day(s) have to accomplish your goal: "; 
        cin >> days; 
        cout << endl << endl;
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << "kg" << endl; 
        cout << "-Completion date: " << days << " day(s)" << endl;
        break;

        case 'M': 
        cout << "Enter the No. of Month(s) have to accomplish your goal: "; 
        cin >> months; 
        cout << endl << endl;
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << "kg" << endl; 
        cout << "-Completion date: " << months << " month(s)" << endl;
        break;

        case 'm': 
        cout << "Enter the No. of Month(s) have to accomplish your goal: "; 
        cin >> months; 
        cout << endl << endl;
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << "kg" << endl; 
        cout << "-Completion date: " << months << " month(s)" << endl;
        break;

        case 'Y': 
        cout << "Enter the No. of Year(s) have to accomplish your goal: "; 
        cin >> years; 
        cout << endl << endl;
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << "kg" << endl; 
        cout << "-Completion date: " << years << " year(s)" << endl;
        break;

        case 'y': 
        cout << "Enter the No. of Year(s) have to accomplish your goal: "; 
        cin >> years;
        cout << endl << endl;
        cout << "SUMMARY TABLE " << endl; 
        cout << "-Goal: to improve " << goal << endl;  
        cout << "-Current personal best: " << currentPR << "kg" << endl;
        cout << "-Final target to reach: " << target << "kg" << endl; 
        cout << "-Completion date: " << years << " year(s)" << endl;
        break; 
    }
    
}

void Goal::updateProgress(){
    cout << "Enter New PR[kg]: ";
    cin >> newPR;
}

void Goal :: setType(){
    if(goal == "Swim" || goal == "Run" || goal == "Cycle" || goal == "Row" || goal == "Walk" || goal == "Hike" || goal == "Jump" || goal == "Throw" || goal == "Climb" || goal == "Running" || goal == "Swimming" || goal == "Cycling" || goal == "Rowing" || goal == "Walking" || goal == "Hiking" || goal == "Jumping" || goal == "Throwing" || goal == "Climbing"){
        type = "Cardio";
    } else {
        type = "Strength";
    }
}

void Goal::checkProgress(){

    if (newPR > currentPR){
        improvement = newPR - currentPR;
        percentage = (improvement / (target - currentPR)) * 100;
    }else {
        newPR = currentPR;
        improvement = 0;
        percentage = 0;
    }

    if (percentage >=100) {
        cout << "-Goal Achieved!" << endl; 
        updateStatus();
    } else if (percentage >= 90){
        cout << "-Nearly there! Keep up the good work!" << endl; 
        cout << "-You have improved your PR by:  " << improvement << " kg (" << percentage << "%)" << endl;
        updateStatus();
    } else if (percentage >= 75){
        cout << "-Excellent Progress!" << endl; 
        cout << "-You have improved your PR by:  " << improvement << " kg (" << percentage << "%)" << endl;
        updateStatus();
    } else if (percentage >= 50){
        cout<< "-Good Progress!" << endl;
        cout << "-You have improved your PR by:  " << improvement << " kg (" << percentage << "%)" << endl; 
        updateStatus();
    } else if (percentage >= 25){
        cout << "-Making Progress!" << endl; 
        cout << "-You have improved your PR by:  " << improvement << " kg (" << percentage << "%)" << endl;
        updateStatus();
    } else {
        cout << "-Just getting started! Don't lose track of your Goal" << endl; 
        updateStatus();
    }
}

void Goal ::updateStatus(){
    if (percentage == 100){
        status = "Goal Achieved!";
    } else {
        status = "In Progress";
    }
}   


void Goal :: updateDeadline(){
    if(timePeriod == 'D' || timePeriod == 'd'){
        deadline = to_string(days) + " day";
    } else if (timePeriod == 'M' || timePeriod == 'm'){
        deadline = to_string(months) + " month";
    } else if (timePeriod == 'Y' || timePeriod == 'y'){
        deadline = to_string(years) + " year";
    }
}

void Goal::displayDetails(){
    cout << "Goal: " << getGoal() << endl; 
    cout << "Type:  " << getType() << endl; 
    cout << "Target: " << getTarget() << "kg" << endl; 
    cout << "Deadline: " << getDeadline() << endl; 
    cout << "Progress: improved by " << improvement << " kg (" << percentage << "%)" << endl;
    cout << "Status: " << getStatus() << endl; 
}




