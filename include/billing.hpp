#ifndef BILLING_H
#define BILLING_H

#include"iostream"
#include"set"
using namespace std;

class Billing {
    private:
        static set<string>billids;
        bool dateValidator(string date);
        string generateUniqueBillID();
        public:
        string patientId;
        string billID;
        double ammount;
        string date;
        string status;
        Billing();
        Billing(string patientId,double ammount,string date);
        void generateBill();
        void payBill();
        void getBillDetails();
        void static saveToFile(const Billing&);
        void static loadFromFile();
        string getBillID();
};

class BillIDError : public runtime_error {
    public:
        BillIDError(const char* message) : runtime_error(message){};
};
#endif