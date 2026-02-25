#include "Login.h"
#include <iostream>
using namespace std;

// Function declarations
void showLogo();
string hideInput();
void clearScreen();
void pressAnyKey();
bool login(Login &auth);
void registerUser(Login &auth);
void setGoal(User &user);
void dashboard(Login &auth);
void showProfile(User *user);
void updateGoal(User *user);

int main() {
    Login auth;
    
    showLogo();
    
    while(true) {
        cout << "\n====================\n";
        cout << "   FITNESS TRACKER  \n";
        cout << "====================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            if(login(auth)) {
                dashboard(auth);
            }
        }
        else if(choice == 2) {
            registerUser(auth);
            if(auth.getCurrentUser() != NULL) {
                dashboard(auth);
            }
        }
        else if(choice == 3) {
            cout << "\nGoodbye!\n";
            break;
        }
        else {
            cout << "\nInvalid choice!\n";
            pressAnyKey();
        }
    }
    
    return 0;
}

void showLogo() {
    cout << R"(
 _____ _ _                         _____               _             
|  ___(_) |_ _ __   ___  ___ ___  |_   _| __ __ _  ___| | _____ _ __ 
| |_  | | __| '_ \ / _ \/ __/ __|   | || '__/ _` |/ __| |/ / _ \ '__|
|  _| | | |_| | | |  __/\__ \__ \   | || | | (_| | (__|   <  __/ |   
|_|   |_|\__|_| |_|\___||___/___/   |_||_|  \__,_|\___|_|\_\___|_|   
| |__  _   _                                                            
| '_ \| | | |                                                           
| |_) | |_| |                                                           
|_.__/ \__, |                                                           
 __  __|___/       _                     ___     _  __          _       
|  \/  | __ _ _ __| | ___   _ ___ ___   ( _ )   | |/ /_____   _(_)_ __  
| |\/| |/ _` | '__| |/ / | | / __/ __|  / _ \/\ | ' // _ \ \ / / | '_ \
| | |  | (_| | |  |   <| |_| \__ \__ \ | (_>  < | . \  __/\ V /| | | | |
|_|  |_|\__,_|_|  |_|\_\\__,_|___/___/  \___/\/ |_|\_\___| \_/ |_|_| |_|
    )" << endl;
    cout << "\nPress ENTER to continue..." << endl;
}

string hideInput() {
    string input = "";
    char ch;
    while(true) {
        if(ch == 13) break;
        if(ch == 8 && input.length() > 0) {
            cout << "\b \b";
            input.pop_back();
        }
        else if(ch != 8) {
            input += ch;
            cout << "*";
        }
    }
    cout << endl;
    return input;
}

void clearScreen() {
    system("cls");
}

void pressAnyKey() {
    cout << "\nPress any key to continue...";
}

bool login(Login &auth) {
    clearScreen();
    cout << R"(
 _                _       
| |    ___   __ _(_)_ __  
| |   / _ \ / _` | | '_ \ 
| |__| (_) | (_| | | | | |
|_____\___/ \__, |_|_| |_|
            |___/          
    )" << endl;
    cout << "Email: ";
    string email;
    getline(cin, email);
    
    cout << "Password: ";
    string pass;
    getline(cin,pass);

    
    User found;
    if(auth.findUser(email, found) && found.getPassword() == pass) {
        User* loggedIn = new User();
        *loggedIn = found;
        auth.setCurrentUser(loggedIn);
        cout << "\nLogin successful!\n";
        return true;
    }
    
    cout << "\nInvalid credentials!\n";
    pressAnyKey();
    return false;
}

void registerUser(Login &auth) {
    clearScreen();
    cout << R"(
 ____            _     _            
|  _ \ ___  __ _(_)___| |_ ___ _ __ 
| |_) / _ \/ _` | / __| __/ _ \ '__|
|  _ <  __/ (_| | \__ \ ||  __/ |   
|_| \_\___|\__, |_|___/\__\___|_|   
           |___/                    
    )" << endl;
    
    cout << "Email: ";
    string email;
    getline(cin, email);
    
    User existing;
    if(auth.findUser(email, existing)) {
        cout << "\nEmail already exists!\n";
        pressAnyKey();
        return;
    }
    
    cout << "Password: ";
    string pass;
    getline(cin,pass);
    
    User newUser;
    newUser.setEmail(email);
    newUser.setPassword(pass);
    
    cout << "Name: ";
    string name;
    getline(cin, name);
    newUser.setName(name);
    
    cout << "Age: ";
    int age;
    cin >> age;
    newUser.setAge(age);
    
    cout << "Height (m): ";
    double height;
    cin >> height;
    newUser.setHeight(height);
    
    cout << "Weight (kg): ";
    double weight;
    cin >> weight;
    newUser.setWeight(weight);
    
    cout << "\nFitness Level:\n";
    cout << "1. Beginner\n";
    cout << "2. Intermediate\n";
    cout << "3. Advanced\n";
    cout << "Choice: ";
    int level;
    cin >> level;
    cin.ignore();
    
    if(level == 1) newUser.setFitnessLevel("Beginner");
    else if(level == 2) newUser.setFitnessLevel("Intermediate");
    else newUser.setFitnessLevel("Advanced");
    
    setGoal(newUser);
    
    auth.addUser(newUser);
    
    User* current = new User();
    *current = newUser;
    auth.setCurrentUser(current);
    
    cout << "\nRegistration successful!\n";
}

void setGoal(User &user) {
    clearScreen();
    cout << R"(
 ____       _    __   __                  ____             _   _ 
/ ___|  ___| |_  \ \ / /__  _   _ _ __   / ___| ___   __ _| | | |
\___ \ / _ \ __|  \ V / _ \| | | | '__| | |  _ / _ \ / _` | | | |
 ___) |  __/ |_    | | (_) | |_| | |    | |_| | (_) | (_| | | |_|
|____/ \___|\__|   |_|\___/ \__,_|_|     \____|\___/ \__,_|_| (_)
    )" << endl;
    cout << "1. Weight Loss\n";
    cout << "2. Build Muscle\n";
    cout << "3. Increase Strength\n";
    cout << "4. Improve Endurance\n";
    cout << "5. General Fitness\n";
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    string goal;
    if(choice == 1) goal = "Weight Loss";
    else if(choice == 2) goal = "Build Muscle";
    else if(choice == 3) goal = "Increase Strength";
    else if(choice == 4) goal = "Improve Endurance";
    else goal = "General Fitness";
    
    user.setFitnessGoal(goal);
    cout << "\nGoal set to: " << goal << "!\n";

}

