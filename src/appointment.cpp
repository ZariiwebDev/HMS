#include"appointment.hpp"
#include"iostream"
#include"fstream"
#include"string.h"
using namespace std;

set<string> Appointment::appointmentIds;

Appointment::Appointment(){
    appointmentID="";
    doctor.doctorID="";
    doctor.name="";
    doctor.age=0;
    doctor.contact = "000000000000";
    doctor.specialization="";
    doctor.shedule.from="";
    doctor.shedule.to="";
    patient.name = "";
    patient.patientID="";
    patient.age=0;
    patient.contact = "000000000000";
    patient.disease="";
}

Appointment::Appointment(string appointmentID,string date, string time, string status, string doctorID, string docname,string doccontact, string docspecialization, string to , string from , string PatientID, string paname, int paage , string pacontact , string disease )
{

    if(appointmentIds.find(appointmentID)!=appointmentIds.end()){
        throw UniqueAppointmentError("Appointment was already sheduled with this ID");
    }    
    appointmentIds.insert(appointmentID);
    this->appointmentID = appointmentID;

}

bool Appointment::dateValidator(string date){
    // int day = stoi(date.substr(0,(date.find('/')+1)));
    // int month = stoi(date.substr(date.find('/',0),(date.find('/')+1)));
    // int year = stoi(date.substr(date.rfind('/'),date.length()));
    string day =(date.substr(0,(date.find('/'))));
    string month = (date.substr((date.find('/', 0)+1), (date.find('/'))));
    string year = (date.substr((date.rfind('/')+1), date.length()));
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