#ifndef SESSION_H
#define SESSION_H

#include <iostream>
using namespace std;

class Session{
    private:
        int id;
        string sessionName;
        string trainerName;
        int sessionDay;
        int sessionMonth;
        int sessionYear;
        string time;
        int spacesAvailable;
    
    public:
        // Constructors & Destructors
        Session();
        Session(int i, string sn, string tn, int sd, int sm, int sy, string t, int sa);
        ~Session();


        // Getters
        int getId(){return id;}
        string getSessionName(){return sessionName;}
        string getTrainerName(){return trainerName;}
        int getSessionDay(){return sessionDay;}
        int getSessionMonth(){return sessionMonth;}
        int getSessionYear(){return sessionYear;}
        string getTime(){return time;}
        int getSpacesAvailable(){return spacesAvailable;}

        // Setters
        void setId(int sid){id = sid;}
        void setSessionName(string sn){sessionName = sn;}
        void setTrainerName(string tn){trainerName = tn;}
        void setSessionDay(int sd){sessionDay = sd;}
        void setSessionMonth(int sm){sessionMonth = sm;}
        void setSessionYear(int sy){sessionYear = sy;}
        void setTime(string st){time = st;}
        void setSpacesAvailable(int sa){spacesAvailable = sa;}


        // Functions
        void createSession();
        void displaySession();
        void editSession();
        void bookSession();
        bool getValidDate(int& dd, int& dm, int& dy);
        
        //UI
        void clearScreen();
        void line();
};
#endif