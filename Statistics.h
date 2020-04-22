#pragma once

#include "student.h"
#include "registrar.h"

class Statistics {
private:
    double meanWait;
    double medianWait;
    int longestWait;
    int numStudentsLongWait;
    double meanWindowIdleTime;
    int longestWindowIdleTime;
    int numWindowsIdleOver5Min;

    int totalWaitTime;
    int totalStudentCount;

    int totalWindowIdleTime;
    int totalWindowBusyTime;

    int* studentWaitTime;
   
    int currentStudentIndex;
    int numWindows;

public:
    Statistics(int totalStudentCount, int numWindows);
    ~Statistics() { delete[] studentWaitTime; }

    void finishStudent(Student *student, int currentTime);
    void windowOccupied(RegistrarWindow *w, int currentTime);
    void windowVacated(RegistrarWindow *w, int currentTime);
    void printStats(int currentTime, RegistrarWindow* windows);
};
