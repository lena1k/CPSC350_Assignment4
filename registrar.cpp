#include <stdlib.h>
#include <iostream>
#include "registrar.h"
#include "student.h"
#include "Statistics.h"

using namespace std;

// initialize and create all windows 
Registrar::Registrar(int numWindows, int totalstudents) {
    this->stats = new Statistics(totalstudents, numWindows); // create a Statistics object
    this->numWindows = numWindows;                           
    this->windows = new RegistrarWindow[numWindows];         // create an array of windows
    for (int i = 0; i < numWindows; i++) {
        this->windows[i].isFree = true;
        this->windows[i].s = NULL;
        this->windows[i].timeLastOccupied = 0;
        this->windows[i].timeLastVacated = 0;
    }
    this->busy_windows = 0;
}
    

Registrar::~Registrar() {
    delete stats;
    delete windows;
}

// adding strudents to a window, method assumes there is a free window
void Registrar::add_student(Student* s, int current_time) {
    if (!any_window_free()) {
        cout << "Program error\n";
        exit(1);
    }
    for (int i = 0; i < numWindows; i++) {                      // loop for open window, if free
        if (windows[i].isFree) {
            s->finishedTime = current_time + s->waitTime;       // calculates finished time by adding current time and wait time of the student
            windows[i].s = s;                               
            windows[i].isFree = false;                          // window is no longer free
            busy_windows++;
            stats->windowOccupied(&windows[i], current_time);  
            return;                                 
        }
    }
}

// at each clock tick this function is called. Checks to see if any window service is expiring and should be freed
void Registrar::tiktok(int current_time) {
    if (any_window_busy()) {
        for (int i = 0; i < numWindows; i++) {
            if (!windows[i].isFree) {                                 // look for occupied windows
                if(windows[i].s->finishedTime == current_time) {      // check if student is finished at window
                    stats->finishStudent(windows[i].s, current_time); // if so, remove student from window 
                    windows[i].isFree = true;                         // open up window
                    busy_windows--;
                    stats->windowVacated(&windows[i], current_time);  // calculates at which time window is vacated 
                }
            }
        }
    }
}

bool Registrar::any_window_busy() {
    return (busy_windows > 0);
}

bool Registrar::any_window_free() {
    return (busy_windows < numWindows);
}

void Registrar::printStats(int currentTime) {
    stats->printStats(currentTime, windows);
}