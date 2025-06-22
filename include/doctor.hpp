#ifndef DOCTOR_H
#define DOCTOR_H
#include"iostream"
#include"set"
#include"person.hpp"
using namespace std;

class Shedule {
    public:
        string from;
        string to;
        Shedule(string,string);
        Shedule();
        string getShedule();
};
class Doctor : public Person {
    private:
        static set<string> doctorids;
    public:
        string doctorID;
        string specialization;
        Shedule shedule;
        Doctor();
        Doctor(string name, int age, string contact, string doctorID, string specialization, string from, string to);
        void static updateDoctorInfo(Doctor &, string name, int age, string contact, string doctorID, string specialization, string from, string to);
        void getDetails() override;
        void static saveToFile(const Doctor&);
        void static loadFromFile();   
        string getDoctorID();
        void static removeDoctor(const string&);
};

class UniqueDoctorIDError : public runtime_error {
    public:
        UniqueDoctorIDError(const char* message):runtime_error(message){}
};

#endif