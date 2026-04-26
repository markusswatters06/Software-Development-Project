#ifndef TRAINER_H
#define TRAINER_H

#include <vector>
#include <stdexcept>

#include "User.h"
#include "Session.h"
#include "Goal.h"
#include "Client.h"
#include "Cardio.h"
#include "Exercise.h"
#include "WorkoutPlan.h"
#include "WorkoutExercise.h"

class Client;

class Trainer : public User{
    private:
        string bio;             // Bio
        string cert;            // Certificates
        double rating;          // Rating (0-5)
        int yearsExp;           // Years of Experience
        int clients;            // Clients Assigned
        int sessionsPerWeek;    // Sessions Available per Week
        double sessionRate;     // Session Rate (€)
        string availablility;   // Session Availabilty
        Session trainerSession; //
        Goal* trainerGoal;  
        WorkoutPlan* trainerWorkout;;
        vector<WorkoutPlan> trainerWorkouts;
        vector<Goal> trainGoals;     
        vector<Client*> ownedClients;
        vector<Client*> assignedClients;
        bool isClientAssigned(int clientId) const;
        void printAvailableClientsTable() const;
        void printProfileDetails() const;

    public:
        // Constructors & Destructor
        Trainer();
        Trainer(string b, string c, double r, int ye, int cl, int spw, double sr, string a);
        ~Trainer();

        // Operator Overloading
        Trainer& operator+=(Client& client);
        bool operator==(const Trainer& other) const;
        friend ostream& operator<<(ostream& os, const Trainer& trainer);

        // Getters
        string getBio(){return bio;}
        string getCert(){return cert;}
        double getRating(){return rating;}
        int getYearsExp(){return yearsExp;}
        int getClients(){return clients;}
        int getSessionsPerWeek(){return sessionsPerWeek;}
        double getSessionRate(){return sessionRate;}
        string getAvailability(){return availablility;}

        // Setters
        void setBio(string b){bio = b;}
        void setCert(string c){cert = c;}
        void setRating(double r){rating = r;}
        void setYearsExp(int ye){yearsExp = ye;}
        void setClients(int cl){clients = cl;}
        void setSessionsPerWeek(int swp){sessionsPerWeek = swp;}
        void setSessionRate(double sr){sessionRate = sr;}
        void setAvailability(string a){availablility = a;}
        void setCurrentGoal(const Goal& newGoal);


        // Functions
        void registerAccount() override;
        
        // Menu
        void displayMenu();
        void displayDetails();
        void clientMenu();
        void sessionMenu();
        void workoutMenu();
        void goalMenu();

        // Profile
        void editProfile();

        // Clients
        void displayClients();
        void addAvailableClient(const Client& client);
        void assignClients();
        void assignClients(Client& client);
        void displayAssignedClients() const;
        void removeClients();

        // Session
        void createSession();
        void displaySession();
        void editSession();
        void removeSession();
        
        // Goal
        void addGoal(const Goal& goal);
        void editGoal();
        void removeGoal();
        void displayGoal();
        void displayGoals();
        void displayClientGoals();
        void updateProgress();
        void updateDeadline();
        void updateStatus();
        void checkProgress();

        // Workout
        void displayWorkouts();
        void createWorkout();
        void editWorkout();
        void removeWorkout();
        void displayClientWorkouts();

        // UI
        void clearScreen();
        void line() const;
        void lineLong();
        void dashedLine();
};
#endif
