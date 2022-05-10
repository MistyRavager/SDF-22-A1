#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>
#include "lecture.h"

using namespace std;

#ifndef __student__
#define __student__


class student {
    public:
        student(string roll_num){
            roll = roll_num;
        }
        void reg(string course){
            reg_courses.push_back(course);
            ++num_reg_courses;
            gradesheet.push_back(course);
            gradesheet.push_back("null");
            ifstream infile;
            infile.open("courses.txt");
            ofstream outfile;
            outfile.open("buffer.txt");
            string buffer;
            string loaded_course;
            lec C(course);
            infile >> C;
            C.add_student(roll);
            infile.close();
            infile.open("courses.txt");
            while (infile.peek()!=EOF && !(infile.eof())){
                infile >> loaded_course;
                if (infile.peek() == EOF) break;
                if (loaded_course == C.get_id()){
                    getline(infile,buffer);
                    outfile << C;
                    continue;
                }
                getline(infile,buffer);
                
                outfile << loaded_course << buffer << endl;
            }
            outfile.close();
            infile.close();
            remove("courses.txt");
            rename("buffer.txt","courses.txt");

            ifstream infile1("records.txt");
            ofstream outfile1("buffer1.txt");
            string loaded_roll;
            int reg_num;
            while (infile1.peek() != EOF && !(infile1.eof())){
                infile1 >> loaded_roll;
                infile1 >> reg_num;
                getline(infile1,buffer);
                if (loaded_roll == roll){
                    outfile1 << loaded_roll << ' ' << reg_num+1 << ' ' << course << ' ' <<  "null" << buffer <<endl;
                    continue;
                }
                outfile1 << loaded_roll << ' ' << reg_num << buffer << endl;
            }
            remove("records.txt");
            rename("buffer1.txt","records.txt");
            
        }

        void de_reg(string course){
            auto itr = find(reg_courses.begin(),reg_courses.end(),course);
            if (itr == reg_courses.end()) return;
            reg_courses.erase(itr);
            auto itr1 = find(gradesheet.begin(),gradesheet.end(),course);
            gradesheet.erase(itr1,itr1+2);
            --num_reg_courses;
            ifstream infile("courses.txt");
            ofstream outfile("buffer.txt");
            string buffer;
            string loaded_roll;
            string loaded_course;
            lec C(course);
            infile >> C;
            C.rem_student(roll);
            infile.close();
            infile.open("courses.txt");
            while (infile.peek()!=EOF && !(infile.eof())){
                infile >> loaded_course;
                if (infile.peek() == EOF) break;
                if (loaded_course == C.get_id()){
                    getline(infile,buffer);
                    outfile << C;
                    continue;
                }
                getline(infile,buffer);
                outfile << loaded_course << buffer << endl;
            }
            outfile.close();
            infile.close();
            remove("courses.txt");
            rename("buffer.txt","courses.txt");

            string loaded_grade;
            ifstream infile1("records.txt");
            ofstream outfile1("buffer.txt");
            int reg_num = 0;
            while (infile1.peek() != EOF && !(infile1.eof())){
                infile1 >> loaded_roll;
                if (infile1.peek()==EOF) break;
                infile1 >> reg_num;
                
                if (loaded_roll == roll){
                    outfile1 << loaded_roll << ' ' << num_reg_courses;
                    while(infile1.peek()!='\n'){
                        infile1 >> loaded_course;
                        infile1 >> loaded_grade;
                        if (loaded_course == course){
                            continue;
                        }
                        outfile1 << ' ' << loaded_course << ' ' << loaded_grade;
                    }
                    outfile1 << endl;
                }
                else {
                    getline(infile1,buffer);
                    outfile1 << loaded_roll << ' ' << reg_num << buffer << endl;
                }
            }
            remove("records.txt");
            rename("buffer.txt","records.txt");
        }
        
        void put_num_reg_courses(int n){
            num_reg_courses = n;
        }
        void put_reg_courses(vector <string> loaded_data){
            reg_courses = loaded_data;
        }

        void print_reg(){
            printf("%47s%s","","\033[33;3m");   //formatting the output using ANSI codes
            for (size_t i =0; i< reg_courses.size();i++){
                printf("%s ",reg_courses[i].c_str());
            }
            printf("%s\n","\033[0m");
            return;
        }

        void print_gradesheet(){
            printf("%s","\033[33;3m");
            for (size_t i =0; i< gradesheet.size();i+=2){
                printf("%47s%s %s\n","",gradesheet[i].c_str(),gradesheet[i+1].c_str());
            }
            printf("%s","\033[0m");
            return;
        }

        void grade(string course,string grade){
            for(size_t j =0; j< gradesheet.size();j+=2){
                    if (gradesheet[j] == course){
                        gradesheet[j+1] = grade;
                    }
            }
            string buffer;
            ifstream infile1("records.txt");
            ofstream outfile1("buffer1.txt");
            string loaded_roll;
            string loaded_course;
            string loaded_grade;
            int reg_num;
            while (infile1.peek() != EOF && !(infile1.eof())){
                infile1 >> loaded_roll;
                if (infile1.peek() == EOF) break;
                infile1 >> reg_num;
                outfile1 << loaded_roll << ' ' << reg_num;
                if (loaded_roll == roll){
                    while (infile1.peek()!='\n' || infile1.peek()!= EOF){
                        infile1 >> loaded_course;
                        infile1 >> loaded_grade;                      
                        outfile1 << ' ' << loaded_course;
                        if (loaded_course == course){
                            outfile1 << ' ' << grade;
                            if (infile1.peek() == '\n' ) break;
                            continue;
                        }
                        outfile1 << ' ' << loaded_grade;
                        if (infile1.peek() == '\n' ) break;
                    }
                    outfile1 << endl;
                    continue;
                }
                getline(infile1,buffer);
                outfile1 << buffer << endl;
            }
            remove("records.txt");
            rename("buffer1.txt","records.txt");
        }

        vector <string> get_gradesheet(){
            return gradesheet;
        }

        vector <string> get_reg_courses(){
            return reg_courses;
        }

        string get_roll(){
            return roll;
        }

        string get_found() {
            return found;
        }

        friend istream& operator >> (istream& in, student& obj){  
            string data;
            obj.reg_courses.clear();
            obj.gradesheet.clear();
            
            string loaded_roll;
            string buffer;
            string grade;
            while(in.peek()!=EOF){
                in >> loaded_roll;
                if (loaded_roll == obj.roll){
                    obj.found = "yes";
                    in >> obj.num_reg_courses;
                    for (int i = 0; i< obj.num_reg_courses; i++){
                        in >> data;
                        in >> grade;
                        obj.reg_courses.push_back(data);
                        obj.gradesheet.push_back(data);
                        obj.gradesheet.push_back(grade);
                    }
                    break;
                }
                else getline(in,buffer);
            }
            return in;
        }
        
        friend ostream& operator << (ostream& out, const student& obj){
            string buffer;
            out << obj.roll;
            out << ' ' << obj.num_reg_courses;
            for (size_t i = 0; i<obj.reg_courses.size();++i){
                out << ' ' << obj.reg_courses[i] << ' ' << obj.gradesheet[2*i + 1];
            }
            out << endl;
            return out;
        }
    private:
        vector <string> reg_courses;
        string roll;
        int num_reg_courses = 0;
        vector <string> gradesheet;
        string found = "no";
};
#endif