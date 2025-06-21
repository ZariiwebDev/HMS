#include"iostream"
#include "../include/person.hpp"
using namespace std;

// --> Implementation for person.hpp

// custome error classes

// default constructor imp 
Person::Person(){
    name="";
    age = 0;
    contact="000000000000";
}


Person::Person(string name,int age,string contact){

        if(name.length() > NAME_M){
            throw RangeError("Name is too long !");
        }
        if(contact.length()>CONTACT_M){
            throw RangeError("You entered very long Contact Number please make it to maximum 12 digits !");
        }
        if(contact.length()!=11 && contact.length()!=CONTACT_M){
            throw RangeError("Please Enter correct Contact Number , correct contact number have must be 11 or 12 digits long !");
        }
        this->age = age;
        this->name=name;       
        this->contact=contact;
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
        this->name=name;        
        this->contact=contact;
}

void Person::getDetails(){
    cout<<"Name : "<<name<<"\n Age : "<<age<<"\n Contact No. : "<<contact<<"\n"; 
 }


// END