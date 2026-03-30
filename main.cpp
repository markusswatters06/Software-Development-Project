#include "User.h"
#include "Signup.h"
#include "Login.h"

int x;

int main()
{
    // Testing User
    cout << "---Testing User Constructor---" << endl;
    User u1(1, "name1", "surname1", "user1@email.com", 891, 30 , 03, 2026, "pass1");
    u1.displayDetails();


    // Testing Signup
    Signup s;
    cout << "\n---Registering an Account---" << endl;
    s.registerAccount();
    s.displayDetails();


    // Testing Login
    Login l;
    cout << "\n---Testing Login---" << endl;
    l.setId(s.getId());
    l.setFirstName(s.getFirstName());
    l.setSurname(s.getSurname());
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


    cin.ignore();
    cin.get();
    return 0; 
};
