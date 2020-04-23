#include "Statistics.h"
#include "registrar.h"
#include <iostream>

using namespace std;

Statistics::Statistics(int totalStudentCount, int numWindows) {

    meanWait = 0;               // calculate at end (1)
    medianWait = 0;             // calculate at end (2)

    longestWait = 0;            // update as each student finishes (3)
    numStudentsLongWait = 0;    // update as each student finishes (4)

    meanWindowIdleTime = 0;     // calculate at end (5)
   
    longestWindowIdleTime = 0;      // update as each Windows is occupied (6)
    numWindowsIdleOver5Min = 0;     // update as each Window is occupied (7)

    totalWaitTime = 0;          // update as each student finishes
    this->totalStudentCount = totalStudentCount;

    totalWindowIdleTime = 0;    // update as each Windows is occupied
    totalWindowBusyTime = 0;    // update as each Window is vacated

    studentWaitTime = new int[totalStudentCount];       // array needed to calculate median wait for students
    currentStudentIndex = 0;

    this->numWindows = numWindows;    
}

// called when student leaves window
void Statistics::finishStudent(Student* student, int currentTime) {
    int waitTime = currentTime - student->timeArrived;      // calculates waitTime
    
    if (waitTime > longestWait) {                           // check if this was the longest wait
         longestWait = waitTime;
    }
    if (waitTime > 10) {                                    // check if wait time exceed 10 minutes
        numStudentsLongWait++;
    }
    totalWaitTime += waitTime;  

    studentWaitTime[currentStudentIndex++] = waitTime;      // holds wait time for each student
    delete student;
}

// called when a window is occupied
void Statistics::windowOccupied(RegistrarWindow *w, int currentTime) {
    int idleTime = currentTime - w->timeLastVacated;        // calculates idle time
    totalWindowIdleTime += idleTime;
    if (idleTime > longestWindowIdleTime) {                 // check if this was the longest idle time
        longestWindowIdleTime = idleTime;
    }
    if (idleTime > 5) {                                     // check if idle time exceeded 5 minutes
        numWindowsIdleOver5Min++;
    }
    w->timeLastOccupied = currentTime;                      // window is free, last occupied time is now
}

// called when a window is being vacated
void Statistics::windowVacated(RegistrarWindow *w, int currentTime) {
    int busyTime = currentTime - w->timeLastOccupied;       // window was busy, calculate the time the window was occupied 
    totalWindowBusyTime += busyTime;                        
    w->timeLastVacated = currentTime;                       // window is free now
}

// A function to implement bubble sort
// Source: https://www.geeksforgeeks.org/bubble-sort/

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place  
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void Statistics::printStats(int currentTime, RegistrarWindow* windows) {
 
    
    // sort array, calculate median
    bubbleSort(studentWaitTime, totalStudentCount);

    // check for even case
    if ((totalStudentCount % 2) == 0) {
        medianWait = (double)((double)studentWaitTime[(totalStudentCount-1)/2] +
            studentWaitTime[totalStudentCount/2]) / 2.0;
    }
    else {
        medianWait = (double)studentWaitTime[totalStudentCount / 2];
    }

    // calculate means
    meanWait = ((double)totalWaitTime / (double)totalStudentCount);
    meanWindowIdleTime = ((double)totalWindowIdleTime / (double)numWindows);


    // check idle time for all windows
    for (int i = 0; i < numWindows; i++) {
        windowOccupied(&windows[i], currentTime);
    }

    //print everything out
    cout << "Mean Student Wait: " << meanWait << endl;
    cout << "Median Student Wait: " << medianWait << endl;
    cout << "Longest Student Wait: " << longestWait << endl;
    cout << "Number of students waiting over 10 minutes: " << numStudentsLongWait << endl;
    cout << "Mean Window Idle Time: " << meanWindowIdleTime << endl;
    cout << "Longest Window Idle Time: " << longestWindowIdleTime << endl;
    cout << "Number of windows idle for over 5 minutes: " << numWindowsIdleOver5Min << endl;

}

