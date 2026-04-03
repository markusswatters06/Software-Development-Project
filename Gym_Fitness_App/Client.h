#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"

#include <iostream>
using namespace std;

class Client : public User{
    private:
        double height, weight;
        string membershipType, goal;
        int expiryDay, expiryMonth, expiryYear;

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
        void getExpiryDate(int &ed, int &em, int &ey)
        {
                ed = expiryDay;
                em = expiryMonth;
                ey = expiryYear;
        }


        // Setters
        void setHeight(double h){height = h;}
        void setWeight(double w){weight = w;}
        void setMembershipType(string mt){membershipType = mt;}
        void setGoal(string g){goal = g;}
        void setExpiryDate(int ed, int em, int ey){expiryDay = ed; expiryMonth = em; expiryYear = ey;}


        // Functions

        // Menus
        void displayMenu() override;
        void workoutMenu();
        void sessionMenu();
        void membershipMenu();
        void progressMenu();

        // Profile
        void displayDetails() override;
        void editProfile();

        // Workouts
        void displayWorkout();
        void editWorkout();
        void logWorkout();

        //Sessions
        void viewSession();
        void bookSession();

        // Progress
        void viewProgress();
        void editProgress();

        // Membership
        void renewMembership();
        void upgradeMembership();

        // UI
        void clearScreen();
        void line();
        void title(string t);
};
#endif