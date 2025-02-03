#include<iostream>
#include<iomanip>
#include"user.cpp"
#include<fstream>
#include<string>
using namespace std;



void display_logo(){
	cout << setw(80) << "===============================================" << endl;
	cout << setw(80) << "=                                             =" << endl;
	cout << setw(80) << "=       Banking Management System             =" << endl;
	cout << setw(80) << "=                                             =" << endl;
	cout << setw(80) << "===============================================" << endl;
	cout << endl;
}
void existing_userClientMenu(UserClient&user) {
	bool ischeck = true;
	int choice;

	while (ischeck){
		string empID, password;
		cout << "Enter Employee ID: ";
		cin >> empID;
		cout << "Enter Password: ";
		cin >> password;

		if (user.verify(empID, password) == true){
			cout << "Login Successful" << endl;
			ischeck = false;
			while (true) {
				system("cls");
				cout << "1. Deposit Funds" << endl;
				cout << "2. Withdraw Funds" << endl;
				cout << "3. View Account Details" << endl;
				cout << "4. Transfer Funds" << endl;
				cout << "5. Transaction History" << endl;
				cout << "6. Log Out" << endl;
				cout << "Please choose an option: ";
				cin >> choice;

				switch (choice) {
				case 1:
				{
						  string amount;
						  cout << "Enter deposit amount: ";
						  cin >> amount;
						  user.depositandwithdraw(amount, empID, password,choice);
						  break;
				}
				case 2:
				{
						  string amount;
						  cout << "Enter withdrawal amount: ";
						  cin >> amount;
						  user.depositandwithdraw(amount, empID, password, choice);
						  break;
				}
				case 3:
				{
						   user.showAccountDetails(empID, password);
						   break;
				}
					
				case 4:
				{
						   string empID2,password2;
						   cout << "Enter Employee ID Whome You want to Tranfer Funds : ";
						   cin >> empID2;
						   cout << "Enter Password: ";
						   cin >> password2;
						   string amount;
						   cout << "Enter amount You want to transfer : ";
						   cin >> amount;
						   user.transferamount(empID, password, empID2,password2, amount);
						   break;
				}
				case 5:
				{
						  user.viewtransa(empID,password);
				}
				case 6:
				{
						  cout << "Logging out..." << endl;
						  return;
				}
					
				default:
					cout << "Invalid option. Please try again." << endl;
				
				}
			}
				}
					

		else{
			

			int c;
			cout << "1:Try again" << endl;
			cout << "2:Exit" << endl;
			cout << "Enter choice : ";
			cin >> c;
			if (c == 1){
				ischeck = true;
			}
			else if (c == 2){
				return;
			}
		}
	}
}

void signup_login(UserClient &user){
	int choice;
	while (true){
		system("cls");
		cout << "User Client Menu" << endl;
		cout << "1: Create Account" << endl;
		cout << "2: Login Account" << endl;
		cout << "3: Logout" << endl;
		cout << "Enter your choice : ";
		cin >> choice;
		switch (choice){
		case 1:{
				   system("cls");
				   cin.ignore();
				   user.create_user();
				   break;
		}
		case 2:{
				   system("cls");
				   existing_userClientMenu(user);
				   break;
		}
		case 3:
		{
				  cout << "Logging out..." << endl;
				  system("cls");
				  return;
		default:
			cout << "Invalid option. Please try again." << endl;
		}
		}
	}

}

void CompanyClientMenu(CompanyClient &company){
	int choice;
	bool loggedIn = false;

	while (true) {
		if (!loggedIn) {
			system("cls");
			cout <<  endl<<"===== Welcome to the Banking System =====" << endl;
			cout << "1. Create Company Account" << endl;
			cout << "2. Login" << endl;
			cout << "3. Exit" << endl;
			cout << "Enter choice: "; 
			cin >> choice;

			if (choice == 1) {
				company.createAccount();
			}
			else if (choice == 2) {
				loggedIn = company.login();
			}
			else if (choice == 3) {
				system("cls");
				return;
			}
			else {
				cout << "Invalid Choice!"<<endl;
			}
		}
		else {
			
			system("cls");
			cout << "===== Company Client Menu =====" << endl;
			cout << "1. Deposit Funds" << endl;
			cout << "2. Withdraw Funds" << endl;
			cout << "3. View Details" << endl;
			cout << "4. Request Loan" << endl;
			cout << "5. Logout" << endl;
			cout << "Enter choice: "; cin >> choice;

			switch (choice) {
			case 1: company.deposit(); break;
			case 2: company.withdraw(); break;
			case 3: company.view_details(); break;
			case 4: company.requestLoan(); break;
			case 5:  loggedIn = false; break;
			default: cout << "Invalid Choice!"<<endl;
			}
		}
	}
}
void bankMenu2(BankingEmployee &employee){
	bool istrue = true;
	int choice;
	while (istrue){
		system("cls");
		cout << "1:Approve or reject New application" << endl;
		cout << "2:Approve or reject Loan application" << endl;
		cout << "3:View Transaction History " << endl;
		cout << "4:Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		if (choice == 1){
			employee.approvereq();
		}
		else if (choice == 2){
			employee.approveloan();
		}
		else if (choice == 3){
			employee.viewall();
		}
		else if (choice == 4){
			istrue = false;
		}
		else{
			cout << "Invalid choice" << endl;
		}
	}
}
void bankingEmployeeMenu(BankingEmployee &employee)
{
	int choice;
	bool loggedIn = false;

	while (true) {
		if (!loggedIn) {
			system("cls");
			cout << endl << "===== Welcome to the Banking System =====" << endl;

			cout << "1. Login as admin" << endl;
			cout << "2. Exit" << endl;
			cout << "Enter choice: ";
			cin >> choice;
			if (choice == 1){
				if (employee.login()){
					bankMenu2(employee);
				}
				else{
					cout << "Invalid ID or Password" << endl;
					system("pause");
				}
			}
			else if (choice == 2){
				system("cls");
				return;
				
			}
			else{
				cout << "Invalid choice" << endl;
			}
		}
	}
}
int main(){
	display_logo();





	int choice;
	CompanyClient company;
	BankingEmployee employee;
	UserClient user;
	while (true) {
		cout << "Welcome to the  Bank Management System" << endl;
		cout << "1. User Client Menu" << endl;
		cout << "2. Company Client Menu" << endl;
		cout << "3. Banking Employee Menu" << endl;
		cout << "4. Exit" << endl;
		cout << "Please choose an option: ";
		cin >> choice;
		UserClient u1;
		
		switch (choice) {
		case 1:
			signup_login(u1);

			break;
		case 2:
			CompanyClientMenu(company);
			break;
		case 3:
			bankingEmployeeMenu(employee);
			break;
		case 4:
			cout << "Exiting the system."<<endl;
			return 0;
		default:
			cout << "Invalid option. Please try again."<<endl;
		}
	}

	system("pause");
	return 0;
}
