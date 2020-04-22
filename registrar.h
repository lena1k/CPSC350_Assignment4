#pragma once

#include "student.h"

class Statistics;

// RegistrarWindow defines each windows of the registrar office
class RegistrarWindow {
public:
    bool isFree;    
    Student* s;
    int timeLastOccupied; 
    int timeLastVacated;
};

class Registrar {
private:
    Statistics* stats;
    int numWindows;
    RegistrarWindow* windows;
    int busy_windows;
    
public:

    Registrar(int numWindows, int totalStudents);
    ~Registrar();

    void add_student(Student* s, int current_time);
    void tiktok(int current_time);

    bool any_window_busy();
    bool any_window_free();

    void printStats(int currentTime);
};