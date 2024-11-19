#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//abstract Class
class Employee{
	protected:
		int empId;
		string name;
	public:
		//concrete method
		void InputBasicInfo(){
			cout<<"Enter Employee ID :";
			cin>>empId;
			cout<<"Enter Employee Name :";
			cin.ignore();
			getline(cin,name);
		}
		void DisplayBasicInfo()const{
			cout<<"---------- Basic Information -------------"<<endl;
			cout<<"Employee ID :"<<empId<<endl;
			cout<<"Employee Name :"<<name<<endl;
		}
		//Pure Virtual Function
		virtual void inputInfo() = 0;
		virtual void calculateSalary() const= 0;
};
//dirived Class Visiting Employee 
class visitingEmp : public Employee{
	private:
		int numberOfDays;
		float dailyWages;
	public:
		//@Override
		void inputInfo(){
			cout<<"Enter Daily Wages :";
			cin>>dailyWages;
			cout<<"Enter Number of Days :";
			cin>>numberOfDays;
		}
		//@Override
		void calculateSalary() const{
			float salary = dailyWages*numberOfDays;
			cout<<"Salary :"<<salary<<endl;
		}
		void saveToFile() const {
    ofstream outFile("EmployeeData.txt", ios::app); // Open in append mode
    if (outFile) {
        outFile << "Visiting Employee\n"; // Identify the type of employee
        outFile << empId << "\n" << name << "\n"; // Save basic info
        outFile << dailyWages << "\n" << numberOfDays << "\n"; // Save visiting-specific info
        outFile.close();
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void loadFromFile(ifstream &inFile) {
    inFile >> empId; inFile.ignore();
    getline(inFile, name);
    inFile >> dailyWages >> numberOfDays;
}

};
//darived Class Parmanet Employee 
class ParmanentEmp : public Employee{
	private:
		int monthlySalary;
	public:
		void inputInfo(){
			cout<<"Enter Monthly Salary :";
			cin>>monthlySalary;
			}
		void calculateSalary() const{
			cout<<"Salary :"<<monthlySalary<<" Per Month"<<endl;
		}
		void saveToFile() const {
    ofstream outFile("EmployeeData.txt", ios::app); // Open in append mode
    if (outFile) {
        outFile << "Permanent Employee\n"; // Identify the type of employee
        outFile << empId << "\n" << name << "\n"; // Save basic info
        outFile << monthlySalary << "\n"; // Save permanent-specific info
        outFile.close();
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void loadFromFile(ifstream &inFile) {
    inFile >> empId; inFile.ignore();
    getline(inFile, name);
    inFile >> monthlySalary;
}
		
};
void loadAllEmployees() {
    ifstream inFile("EmployeeData.txt"); // Open file in read mode
    if (inFile) {
        string type;
        while (getline(inFile, type)) {
            if (type == "Visiting Employee") {
                visitingEmp vEmp;
                vEmp.loadFromFile(inFile); // Load visiting employee data
                vEmp.DisplayBasicInfo();
                vEmp.calculateSalary();
            } else if (type == "Permanent Employee") {
                ParmanentEmp pEmp;
                pEmp.loadFromFile(inFile); // Load permanent employee data
                pEmp.DisplayBasicInfo();
                pEmp.calculateSalary();
            }
        }
        inFile.close();
    } 
	else {
        cout << "No existing data found.\n";
    }
}
main(){
	Employee *Emp;
    int choice;

    // Load existing employees from the file
    loadAllEmployees();

    do {
        cout << "-------- Main Menu ----------\n";
        cout << "1. Create Visiting Employee \n";
        cout << "2. Create Permanent Employee \n";
        cout << "0. Exit \n";
        cout << "Enter Your Choice :";
        cin >> choice;

        switch (choice) {
            case 1:
                Emp = new visitingEmp();
                break;
            case 2:
                Emp = new ParmanentEmp();
                break;
            case 0:
                cout << "Exiting The Program \n";
                break;
            default:
                cout << "Invalid Number: Please Enter a Valid Number\n";
                continue;
        }
        if (choice != 0) {
            Emp->InputBasicInfo(); // Input basic info
            Emp->inputInfo(); // Input employee-specific info
            cout << "\nEmployee Information\n";
            Emp->DisplayBasicInfo();
            Emp->calculateSalary();

            // Save employee data to the file
            if (choice == 1) {
                static_cast<visitingEmp*>(Emp)->saveToFile();
            } else if (choice == 2) {
                static_cast<ParmanentEmp*>(Emp)->saveToFile();
            }
            delete Emp; // Free memory
        }
    } while (choice != 0);
}
