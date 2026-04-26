#include <gtest/gtest.h>

#include "Client.h"
#include "Goal.h"
#include "Session.h"
#include "Trainer.h"
#include "WorkoutPlan.h"
#include "Exercise.h"

TEST(SessionTests, AddSessionThrowsForDuplicateId)
{
    Session manager;
    Session session(9001, "Strength AM", "Markuss", 21, 4, 2026, "08:00", 10);

    EXPECT_NO_THROW(manager.addSession(session));
    EXPECT_THROW(manager.addSession(session), SessionException);
}

TEST(SessionTests, BookSessionByIdReducesAvailableSpaces)
{
    Session manager;
    Session session(9002, "Yoga Flow", "Markuss", 22, 4, 2026, "09:00", 5);

    ASSERT_NO_THROW(manager.addSession(session));
    EXPECT_TRUE(manager.bookSessionById(9002));
}

TEST(SessionTests, BookSessionByIdFailsForMissingSession)
{
    Session manager;
    EXPECT_FALSE(manager.bookSessionById(9999));
}

TEST(WorkoutPlanTests, AddExerciseStoresExerciseAndIncreasesCount)
{
    WorkoutPlan plan("WP201", "Upper Body", "22/04/2026", "22/06/2026");
    Exercise benchPress("Strength", "Bench Press", "Chest", "Barbell");

    EXPECT_TRUE(plan.addExercise(benchPress));
    EXPECT_EQ(plan.getExerciseCount(), 1);
    ASSERT_NE(plan.findExercise("Bench Press"), nullptr);
    EXPECT_EQ(plan.findExercise("Bench Press")->getMuscleGroup(), "Chest");
}

TEST(WorkoutPlanTests, RemoveExerciseDeletesStoredExercise)
{
    WorkoutPlan plan("WP202", "Leg Day", "22/04/2026", "22/06/2026");
    Exercise squat("Strength", "Squat", "Legs", "Barbell");

    ASSERT_TRUE(plan.addExercise(squat));
    ASSERT_EQ(plan.getExerciseCount(), 1);

    EXPECT_TRUE(plan.removeExercise("Squat"));
    EXPECT_EQ(plan.getExerciseCount(), 0);
    EXPECT_EQ(plan.findExercise("Squat"), nullptr);
}

TEST(TrainerTests, AssignClientsAddsValidClient)
{
    Trainer trainer("Bio", "Cert", 4.5, 5, 0, 3, 50.0, "Weekdays");
    Client client(501, "Aoife", "aoife@test.com", 871111111, 1, 1, 2000, "pass", 165, 60, "Build Strength");

    EXPECT_NO_THROW(trainer.assignClients(client));
    EXPECT_EQ(trainer.getClients(), 1);
}

TEST(TrainerTests, AssignClientsThrowsForDuplicateClient)
{
    Trainer trainer("Bio", "Cert", 4.5, 5, 0, 3, 50.0, "Weekdays");
    Client client(502, "Daniel", "daniel@test.com", 872222222, 2, 2, 2001, "pass", 180, 75, "Lose Weight");

    ASSERT_NO_THROW(trainer.assignClients(client));
    EXPECT_THROW(trainer.assignClients(client), runtime_error);
}

TEST(TrainerTests, AssignClientsThrowsForEmptyClientName)
{
    Trainer trainer("Bio", "Cert", 4.5, 5, 0, 3, 50.0, "Weekdays");
    Client client(503, "", "empty@test.com", 873333333, 3, 3, 2002, "pass", 170, 70, "General Fitness");

    EXPECT_THROW(trainer.assignClients(client), invalid_argument);
}

TEST(ClientTests, SetCurrentGoalStoresGoalInClientList)
{
    Client client(601, "Sophie", "sophie@test.com", 874444444, 4, 4, 2003, "pass", 168, 58, "Improve Fitness");
    Goal goal(701, 50, 30, 0, 0, 'D', 0, "Bench Press", "Strength", 70, "30/09/2026", 0, 0, "Not Started");

    client.setCurrentGoal(goal);

    ASSERT_EQ(client.getClientGoals().size(), 1);
    EXPECT_EQ(client.getClientGoals()[0].getId(), 701);
    EXPECT_EQ(client.getClientGoals()[0].getGoal(), "Bench Press");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
