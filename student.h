#pragma once

// class object represents each student
class Student {
public:
    Student(int timeArrived, int waitTime);
    ~Student();

    int timeArrived; // what time students arrive at queue
    int waitTime; // how much time in window
    int finishedTime;
};
