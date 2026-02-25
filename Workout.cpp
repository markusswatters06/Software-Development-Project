#include "Workout.h"
Workout::Workout()
{
	exercise = "N/A";
    sets = 0;
    reps = 0;
    weight = 0.00;
    mins = 0;
    tenSeconds = 0;
    seconds = 0;
    //cout << "Default Constructor Called\n";
}
Workout::Workout(string e, int st, int r, float w, int m, int t, int s)
{
	exercise = e;
    sets = st;
    reps = r;
    weight = w;
    mins = m;
    tenSeconds = t;
    seconds = s;
    //cout << " Constructor Called\n";
}

Workout::~Workout()
{

}

void Workout::displayDetails()
{
    cout << "-------------------" << endl;
	cout << "\n" << exercise << endl;
    cout << "-Sets: " << sets << endl;
    cout << "-Reps: " << reps << endl;
    cout << "-Weight: " << weight << "kg" << endl;
    cout << "-Time: " << mins << ":" << tenSeconds << seconds << endl;
    cout << "-------------------\n" << endl;
    if (tenSeconds > 5 || tenSeconds < 0)
    {
    	cout << "ERROR: Please insert a number between 0-5!\n";
    }
    if (seconds > 9 || seconds < 0)
    {
    	cout << "ERROR: Please insert a number between 0-9!\n";
    }

}

void Workout::displayDetailsTest()
{
    cout << "|______________________|" << endl;
    cout << "|                      |" << endl;
	cout << "|     " << exercise << "      |"<< endl;
    cout << "|                      |" << endl;
    cout << "|----------------------|" << endl;
    cout << "| Sets | Reps | Weight |\n";
    cout << "|----------------------|" << endl;
    cout << "|   1  |  " << reps << "  |  " << weight << "kg |" << endl;
    cout << "|   2  |  " << reps << "  |  " << weight << "kg |" << endl;
    cout << "|   3  |  " << reps << "  |  " << weight << "kg |" << endl;
    cout << "|   4  |  " << reps << "  |  " << weight << "kg |" << endl;
    cout << "|______________________|\n" << endl;
    if (tenSeconds > 5 || tenSeconds < 0)
    {
    	cout << "ERROR: Please insert a number between 0-5!\n";
    }
    if (seconds > 9 || seconds < 0)
    {
    	cout << "ERROR: Please insert a number between 0-9!\n";
    }

}
