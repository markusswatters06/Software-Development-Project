#include "User.h"
#include "Client.h"

int x;

int main()
{
/*// Testing User
    cout << "---Testing User Constructor---" << endl;
    User u1(1, "name1", "user1@email.com", 891, 30 , 03, 2026, "pass1");
    u1.displayMenu();

// Testing Signup
    User s;
    s.registerAccount();
    s.displayDetails();


// Testing Login
    User l;
    cout << "\n---Testing Login---" << endl;
    l.setId(s.getId());
    l.setName(s.getName());
    l.setPhone(s.getPhone());
    l.setEmail(s.getEmail());
    l.setPassword(s.getPassword());
    l.setDobDay(s.getDobDay());
    l.setDobMonth(s.getDobMonth());
    l.setDobYear(s.getDobYear());

    int i;
    string p;
    cout << "\n---Testing Logging In---" << endl;
    l.loggingIn(i,p);
    l.loginUser(i,p);
    cout << "\n---Test Successful---" << endl; 
    l.displayDetails();


// Testing Client
    User u4(1, "name1", "user1@email.com", 891, 30 , 03, 2026, "pass1");*/
    Client c1(1, "name1", "email1@email.com", 1234567890, 1, 1, 2000, "pass", 192.1, 90, "Gym", "Goal 1", 1, 4, 2026);
    c1.displayMenu();
    //c1.displayDetails();
    //c1.membershipMenu();
    //c1.progressMenu();
    //c1.workoutMenu();
    //c1.sessionMenu();



    cin.get();
    return 0; 
};
