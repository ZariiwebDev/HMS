#include "staff.hpp"
#include "iostream"
#include "fstream"
#include "cctype"
#include "patient.hpp"
using namespace std;

set<string> Staff::uniquestaffids;

Staff::Staff() : Person()
{
    staffID = "";
    role = "";
    shift = "";
}
Staff::Staff(string name, int age, string contact, string staffID, string role, string shift) : Person(name,age,contact)
{
    if(staffID.length()>11){
        throw RangeError("staff id can't be longer than 10 characters" );
    }
    if(uniquestaffids.find(staffID)!=uniquestaffids.end()){
        throw UniqueIDError("Staff with this ID already exists ");
    }
    uniquestaffids.insert(staffID);
    this->staffID = staffID;
    this->role = role;
    // this will convert the shift to lowercase 
    string newString = toLowerCase(shift);
    
    if (newString == "morning" || newString == "evening" || newString == "night")
    {
        this->shift = shift;
    }
    else
    {
        throw ShiftError("You entered wrong shift");
    }
}


string Staff::toLowerCase(string str){
    string newstr;
    for(char ch : str){
        newstr +=tolower(ch);
    }
    return newstr;
}

void Staff::getDetails(){
    cout << "id: " <<staffID<< "\n";
    Person::getDetails();
    cout<<"role: "<<role<<"\n";
    cout<<"shift: "<<shift<<"\n";
}

void Staff::saveToFile(const Staff& s){
    fstream file(".//data//staff.txt", ios::out | ios::app);
    if (!file.is_open())
    {
        throw FileNotOpening("sorry we can't store patient data");
    }

    file << s.staffID << "\n";
    file << s.name << "\n";
    file << s.age << "\n";
    file << s.contact << "\n";
    file << s.role << "\n";
    file << s.shift << "\n";

    cout << "Staff Member is added sucessfully\n";
}

void Staff::loadFromFile(){
    fstream file(".//data//staff.txt", ios::in);
    if(!file.is_open()){
        ofstream temp(".//data//staff.txt");
        if (!temp.is_open())
        {
            throw FileNotOpening("sorry we can't store patient data");
        }
    }
    file.seekg(0,ios::end);
    if(file.tellg() == 0 ){
        cout<<"no staff found\n";
        return;
    }
    file.seekg(0,ios::beg);
    string buffer;
    while(!file.eof()){
        getline(file,buffer);
        if(buffer.length()){
            cout << "id: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "name: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "age: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "contact: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "role: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "shift: " << buffer << "\n\n\n";
        }
        buffer="";   
    }
}


void Staff::updateStaffInfo(Staff& s, string name, int age, string contact, string staffID, string role, string shift)
{

    if(uniquestaffids.find(s.staffID)!=uniquestaffids.end()){
        if (staffID.length() > 11)
        {
            throw RangeError("staff id can't be longer than 10 characters");
        }
        if(s.staffID!=staffID){
            uniquestaffids.erase(s.staffID);
            uniquestaffids.insert(staffID);
        }
        s.staffID = staffID;
        s.name = name;
        s.age = age;
        s.contact = contact;
        s.role = role;
        string newString = s.toLowerCase(shift);
        if (newString == "morning" || newString == "evening" || newString == "night")
        {
            s.shift = shift;
        }
        else
        {
            throw ShiftError("You entered wrong shift");
        }
        return;
    }

    throw StaffNotFound("Staff with this ID does not exist");
}