#include"../include/patient.hpp"
#include"string.h"
#include"fstream"
using namespace std;
set<string> Patient::UniqueIDs;
Patient::Patient():Person(){
    strcpy(patientID,"0");
    strcpy(disease,"");
}
Patient::Patient(string name, int age, string contact, string patientID="", string disease="") : Person(name, age, contact)
{
    loadIds();
    if(patientID.length()>14){
        throw RangeError("Patient ID can't be more than 14 characters!");
    }
    if (disease.length() > 30)
    {
        throw RangeError("Disease length exceeds it must be within 30 characters");
    }
    if(UniqueIDs.find(patientID)!=UniqueIDs.end()){
        throw UniquePatientID("Patient already exists on this ID");
    }
    UniqueIDs.insert(patientID);
    strcpy(this->patientID,patientID.c_str());
    strcpy(this->disease,disease.c_str());
    saveids();
}

void Patient::registerPatient(string patientID, string disease){
    loadIds();
    if (patientID.length() > 14)
    {
        throw RangeError("Patient ID can't be more than 14 characters!");
    }
    if (disease.length() > 30)
    {
        throw RangeError("Disease length exceeds it must be within 30 characters");
    }
    if (UniqueIDs.find(patientID) != UniqueIDs.end())
    {
        throw UniquePatientID("Patient already exists on this ID");
    }
    UniqueIDs.insert(patientID);
    strcpy(this->patientID, patientID.c_str());
    strcpy(this->disease, disease.c_str());
    saveids();
}
void Patient::updatePatientInfo(string name, int age, string contact, string patientID, string disease)
{
    if(UniqueIDs.find(patientID)!=UniqueIDs.end()){
        Person(name,age,contact);
        strcpy(this->disease,disease.c_str());
    }else{
        throw UniquePatientID("This person does not exists");
    }
}

void Patient::getPatientDetails()
{
    cout<<"id: "<<patientID<<"\n";
    Person::getPersonDetails();
    cout<<"Disease: "<<disease<<"\n";
}

size_t Patient::sizeOf() const{
    return sizeof(*this);
}

void Patient::saveids()
{
    ofstream file(".//data//patientids.txt", ios::out);
    if (!file.is_open())
    {
        throw FileNotOpening("unique ids can't be stored");
    }
    for(string ele : UniqueIDs){
        file<<ele<<"\n";
    }
    file.close();
}

void Patient::loadIds()
{
    ifstream file(".//data//patientids.txt", ios::in|ios::out);
    if (!file.is_open())
    {
        throw FileNotOpening("unique ids can't be fetched ");
    }
    file.seekg(0,ios::end);
    if(file.tellg()==0){
       return;
    }
    file.seekg(0,ios::beg);
    string buffer;
    while(getline(file,buffer)){
        if(buffer.length())
            UniqueIDs.insert(buffer);
    }
}


void Patient::saveToFile(const Patient& p){
    fstream file(".//data//patient.txt",ios::out|ios::app);
    if(!file.is_open()){
        throw FileNotOpening("sorry we can't store patient data");
    }

    file<<p.patientID<<"\n";
    file<<p.name<<"\n";
    file<<p.age<<"\n";
    file<<p.contact<<"\n";
    file<<p.disease<<"\n";

    cout << "patient is added sucessfully\n";
}

void Patient::loadFromFile(){
    fstream file(".//data//patient.txt",ios::in);
    if(!file.is_open()){
        // in case check if no data is stored
        ofstream temp(".//data//patient.txt", ios::out);
        if(!temp.is_open()){
            throw FileNotOpening("Patients can't be fetched due to file not found");
        }
    }

    // moving pointer to the end of file in case if file is empty
    file.seekg(0,ios::end);
    if(file.tellg()==0){
        cout<<"no patient found";
    }
    file.seekg(0,ios::beg);
    string buffer;
    while(!file.eof()){
        getline(file,buffer);
        if(buffer.length())
        cout<<"Patient ID: "<<buffer<<"\n";
        buffer="";
        getline(file,buffer);
        if(buffer.length())
        cout<<"name: "<<buffer<<"\n";
        buffer="";
        getline(file,buffer);
        if(buffer.length())
        cout<<"age: "<<buffer<<"\n";
        buffer="";
        getline(file,buffer);
        if(buffer.length())
        cout<<"contact: "<<buffer<<"\n";
        buffer="";
        getline(file,buffer);
        if(buffer.length())
        cout<<"disease: "<<buffer<<"\n";
        buffer="";
    }
}