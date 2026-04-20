#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"
#include "Session.h"
#include "Goal.h"

class Client : public User{
    private:
        double height, weight;
        string membershipType, goal;
        int expiryDay, expiryMonth, expiryYear;
        Session bookedSession;
        Goal currentGoal;

    public:
        // Constructors & Destructors
        Client(); 
        Client(double h, double w, string mt, string g, int ed, int em, int ey); 
        Client(int i, string n, string e, int ph, int dd, int dm, int dy, string p, double h, double w, string mt, string g, int ed, int em, int ey); 
        ~Client();


        // Getters
        double getHeight(){return height;}
        double getWeight(){return weight;}
        string getMembershipType(){return membershipType;}
        string getGoal(){return goal;}
        void getExpiryDate(int &ed, int &em, int &ey){ed = expiryDay; em = expiryMonth; ey = expiryYear;}


        // Setters
        void setHeight(double h){height = h;}
        void setWeight(double w){weight = w;}
        void setMembershipType(string mt){membershipType = mt;}
        void setGoal(string g){goal = g;}
        void setExpiryDate(int ed, int em, int ey){expiryDay = ed; expiryMonth = em; expiryYear = ey;}


        // Functions
        void registerAccount() override;
        
        // Menus
        void displayMenu() override;
        void workoutMenu();
        void sessionMenu();
        void membershipMenu();
        void goalMenu();

        // Profile
        void displayDetails() override;
        void editProfile();

        // Membership
        void renewMembership();
        void upgradeMembership();

        // Workouts
        void displayWorkout();
        void editWorkout();
        void logWorkout();

        // Goals
        void addGoal();
        void displayGoal();
        void updateProgress();
        void checkProgress();

        //Sessions
        void viewSession();
        void bookSession();


        // UI
        void clearScreen();
        void line();
        void title(string t);
};
#endif
