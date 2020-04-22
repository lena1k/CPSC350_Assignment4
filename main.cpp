#include "Registrar.h"
#include "GenQueue.h"
#include "DoublyLinkedList.h"
#include "student.h"
#include "NodeList.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

// Registrar and Queue objects
Registrar* reg; 
GenQueue<Student>* studentQueue;

int currTime = 0;       // global time
fstream inputFile;

// read a number from input file, one line at a time
int read_num() {
    int num;
    string line;

    getline(inputFile, line);
    try {
        num = std::stoi(line);
        return (num);
    }
    catch (...) {
        cout << "Invalid input file" << endl;
        exit(1);
    }
}

int main(int argc, char** argv) {


    if (argc != 2) {
        cout << "Expecting one input file name" << endl;
        exit(1);
    }

    //opens file, reads in num of windows, calls registrar with that number of lines, pointer to registrar
    //reads students, giant loop, loop how many students there are, each students create queue and put it inside queue, points to queue

    string fileName = argv[1];
    inputFile.open(fileName);
    if (!inputFile) {
        cout << "File not found" << endl;
        exit(1);
    }

    int num_windows = read_num();

    // create queue and read students into the queue
    studentQueue = new GenQueue<Student>();
    int totalStudents = 0;
    //read students into queue
    while (!inputFile.eof()) {
        int nextArrivalTime = read_num();       // arrival time for next batch of students
        int numStudents = read_num();           // number of students at arrival time
        totalStudents += numStudents;
        
        // read in number of students who arrived at arrival time
        for (int i = 0; i < numStudents; ++i) {
            int serviceTime = read_num();
            Student* s = new Student(nextArrivalTime, serviceTime);
            studentQueue->enqueue(s);
        }
    }
    
    // create a registrar with number of windows and total students
    reg = new Registrar(num_windows, totalStudents);

    // main program loop as long as students are in queue or at window, incremement time, and check for students at window finishing
    while (!studentQueue->isEmpty() || reg->any_window_busy()) {
        currTime++;
        reg->tiktok(currTime);

        // go through queue as long as some window is free, one student at a time assuming they have actually arrived
        while (reg->any_window_free() && (!studentQueue->isEmpty() && (studentQueue->peek()->timeArrived <= currTime))) {
            Student *s = studentQueue->dequeue();
            reg->add_student(s, currTime);
        }
    }

    currTime--; // adjust last tick
    reg->printStats(currTime);
}


