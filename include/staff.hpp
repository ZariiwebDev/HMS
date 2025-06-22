#ifndef STAFF_H
#define STAFF_H
#include"iostream"
#include"set"
#include"person.hpp"
using namespace std;
class Staff : public Person {
    private:
        static set<string>uniquestaffids;
        string toLowerCase(string);
    public:
        string staffID;
        string role; // doctor etc
        string shift;
        Staff();
        Staff(string name,int age,string contact,string staffID,string role,string shift);
        void static updateStaffInfo(Staff&, string name, int age, string contact, string staffID, string role, string shift);
        void getDetails() override;
        void static saveToFile(const Staff&);
        void static loadFromFile();
        string getStaffID();
        void static removeStaff(const string &staffID);
};  

class UniqueIDError : public runtime_error {
    public:
        UniqueIDError(const char* message) : runtime_error(message){}
};
class ShiftError : public runtime_error {
    public:
       ShiftError(const char* message) : runtime_error(message){} 
};
class StaffNotFound : public runtime_error
{
public:
    StaffNotFound(const char *message) : runtime_error(message) {}
};

#endif