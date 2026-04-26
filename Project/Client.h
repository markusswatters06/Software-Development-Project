#ifndef CLIENT_H
#define CLIENT_H

#include <vector>

#include "User.h"
#include "Session.h"
#include "Goal.h"
#include "Cardio.h"
#include "Exercise.h"
#include "WorkoutPlan.h"
#include "WorkoutExercise.h"

class Client : public User{
    private:
        double height, weight;
        string goal;
        vector<int> bookedSessionIds;
        vector<Goal> clientGoals;
        Session* bookedSession;
        Goal* currentGoal;
        Cardio cardioWorkout;
        Exercise currentExercise;
        WorkoutPlan currentWorkoutPlan;
        WorkoutExercise currentWorkoutExercise;

        void initializeWorkoutData();
        void syncWorkoutLinks();
        //void printProfileDetails() const;

    public:
        // Constructors & Destructors
        Client(); 
        Client(double h, double w, string g); 
        Client(int i, string n, string e, int ph, int dd, int dm, int dy, string p, double h, double w, string g); 
        Client(const Client& other);
        Client& operator=(const Client& other);
        ~Client();

        // Operator Overloading
        bool operator==(const Client& other) const;
        friend ostream& operator<<(ostream& os, const Client& client);


        // Getters
        double getHeight(){return height;}
        double getWeight(){return weight;}
        string getGoal(){return goal;}
        const vector<Goal>& getClientGoals() const { return clientGoals; }


        // Setters
        void setHeight(double h){height = h;}
        void setWeight(double w){weight = w;}
        void setGoal(string g){goal = g;}
        void setBookedSession(const Session& session);
        void setCurrentGoal(const Goal& newGoal);
        void setWorkoutTester(const WorkoutPlan& workoutPlan, string exerciseName, int sets, int reps, int restTime);
        bool hasBookedSession(int sessionId) const;


        // Functions
        void registerAccount() override;
        
        // Menus
        virtual void displayMenu();
        void workoutMenu();
        void sessionMenu();
        void goalMenu();

        // Profile
        void displayDetails() override;
        void displayClients() const;
        void editProfile();


        // Workouts
        void displayWorkouts();
        void displayCurrentWorkout() const;
        void createWorkout();
        void editWorkout();
        void removeWorkout();

        // Goals
        void addGoal(const Goal& goal);
        void editGoal();
        void removeGoal();
        void displayGoal();
        void displayGoals();
        void updateProgress();
        void updateDeadline();
        void updateStatus();
        void checkProgress();

        //Sessions
        void viewSession();
        void bookSession();
        void unbookSession();


        // UI
        void clearScreen();
        void line();
        void lineLong();
        void dashedLine();
};
#endif
