#include"billing.hpp"
#include"appointment.hpp"
#include"iostream"
#include"ctime"
#include"stdlib.h"
#include"fstream"
using namespace std;

set<string> Billing::billids;

Billing::Billing()
{
    billID="";
    patientId="";
    ammount=0;
    date="0/0/0";
    status="pending";
}

Billing::Billing(string patientId, double ammount, string date)
{
    this->patientId = patientId;
    if(!dateValidator(date)){
        throw DateError("Date must follow the format: dd/mm/yy");
    }
    this->date=date;
    this->status="pending";
    this->billID = generateUniqueBillID();
    if(billids.find(billID)!=billids.end()){
        throw BillIDError("This bill is already exists in database");
    }
    billids.insert(billID);
    if(ammount<0){
        throw runtime_error("ammount cannot be -ve");
    }
    this->ammount = ammount;
}
string Billing::generateUniqueBillID()
{
    srand(time(0));
    int length[] = {5,8,10,12};
    int randomIndex = rand() % 4;
    int randlength = length[randomIndex];

    string util = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string uniquepass;
    for(int i=0;i<randlength;i++){
        int randIndex= rand() % (util.length()-1);
        uniquepass += util[randIndex];
    }

    return uniquepass;
}
bool Billing::dateValidator(string date)
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

void Billing::generateBill()
{
    status="unpaid";
    cout << "Bill ID: " << billID << "\nAmount: " << ammount << " PKR\nDate: " << date << "\nStatus: " << status << endl;
}
void Billing ::payBill()
{
    this->status = "Paid";
    cout << "Bill " << billID << " marked as paid" << endl;
}

void Billing::getBillDetails()
{
    cout<<"Bill ID: "<<billID<<"\n";
    cout<<"Ammount (PKR): "<<ammount<<"\n";
    cout<<"Date: "<<date<<"\n";
    cout<<"Status: "<<status<<"\n";

}
void Billing::saveToFile(const Billing& b)
{
    ofstream file(".//data//bills.txt", ios::out | ios::app);
    if (!file.is_open())
    {
        throw FileNotOpening("FILE CREATION ERROR : Sorry we do not store generated bills ");
    }

    file<<b.billID << "\n";
    file << b.ammount << "\n";
    file << b.date << "\n";
    file << b.status << "\n";

    cout<<"Bill"<<b.billID<<" Is successfully stored";
}


void Billing::loadFromFile(){
    ifstream file(".//data//bills.txt");
    if (!file.is_open())
    {
        ofstream tmp(".//data//bills.txt");
        if (!tmp.is_open())
        {
            throw FileNotOpening("Sorry we can't fetch data beacuse no data found for appointments");
        }
    }
    file.seekg(0, ios::end);
    if (file.tellg() == 0)
    {
        cout << "No records were Found";
        return;
    }
    file.seekg(0, ios::beg);

    string buffer;
    while(!file.eof()){
        getline(file,buffer);
        if(buffer.length()){
            cout << "Bill ID: " <<buffer<< "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "Ammount (PKR): " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "Date: " << buffer << "\n";
        }
        buffer="";
        getline(file,buffer);
        if(buffer.length()){
            cout << "Status: " << buffer << "\n";
        }
        buffer="";


    }
}

string Billing::getBillID(){
    return billID;
}