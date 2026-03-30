#include "Signup.h"

Signup::Signup() : User(){}

Signup::Signup(int i,string fn, string sn, string e, int ph, int dd, int dm, int dy, string p)
    : User(i,fn,sn,e,ph,dd,dm,dy,p){}

void Signup::registerAccount()
{
    int i, ph, dd, dm, dy;
    string fn, sn, e, p;

    cout << "\nEnter Name " << endl;
    cout << "(First Name): ";
    cin >> fn;

    cout << "(Surname): ";   
    cin >> sn;

    cout << "\nEnter Email Address: ";
    cin >> e;

    cout << "\nEnter Phone Number: ";
    cin >> ph;
    
    cout << "Enter Date of Birth\n";
    getValidDate(dd, dm, dy);

    cout << "\nEnter ID: ";
    cin >> i;

    cout << "\nEnter Password: "; 
    cin >> p;
    
    setId(i);
    setFirstName(fn);
    setSurname(sn);
    setEmail(e);
    setPhone(ph);
    setDobDay(dd);
    setDobMonth(dm);
    setDobYear(dy);
    setPassword(p);

    cout << "\nSignup Successful!" << endl;
}
