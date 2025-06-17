#include"iostream"
#include"string.h"          //---> included to use strcpy()
#include "../include/person.hpp"
using namespace std;

// --> Implementation for person.hpp

// custome error classes

// default constructor imp 
Person::Person(){
    /* initialized members with there initial value
        --> for char array : "" null 
        --> for int : 0 
    */
    strcpy(name,"");
    age = 0;
    strcpy(contact,"");
}


Person::Person(string name,int age,string contact){

        if(name.length() > NAME_M){
            throw RangeError("Name is too long !");
        }
        if(contact.length()>CONTACT_M){
            throw RangeError("You entered very long Contact Number please make it to maximam 12 digits !");
        }
        if(contact.length()!=11 && contact.length()!=CONTACT_M){
            throw RangeError("Please Enter correct Contact Number , correct contact number have must be 11 or 12 digits long !");
        }
        this->age = age;
        strcpy(this->name,name.c_str());        // c_str() -> returns the null terminated const char*
        strcpy(this->contact,contact.c_str());
}
void Person::setPerson(string name,int age,string contact){

      if(name.length() > NAME_M){
            throw RangeError("Name is too long !");
        }
        if(contact.length()>CONTACT_M){
            throw RangeError("You entered very ong Contact Number please make it to maximam 12 digits !");
        }
        if(contact.length()!=11 && contact.length()!=CONTACT_M){
            throw RangeError("Please Enter correct Contact Number , correct contact number have must be 11 or 12 digits long !");
        }
        this->age = age;
        strcpy(this->name,name.c_str());        // c_str() -> returns the null terminated const char*
        strcpy(this->contact,contact.c_str());
}

void Person::getPersonDetails(){
    cout<<"Name : "<<name<<"\n Age : "<<age<<"\n Contact No. : "<<contact<<"\n\n"; 
 }
// returns the age : int
int Person::getAge(){
    return age;
}
// returns the name : string
string Person::getName(){
    string name_str = name;
    return name_str;
}
// returns the contact : string
string Person::getContact(){
    string contact_str = contact;
    return contact_str;
}



// END