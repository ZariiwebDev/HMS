#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include"iostream"
#include"set"
#include"doctor.hpp"
#include"patient.hpp"
using namespace std;

class Appointment{
    private:
       static set<string> appointmentIds;
       public:
       bool dateValidator(string date);
        string appointmentID;
        Doctor doctor;
        Patient patient;
        string date;
        string time;
        string status;
        Appointment();
        Appointment(string appointmentID,string date,string time,string status,string doctorID, string docname,string doccontact, string docspecialization, string to, string from, string PatientID, string paname, int paage, string pacontact, string disease);
        void sheduleAppointment();
        void cancelAppointment();
        void getAppointmentDetails();
        void static saveToFile(const Appointment&);
        void static loadFromFile();
};

class UniqueAppointmentError : public runtime_error {
    public:
        UniqueAppointmentError(const char *message) : runtime_error(message) {}
};
class DateError : public runtime_error {
    public:
        DateError(const char *message) : runtime_error(message) {}
};
#endif
