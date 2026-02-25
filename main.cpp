#include "Login.h"

using namespace std;

int main()
{
    // Testing Constructor
    Workout w1("Bench Press", 3, 12, 120, 57, 5, 6);
    //w1.displayDetails();
    w1.displayDetailsTest();

    // Testing Setters
    Workout w2;
    w2.setExercise("Squats");
    w2.setSets(6);
    w2.setReps(8);
    w2.setWeight(100);
    w2.setMins(25);
    w2.setTenSeconds(4);
    w2.setSeconds(9);
    w2.displayDetailsTest();
    cin >> x;

    return 0;
};
