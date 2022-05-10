#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>

using namespace std;

#ifndef __globals__
#define __globals__

vector <string> floated_courses;

vector <string> all_courses;

void load_all_courses(){
    all_courses.clear();
    fstream file;
    file.open("courses.txt", ios:: in);
    string buffer;
    string loaded_course;
    while (!file.eof() && file.peek()!= EOF){
        file >> loaded_course;
        getline(file,buffer);
        all_courses.push_back(loaded_course);
    }
    file.close();
}

void load_floated_courses(){
    floated_courses.clear();
    fstream file;
    file.open("floated_courses.txt", ios:: in);
    string buffer;
    while (!file.eof() && file.peek()!= EOF){
        file >> buffer;
        if (file.peek()==EOF){
            break;
        }
        floated_courses.push_back(buffer);
    }
    file.close();
}

void view_all_courses(){
    load_all_courses();
    printf("\n%47s%s\n","","\033[33;3mAll Courses: \033[0m");         //formatting the output using ANSI codes
    printf("%47s%s","","\033[33;3m");
    for (size_t i =0; i< all_courses.size();i++){
        printf("%s ",all_courses[i].c_str());
    }
    printf("%s\n","\033[0m");
}

void view_all_floated_courses(){
    load_floated_courses();
    printf("\n%47s%s\n","","\033[33;3mAll Floated Courses: \033[0m");
    printf("%47s%s","","\033[33;3m");
    for (size_t i =0; i< floated_courses.size();i++){
        printf("%s ",floated_courses[i].c_str());
    }
    printf("%s\n","\033[0m");
}
#endif