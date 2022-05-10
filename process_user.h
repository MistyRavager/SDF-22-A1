#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>
// #include "faculty.h"
#include "admin.h"

using namespace std;

#ifndef __user__
#define __user__


void process_faculty(string username,string course){
    ifstream infile("courses.txt");
    lec C(course);
    infile >> C;
    infile.close();
    faculty f(username,&C);

    string choice;
    string flag;
    flag = "on";
    while (flag == "on"){
        printf("\n%47s%s\n","","\033[33;1mFACULTY OPERATIONS : \033[0m");   //formatting the output using ANSI codes
        printf ("%50s%s\n%50s%s\n%50s%s\n"
        ,"", "\033[36;1m1. View Students\033[0m"
        ,"", "\033[36;1m2. Grade Students\033[0m"
        ,"", "\033[36;1m3. Logout\033[0m");
        
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice == "1") f.print_students();
        else if (choice == "2") f.grade();    
        else if (choice == "3") flag = "off";     
        else printf("%47s%s\n","","\033[31;1mERROR: Enter valid option number.\033[0m");
    }
}

void process_student(string username){
    student user(username);
    fstream file;
    file.open("records.txt",ios :: in);
    file >> user;
    file.close();
    string choice;
    string flag;
    flag = "on";
    string course;
    while(flag == "on"){
        printf("\n%47s%s\n","","\033[33;1mSTUDENT OPERATIONS : \033[0m");
        printf ("\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n"
        ,"", "\033[36;1m1. Register\033[0m"
        ,"", "\033[36;1m2. De-Regsiter\033[0m"
        ,"", "\033[36;1m3. View Gradesheet\033[0m"
        ,"", "\033[36;1m4. Logout\033[0m");
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice == "1"){
            view_all_floated_courses();
            printf("\n%47s%s\n","","\033[33;3mAll Registered Courses : \033[0m");
            user.print_reg();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to register: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            vector <string> reg_courses = user.get_reg_courses();
            //auto itr = find(user.get_reg_courses().begin(),user.get_reg_courses().end(),course);
            //if itr != find(user.get_reg_coureses.end()) print error
            auto itr = find(reg_courses.begin(),reg_courses.end(),course);

            auto itr2 = find(floated_courses.begin(),floated_courses.end(),course);
            if (itr != reg_courses.end()) {
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course is already registered.\033[0m");
                continue;
            }
            if (itr2 == floated_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course is not floated.\033[0m");
                continue;
            }
            user.reg(course);                
        }
        
        else if (choice == "2"){
            printf("\n%47s%s\n","","\033[33;3mAll Registered Courses : \033[0m");
            user.print_reg();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to De-register: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            vector <string> gradesheet = user.get_gradesheet();
            auto itr = find(gradesheet.begin(),gradesheet.end(),course);
            if (itr == gradesheet.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course not registered.\033[0m");
                continue;
            }
            if (*(itr+1)!="null"){
                printf("%47s%s\n","","\033[31;1mERROR: Cannot De-register for graded course (grade submitted).\033[0m");
                continue;
            }
            user.de_reg(course);
        }
        
        else if (choice == "3"){
            user.print_gradesheet();
        }
        
        else if (choice == "4") flag = "off";
        
        else printf("%47s%s\n","","\033[31;1mERROR: Enter valid option number.\033[0m");
    }
    return;
}

void process_admin(string username){
    admin user(username);
    string choice;
    string flag;
    flag = "on";
    string id;
    string course;
    string role;
    string password;
    while(flag == "on"){
        printf("\n%47s%s\n","","\033[33;1mADMIN OPERATIONS : \033[0m");
        printf ("%50s%s\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n%50s%s\n"
        ,"", "\033[36;1m1. Add Course\033[0m"
        ,"", "\033[36;1m2. Del Course\033[0m"
        ,"", "\033[36;1m3. Add User\033[0m"
        ,"", "\033[36;1m4. Del User\033[0m"
        ,"", "\033[36;1m5. Add Student in course\033[0m"
        ,"", "\033[36;1m6. Del Student from course\033[0m"
        ,"", "\033[36;1m7. Float Course\033[0m"
        ,"", "\033[36;1m8. Unfloat Course\033[0m"
        ,"", "\033[36;1m9. Logout\033[0m");
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice == "1"){
            view_all_courses();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to be added: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            auto itr = find(all_courses.begin(),all_courses.end(),course);
            if (itr != all_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Course already exists.\033[0m");
                continue;
            }
            user.add_course(course);
        }
        
        else if (choice == "2"){
            view_all_courses();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to be deleted: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            auto itr = find(all_courses.begin(),all_courses.end(),course);
            if (itr == all_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course does not exist.\033[0m");
                continue;
            }
            user.del_floated_course(course);
            user.del_course(course);
        }
        
        else if (choice == "3"){
            printf("\n%47s%s\n","","\033[33;3mEnter Roll of new user: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> role;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            printf("\n%47s%s\n","","\033[33;3mEnter ID/Username of new User: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            printf("\n%47s%s\n","","\033[33;3mEnter Password of new User: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> password;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if (role != "student" && role != "faculty" && role != "admin"){
                printf("%47s%s\n","","\033[31;1mERROR: Invalid Role.\033[0m");
                continue;
            }
            user.add_user(role,id,password);
        }        
        
        else if (choice == "4"){
            printf("\n%47s%s\n","","\033[33;3mEnter Role of user to be deleted: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> role;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            printf("\n%47s%s\n","","\033[33;3mEnter ID/Username of the user to be deleted: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            user.del_user(role,id);
        }
        
        else if (choice == "5"){
            printf("\n%47s%s\n","","\033[33;3mEnter ID/Username of student for adding course: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            printf("\n%47s%s\n","","\033[33;3mEnter Course to be added: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            user.add_student_to_course(id,course);
        }
        
        else if (choice == "6"){
            printf("\n%47s%s\n","","\033[33;3mEnter ID/Username of student for deleting course: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            printf("\n%47s%s\n","","\033[33;3mEnter Course to be deleted: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            user.del_student_from_course(id,course);
        }
        
        else if (choice == "7"){
            view_all_courses();
            view_all_floated_courses();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to be floated: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            auto itr = find(all_courses.begin(),all_courses.end(),course);
            auto itr2 = find(floated_courses.begin(),floated_courses.end(),course);
            if (itr == all_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course does not exist.\033[0m");
                continue;
            }
            if (itr2 != floated_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course is already floated.\033[0m");
                continue;
            }
            user.float_course(course);
        }
        
        else if (choice == "8"){
            view_all_floated_courses();
            printf("\n%47s%s\n","","\033[33;3mEnter Course to unfloat: \033[0m");
            printf ("%48s%s","","\033[1m-> \033[0m");
            std :: cin >> course;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            auto itr = find(floated_courses.begin(),floated_courses.end(),course);
            if (itr == floated_courses.end()){
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course is already unfloated.\033[0m");
                continue;
            }
            user.del_floated_course(course);
        }
        
        else if (choice == "9") flag = "off";
        
        else printf("%47s%s\n","","\033[31;1mERROR: Entered Valid option number.\033[0m");
    }
}

#endif