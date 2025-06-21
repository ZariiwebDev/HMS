#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include"iostream"
#include"set"
#include"doctor.hpp"
#include"billing.hpp"
#include"patient.hpp"
using namespace std;

class Appointment{
    private:
       static set<string> appointmentIds;
       bool dateValidator(string date);
       bool timeValidator(string time);
       public:
        string appointmentID;
        Doctor doctor;
        Patient patient;
        string date;
        string time;
        string status;
        Billing bill;
        Appointment();
        Appointment(string appointmentID, string date, string time, string doctorID, string docname, string doccontact, string docspecialization, string from, string to, string PatientID, string paname, string pacontact, string disease,double ammount);
        void sheduleAppointment();
        void confirmAppointment();
        void cancelAppointment();
        void getAppointmentDetails();
        void generateBill();
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
class TimeError : public runtime_error {
    public:
        TimeError(const char *message) : runtime_error(message) {}
};
class BillGenerationError : public runtime_error {
    public:
        BillGenerationError(const char* message):runtime_error(message){};
};
#endif
