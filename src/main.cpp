#include"iostream"
#include"patient.hpp"         // --> Patient
#include"staff.hpp"          // --> Staff
#include"doctor.hpp"        // --> Doctor
#include"appointment.hpp"  // --> appointment
#include"stdexcept"
#include"vector"
#include"windows.h"
using namespace std;

void adminMenu(void);
// patient management
void patientManagement(void);
// searching
void patientRemove(string );
void showPatientRecords();
void updatePatientRecords(int);
int searchPatient(string);


// staff management
void staffManagement(void);
void addStaff();
void showStaffRecords();
int searchStaff(string);
void updateStaffRecords(int);
void removeStaff(string);

// doctor management
void doctorManagement(void);
void addDoctor();
void showDoctorRecords();
int searchDoctor(string);
void updateDoctorRecords(int);
void removeDoctor(string);

// biling management

void billManagement(void);

// appointment management
void appointmentManagement(void);
void patientRecords();
void doctorRecords();
int showRecordsForAppointments();
void createNSheduleAppointment();
void showAppointments();
int searchAppointments(string);


// database records
vector<Patient>patients;
vector<Staff> staff;
vector<Doctor> doctors;
vector<Appointment> appointments;


int main(){
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout<<"\n\n";
    int choice;
    do{ 
        adminMenu();
        cin>>choice;
        if(choice==5){
            cout<<"\nGoodBye\n";
            exit(0);
        }
        else if(choice==1){
            patientManagement();   
        }
        else if(choice==2){
            staffManagement();
        }
        else if(choice==3){
            doctorManagement();
        }
        else if(choice==4){
            if(patients.size() && doctors.size()){
                int ch = showRecordsForAppointments();
                cout<<"\n\n\n";
                if(ch==1){
                    appointmentManagement();
                }
            }
            else{
                cout << "\n\033[31mPlease first add patients and doctors to manage Appointments\033[0m\n";
            }   
        }
        else{
            cout<<"\n Please Choose correct Option\n";
        }
    }while(true);
    return 0;
}

void adminMenu(){
    cout<<"\n";
    cout<<"╭────────────────────────────────·· ꓓ ꓥ ꓢ ꓧ ꓐ ꓳ ꓥ ꓣ ꓓ ··──────────────────────────···" << endl;
    cout<<"│ "<<endl;
    cout<<"│▶> 1 - Patient Management "<<endl;
    cout<<"│"<<endl;
    cout<<"│▶> 2 - Staff Management "<<endl;
    cout<<"│"<<endl;
    cout<<"│▶> 3 - Doctor Management "<<endl;
    cout<<"│ "<<endl;
    cout<<"│▶> 4 - Appointment Management "<<endl;
    cout<<"│ "<<endl;
    cout<<"│▶> 5 - Exit system "<<endl;
    cout<<"│ "<<endl;
    cout<<"│ Select one of above "<<endl;
    cout<<"╰──────────────···"<<endl;
    cout<<"\nEnter your choice: ";
}

