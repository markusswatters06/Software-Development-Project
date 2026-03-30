#include "User.h"
#include "Signup.h"
#include "Login.h"

int x;

int main()
{
    // Testing User
    User u1(1, "user1", "pass1");
    u1.displayDetails();

    
    // Testing Signup
    Signup s;
    s.registerAccount();
    s.displayDetails();


    // Testing Login
    Login l;
    l.setId(s.getId());
    l.setUsername(s.getUsername());
    l.setPassword(s.getPassword());
    string u, p;
    l.displayLogin(u,p);
    l.loginUser(u,p);



    cin.ignore();
    cin.get();
    return 0; 
};
