#ifndef PERSON_H
#define PRSON_H
/*
   --> IMPLEMENTED BY UZAIR 
 */
#include"iostream"
using namespace std;

// define macros for the max size for name,contact.
#define NAME_M 30 
#define CONTACT_M 12
class Person{
    // Person Members
    char name[31];   // 30 chars  for name and 1 for null terminator.    
    int age;
    char contact[13];   // 12 chars  for contactNumber and 1 for null terminator. 
    public:
        Person();   // default constructor.
        Person(string name,int age,string contact);  // parameterized constructor.
        void getPersonDetails();     // display function.
        void setPerson(string name,int age,string contact);      // setter function.

        // help functions rarely used
        string getName();       
        string getContact();
        int getAge();       
};


class RangeError : public runtime_error{
    public:
        
        RangeError(const char* message) : runtime_error(message){}
};

#endif