void dashboard(Login &auth) {
    while(true) {
        clearScreen();
        cout << R"(
 ____            _     _                         _ 
|  _ \  __ _ ___| |__ | |__   ___   __ _ _ __ __| |
| | | |/ _` / __| '_ \| '_ \ / _ \ / _` | '__/ _` |
| |_| | (_| \__ \ | | | |_) | (_) | (_| | | | (_| |
|____/ \__,_|___/_| |_|_.__/ \___/ \__,_|_|  \__,_|
        )" << endl;
        
        User* user = auth.getCurrentUser();
        if(user != NULL) {
            cout << "\nName: " << user->getName() << endl;
            cout << "Goal: " << user->getFitnessGoal() << endl;
        }
        
        cout << "\n1. View Profile\n";
        cout << "2. Update Goal\n";
        cout << "3. Start Workout\n";
        cout << "4. View Progress\n";
        cout << "5. Logout\n";
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) showProfile(user);
        else if(choice == 2) updateGoal(user);
        else if(choice == 3) {
            cout << "\nWorkout feature coming soon!\n";
            pressAnyKey();
        }
        else if(choice == 4) {
            cout << "\nProgress feature coming soon!\n";
            pressAnyKey();
        }
        else if(choice == 5) {
            auth.logout();
            break;
        }
    }
}

void showProfile(User *user) {
    if(user == NULL) return;
    
    clearScreen();
    cout << R"(
 ____             __ _ _      
|  _ \ _ __ ___  / _(_) | ___ 
| |_) | '__/ _ \| |_| | |/ _ \
|  __/| | | (_) |  _| | |  __/
|_|   |_|  \___/|_| |_|_|\___|
    )" << endl;
    cout << "Name: " << user->getName() << endl;
    cout << "Email: " << user->getEmail() << endl;
    cout << "Age: " << user->getAge() << endl;
    cout << "Height: " << user->getHeight() << " m\n";
    cout << "Weight: " << user->getWeight() << " kg\n";
    cout << "Fitness Level: " << user->getFitnessLevel() << endl;
    cout << "Fitness Goal: " << user->getFitnessGoal() << endl;
    pressAnyKey();
}

void updateGoal(User *user) {
    if(user == NULL) return;
    setGoal(*user);
}