// patient management
void patientManagement(){
    int patientchoice;
    do{
        cout << "\n";
        cout << "╭────────────────────────────────·· ꓑ ꓥ ꓔ ꓲ ꓱ ꓠ ꓔ ··──────────────────────────···" << endl;
        cout << "│ " << endl;
        cout << "│▶> 1 - Add Patient " << endl;
        cout << "│" << endl;
        cout << "│▶> 2 - Remove Patient " << endl;
        cout << "│" << endl;
        cout << "│▶> 3 - Update Patient " << endl;
        cout << "│ " << endl;
        cout << "│▶> 4 - Show Patients " << endl;
        cout << "│ " << endl;
        cout << "│▶> 5 - Save Records To File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 6 - Load Records From File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 7 - Exit to Dashboard" << endl;
        cout << "│ " << endl;
        cout << "│ Select one of above " << endl;
        cout << "╰──────────────···" << endl;
        cout << "\nEnter your choice: ";
        cin>>patientchoice;
        if(patientchoice==7){
            cout<<"\n exiting to Dashboard\n";
            break;
        }else if(patientchoice==1){
            bool is_error=false;
            do{
                try{
                    string patientId,name,contact,disease;
                    int age;
                    cout<<"Enter Patient ID [UNIQUE]: ";
                    cin>>patientId;
                    cin.ignore();
                    cout<<"Enter Patient name: ";
                    getline(cin,name);
                    cout<<"Enter Patient age: ";
                    cin>>age;
                    cout<<"Enter Patient Contact: ";
                    cin>>contact;
                    cin.ignore();
                    cout<<"Enter Patient Disease: ";
                    getline(cin,disease);
                    patients.push_back(Patient(name,age,contact,patientId,disease));            //! *** 
                    cout<<"\n Patient is successfully added ✅\n";
                    is_error=false;
                }
                catch(const RangeError& error){
                    cout<<"\n \033[31m RANGE ERROR : "<<error.what()<<"\033[0m \n";
                    cout<<"Enter your details again in correct format\n";
                    is_error=true;
                }
                catch(const UniquePatientID& error){
                    cout<<"\n \033[31m UNIQUE ID ERROR : "<<error.what()<<" \033[0m \n";
                    cout<<"\tEnter your details again in correct format\n";
                    is_error=true;
                }
            }while(is_error);

        }
        else if (patientchoice==2){
            if(!patients.size())
            {
                cout << "\n \033[31m Please First Add patients to remove them"<<" \033[0m \n";
                continue;
            }
            else
            {
                string patientid;
                cout<<"Enter Patient ID : ";
                cin>>patientid;
                try{
                    patientRemove(patientid);
                }
                catch(const PatientExists& e){
                    cout << "\n \033[31m ERROR: " << e.what() << " \033[0m \n";
                }
            }
        }
        else if (patientchoice==3){
            if (!patients.size())
            {
                cout << "\n \033[31m Please First Add patients to update records" << " \033[0m \n";
                continue;
            }
            else
            {
                string patientid;
                cout << "Enter Patient ID : ";
                cin >> patientid;
                try
                {
                    int index=searchPatient(patientid);
                    if(index==-1){
                        throw PatientExists("Patient ID does not exist");
                    }

                    updatePatientRecords(index);
                }
                catch (const PatientExists &e)
                {
                    cout << "\n \033[31m ERROR: " << e.what() << " \033[0m \n";
                }
                catch(const UniquePatientID& e){
                    cout << "\n \033[31m ERROR: " << e.what() << " \033[0m \n";
                }
            }
        }
        else if(patientchoice==4){
            if (!patients.size())
            {
                cout << "\n \033[31m Please First Add patients to show records" << " \033[0m \n";
                continue;
            }else{
                showPatientRecords();
            }
        }
        else if(patientchoice==5){
            if (!patients.size())
            {
                cout << "\n \033[31m Please First Add patients to save records" << " \033[0m \n";
                continue;
            }
            else
            {
                try{
                    int size=patients.size();
                    for(int i=0;i<size;i++){
                        Patient::saveToFile(patients[i]);
                    }
                    cout << "patients are added sucessfully to file \n";
                    
                }
                catch(const FileNotOpening& e){
                    cout << "\n \033[31m ERROR: " << e.what() << " \033[0m \n";
                }
            }
        }
        else if(patientchoice==6){
                try
                {
                    cout << "\npatients are added sucessfully loaded... \n\n";
                    Patient::loadFromFile();
                }
                catch (const FileNotOpening &e)
                {
                    cout << "\n \033[31m ERROR: " << e.what() << " \033[0m \n";
                }
        }
        else {
            cout << "\n \033[31m Please choose correct options" << " \033[0m \n";
            continue;
        }
    }while(true);
}

void patientRemove(string target)
{
    int size = patients.size();
    for (int i = 0; i < size ; i++)
    {
        if(patients[i].getPatientID() == target){
            if(i!=0){
                cout<<"\nPatient # "<<patients[i].getPatientID()<<" is successfully removed \n";
                patients[i].removePatient(target);
                patients.erase(patients.begin()+i);
                return;
            }
            else{
                cout << "\nPatient # " << patients[i].getPatientID() << " is successfully removed\n";
                patients[i].removePatient(target);
                patients.erase(patients.begin());
                return;
            }
        }
    }
    throw PatientExists("You Entered Wrong Patient ID");
}

void showPatientRecords()
{
    int size = patients.size();
    cout<<"\t\t\t\t Total Patients#"<<size<<"\n";
    for(int i=0;i<size;i++){
        cout<<"\n\nPATIENT # "<<i+1<<"\n";
        patients[i].getDetails();
    }
}

int searchPatient(string target){
    int size = patients.size();
    for (int i = 0; i < size; i++)
    {
        if (patients[i].getPatientID() == target)
        {
            return i;   
        }
    }
    return -1;
}

