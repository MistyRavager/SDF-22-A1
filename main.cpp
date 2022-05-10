#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>
#include "authentication.h"
#include "process_user.h"  
#include <limits>
using namespace std;

void Role(string role){
    string choice;
    string username;
    string flag;
    flag = "on";
    string course;
    course = "null";
    while (flag=="on"){
        printf ("\n%50s%s\n%50s%s\n%50s%s\n"
        ,"", "\033[36;1m1. Existing User\033[0m"
        ,"", "\033[36;1m2. New User\033[0m"
        ,"", "\033[36;1m3. Back\033[0m");
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice == "1") username = authenticate("old",role,&flag,&course);
        else if (choice == "2") username = authenticate("new",role,&flag,&course);
        else if (choice == "3") flag = "off";
        else {
            printf("%48s%s\n","","\033[31;1mERROR: enter valid option number\033[0m");
            continue;
        }
        
    }
    if (choice == "3") return;
    if (role == "student"){
        process_student(username);
    }
    else if (role == "admin"){
        process_admin(username);
    }
    else if (role == "faculty"){
        process_faculty(username,course);
    }
}

void menu(){
    string choice;
    string flag;
    flag = "on";
    while (flag == "on"){
        printf("\n%47s%s\n","","\033[33;1mROLE : \033[0m"); //formatting the output using ANSI codes
        printf ("%50s%s\n%50s%s\n%50s%s\n%50s%s\n"
        ,"", "\033[36;1m1. Admin\033[0m"
        ,"", "\033[36;1m2. Faculty\033[0m"
        ,"", "\033[36;1m3. Student\033[0m"
        ,"", "\033[36;1m4. Exit\033[0m");
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> choice; 
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choice == "1") Role("admin");
        else if (choice == "2") Role("faculty");
        else if (choice == "3") Role("student");
        else if (choice == "4") flag = "off";
        else printf("%48s%s\n","","\033[31;1mERROR: enter valid option number\033[0m");
    }        
}

int main() {
    menu();
    return 0;
}