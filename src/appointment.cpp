#include "appointment.hpp"
#include "patient.hpp"
#include "iostream"
#include "fstream"
#include "string.h"
using namespace std;

set<string> Appointment::appointmentIds;

Appointment::Appointment()
{

    appointmentID = "";
    date = "";
    time = "00:00";
    status = "pending";
    doctor.doctorID = "";
    doctor.name = "";
    doctor.age = 0;
    doctor.contact = "000000000000";
    doctor.specialization = "";
    doctor.shedule.from = "";
    doctor.shedule.to = "";
    patient.name = "";
    patient.patientID = "";
    patient.age = 0;
    patient.contact = "000000000000";
    patient.disease = "";
}

Appointment::Appointment(string appointmentID, string date, string time, string doctorID, string docname, string doccontact, string docspecialization, string from, string to, string PatientID, string paname, string pacontact, string disease,double ammount)
{

    if (appointmentIds.find(appointmentID) != appointmentIds.end())
    {
        throw UniqueAppointmentError("Appointment was already created with this ID");
    }
    appointmentIds.insert(appointmentID);
    this->appointmentID = appointmentID;
    if (!dateValidator(date))
    {
        throw DateError("Date is in incorrect format : [HINT] dd/mm/yy");
    }
    this->date = date;
    if (!timeValidator(time))
    {
        throw TimeError("Time is not correct");
    }
    this->time = time;
    this->doctor.doctorID = doctorID;
    this->doctor.name = docname;
    this->doctor.contact = doccontact;
    this->doctor.specialization = docspecialization;
    this->doctor.shedule.from = from;
    this->doctor.shedule.to = to;
    this->patient.name = paname;
    this->patient.contact = pacontact;
    this->patient.disease = disease;
    this->status="pending";
    bill = Billing(PatientID,ammount,date);
}

void Appointment::sheduleAppointment()
{
    cout<<"Appointment "<<appointmentID<<" sheduled for "<<this->patient.name<<" with  Dr."<<this->doctor.name<< " on "<<date<<" at "<<time<<"\n";
}
void Appointment::confirmAppointment()
{
    status="confirmed";
    cout<<"Appointment "<<appointmentID<<" confirmed" <<"\n";
}
void Appointment::cancelAppointment()
{
    this->status = "cancelled";
    cout<<" Appointment "<<appointmentID<<" cancelled \n";
}

void Appointment::getAppointmentDetails()
{
    cout<<"ID: "<<appointmentID<<"\nPatient ID: "<<patient.patientID<<"\nDoctor ID: "<<doctor.doctorID<<"\n";
    cout<<"Date: "<<date<<"\nTime: "<<time<<"\nStatus: "<<status<<"\n";
}

bool Appointment::dateValidator(string date)
{
    int count = 0;
    for (char ch : date)
    {
        if (ch == '/')
        {
            count++;
        }
    }
    if (count == 2)
    {
        string day = (date.substr(0, (date.find('/'))));
        string month = (date.substr((date.find('/', 0) + 1), (date.find('/'))));
        string year = (date.substr((date.rfind('/') + 1), date.length()));
        int dayint = stoi(day);
        int monthint = stoi(month);
        int yearint = stoi(year);

        // Basic validation
        if (dayint <= 0 || dayint > 31 || monthint <= 0 || monthint > 12 || yearint <= 0)
        {
            return false;
        }

        // Month-specific day limits
        if (monthint == 4 || monthint == 6 || monthint == 9 || monthint == 11)
        {
            if (dayint > 30)
                return false;
        }
        else if (monthint == 2)
        {
            // Leap year check
            bool isLeapYear = (yearint % 4 == 0 && yearint % 100 != 0) || (yearint % 400 == 0);
            if (isLeapYear)
            {
                if (dayint > 29)
                    return false;
            }
            else
            {
                if (dayint > 28)
                    return false;
            }
        }
        else if (dayint > 31)
        {
            return false;
        }

        // If all checks pass
        return true;
    }
    else
    {
        return false;
    }
}

bool Appointment::timeValidator(string time)
{
    int count = 0;
    for (char ch : time)
    {
        if (ch == ':')
        {
            count++;
        }
    }

    if (count == 1)
    {
        int hours = stoi(time.substr(0, time.find(':')));
        int minutes = stoi(time.substr((time.find(':') + 1), time.length()));
        if (hours <= 0 || minutes <= 0)
        {
            return false;
        }
        if (hours > 24 || minutes > 60)
        {
            return false;
        }
        if (hours == 24 && minutes != 0)
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Appointment::generateBill()
{
    if(status=="confirmed"){
        bill.generateBill();
    }else{
        string errormsg = "Cannot generate bill: Appointment " + appointmentID + " is not confirmed!";
        throw BillGenerationError(errormsg.c_str());
    }
} 
void Appointment::saveToFile(const Appointment &ap)
{
    ofstream file(".//data//appointments.txt",ios::out|ios::app);
    if(!file.is_open()){
        throw FileNotOpening("FILE CREATION ERROR : Sorry we do not store appointments ");
    }

    file<<ap.appointmentID<<"\n";
    file<<ap.patient.patientID<<"\n";
    file<<ap.patient.name<<"\n";
    file<<ap.doctor.doctorID<<"\n";
    file<<ap.doctor.name<<"\n";
    file<<ap.date<<"\n";
    file<<ap.time<<"\n";
    file<<ap.status<<"\n";

    cout<<"Appointment successfully saved to database\n";
}
void Appointment::loadFromFile(){
    ifstream file(".//data//appointments.txt");
    if(!file.is_open()){
        ofstream tmp(".//data//appointments.txt");
        if(!tmp.is_open()){
            throw FileNotOpening("Sorry we can't fetch data beacuse no data found for appointments");
        }
    }
    file.seekg(0,ios::end);
    if(file.tellg()==0){
        cout<<"No records were Found";
        return;
    }
    file.seekg(0,ios::beg);

    string buffer;
    while(!file.eof()){
        getline(file,buffer);
        if(buffer.length()){
            cout<<"ID: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Patient ID: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Patient Name: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Doctor ID: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Doctor Name: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Date: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Time: "<<buffer<<"\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout<<"Status: "<<buffer<<"\n";
        }
        buffer="";

    }
}


string Appointment::getAppointmentID(){
    return appointmentID;
}
void Appointment::removeAppointment(const string& appointmentID){
    if (appointmentIds.find(appointmentID) != appointmentIds.end())
    {
        appointmentIds.erase(appointmentID);
    }
    else
    {
        throw UniqueAppointmentError("Appointment with this ID does not exist");
    }
}