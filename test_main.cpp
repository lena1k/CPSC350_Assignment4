// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
#include <iostream>
#include "DoublyLinkedList.h"

struct student_record {
    int id;
};

student_record* s1;
student_record* s2;
student_record* s3;
student_record* s4;
student_record* s5; 


int main()
{
    std::cout << "Hello World!\n";


    DoublyLinkedList<student_record> dl;

    s1 = new student_record;  s1->id = 1;
    s2 = new student_record;  s2->id = 2;
    s3 = new student_record;  s3->id = 3;
    s4 = new student_record;  s4->id = 4;
    s5 = new student_record;  s5->id = 5;
    

    if (!dl.isEmpty()) {
        std::cout << "Should be empty!\n";
        exit(1);
    }

    dl.insertFront(s5);
    dl.insertFront(s4);
    dl.insertFront(s3);
    dl.insertFront(s2);
    dl.insertFront(s1);

    int id = 1;
    while (!dl.isEmpty()) {
        student_record* srec = dl.removeFront();
        if (srec->id != id) {
            std::cout << "Found " << srec->id << " Should be " << id <<"\n";
            exit(1);
        }
        id++;
    }

    dl.insertFront(s5);
    dl.insertFront(s4);
    dl.insertFront(s3);
    dl.insertFront(s2);
    dl.insertFront(s1);

    id = 5;
    while (!dl.isEmpty()) {
        student_record* srec = dl.removeBack();
        if (srec->id != id) {
            std::cout << "Should be" << id << "\n";
            exit(1);
        }
        id--;
    }
  
    std::cout << "Success!\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/