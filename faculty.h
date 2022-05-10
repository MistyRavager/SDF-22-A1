#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>
#include "student.h"


using namespace std;

#ifndef __faculty__
#define __faculty__


class faculty{
    public:
        faculty(string ID,lec *C){
            id = ID;
            course == *C;
        }
        
        void print_students(){
            course.view_students();
        }
        void grade(){
            printf("\n%47s%s\n","","\033[33;3mRegistered students: \033[0m");       //formatting the output using ANSI codes
            print_students();
            vector <string> gradesheet;
            string grade;
            for (size_t i = 0; i<course.get_students().size();i++){
                student stu(course.get_students()[i]);
                ifstream infile("records.txt");
                infile >> stu;
                printf("\n%47s%s%s%s\n","","\033[33;3mEnter Grade for ",stu.get_roll().c_str(),": (enter \"null\" for skip, \"stop\" to stop grading)");
                printf ("%48s%s","","\033[1m-> \033[0m");
                std :: cin >> grade;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                if (grade == "stop") {
                    infile.close();
                    break;
                }
                if (grade != "null" && grade != "A+" && grade != "A" && grade != "A-" && grade != "B" && grade != "B-" && grade != "C"
                && grade != "C-" && grade != "D" && grade != "D-" && grade != "E" && grade != "E-" && grade != "F"){
                    printf("%47s%s\n","","\033[31;1mERROR: Grade not like (A-,A,etc).graded as \"null\"\033[0m");
                    grade = "null";
                }
                stu.grade(course.get_id(),grade);
                infile.close();
            }
        }
    private:
        string id;
        lec course;
};
#endif