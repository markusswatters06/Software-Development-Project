#ifndef WORKOUT_H
#define WORKOUT_H

#include <iostream>
using namespace std;

class Workout {
    private:
    	string exercise;
        int sets;
        int reps;
        float weight;
        int mins;
        int tenSeconds;
        int seconds;

    public:
        Workout();
        Workout(string e, int st, int r, float w, int m, int t, int s);
        ~Workout();

        // Setters
        void setExercise(string e){exercise = e;}
        void setSets(int st){sets = st;}
        void setReps(int r){reps = r;}
        void setWeight(float w){weight = w;}
        void setTenSeconds(int t){tenSeconds = t;}
        void setSeconds(int s){seconds = s;}
        void setMins(int m){mins = m;}

        // Getters
        string getExercise(){return exercise;}
        int getSets(){return sets;}
        int getReps(){return reps;}
        float getWeight(){return weight;}        
        int getTenSeconds(){return tenSeconds;}
        int getSeconds(){return seconds;}
        int getMins(){return mins;}

        // Functions
        void displayDetails();
        void displayDetailsTest();
};
#endif