void updatePatientRecords(int index){
    bool is_error = false;
    do
    {
        try
        {
            string patientId, name, contact, disease;
            int age;
            cout << "Enter Patient ID [UNIQUE]: ";
            cin >> patientId;
            cin.ignore();
            cout << "Enter Patient name: ";
            getline(cin, name);
            cout << "Enter Patient age: ";
            cin >> age;
            cout << "Enter Patient Contact: ";
            cin >> contact;
            cin.ignore();
            cout << "Enter Patient Disease: ";
            getline(cin, disease);
            Patient::updatePatientInfo(patients[index],name,age,contact,patientId,disease); //! ***
            cout << "\n Patient is successfully updated ✅\n";
            is_error = false;
        }
        catch (const RangeError &error)
        {
            cout << "\n \033[31m RANGE ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const UniquePatientID &error)
        {
            cout << "\n \033[31m UNIQUE ID ERROR : " << error.what() << " \033[0m \n";
            cout << "\tEnter your details again in correct format\n";
            is_error = true;
        }
    } while (is_error);
}



// staff management

void staffManagement(){
    int staffchoice;
    do{
        cout << "\n";
        cout << "╭────────────────────────────────·· ꓢ ꓔ ꓥ ꓝ ꓝ ··──────────────────────────···" << endl;
        cout << "│ " << endl;
        cout << "│▶> 1 - Add Staff " << endl;
        cout << "│" << endl;
        cout << "│▶> 2 - Remove Staff " << endl;
        cout << "│" << endl;
        cout << "│▶> 3 - Update Staff " << endl;
        cout << "│ " << endl;
        cout << "│▶> 4 - Show Staff " << endl;
        cout << "│ " << endl;
        cout << "│▶> 5 - Save Records To File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 6 - Load Records From File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 7 - Exit to Dashboard" << endl;
        cout << "│ " << endl;
        cout << "│ Select one of above " << endl;
        cout << "╰──────────────···" << endl;
        cout << "\nEnter your choice: ";
        cin>>staffchoice;
        if(staffchoice==7){
            cout << "\n exiting to Dashboard ...\n";
            break;
        }
        else if(staffchoice==1){
            addStaff();
        }
        else if(staffchoice==2){
            if(!staff.size()){
                cout << "\n \033[31m Please First Add Staff to remove them" << " \033[0m \n";
                continue;
            }
            else{
                string staffid;
                cout<<"Enter Staff ID: ";
                cin>>staffid;
                try{
                    removeStaff(staffid);
                }
                catch (const StaffNotFound& e)
                {
                    cout << "\n \033[31m ERROR : " << e.what() << " \033[0m \n";
                }
                catch (const UniqueIDError& e)
                {
                    cout << "\n \033[31m UNIQUE ID ERROR : " << e.what() << " \033[0m \n";
                }
            }
        }
        else if(staffchoice==3){
            if (!staff.size())
            {
                cout << "\n \033[31m Please First Add Staff to update them" << " \033[0m \n";
                continue;
            }
            else
            {
                string staffid;
                cout << "Enter Staff ID: ";
                cin >> staffid;
                try{
                    int index = searchStaff(staffid);
                    if(index==-1){
                        throw StaffNotFound("Sorry we cannot find the Staff in database");
                    }
                    updateStaffRecords(index);
                }
                catch (const StaffNotFound &error)
                {
                    cout << "\n \033[31m ERROR : " << error.what() << "\033[0m \n";        
                }
            }
        }
        else if(staffchoice==4){
            if (!staff.size())
            {
                cout << "\n \033[31m Please First Add Staff to see them" << " \033[0m \n";
                continue;
            }
            else
            {
                showStaffRecords();
            }
        }
        else if(staffchoice==5){
            if (!staff.size())
            {
                cout << "\n \033[31m Please First Add Staff to save them" << " \033[0m \n";
                continue;
            }
            else {
            cout<<"\n storing Staff records...\n";
            int size=staff.size();
            try{
                for(int i=0;i<size;i++){
                    cout<<"\n Staff # "<<(i+1)<<" ";
                    Staff::saveToFile(staff[i]);
                }
                cout<<"\n";
            }
            catch(const FileNotOpening& e){
                cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
            }
         }
        }
        else if(staffchoice==6){
            cout << "\n loading Staff records...\n";
            
            try
            {
                Staff::loadFromFile();
                cout<<"Staff records are loaded successfully ✅\n";
            }
            catch (const FileNotOpening &e)
            {
                cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
            }
        }
        else{
            cout<<"\nPlease choose correct option\n";
            continue;
        }
    }while(true);
}

void addStaff(){
    bool is_error=false;
    do{
        string name,contact,role,shift,staffid;
        int age;
        cout<<"Enter Staff ID[UNIQUE]: ";
        cin>>staffid;
        cin.ignore();
        cout<<"Enter Staff Person Name: ";
        getline(cin,name);
        cout<<"Enter Staff Person Age: ";
        cin>>age;
        cout<<"Enter Staff Person ContactNo: ";
        cin>>contact;
        cin.ignore();
        cout<<"Enter Staff Person Role: ";
        getline(cin,role);
        cout<<"Enter Staff Person Shift: ";
        cin>>shift;
        try{
            staff.push_back(Staff(name,age,contact,staffid,role,shift));
            cout<<"\nStaff successfully added ✅\n";
            is_error=false;
        }
        catch (const RangeError &error)
        {
            cout << "\n \033[31m RANGE ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const UniqueIDError &error)
        {
            cout << "\n \033[31m ID ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const ShiftError &error)
        {
            cout << "\n \033[31m Shift ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        
    } while (is_error);
}

void removeStaff(string target){
    int size = staff.size();
    for (int i = 0; i < size; i++)
    {
        if (staff[i].getStaffID() == target)
        {
            if (i != 0)
            {
                cout << "\nStaff # " << staff[i].getStaffID() << " is successfully removed \n";
                staff[i].removeStaff(target);
                staff.erase(staff.begin() + i);
                return;
            }
            else
            {
                cout << "\nStaff # " << staff[i].getStaffID() << " is successfully removed \n";
                staff[i].removeStaff(target);
                staff.erase(staff.begin());
                return;
            }
        }
    }
    throw StaffNotFound("You Entered Wrong Staff ID");
}

int searchStaff(string target){
    int size = staff.size();
    for (int i = 0; i < size; i++)
    {
        if (staff[i].getStaffID() == target)
        {
            return i;
        }
    }
    return -1;
}

void updateStaffRecords(int index){
    bool is_error = false;
    do
    {
        string name, contact, role, shift, staffid;
        int age;
        cout << "Enter Staff ID[UNIQUE]: ";
        cin >> staffid;
        cin.ignore();
        cout << "Enter Staff Person Name: ";
        getline(cin, name);
        cout << "Enter Staff Person Age: ";
        cin >> age;
        cout << "Enter Staff Person ContactNo: ";
        cin >> contact;
        cin.ignore();
        cout << "Enter Staff Person Role: ";
        getline(cin, role);
        cout << "Enter Staff Person Shift: ";
        cin >> shift;
        try
        {
            Staff::updateStaffInfo(staff[index],name, age, contact, staffid, role, shift);
            cout << "\nStaff successfully updated ✅\n";
            is_error = false;
        }
        catch (const RangeError &error)
        {
            cout << "\n \033[31m RANGE ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const UniqueIDError &error)
        {
            cout << "\n \033[31m ID ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const ShiftError &error)
        {
            cout << "\n \033[31m Shift ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const StaffNotFound &error)
        {
            cout << "\n \033[31m ERROR : " << error.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }

    } while (is_error);
}

void showStaffRecords(){
    int size = staff.size();
    cout << "\t\t\t\t Total Staff Members#" << size << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "\n\nStaff Member# " << i + 1 << "\n\n";
        staff[i].getDetails();
    }
}


// doctor management

void doctorManagement(){
    int doctorChoice;
    do{
        cout << "\n";
        cout << "╭────────────────────────────────·· ꓓ ꓳ ꓛ ꓔ ꓳ ꓣ  ··──────────────────────────···" << endl;
        cout << "│ " << endl;
        cout << "│▶> 1 - Add Doctor " << endl;
        cout << "│" << endl;
        cout << "│▶> 2 - Remove Doctor " << endl;
        cout << "│" << endl;
        cout << "│▶> 3 - Update Doctor " << endl;
        cout << "│ " << endl;
        cout << "│▶> 4 - Show Doctor " << endl;
        cout << "│ " << endl;
        cout << "│▶> 5 - Save Records To File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 6 - Load Records From File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 7 - Exit to Dashboard" << endl;
        cout << "│ " << endl;
        cout << "│ Select one of above " << endl;
        cout << "╰──────────────···" << endl;
        cout << "\nEnter your choice: ";
        cin >> doctorChoice;
        if (doctorChoice == 7)
        {
            cout << "\n exiting to Dashboard ...\n";
            break;
        }
        else if (doctorChoice == 1)
        {
            addDoctor();
        }
        else if (doctorChoice == 2)
        {
            if (!doctors.size())
            {
                cout << "\n \033[31m Please First Add Doctor to remove them" << " \033[0m \n";
                continue;
            }
            else
            {
                string doctorid;
                cout << "Enter Doctor ID: ";
                cin >> doctorid;
                try
                {
                    removeDoctor(doctorid);
                }
                catch (const UniqueDoctorIDError &e)
                {
                    cout << "\n \033[31m ERROR : " << e.what() << " \033[0m \n";
                }
            }
        }
        else if (doctorChoice == 3)
        {
            if (!doctors.size())
            {
                cout << "\n \033[31m Please First Add Doctors to update them" << " \033[0m \n";
                continue;
            }
            else
            {
                string doctorid;
                cout << "Enter Doctor ID: ";
                cin >> doctorid;
                try
                {
                    int index = searchDoctor(doctorid);
                    if (index == -1)
                    {
                        throw UniqueDoctorIDError("Sorry we cannot find the doctors in database");
                    }
                    updateDoctorRecords(index);
                }
                catch (const UniqueDoctorIDError &error)
                {
                    cout << "\n \033[31m ERROR : " << error.what() << "\033[0m \n";
                }
            }
        }
        else if (doctorChoice == 4)
        {
            if (!doctors.size())
            {
                cout << "\n \033[31m Please first add doctors to see them" << " \033[0m \n";
                continue;
            }
            else
            {
                showDoctorRecords();
            }
        }
        else if (doctorChoice == 5)
        {
            if (!doctors.size())
            {
                cout << "\n \033[31m Please First Add Doctors to save them" << " \033[0m \n";
                continue;
            }
            else
            {
                cout << "\n storing Doctors records...\n";
                int size = doctors.size();
                try
                {
                    for (int i = 0; i < size; i++)
                    {
                        cout << "\n Doctor # " << (i + 1) << " ";
                        Doctor::saveToFile(doctors[i]);
                    }
                    cout << "\n";
                }
                catch (const FileNotOpening &e)
                {
                    cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
                }
            }
        }
        else if (doctorChoice == 6)
        {
            cout << "\n loading Doctors records...\n";

            try
            {
                Doctor::loadFromFile();
                cout << "Doctors record are loaded successfully ✅\n";
            }
            catch (const FileNotOpening &e)
            {
                cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
            }
        }
        else
        {
            cout << "\nPlease choose correct option\n";
            continue;
        }
    }while(true);
}

void addDoctor(){
    bool is_error = false;
    do{
        string name, contact,doctorid,from,to,specialization;
        int age;
        cout<<"Enter Doctor ID[UNIQUE]: ";
        cin>>doctorid;
        cin.ignore();
        cout<<"Enter Doctor Name: ";
        getline(cin,name);
        cout<<"Enter Doctor age: ";
        cin>>age;
        cout<<"Enter Doctor Contact No : ";
        cin>>contact;
        cin.ignore();
        cout<<"Enter Doctor Specialization: ";
        getline(cin,specialization);
        cout<<"Enter Doctor Shedule Time from --> to : ";
        cin>>from>>to;
        try{
            doctors.push_back(Doctor(name,age,contact,doctorid,specialization,from,to));
            cout<<"\nDoctor successfully added ✅\n";
            is_error=false;
        }
        catch(const RangeError& e){
            cout << "\n \033[31m RANGE ERROR : " << e.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch(const UniqueDoctorIDError& e){
            cout << "\n \033[31m RANGE ERROR : " << e.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
    }while(is_error);
}

void removeDoctor(string target){
    int size = doctors.size();
    for (int i = 0; i < size; i++)
    {
        if (doctors[i].getDoctorID() == target)
        {
            if (i != 0)
            {
                cout << "\nDoctor # " << doctors[i].getDoctorID() << " is successfully removed \n";
                doctors[i].removeDoctor(target);
                doctors.erase(doctors.begin() + i);
                return;
            }
            else
            {
                cout << "\nDoctor # " << doctors[i].getDoctorID() << " is successfully removed \n";
                doctors[i].removeDoctor(target);
                doctors.erase(doctors.begin());
                return;
            }
        }
    }
    throw UniqueDoctorIDError("Sorry Doctor with this ID does not Found");
}


int searchDoctor(string target){
    int size = doctors.size();
    for (int i = 0; i < size; i++)
    {
        if (doctors[i].getDoctorID() == target)
        {
            return i;
        }
    }
    return -1;
}

void updateDoctorRecords(int index){
    bool is_error = false;
    do
    {
        string name, contact, doctorid, from, to, specialization;
        int age;
        cout << "Enter Doctor ID[UNIQUE]: ";
        cin >> doctorid;
        cin.ignore();
        cout << "Enter Doctor Name: ";
        getline(cin, name);
        cout << "Enter Doctor age: ";
        cin >> age;
        cout << "Enter Doctor Contact No : ";
        cin >> contact;
        cin.ignore();
        cout << "Enter Doctor Specialization: ";
        getline(cin, specialization);
        cout << "Enter Doctor Shedule Time from --> to : ";
        cin >> from >> to;
        try
        {
            Doctor::updateDoctorInfo(doctors[index],name,age,contact,doctorid,specialization,from,to);
            cout << "\nDoctors are successfully updated ✅\n";
            is_error = false;
        }
        catch (const RangeError &e)
        {
            cout << "\n \033[31m RANGE ERROR : " << e.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
        catch (const UniqueDoctorIDError &e)
        {
            cout << "\n \033[31m RANGE ERROR : " << e.what() << "\033[0m \n";
            cout << "Enter your details again in correct format\n";
            is_error = true;
        }
    } while (is_error);
}

void showDoctorRecords(){
    int size = doctors.size();
    cout << "\t\t\t\t Total Doctors#" << size << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << "\n\nDoctor# " << i + 1 << "\n\n";
        doctors[i].getDetails();
    }
}

void appointmentManagement(void){
    bool permissions=false;
    int appointmentChoice;
    do{
        cout << "\n";
        cout << "╭────────────────────────────────·· ꓥ ꓑ ꓑ ꓛ ꓲ ꓠ ꓔ ꓟ ꓰ ꓠ ꓔ  ··──────────────────────────···" << endl;
        cout << "│ " << endl;
        cout << "│▶> 1 - Create & Shedule Appointment " << endl;
        cout << "│" << endl;
        cout << "│▶> 2 - Confirm Appointment " << endl;
        cout << "│ " << endl;
        cout << "│▶> 3 - Cancel Appointment " << endl;
        cout << "│ " << endl;
        cout << "│▶> 4 - Show Appointments" << endl;
        cout << "│ " << endl;
        cout << "│▶> 5 - Billing " << endl;
        cout << "│ " << endl;
        cout << "│▶> 6 - Save To File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 7 - Load From File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 8 - Exit To DashBoard" << endl;
        cout << "│ " << endl;
        cout << "│ Select one of above " << endl;
        cout << "╰──────────────···" << endl;
        cout << "\nEnter your choice: ";
        cin>>appointmentChoice;
        if(appointmentChoice==8){
            cout<<"\nExiting to Dashboard ...\n";
            break;
        }
        else if(appointmentChoice==1){
            createNSheduleAppointment();
        }
        else if(appointmentChoice==2){
            if(!appointments.size()){
                cout<<"\n\033[31m Please First Create and shedule Appointment to confirm \033[0m\n";
                continue;
            }
            else{
                string appid;
                cout<<"Enter Appointment ID : ";
                cin>>appid;
                try{
                    int index = searchAppointments(appid);
                    if(index==-1){
                        throw UniqueAppointmentError("Sorry we can't find appointment on this ID");
                    }
                    appointments[index].confirmAppointment();
                    permissions=true;
                }
                catch (const UniqueAppointmentError& e)
                {
                    cout << "\n \033[31m APPOINTMENT ERROR : " << e.what() << "\033[0m \n";
                }
            }
        }
        else if(appointmentChoice==3){
            if (!appointments.size())
            {
                cout << "\n\033[31m Please First Create and shedule Appointment to cancel \033[0m\n";
                continue;
            }else{
                string appid;
                cout << "Enter Appointment ID : ";
                cin >> appid;
                try
                {
                    int index = searchAppointments(appid);
                    if (index == -1)
                    {
                        throw UniqueAppointmentError("Sorry we can't find appointment on this ID");
                    }
                    appointments[index].cancelAppointment();
                }
                catch (const UniqueAppointmentError &e)
                {
                    cout << "\n \033[31m APPOINTMENT ERROR : " << e.what() << "\033[0m \n";
                }
            }
        }
        else if(appointmentChoice==4){
            if (!appointments.size())
            {
                cout << "\n\033[31m Please First Create and shedule Appointment to cancel \033[0m\n";
                continue;
            }
            else{
                int size = appointments.size();
                for(int i=0;i<size;i++){
                    appointments[i].getAppointmentDetails();
                    cout<<"\n";
                }
            }
        }
        else if(appointmentChoice==5){
                //  billing management
                if(!appointments.size() && !permissions){
                    cout << "\n\033[31m Please First Confirm any  Appointment to access billing \033[0m\n";
                    continue;
                }
                else{
                    billManagement();
                }
        }
        else if(appointmentChoice==6){
            if (!appointments.size())
            {
                cout << "\n\033[31m Please First Create and shedule Appointment to save \033[0m\n";
                continue;
            }
            else{
                try{
                    int size = appointments.size();
                    for(int i=0;i<size;i++){
                        cout<<"\nAppointment#"<<i+1<<"\n";
                        Appointment::saveToFile(appointments[i]);
                    }
                    cout<<"Appointments are successfully added ✅\n";
                }
                catch(const FileNotOpening& e){
                    cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
                }
            }
        }
        else if(appointmentChoice==7){
                try{
                    cout<<"loading appointments ...\n";

                    cout<<"Appointments are successfully loaded ✅\n";
                }
                catch(const FileNotOpening& e){
                    cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
                }
        }
    }while(true);
}


int showRecordsForAppointments(){
    cout << "\n\t\t\033[31m ⚠⚠⚠ PLEASE READ THESE DETAILS FIRST BEFORE MAKING APPOINTMENTS \033[0m\n";
    patientRecords();
    cout<<"\n\n\n";
    doctorRecords();
    char choice;
    do{
        cout<<"\n Press y/n to start: ";
        cin>>choice;
        if(choice!='y'&& choice!='Y'&& choice!='n'&& choice!='N'){
            cout<<"\n please Enter Correct Choice\n";
        }
    }while(choice!='y'&& choice!='Y'&& choice!='n'&& choice!='N');
    if(choice=='y'||choice=='Y'){
        return 1;
    }
    if(choice=='n'||choice=='N'){
        return 0;
    }
    return -1;
}

void patientRecords(){
    cout<<"\n\t\t\t\t PATIENTS \n\n";
    int size = patients.size();
    cout<<"ID\t\t\tName\t\t\t ContactNo.\t\n\n";
    for(int i=0;i<size;i++){
        cout<<patients[i].getPatientID()<<"\t\t\t"<<patients[i].name<<"\t\t  "<<patients[i].contact<<"\n";
    }
}

void doctorRecords(){
    cout<<"\n\t\t\t\t DOCTORS \n\n";
    int size = doctors.size();
    cout<<"ID\t\t\tName\t\t\t ContactNo.\t\n\n";
    for(int i=0;i<size;i++){
        cout << doctors[i].getDoctorID() << "\t\t\t" << doctors[i].name << "\t\t  " << doctors[i].contact << "\n";
    }
}

void createNSheduleAppointment(){
        try{
            string patientid;
            string doctorid;
            string appid, date,time;
            double ammout;
            cout<<"Enter Patient ID: ";
            cin>>patientid;
            int patientIndex = searchPatient(patientid);
            if(patientIndex==-1){
                throw UniquePatientID("Sorry no patient Found in database to appoint");
            }
            cout<<"Enter Doctor ID: ";
            cin>>doctorid;
            int doctorIndex = searchDoctor(doctorid);
            if(doctorIndex==-1){
                throw UniqueDoctorIDError("Sorry no doctor Found in database to appoint");
            }
            cout<<"Enter Appointment ID:";
            cin>>appid;
            cout<<"Enter Date for Appointment [dd/mm/yy] : ";
            cin>>date;
            cout<<"Enter Time for Appointment [hh/mm] : ";
            cin>>time;
            cout<<"Enter Doctor Frees (PKR): ";
            cin>>ammout;
            appointments.push_back(Appointment(appid, date, time, doctors[doctorIndex].getDoctorID(), doctors[doctorIndex].name, doctors[doctorIndex].contact, doctors[doctorIndex].specialization, doctors[doctorIndex].shedule.from, doctors[doctorIndex].shedule.to,patients[patientIndex].getPatientID(),patients[patientIndex].name,patients[patientIndex].contact,patients[patientIndex].disease,ammout));
            int index = searchAppointments(appid);
            if(index==-1){
                throw UniqueAppointmentError("Sorry the Appointment with this ID is not created ❌");
            }
            cout<<"\n\n";
            appointments[index].sheduleAppointment();
            cout<<"\n\n";
        }
        catch(const UniquePatientID& e){
            cout << "\n \033[31m PATIENT ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const UniqueDoctorIDError &e)
        {
            cout << "\n \033[31m DOCTOR ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const UniqueAppointmentError &e)
        {
            cout << "\n \033[31m APPOINTMENT ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const DateError &e)
        {
            cout << "\n \033[31m DATE ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const TimeError &e)
        {
            cout << "\n \033[31m TIME ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const BillIDError &e)
        {
            cout << "\n \033[31m BILL ID ERROR : " << e.what() << "\033[0m \n";
        }
        catch (const runtime_error &e)
        {
            cout << "\n \033[31m Ammount ERROR : " << e.what() << "\033[0m \n";
        }
}

int searchAppointments(string target){
    int size = appointments.size();
    for (int i = 0; i < size; i++)
    {
        if (appointments[i].getAppointmentID() == target)
        {
            return i;
        }
    }
    return -1;
}

void billManagement()
{
    bool permission=false;
    int billchoice;
    do{
        cout << "\n";
        cout << "╭────────────────────────────────·· ꓐ ꓲ ꓡ ꓡ ꓲ ꓠ ꓖ  ··──────────────────────────···" << endl;
        cout << "│ " << endl;
        cout << "│▶> 1 - Generate Bill " << endl;
        cout << "│" << endl;
        cout << "│▶> 2 - Pay Bill " << endl;
        cout << "│" << endl;
        cout << "│▶> 3 - Show Bills " << endl;
        cout << "│" << endl;
        cout << "│▶> 4 - Save Records To File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 5 - Load Records From File" << endl;
        cout << "│ " << endl;
        cout << "│▶> 6 - Exit to Appointment" << endl;
        cout << "│ " << endl;
        cout << "│ Select one of above " << endl;
        cout << "╰──────────────···" << endl;
        cout << "\nEnter your choice: ";
        cin>>billchoice;
        if(billchoice==6){
            cout<<"Exiting to APPOINTMENT MENU ...\n";
            break;
        }
        else if(billchoice==1){
            string appid;
            cout<<"Enter Appointment ID: ";
            cin>>appid;
            try{
                int index = searchAppointments(appid);
                if(index==-1){
                    throw UniqueAppointmentError("Sorry cannot find appointment on this ID");
                }
                appointments[index].generateBill();
                permission=true;
            }
            catch(const UniqueAppointmentError& e){
                cout << "\n \033[31m APPOINTMENT ERROR : " << e.what() << "\033[0m \n";
            }
            catch(const BillGenerationError& e){
                cout << "\n \033[31m BILL ERROR : " << e.what() << "\033[0m \n";
            }
        }
        else if(billchoice==2){
            if(!permission){
                cout << "\n\033[31m Please First generate Bill \033[0m\n";
                continue;
            }else{
                string appid;
                cout<<"Enter appointment ID: ";
                cin>>appid;
                try{
                    int index = searchAppointments(appid);
                    if (index == -1)
                    {
                        throw UniqueAppointmentError("Sorry cannot find appointment on this ID");
                    }
                    double ammount;
                    cout<<"\n\t\t\t\t\t\tAmount to Pay => "<<appointments[index].bill.ammount<<"PKR\n\n";
                    do{
                        cout<<"Enter amount: ";
                        cin>>ammount;
                        if (ammount != appointments[index].bill.ammount){
                            cout<<"Ammount must match  the ammount to Pay\n";
                        }
                    } while (ammount != appointments[index].bill.ammount);
                    if(appointments[index].status=="confirmed"){
                        appointments[index].bill.payBill();
                    }else{
                        throw BillGenerationError("Appointment is not yet confirmed");
                    }
                }
                catch (const UniqueAppointmentError &e)
                {
                    cout << "\n \033[31m APPOINTMENT ERROR : " << e.what() << "\033[0m \n";
                }
            }
        }
        else if(billchoice==3){
            int size = appointments.size();
            for(int i=0;i<size;i++){
                if(appointments[i].status=="confirmed"){
                    cout<<"bill#"<<i+1<<"\n";
                    appointments[i].bill.getBillDetails();
                }
            }
        }
        else if(billchoice==4){
            int size  = appointments.size();

            try{
                cout << "saving bills ...\n";
                for (int i = 0; i < size; i++)
                {
                    if (appointments[i].status == "confirmed")
                    {
                        Billing::saveToFile(appointments[i].bill);
                    }
                }
                cout << "Bills saved successfully ✅\n";
            }
            catch(const FileNotOpening& e){
                cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
            }
        }
        else if(billchoice==5){
            try{
                cout<<"loading bills ...\n";
                Billing::loadFromFile();
                cout<<"Bills loaded successfully ✅\n";
            }
            catch(const FileNotOpening& e){
                cout << "\n \033[31m FILE ERROR : " << e.what() << "\033[0m \n";
            }
        }
        else{
            cout<<"\nWrong Choice please cooose correct option\n";
        }
    }while(true);
}