#include"../include/patient.hpp"
#include"fstream"
using namespace std;
set<string> Patient::UniqueIDs;
Patient::Patient():Person(){
    patientID="";
    disease="";
}
Patient::Patient(string name, int age, string contact, string patientID="", string disease="") : Person(name, age, contact)
{
    if(patientID.length()>=10){
        throw RangeError("Patient ID can't be more than 10 characters!");
    }
    if (disease.length() > 30)
    {
        throw RangeError("Disease length exceeds it must be within 30 characters");
    }
    if(UniqueIDs.find(patientID)!=UniqueIDs.end()){
        throw UniquePatientID("Patient already exists on this ID");
    }
    UniqueIDs.insert(patientID);
    this->patientID=patientID;
    this->disease=disease;
}



void Patient::updatePatientInfo(Patient& p,string name, int age, string contact, string patientID, string disease)
{
    if(UniqueIDs.find(p.patientID)!=UniqueIDs.end()){
        if(p.patientID!=patientID){
            UniqueIDs.erase(p.patientID);
            UniqueIDs.insert(patientID);
            p.patientID = patientID;
        }
        p.name = name;
        p.age = age;
        p.contact = contact;
        p.disease=disease;
        return;
    }

    throw UniquePatientID("This person does not exists");
}

void Patient::getDetails()
{
    cout<<"id: "<<patientID<<"\n";
    Person::getDetails();
    cout<<"Disease: "<<disease<<"\n";
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
        return;
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
        cout << "disease: " << buffer << "\n\n\n";
        buffer="";
    }
}

string Patient::getPatientID(){
    return patientID;
}

void Patient::removePatient(const string& patientID){
    if(UniqueIDs.find(patientID)!=UniqueIDs.end()){
        UniqueIDs.erase(patientID);
    }else{
        throw PatientExists("Patient With this Id does not exists");
    }
}