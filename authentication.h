#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include<bits/stdc++.h>

using namespace std;

#ifndef __authenticate__
#define __authenticate__


string authenticate(string status, string role, string *flag, string *course){
    fstream file;
    string repeat="on";
    string username;
    printf("\n%47s%s\n","","\033[33;3mEnter Username: \033[0m");         //formatting the output using ANSI codes
    printf ("%48s%s","","\033[1m-> \033[0m");
    std :: cin >> username;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    string password;
    printf("\n%47s%s\n","","\033[33;3mEnter Password: \033[0m");
    printf ("%48s%s","","\033[1m-> \033[0m");
    std :: cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    if (role == "faculty"){
        printf("\n%47s%s\n","","\033[33;3mEnter Course: \033[0m");
        printf ("%48s%s","","\033[1m-> \033[0m");
        std :: cin >> (*course);
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    if (status == "old"){
        string buffer;
        string loaded_role;
        string loaded_username;
        string loaded_pwd;
        string loaded_course;
        while(repeat == "on"){
            file.open("details.txt", ios :: in);
            while (!(file.eof()) && file.peek()!= EOF && repeat == "on"){
                file >> loaded_role;
                if (loaded_role == role && role != "faculty"){
                    file >> loaded_username;
                    file >> loaded_pwd;
                    if (loaded_pwd == password && loaded_username == username){
                        repeat = "off";
                        break;
                    }
                }
                else if (loaded_role == role && role == "faculty"){
                    file >> loaded_username;
                    file >> loaded_pwd;
                    file >> loaded_course;
                    if (loaded_pwd == password && loaded_username == username && loaded_course == (*course)){
                        repeat = "off";
                        break;
                    }
                }
                else getline(file,buffer);

            }
            if (repeat=="on"){
                if (role == "faculty") printf("%48s%s\n","","\033[31;1mERROR: Invalid username/password/course\033[0m");
                else printf("%47s%s\n","","\033[31;1mERROR: Invalid username/password\033[0m");
                printf("\n%47s%s\n","","\033[33;3mEnter Username: \033[0m");
                printf ("%48s%s","","\033[1m-> \033[0m");
                std :: cin >> username;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                printf("\n%47s%s\n","","\033[33;3mEnter Password: \033[0m");
                printf ("%48s%s","","\033[1m-> \033[0m");
                std :: cin >> password;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                if (role == "faculty") {
                    printf("\n%47s%s\n","","\033[33;3mEnter Course: \033[0m");
                    printf ("%48s%s","","\033[1m-> \033[0m");
                    std :: cin >> (*course);
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }                
            }
            file.close();
        }
    }
    else if (status == "new"){
        file.open("details.txt",ios :: app);
        if (role == "faculty") file << role << ' ' << username << ' ' << password << ' ' << *course << endl;
        else file << role << ' ' << username << ' ' << password << endl;
    }
    *flag = "off";
    file.close();
    return username;
}

#endif