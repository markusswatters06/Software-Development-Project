#ifndef _WEIGHTLOSS_
#define _WEIGHTLOSS_

#include "Goal.h"

class WeightLoss : public Goal {
private:
    double startWeight;
    double targetWeight;
    double currentWeight;
    std::string unit;

    std::string getValidUnit();

public:
    WeightLoss();
    virtual ~WeightLoss() {}

    // Overrides
    void addGoal() override;
    void updateProgress() override;
    void checkProgress() override;
    void displayGoal() override;
    void editGoal() override;
    void updateStatus() override;

    string getSummary() const override;
};

#endif