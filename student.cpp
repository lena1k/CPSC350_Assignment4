#include "student.h"

Student::Student(int timeArrived, int waitTime) {
    this->timeArrived = timeArrived;
    this->waitTime = waitTime;
    this->finishedTime = 0;
}

Student::~Student() {
}