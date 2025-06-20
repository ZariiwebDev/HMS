#ifndef PERSON_H
#define PERSON_H

#include"iostream"
using namespace std;

// define macros for the max size for name,contact.
#define NAME_M 30 
#define CONTACT_M 12
class Person{
    // Person Members
    public:
        int age;
        string name;   
        string contact;    
        Person();                                             // default constructor.
        Person(string name, int age, string contact);         // parameterized constructor.
        virtual void getDetails();                              // display function.
        void setPerson(string name, int age, string contact); // setter function.
};

// custome errors may be thrown by the above class
class RangeError : public runtime_error{
    public:
        
        RangeError(const char* message) : runtime_error(message){}
};

#endif