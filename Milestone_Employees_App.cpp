/*
Application Development Using c++
Uliana Rozzhyvaikina

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <iomanip>


using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct Employee {
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char extension[10];
	char email[100];
	char officecode[10];
	int  reportsTo;
	char jobTitle[50];
};

void displayTitle() {
	cout << "********************* HR Menu *********************" << endl;
}

int menu(void) {
	displayTitle();
	cout << "1) Find Employee" << endl;
	cout << "2) Employee Report" << endl;
	cout << "3) Add Employee" << endl;
	cout << "4) Update Employee" << endl;
	cout << "5) Remove Employee" << endl;
	cout << "0) Exit" << endl;
	cout << "Select an option: ";
	int choice;
	cin >> choice;
	return choice;
}




void insertEmployee(struct  Employee* emp) {
	strcpy(emp->officecode, "1");
	emp->reportsTo = 1002;

	cout << "-------------- New Employee Information -------------" << endl;
	cout << "Employee Number: ";
	cin >> emp->employeeNumber;
	cout << "Last Name: ";
	cin >> emp->lastName;
	cout << "First Name: ";
	cin >> emp->firstName;
	cout << "Extension: ";
	cin >> emp->extension;
	cout << "Email: ";
	cin >> emp->email;
	cout << "Office Code: " << emp->officecode << endl;
	cout << "Manager ID: " << emp->reportsTo << endl;
	cout << "Job Title: ";
	cin >> emp->jobTitle;

}
void deleteEmployee(Connection* conn, int employeeNumber) {
	Statement* stmt = conn->createStatement();
	try {
		stmt->setSQL("DELETE FROM employees WHERE employeeNumber = :1");
		stmt->setInt(1, employeeNumber);
		stmt->executeUpdate();
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	conn->commit();
	conn->terminateStatement(stmt);

}

void updateEmployee(Connection* conn, int employeeNumber, Employee emp) {
	Statement* stmt = conn->createStatement("UPDATE EMPLOYEES SET EXTENSION = :1 WHERE EMPLOYEENUMBER = : 2");
	string ext;
	cout << "Employee Number: " << emp.employeeNumber << endl;
	cout << "Last Name: " << emp.lastName << endl;
	cout << "First Name: " << emp.firstName << endl;
	cout << "Extension: ";
	cin >> ext;
	try {
		
		stmt->setString(1, ext);
		stmt->setInt(2, employeeNumber);
		stmt->executeUpdate();
		conn->commit();
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	
	conn->terminateStatement(stmt);
}
void insertEmployee(Connection* conn, struct Employee emp) {
	Statement* stmt = conn->createStatement();
	try {

		stmt->setSQL("INSERT INTO employees VALUES (:1,:2,:3,:4,:5,:6,:7,:8)");
		stmt->setInt(1, emp.employeeNumber);
		stmt->setString(2, emp.lastName);
		stmt->setString(3, emp.firstName);
		stmt->setString(4, emp.extension);
		stmt->setString(5, emp.email);
		stmt->setString(6, emp.officecode);
		stmt->setInt(7, emp.reportsTo);
		stmt->setString(8, emp.jobTitle);
		stmt->executeUpdate();
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	conn->commit();
	conn->terminateStatement(stmt);


}

int findEmployee(Connection* conn, int employeeNumber, Employee* emp) {
	int	employeeNumberr = 0;
	string	firstName;
	string	lastName;
	string extension;
	string	email;
	string	officecode;
	int	reportsTo = 0;
	string	jobTitle;
	int ret = 0;
	int count = 0;
	int printEm = employeeNumber; // variable to print the number if employee doesnt exist
	Statement* stmt = conn->createStatement();
	try {

		stmt->setSQL("SELECT * FROM employees where employeenumber = :employeeN");
		stmt->setInt(1, employeeNumber);
		ResultSet* rs = stmt->executeQuery();
		while (rs->next()) {
			employeeNumberr = rs->getInt(1);
			firstName = rs->getString(2);
			lastName = rs->getString(3);
			extension = rs->getString(4);
			email = rs->getString(5);
			officecode = rs->getString(6);
			reportsTo = rs->getInt(7);
			jobTitle = rs->getString(8);
			count++; // count for existing record
		}

		if (count > 0) {  //if record found - store into struct 
			ret = 1;
			emp->employeeNumber = employeeNumberr;
			strcpy(emp->firstName, firstName.c_str());// conversion to c-string
			strcpy(emp->lastName, lastName.c_str());
			strcpy(emp->extension, extension.c_str());
			strcpy(emp->email, email.c_str());
			strcpy(emp->officecode, officecode.c_str());
			emp->reportsTo = reportsTo;
			strcpy(emp->jobTitle, jobTitle.c_str());

		}
		else {   //if record empty - print error
			ret = 0;
		}
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return ret;
	conn->terminateStatement(stmt);
}

void displayAllEmployees(Connection* conn) {
	Statement* stmt = conn->createStatement();

	try {

		stmt->setSQL("SELECT e.employeenumber, e.firstname, e.lastname, e.extension, concat(m.firstname, m.lastname) manager FROM employees e JOIN  employees m ON m.employeenumber = e.reportsto");
		ResultSet* rs = stmt->executeQuery();
		cout << "---------------------------------Report1-----------------------------------" << endl;
		cout << "Employee ID   Last name      First name         Extension          Manager" << endl;
		cout << "------------- ----------- ---------------  --------------------  ----------" << endl;
		while (rs->next()) {
			int empNum = rs->getInt(1);
			string firstname = rs->getString(2);
			string lastname = rs->getString(3);
			string extension = rs->getString(4);
			string manager = rs->getString(5);
			cout << left << "   " << empNum << "       " << setw(15) << lastname << " " << setw(15) << firstname << " " << setw(5) << " " << extension << " " << setw(10) << " " << manager << "" << endl;
		}

	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	conn->terminateStatement(stmt);
}

void displayEmployee(Connection* conn, Employee emp) {
	cout << "-------------- Employee Information -------------" << endl;
	cout << "Employee Number: " << emp.employeeNumber << endl;
	cout << "Last Name: " << emp.lastName << endl;
	cout << "First Name: " << emp.firstName << endl;
	cout << "Extension: " << emp.extension << endl;
	cout << "Email: " << emp.email << endl;
	cout << "Office Code: " << emp.officecode << endl;
	cout << "Manager ID: " << emp.reportsTo << endl;
	cout << "Job Title: " << emp.jobTitle << endl;
}

int main(void) {

	Environment* env = nullptr;
	Connection* conn = nullptr;
	string str;
	string user = "dbs211_202f30";
	string pass = "20283149";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	env = Environment::createEnvironment(Environment::DEFAULT);
	conn = env->createConnection(user, pass, constr);
	struct Employee emp = { 0 };
	int employeeNumber;
	int done = 0;
	while (done == 0) {
		int selection = menu();
		if (selection == 1) {
			cout << "Enter Employee Number: ";
			cin >> employeeNumber;
			int check = findEmployee(conn, employeeNumber, &emp);
			if (check == 1) {
				displayEmployee(conn, emp);
				cout << endl;
			}
			else {
				cout << "Employee " << employeeNumber << " does not exist " << endl;
			}
		}
		else if (selection == 2) {
			displayAllEmployees(conn);
			cout << endl;
		}
		else if (selection == 3) {
			insertEmployee(&emp);
			int check2 = findEmployee(conn, emp.employeeNumber, &emp);
			if (check2 == 0) {
				insertEmployee(conn, emp);
				cout << "The new employee is added successfully." << endl;
			}
			else {
				cout << "An employee with the same employee number exists." << endl;
			}

		}

		else if (selection == 4) {
			cout << "Enter Employee Number to update: ";
			cin >> employeeNumber;
			int check3 = findEmployee(conn, employeeNumber, &emp);
			if (check3 == 1) {
				updateEmployee(conn, employeeNumber, emp);
				cout << "The employee's extension is updated successfully." << endl;
			}
			else {
				cout << "The employee with ID " << employeeNumber << " does not exist." << endl;
			}
		}

		else if (selection == 5) {
			cout << "Enter Employee Number to update: ";
			cin >> employeeNumber;
			int check4 = findEmployee(conn, employeeNumber, &emp);
			if (check4 == 1) {
				deleteEmployee(conn, employeeNumber);
				cout << "The employee with ID " << employeeNumber << " is deleted successfully." << endl;
			}
			else {
				cout << "The employee with ID " << employeeNumber << " does not exist." << endl;
			}
		}


		else if (selection == 0) {
			done = 1;
		}
	}

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
	return 0;
}

//header's job
int menu();

int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);

void displayTitle();
void insertEmployee(struct  Employee* emp);
void insertEmployee(Connection* conn, struct Employee emp);
void updateEmployee(Connection* conn, int employeeNumber, Employee emp);
void deleteEmployee(Connection* conn, int employeeNumber);

//:emp->employeeNumber, :emp->lastName, :emp->firstName, :emp->extension, :emp->email, :emp->officecode, :emp->reportsTo, :emp->jobTitle