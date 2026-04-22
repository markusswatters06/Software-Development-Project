#ifndef _CARDIO_
#define _CARDIO_

#include "Goal.h"

class Cardio : public Goal {
private:
    string cardioType;
    double distance;
    double currentPaceMin, currentPaceSec;
    double targetPaceMin, targetPaceSec;
    double newPaceMin, newPaceSec;
    double improvementSec;   // total improvement in seconds (avoid duplicate percentage)

    // Helper functions (same as before)
    double convertToSeconds(double minutes, double seconds) const;
    void convertToMinSec(double totalSeconds, double& minutes, double& seconds) const;
    void displayTime(double minutes, double seconds) const;
    void displayTotalTime(double totalSeconds) const;
    void getValidPaceInput(const std::string& prompt, double& minutes, double& seconds);

public:
    Cardio();
    virtual ~Cardio() {}

    // Overrides
    void addGoal() override;
    void updateProgress() override;
    void checkProgress() override;
    void displayGoal() override;   
    void editGoal() override;      
    void updateStatus() override;

    // Getters / setters
    void setCardioType(string ct);
    string getCardioType() const { return cardioType;}
    double getDistance() const { return distance; }
    string getSummary() const override;
};

#endif