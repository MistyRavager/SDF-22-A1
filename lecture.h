#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>

using namespace std;
#ifndef __lecture__
#define __lecture__

class lec{
    public:
        lec(string ID){
            id = ID;
        }
        lec(){
            id = "null";
        }
        lec(lec &obj){
            obj.get_id() = id;
            obj.get_students() = students;
        }
        friend lec& operator == (lec& obj, lec& old){
            obj.id = old.get_id();
            for (size_t i = 0;i<old.get_students().size();i++){
                obj.students.push_back(old.get_students()[i]);
            }
            return obj;
        }
        void view_students(){
            printf("%47s%s","","\033[33;3m");       //formatting the output using ANSI codes
            for (size_t i =0; i< students.size();i++){
                printf("%s ",students[i].c_str());
            }
            printf("%s\n","\033[0m");
        }
        string get_id(){
            return id;
        }
        vector <string> get_students(){
            return students;
        }
        void add_student(string roll){
            students.push_back(roll);
        }

        void rem_student(string roll){
            auto itr = find(students.begin(),students.end(),roll);
            students.erase(itr);
        }

        string get_found(){
            return found;
        }

        friend istream& operator >> (istream& in, lec& obj){                  //operator overloading
            string loaded_id;
            string buffer;
            string loaded_stu;
            while(in.peek() != EOF){
                in >> loaded_id;
                if (obj.id == loaded_id){
                    obj.found = "yes";
                    obj.students.clear();
                    while (in.peek() != '\n'){
                        in >> loaded_stu;
                        obj.students.push_back(loaded_stu);
                    }
                    break;
                }
                else getline(in,buffer);
            }
            
            return in;
        }

        friend ostream& operator << (ostream& out, const lec& obj){

            out << obj.id;
            for (size_t i = 0;i<obj.students.size();i++){
                out << ' ' << obj.students[i];
            }
            out << endl;
            return out;
        }
    private:
        string id;
        vector <string> students;
        string found = "no";
};
#endif