#include "doctor.hpp"
#include "patient.hpp"
#include "iostream"
#include "fstream"
#include "cctype"
using namespace std;

Shedule::Shedule()
{
    from = "";
    to = "";
}
Shedule::Shedule(string from, string to)
{
    this->from = from;
    this->to = to;
}
string Shedule::getShedule()
{
    return from + " to " + to;
}
set<string> Doctor::doctorids;

Doctor::Doctor() : Person()
{
    doctorID = "null";
    specialization = "none";
   shedule = Shedule("","");
}

Doctor::Doctor(string name, int age, string contact, string doctorID, string specialization, string from, string to) : Person(name, age, contact)
{
   
    if (doctorID.length() > 10)
    {
        throw RangeError("Doctor ID Length can't be more than 10 characters");
    }
    if (doctorids.find(doctorID) != doctorids.end())
    {
        throw UniqueDoctorIDError("Doctor with this ID already exists");
    }
    doctorids.insert(doctorID);
    this->doctorID = doctorID;
    this->specialization = specialization;
    this->shedule = Shedule(from,to);
    
}

void Doctor::getDetails()
{
    cout << "id: " << doctorID << "\n";
    Person::getDetails();
    cout << "Specialization: " << specialization << "\n";
    cout << "shedule: ";
    cout<<shedule.getShedule()<<"\n";

}
void Doctor::updateDoctorInfo(Doctor& doc, string name, int age, string contact,string doctorID, string specialization, string from, string to)
{
    if (doctorids.find(doc.doctorID) != doctorids.end())
    {
        if (doctorID.length() > 10)
        {
            throw RangeError("Doctor ID Length can't be more than 10 characters");
        }
        if(doc.doctorID!=doctorID){
            doctorids.erase(doc.doctorID);
            doctorids.insert(doctorID);
        }
        doc.doctorID = doctorID;
        doc.name=name;
        doc.age=age;
        doc.contact=contact;
        doc.specialization = specialization;
        doc.shedule = Shedule(from,to);
        return;
    }
    throw UniqueDoctorIDError("Sorry the doctor with this id  does not exist in records");
}
void Doctor::saveToFile(const Doctor& d){
    fstream file(".//data//doctors.txt",::ios::out|ios::app);
    if(!file.is_open()){
        throw FileNotOpening("Sorry we can not store the records for doctor");
    }
    file<<d.doctorID<<"\n";
    file<<d.name<<"\n";
    file<<d.age<<"\n";
    file<<d.contact<<"\n";
    file<<d.specialization<<"\n";
    string buff =d.shedule.from + " to "+d.shedule.to;
    file<<buff<<"\n";

    cout<<"\nDoctor record successfully saved\n";
}
void Doctor::loadFromFile()
{
    ifstream file(".//data//doctors.txt");
    if(!file.is_open()){
        ofstream tmp(".//data//doctors.txt");
        if(!tmp.is_open()){
            throw FileNotOpening("Sorry we can't fetch doctors");
        }
    }

    file.seekg(0,ios::end);

    if(file.tellg() == 0){
        cout<<"Sorry we have no records stored for doctors\n";
        return;
    }

    file.seekg(0,ios::beg);

    string buffer;
    while(!file.eof()){
        getline(file,buffer);
        if(buffer.length())
            cout<<"doctor id: "<<buffer<<"\n";
        buffer="";
        getline(file, buffer);
        if(buffer.length())
            cout<<"name: "<<buffer<<"\n";
        buffer="";
        getline(file, buffer);
        if(buffer.length())
            cout<<"age: "<<buffer<<"\n";
        buffer="";
        getline(file, buffer);
        if(buffer.length())
            cout<<"contact: "<<buffer<<"\n";
        buffer="";
        getline(file, buffer);
        if(buffer.length())
            cout<<"specialization: "<<buffer<<"\n";
        buffer="";
        getline(file, buffer);
        if(buffer.length())
            cout<<"shedule: "<<buffer<<"\n\n\n";
        buffer="";
    }

    return;
}

string Doctor::getDoctorID(){
    return doctorID;
}

void Doctor::removeDoctor(const string &doctorID)
{
    if (doctorids.find(doctorID) != doctorids.end())
    {
        doctorids.erase(doctorID);
    }
    else
    {
        throw UniqueDoctorIDError("Doctor with this ID does not exist");
    }
}