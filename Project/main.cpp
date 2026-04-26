#include "User.h"
#include "Client.h"
#include "Trainer.h"
#include "Session.h"
#include "Goal.h"
#include "Cardio.h"
#include "Exercise.h"
#include "WorkoutPlan.h"
#include "WorkoutExercise.h"

int main()
{   
    // Trainer Testers
    Trainer t("Experienced personal trainer with a passion for helping clients achieve their fitness goals. Certified in strength training, weight loss, and functional fitness. Dedicated to creating personalized workout plans that deliver results.", "ACE Certified Personal Trainer", 4.8, 10, 20, 5, 50.0, "Weekdays: 9am - 5pm");
    t.setId(1);
    t.setName("Markuss");
    t.setEmail("markuss@fitzone.com");
    t.setPhone(871234567);
    t.setDobDay(12);
    t.setDobMonth(5);
    t.setDobYear(1998);
    t.setPassword("trainer123");

    // Premade Client Testers
    Client c1(101, "Markuss Watters", "markuss@gmail.com", 871111111, 28, 6, 2006, "markuss123", 190, 90, "Build Muscle");
    Client c2(102, "Kevin Chen", "kevin@gmail.com", 872222222, 6, 8, 1999, "kevin123", 190, 82, "Lose Weight");
    Client c3(103, "Sophie Murphy", "sophie@gmail.com", 873333333, 22, 1, 2001, "sophie123", 165, 58, "Improve Fitness");
    Client c4(104, "Aoife Byrne", "aoife@gmail.com", 874444444, 14, 3, 2002, "aoife123", 172, 68, "Improve Endurance");
    Client c5(105, "Daniel Smith", "daniel@gmail.com", 875555555, 9, 11, 1997, "daniel123", 181, 76, "Get Stronger");

    // Add premade clients to trainer client list
    t.addAvailableClient(c1);
    t.addAvailableClient(c2);
    t.addAvailableClient(c3);
    t.addAvailableClient(c4);
    t.addAvailableClient(c5);

    // Assigned-client test 
    t.assignClients(c1);
    t.assignClients(c2);

    // Premade Goal testers
    Goal goalManager;
    Goal g1(1, 50, 30, 0, 0, 'D', 10, "Squat", "Strength", 90, "30/09/2024", 100, 0, "Not Started");
    Goal g2(2, 30, 20, 0, 0, 'D', 10, "5km Run", "Cardio", 25, "31/12/2024", 0, 0, "Not Started");
    Goal g3(3, 40, 25, 0, 0, 'D', 10, "Deadlift", "Strength", 80, "30/09/2024", 100, 0, "Not Started");
    Goal g4(4, 35, 20, 0, 0, 'D', 10, "Cycle Ride", "Cardio", 30, "31/12/2024", 0, 0, "Not Started");

    // Add premade goals to clients
    goalManager.addGoal(g1);
    goalManager.addGoal(g2);
    goalManager.addGoal(g3);
    goalManager.addGoal(g4);

    c1.setCurrentGoal(g1);
    c2.setCurrentGoal(g2);
    t.setCurrentGoal(g3);
    t.setCurrentGoal(g4);
    

    // Premade Session Testers
    Session sessionManager;

    Session s1(1, "Morning Yoga", "Markuss", 21, 4, 2026, "08:00", 10);
    Session s2(2, "Evening HIIT", "Markuss", 21, 4, 2026, "18:00", 0);
    Session s3(3, "Strength Circuit", "Markuss", 22, 4, 2026, "12:00", 12);
    Session s4(4, "Spin Class", "Markuss", 23, 4, 2026, "17:30", 15);
    Session s5(5, "Mobility Flow", "Markuss", 24, 4, 2026, "07:30", 10);

    sessionManager.addSession(s1);
    sessionManager.addSession(s2);
    sessionManager.addSession(s3);
    sessionManager.addSession(s4);
    sessionManager.addSession(s5);

    // Premade Workout Testers
    WorkoutPlan workoutManager;

    Exercise benchPress("Strength", "Bench Press", "Chest", "Barbell");
    Exercise squat("Strength", "Squat", "Legs", "Barbell");
    Exercise latPulldown("Strength", "Lat Pulldown", "Back", "Cable Machine");
    Exercise shoulderPress("Strength", "Shoulder Press", "Shoulders", "Dumbbells");
    Exercise deadlift("Strength", "Deadlift", "Back", "Barbell");
    Exercise bicepCurl("Strength", "Bicep Curl", "Arms", "Dumbbells");
    Exercise legPress("Strength", "Leg Press", "Legs", "Machine");

    WorkoutPlan strengthPlan("WP101", "Upper Body Builder", "22/04/2026", "22/06/2026");
    strengthPlan.addExercise(benchPress);
    strengthPlan.addExercise(latPulldown);

    WorkoutPlan pullPlan("WP102", "Pull Strength", "22/04/2026", "22/05/2026");
    pullPlan.addExercise(latPulldown);
    pullPlan.addExercise(bicepCurl);

    WorkoutPlan legPlan("WP103", "Leg Strength", "22/04/2026", "22/06/2026");
    legPlan.addExercise(squat);
    legPlan.addExercise(legPress);

    WorkoutPlan pushPlan("WP104", "Push Power", "25/04/2026", "25/06/2026");
    pushPlan.addExercise(benchPress);
    pushPlan.addExercise(shoulderPress);

    WorkoutPlan fullBodyPlan("WP105", "Full Body Strength", "26/04/2026", "26/05/2026");
    fullBodyPlan.addExercise(deadlift);
    fullBodyPlan.addExercise(squat);

    // Add premade workout plans to shared trainer/client workout list
    workoutManager.addPlan(strengthPlan);
    workoutManager.addPlan(pullPlan);
    workoutManager.addPlan(legPlan);
    workoutManager.addPlan(pushPlan);
    workoutManager.addPlan(fullBodyPlan);

    // Premade workout exercise testers
    WorkoutExercise workoutExercise1(&strengthPlan, strengthPlan.findExercise("Bench Press"), 4, 10, 90);
    WorkoutExercise workoutExercise2(&pullPlan, pullPlan.findExercise("Lat Pulldown"), 3, 12, 60);
    WorkoutExercise workoutExercise3(&legPlan, legPlan.findExercise("Squat"), 5, 5, 120);
    WorkoutExercise workoutExercise4(&pushPlan, pushPlan.findExercise("Shoulder Press"), 4, 8, 75);
    WorkoutExercise workoutExercise5(&fullBodyPlan, fullBodyPlan.findExercise("Deadlift"), 4, 6, 120);

    // Assign premade workout testers to clients
    c1.setWorkoutTester(strengthPlan, "Bench Press", 4, 10, 90);
    c2.setWorkoutTester(pullPlan, "Lat Pulldown", 3, 12, 60);
    c3.setWorkoutTester(legPlan, "Squat", 5, 5, 120);
    c4.setWorkoutTester(pushPlan, "Shoulder Press", 4, 8, 75);
    c5.setWorkoutTester(fullBodyPlan, "Deadlift", 4, 6, 120);



    t.displayMenu();

    return 0; 
};
