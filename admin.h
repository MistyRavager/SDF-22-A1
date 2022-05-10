#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>
#include "globals.h"
#include "faculty.h"

#ifndef __admin__
#define __admin__ 

using namespace std;

class admin {
    public:
        admin(string ID){
            id = ID;
        }
        
        void add_user(string role, string id , string password){

            fstream file;
            string course;
            string buffer;
            string loaded_role;
            string loaded_id;
            string loaded_pass;
            if (role == "faculty"){
                printf("\n%47s%s\n","","\033[33;3mEnter course ID: \033[0m");   //formatting the output using ANSI codes
                printf ("%48s%s","","\033[1m-> \033[0m");
                std :: cin >> course;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');    //removes the remaining input buffer
                load_all_courses();
                auto itr = find(all_courses.begin(), all_courses.end(),course);  
                if (itr == all_courses.end()){
                    printf("%47s%s\n","","\033[31;1mERROR: Entered Course does not exist.\033[0m");
                    file.close();
                    return;
                }
            }
            file.open("details.txt", ios :: in);
            while (file.peek()!= EOF && !(file.eof())){           //checks if the file is at end of file
                file >> loaded_role;
                file >> loaded_id;
                file >> loaded_pass;
                getline(file,buffer);
                if (loaded_role == role && loaded_id == id){
                    printf("%47s%s%s\n","","\033[31;1mUser Already exists, password =\033[0m",loaded_pass.c_str());
                    return;
                }
            }
            file.close();
            file.open("details.txt", ios :: app);
            if (role != "faculty") file << role << ' ' << id << ' ' << password << endl;
            else file << role << ' ' << id << ' ' << password << ' ' << course << endl;
            if (role == "student"){
                fstream file1;
                file1.open("records.txt", ios :: app);
                file1 << id << ' ' << 0 << endl;
                file1.close();
            }
            file.close();
        }

        void del_user(string role, string id){
            
            ifstream infile;
            infile.open("details.txt");
            ofstream outfile("buffer.txt");
            string loaded_role;
            string loaded_id;
            string loaded_password;
            string buffer;
            string loaded;
            string found;
            found = "no";
            while (!(infile.eof()) && infile.peek() != EOF){
                infile >> loaded_role;
                if (infile.peek() == EOF){
                    break;
                }
                infile >> loaded_id;
                infile >> loaded_password;
                getline(infile,buffer);
                
                if (loaded_role == role && loaded_id == id){
                    found = "yes";
                    continue;
                }
                outfile << loaded_role << ' ' << loaded_id << ' ' << loaded_password << buffer << endl;

            }
            remove("details.txt");
            rename("buffer.txt","details.txt");
            infile.close();
            outfile.close();
            if (found == "no"){
                printf("%47s%s\n","","\033[31;1mERROR: Details not found. Enter Valid Details.\033[0m");
                return;
            }

            load_all_courses();
            if (role == "student"){
                del_student(id);
            }
        }

        void del_student(string roll){
            ifstream infile("records.txt");
            ofstream outfile("buffer.txt");
            string buffer;
            string loaded_roll;
            while (infile.peek() != EOF && !infile.eof()){
                infile >> loaded_roll;
                if (infile.peek() == EOF) break;
                getline(infile,buffer);
                if (loaded_roll == roll){
                    continue;
                }
                outfile << loaded_roll << buffer << endl;
            }
            remove("records.txt");
            rename("buffer.txt","records.txt");
            infile.close();
            outfile.close();

            infile.open("courses.txt");
            outfile.open("buffer.txt");
            string loaded_course;
            while (infile.peek() != EOF && !(infile.eof())){
                infile >> loaded_course;                       
                if (infile.peek() == EOF) break;
                outfile << loaded_course;
                while(infile.peek()!='\n'){
                    infile >> loaded_roll;
                    if (loaded_roll == roll){
                        continue;
                    }
                    outfile << ' ' << loaded_roll;
                }
                outfile << endl;
            }

            remove("courses.txt");
            rename("buffer.txt","courses.txt");
            infile.close();
            outfile.close();
        }

        void float_course(string course){
            load_floated_courses();
            
            fstream file;
            file.open("floated_courses.txt", ios :: app);
            floated_courses.push_back(course);
            file << course << ' ';
            file.close();
        }

        void del_floated_course(string course){
            load_floated_courses();
            auto itr = find(floated_courses.begin(),floated_courses.end(),course);
            if (itr == floated_courses.end()) return;
            floated_courses.erase(itr);
            ofstream file;
            file.open("floated_courses.txt");
            for (size_t i = 0; i < floated_courses.size(); ++i){
                file << floated_courses[i] << ' ';
            }
            file.close();

        }
        
        void add_student_to_course(string roll, string course){
            ifstream infile1;
            infile1.open("records.txt");
            student stu(roll);
            infile1 >> stu;
            infile1.close();
            if (stu.get_found() == "no") {
                printf("%47s%s\n","","\033[31;1mERROR: Student not found.\033[0m");
                return;
            }
            vector <string> reg_courses;
            reg_courses = stu.get_reg_courses();
            auto itr = find(reg_courses.begin(), reg_courses.end(),course);
            if (itr != reg_courses.end()) {
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course already registered.\033[0m");
                return;
            }
            else {
                load_all_courses();
                auto itr2 = find(all_courses.begin(),all_courses.end(),course);
                if (itr2 == all_courses.end()) {
                    printf("%47s%s\n","","\033[31;1mERROR: Entered Course does not exist.\033[0m");
                    return;
                }
            }
            stu.reg(course);
            
        }

        void del_student_from_course(string roll, string course){

            ofstream outfile("buffer.txt");
            student stu(roll);
            ifstream infile;
            infile.open("records.txt");
            infile >> stu;
            infile.close();
            if (stu.get_found() == "no") {
                printf("%47s%s\n","","\033[31;1mERROR: Student not found.\033[0m");
                return;
            }
            vector <string> courses = stu.get_reg_courses();
            auto itr = find(courses.begin(), courses.end(),course);
            if (itr == courses.end()) {
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course not found.\033[0m");
                return;
            }
            stu.de_reg(course);            
        }
        
        void add_course(string course){
            fstream file;
            file.open("courses.txt", ios :: app);
            file << course << endl;
        }
        
        void del_course(string course){
            del_floated_course(course);
            ifstream infile("courses.txt");
            ofstream outfile("buffer1.txt");
            lec COURSE(course);
            infile >> COURSE;
            string buffer;
            string loaded_course;
            string loaded_roll;
            infile.close();
            if (COURSE.get_found() == "no") {
                printf("%47s%s\n","","\033[31;1mERROR: Entered Course not found.\033[0m");
                return;
            }
            for(size_t i =0;i < COURSE.get_students().size();i++){
                student stu(COURSE.get_students()[i]);
                ifstream infile1("records.txt");
                infile1 >> stu;
                infile1.close();
                if (stu.get_found() == "no") {
                    printf("%47s%s\n","","\033[31;1mERROR: Entered Student not found.\033[0m");
                    return;
                }
                stu.de_reg(course);                
            }
            infile.open("courses.txt");
            while (infile.peek() != EOF && !(infile.eof())){
                infile >> loaded_course;
                if (loaded_course == course){
                    continue;
                }
                getline(infile,buffer);
                outfile << loaded_course << buffer << endl;
            }
            remove("courses.txt");
            rename("buffer1.txt","courses.txt");
            infile.close();
            outfile.close();
        }

    private:
        string id;
};

#endif