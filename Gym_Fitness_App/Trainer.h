#ifndef TRAINER_H
#define TRAINER_H

#include "User.h"
#include "Session.h"

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

    public:
        // Constructors & Destructor
        Trainer();
        Trainer(string b, string c, double r, int ye, int cl, int spw, double sr, string a);
        ~Trainer();

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
        void setBio(string b){b = bio;}
        void setCert(string c){c = cert;}
        void setRating(double r){r = rating;}
        void setYearsExp(int ye){ye = yearsExp;}
        void setClients(int cl){cl = clients;}
        void setSessionsPerWeek(int swp){swp = sessionsPerWeek;}
        void setSessionRate(double sr){sr = sessionRate;}
        void setAvailability(string a){a = availablility;}


        // Functions
        void registerAccount() override;
        
        // Menu
        void displayMenu();
        void displayDetails();
        void clientMenu();
        void sessionMenu();
        void workoutMenu();
        void progressMenu();

        // Profile
        void editProfile();

        // Session
        void createSession();
        void displaySession();
        void editSession();
        

        // UI
        void clearScreen();
        void line();
};
#endif
