#include "Goal.h"
#ifndef _CARDIO_
#define _CARDIO_

class Cardio : public Goal {
    private:
        string cardioType;
        double distance;           // Distance in km
        double currentPaceMin;     // Current pace minutes per km
        double currentPaceSec;     // Current pace seconds per km
        double targetPaceMin;      // Target pace minutes per km
        double targetPaceSec;      // Target pace seconds per km
        double newPaceMin;         // Latest pace minutes per km
        double newPaceSec;         // Latest pace seconds per km
        double improvementMin;     // Improvement in minutes
        double improvementSec;     // Improvement in seconds
        double percentage;         // Percentage toward goal
        
        // Helper functions
        double convertToSeconds(double minutes, double seconds) const;
        void convertToMinSec(double totalSeconds, double& minutes, double& seconds) const;
        void displayTime(double minutes, double seconds) const;
        void displayTotalTime(double totalSeconds) const;
        void getValidPaceInput(const string& prompt, double& minutes, double& seconds);
        
    public:
        Cardio();
        virtual ~Cardio() {}
        
        void setCardioType(string ct);
        string getCardioType() const;
        double getDistance() const { return distance; }
        
        // Override virtual functions
        void startingPoint() override;
        void updateProgress() override;
        void checkProgress() override;
        void displayDetails() override;
        void updateStatus() override;
};

#endif