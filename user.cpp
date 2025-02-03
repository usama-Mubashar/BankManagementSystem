#include<iostream>
#include"trans.cpp"
#include<fstream>
#include<string>
using namespace std;


class UserClient {
private:
	transaction t1;
	card d;
	int id;
	string FullName;
	string address;
	string PhoneNumber;
	string Cnic;
	string LoginId;
	string password;
	double esitimate_withdraw;
	string account_balance;
	string cardNo;
	string pin;
	string status;
	AccountType a1;
public:
	
	void create_user(){

		string cnicPattern = "^[0-9]{13}$";

		cout << "Enter your details to open a new bank account: " << endl;

		cout << "ENTER FULL NAME : ";
		getline(cin, FullName);

		cout << "Address: ";
		getline(cin, address);

		cout << "Phone: ";
		getline(cin, PhoneNumber);

		cout << "CNIC: ";
		getline(cin, Cnic);
		cout << "Login ID: ";
		getline(cin, LoginId);

		cout << "Password: ";
		getline(cin, password);

		cout << "Enter Estimate withdraw limit : ";
		cin >> esitimate_withdraw;
		if (esitimate_withdraw>500000){
			cout << "YOU cannot withdraw such high ammount" << endl;
		}
		else{
			a1.account_limit(esitimate_withdraw, 2);
		}
		

		
		cardNo = d.generateCardNumber();
		ofstream fout("user.csv", ios::app);
		ifstream fin("user.csv");
		UserClient temp;
		bool ischeck = true;
		if (!fin){
			cout << "File not opened" << endl;
		}
		else{
			while (!fin.eof()){
				fin >> id;
				fin.ignore();
				getline(fin, temp.FullName, ',');
				getline(fin, temp.address, ',');
				getline(fin, temp.PhoneNumber, ',');
				getline(fin, temp.Cnic, ',');
				getline(fin, temp.LoginId, ',');
				getline(fin, temp.password, ',');
				getline(fin, temp.account_balance, ',');
				getline(fin, temp.cardNo, ',');
				getline(fin, temp.pin, ',');

				getline(fin, temp.status);


				if ((FullName == temp.FullName) && (Cnic == temp.Cnic)){
					cout << "You already have account in this bank please login to access it " << endl;
					ischeck = false;
					break;

				}

				if ((LoginId == temp.LoginId)){
					cout << "This Login Id is already register please choose another one!!!" << endl;
					cout << "ENTER LoginId AGAIN : ";
					cin >> LoginId;
				}


			}

			if (ischeck == true){
				adddetails(FullName, address, PhoneNumber, Cnic, LoginId, password, cardNo, esitimate_withdraw);
			}

		}
	}
	
	void adddetails(string FullName, string address, string PhoneNumber, string Cnic, string LoginId, string password, string cardNo, double esitimate_withdraw){
		ofstream fout("user.csv", ios::app);
		ifstream fin("user.csv");

		if (!fin){
			cout << "file not opened";
		}
		else{
			account_balance = "0";
			status = "F";
			pin = "0";
			UserClient temp;
			readfile(fin);
			id = id + 1;
			d.addcard(id, cardNo,"0");
			if (id > 1){
				fout << endl;
			}
			fout << id << "," << FullName << "," << address << "," << PhoneNumber << "," << Cnic << "," << LoginId << "," << password << "," << account_balance << "," << cardNo << "," << pin << "," << status;
			cout << "Account is Created but Still unactive untill authorties authorized it " << endl;
			system("pause");
			fout.close();
			fin.close();
			a1.givetype(esitimate_withdraw, id,2);
			
		}

	}
	void readfile(ifstream &fin){
		UserClient temp;
		int count = 0;
		if (!fin){
			id = 0;
		}
		while (!fin.eof()){
			count++;
			fin >> id;
			fin.ignore();
			getline(fin, temp.FullName, ',');
			getline(fin, temp.address, ',');
			getline(fin, temp.PhoneNumber, ',');
			getline(fin, temp.Cnic, ',');
			getline(fin, temp.LoginId, ',');
			getline(fin, temp.password, ',');
			getline(fin, temp.account_balance, ',');
			getline(fin, temp.cardNo, ',');
			getline(fin, temp.pin, ',');

			getline(fin, temp.status);


		}
		if (count == 1){
			id = 0;
		}
	}
	bool verify(string emid, string pass){
		int l = 0;
		int count = 0;
		bool isfirst = false;
		ifstream fin("user.csv");
		ofstream fout("tempfile.csv");
		UserClient temp;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.FullName, ',');
			getline(fin, temp.address, ',');
			getline(fin, temp.PhoneNumber, ',');
			getline(fin, temp.Cnic, ',');
			getline(fin, temp.LoginId, ',');
			getline(fin, temp.password, ',');
			getline(fin, temp.account_balance, ',');
			getline(fin, temp.cardNo, ',');
			getline(fin, temp.pin, ',');

			getline(fin, temp.status);
			if ((emid == temp.LoginId) && (pass == temp.password) && (temp.status == "T")){
				count++;
				if (temp.pin == "0") {
					cout << "PLEASE SET YOUR 4-DIGIT CARD PIN : ";
					cin >> temp.pin;
					d.update_pin(temp.pin,id);
					cout << "YOUR PIN HAS BEEN SET SUCCESSFULLY" << endl;
					system("pause");
					cout << "press any key to continue" << endl;
				}


			}
			else if ((emid == temp.LoginId) && (pass == temp.password) && (temp.status == "F")){

				cout << "Your account is Still Unactive " << endl;
				l = 1;
				break;
			}
			if (isfirst == true){
				fout << endl;
			}
			fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << temp.account_balance << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
			isfirst = true;

		}
		fin.close();
		fout.close();
		remove("user.csv");
		rename("tempfile.csv", "user.csv");
		if (count == 0){
			if (l == 1){
				return false;
			}
			else{
				cout << "Invalid Employe ID or Password!!" << endl;
				return false;
			}
		}
		else{
			return true;
		}
	}

	void depositandwithdraw(string amount, string userempID, string pass,int c){
		bool istranfer = false;
		int ad = 0;
		int add = 0;
		bool iswithdraw = false;
		long int tempam = 0;
		ifstream fin("user.csv");
		ofstream fout("tempfile.csv");
		UserClient temp;
		bool isfirst = false;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.FullName, ',');
			getline(fin, temp.address, ',');
			getline(fin, temp.PhoneNumber, ',');
			getline(fin, temp.Cnic, ',');
			getline(fin, temp.LoginId, ',');
			getline(fin, temp.password, ',');
			getline(fin, temp.account_balance, ',');
			getline(fin, temp.cardNo, ',');
			getline(fin, temp.pin, ',');
			getline(fin, temp.status);
			if (c == 1||c==3){


				if (isfirst == true){
					fout << endl;
				}
				if ((userempID == temp.LoginId) && (pass == temp.password)){
					tempam = stod(temp.account_balance) + stod(amount);
					ad = id;
					fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << tempam << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
					if (c == 3){
						
						add = id;
						istranfer = true;
					}
				}
				else{
					fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << temp.account_balance << "," << temp.cardNo << "," << temp.pin << "," << temp.status;

				}
				isfirst = true;
				
			}

			if (c == 2||c==4){


				if (isfirst == true){
					fout << endl;
				}
				if ((userempID == temp.LoginId) && (pass == temp.password)){
					if (stod(temp.account_balance) > stod(amount)){
						tempam = stod(temp.account_balance) - stod(amount);
						ad = id;
						fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << tempam << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
						iswithdraw = true;
						
					}
					else{
						fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << temp.account_balance << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
						if (c == 2){
							cout << "YOU ACCOUNT DID NOT HAVE SUFFICENT BALANCE TO WITHDRAW " << endl;
							system("pause");
						}
						if (c == 4){
							cout << "You donot have enough funds to tranfer" << endl;
							system("pause");
						}
						
					}
					

				}
				else{

					fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << temp.account_balance << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
					
				}
				isfirst = true;

			}
			
		}
		if (c == 1){
			ofstream fout("transaction.txt", ios::app);
			string date;
			cout << "Enter Date(day-month-year): ";
			cin >> date;
			fout << date << "," << ad << "," << amount << "," << "Deposit" << endl;
			cout << "Ammount Deposited Successful!!!" << endl;
			cout << "Your new Balance is : " << "RS " << tempam << endl;
			fout.close();
			system("pause");
		}
		if (c == 2){
			if (iswithdraw){
				ofstream fout("transaction.txt", ios::app);
				string date;
				cout << "Enter Date(day-month-year): ";
				cin >> date;
				fout << date << "," << ad << "," << amount << "," << "Withdraw" << endl;
				cout << "Ammount Withdraw SuccessFull!!! " << endl;
				cout << "Balance LEFT : " << "RS " << tempam << endl;
				system("pause");
			}
		}
		
		if (c == 3){
			if (istranfer){
				cout << "Ammount has been Tranfered" << endl;
				system("pause");
				ofstream fout("transaction.txt", ios::app);
				fout << add<<endl;
			}
			else{
				cout << "The account you Entered to tranfer Ammount is Incorrect" << endl;
				system("pause");
			}
		
		
		}
		if (c == 4){
			ofstream fout("transaction.txt", ios::app);
			string date;
			cout << "Enter Date(day-month-year): ";
			cin >> date;
			fout << date << "," << ad << "," << amount << "," << "Tranfer "<<",";
		}
		
		fin.close();
		fout.close();
		remove("user.csv");
		rename("tempfile.csv", "user.csv");
		
	}
	void showAccountDetails(string userempID, string pass){

		ifstream fin("user.csv");
		UserClient temp;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.FullName, ',');
			getline(fin, temp.address, ',');
			getline(fin, temp.PhoneNumber, ',');
			getline(fin, temp.Cnic, ',');
			getline(fin, temp.LoginId, ',');
			getline(fin, temp.password, ',');
			getline(fin, temp.account_balance, ',');
			getline(fin, temp.cardNo, ',');
			getline(fin, temp.pin, ',');

			getline(fin, temp.status);
			if ((userempID == temp.LoginId) && (pass == temp.password)){
				cout << "=========================================" << endl;
				cout << "  - Name     : " << temp.FullName  <<endl;
				cout << "  - Phone No : " << temp.PhoneNumber << endl;
				cout << "  - CNIC No  : " << temp.Cnic  << endl;
				cout << "  - Address  : " << temp.address << endl;
				cout << "  - Balance  : " << temp.account_balance << endl;
				a1.explaintype(id);
				cout << "=========================================" << endl;
				system("pause");
			}

		}
	}
	void transferamount(string userempID, string pass, string newempId,string pass2,string amount){
		depositandwithdraw(amount, userempID, pass, 4);
		depositandwithdraw(amount, newempId, pass2, 3);
	}
	void viewtransa(string i,string pas){
		ifstream fin("user.csv");
		UserClient temp;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.FullName, ',');
			getline(fin, temp.address, ',');
			getline(fin, temp.PhoneNumber, ',');
			getline(fin, temp.Cnic, ',');
			getline(fin, temp.LoginId, ',');
			getline(fin, temp.password, ',');
			getline(fin, temp.account_balance, ',');
			getline(fin, temp.cardNo, ',');
			getline(fin, temp.pin, ',');

			getline(fin, temp.status);
			if ((i==temp.LoginId)&&(pas==temp.password)){
			t1.specifictransaction_history(id);
			}
		}
		
	}
	void reqapprove(){
		int count = 0;
		ofstream fout("temp.csv");
			ifstream fin("user.csv");
			UserClient temp;
			bool ischeck = true;
			bool isfirst = false;
			int i = 1;
			while (!fin.eof()){
				int choice;
				fin >> id;
				fin.ignore();
				getline(fin, temp.FullName, ',');
				getline(fin, temp.address, ',');
				getline(fin, temp.PhoneNumber, ',');
				getline(fin, temp.Cnic, ',');
				getline(fin, temp.LoginId, ',');
				getline(fin, temp.password, ',');
				getline(fin, temp.account_balance, ',');
				getline(fin, temp.cardNo, ',');
				getline(fin, temp.pin, ',');
				getline(fin, temp.status);
				if (temp.status == "F"){
					count++;
					cout << endl;
					cout << "Application No: " << i << " For Approval" << endl;
					cout << "Application for approval " << endl;
					cout << "Name: " << temp.FullName << endl;
					cout << "Address: " << temp.address << endl;
					cout << "PhoneNumber: " << temp.PhoneNumber << endl;
					cout << "Cnic: " << temp.Cnic << endl;
					cout << endl;
					cout << "You want to approve it or not: "<<endl;
					cout << "1:Approved" << endl;
					cout << "2:Reject" << endl;
					cout << "Enter your Choice: ";
					cin >> choice;
					if (choice == 1){
						temp.status = "T";
						ischeck = true;
						cout << "Account has Been Approved and Activated " << endl;
						system("pause");
						
					}
					else if (choice == 2){
						ischeck = false;
						cout << "Account has Been Rejected and Removed " << endl;
						system("pause");
						
					}
					else{
						cout << " invalid choice" << endl;
						ischeck = false;
					}
					
					i++;
				}
				
				if (ischeck){
					if (isfirst){
						fout << endl;
					}
					fout << id << "," << temp.FullName << "," << temp.address << "," << temp.PhoneNumber << "," << temp.Cnic << "," << temp.LoginId << "," << temp.password << "," << temp.account_balance << "," << temp.cardNo << "," << temp.pin << "," << temp.status;
					isfirst = true;
				}
			}
			if (count == 0){
				cout << "There is no Application For approval" << endl;
				
			}
			else{
				cout << "All The Applications Has Been Viewed" << endl;
				
			}
			system("pause");
			fin.close();
			fout.close();
			remove("user.csv");
			rename("temp.csv", "user.csv");
	}
}; 








class CompanyClient {
private:
	string companyID, companyName, address, taxNumber, userID, password, estimatedailywithdraw;
	string cardNumber, pin;
	double balance;
	int failedAttempts;
	UserClient c1;
public:
	CompanyClient() : balance(0.0), failedAttempts(0) {}



	void createAccount() {
		cout << "Enter Company ID: ";
		cin >> companyID;
		cout << "Enter Company Name: ";
		cin.ignore();
		getline(cin, companyName);
		cout << "Enter Address: ";
		getline(cin, address);
		cout << "Enter Tax Number: ";
		cin >> taxNumber;
		cout << "Enter User ID: ";
		cin >> userID;
		cout << "Enter Password: ";
		cin >> password;

		

		ofstream fout("companies.txt", ios::app);
		fout << companyID << "," << companyName << "," << address << "," << taxNumber
			<< ", " << userID << "," << password << "," << balance << endl; // ", " << cardNumber << ", " << pin << "\n";
		fout.close();

		cout << "Company account created successfully!" << endl;
		system("cls");
	
	}

	bool login() {
		string inputID, inputPass;
		cout << "Enter Company User ID: ";
		cin >> inputID;
		cout << "Enter Password: ";
		cin >> inputPass;

		ifstream fin("companies.txt");
		while (getline(fin, companyID, ',')){

			getline(fin, companyName, ',');
			getline(fin, address, ',');
			getline(fin, taxNumber, ',');
			getline(fin, userID, ',');

			getline(fin, password, ',');
			fin >> balance;
			getline(fin, cardNumber, ',');
			getline(fin, pin);
			fin.ignore();

			if (inputID == userID && inputPass == password) {
				cout << "Login Successful!" << endl;

				system("pause");
				return true;
			}
		}
		fin.close();
		cout << "Invalid userid or password!" << endl;
		system("pause");
		return false;
	}

	bool authenticateTransaction() {
		string enteredPin;
		cout << "Enter your 4-digit PIN: "; cin >> enteredPin;
		if (enteredPin == pin) {
			failedAttempts = 0;
			return true;
		}
		else {
			failedAttempts++;
			cout << "Incorrect PIN!" << endl;
			if (failedAttempts >= 3) {
				cout << "Account locked due to multiple incorrect attempts!" << endl;
				return false;
			}
			return false;
		}
	}

	void deposit() {
		int c;
		bool isdeposit = false;
		cout << "You want to deposite money in your personal account or company account : " << endl;
		cout << "1:Company Account " << endl;
		cout << "2:Personal Account" << endl;
		cout << "Enter choice: ";
		cin >> c;
		double amount2;
		if (c == 1){
			bool isstart = false;
			ifstream fin("companies.txt");
			ofstream fout("temp.txt");
			string n,p;
			cout << "Enter Companies UserName: ";
			cin>>n;
			cout << "Enter Companies Password: ";
			cin >> p;
			cout << "Enter deposit amount: ";
			cin >> amount2;
			while (getline(fin, companyID, ',')){

				getline(fin, companyName, ',');
				getline(fin, address, ',');
				getline(fin, taxNumber, ',');
				getline(fin, userID, ',');

				getline(fin, password, ',');
				fin >> balance;
				fin.ignore();
				if (isstart == true){
					cout << endl;
				}
				if ((n == userID) && (p == password)){
					balance = balance + amount2;
					isdeposit = true;
				}
				fout << companyID << "," << companyName << "," << address << "," << taxNumber
					<< "," << userID << "," << password << "," << balance;
				isstart = true;

			}
			if (isdeposit){
				cout << "Ammount deposite SuccessFul" << endl;
				system("pause");
			}
			else{
				cout << "Wrong id or password" << endl;
				system("pause");
			}
			fin.close();
			fout.close();
			remove("companies.txt");
			rename("temp.txt", "companies.txt");
		}
		if (c == 2){
			string n, p;
			string amount2;
			cout << "Enter personal UserName: ";
			cin >> n;
			cout << "Enter personal Password: ";
			cin >> p;
			cout << "Enter deposit amount: ";
			cin >> amount2;
			c1.depositandwithdraw(amount2, n, p, 1);
		}
		
		
	}

	void withdraw() {
	

		int c;
		bool iswithdraw = false;
		cout << "You want to Withdraw money From your personal account or company account : " << endl;
		cout << "1:Company Account " << endl;
		cout << "2:Personal Account" << endl;
		cout << "Enter choice: ";
		cin >> c;
		double amount2;
		if (c == 1){
			bool isstart = false;
			ifstream fin("companies.txt");
			ofstream fout("temp.txt");
			string n, p;
			cout << "Enter Companies UserName: ";
			cin >> n;
			cout << "Enter Companies Password: ";
			cin >> p;
			cout << "Enter Withdraw amount: ";
			cin >> amount2;
			while (getline(fin, companyID, ',')){

				getline(fin, companyName, ',');
				getline(fin, address, ',');
				getline(fin, taxNumber, ',');
				getline(fin, userID, ',');

				getline(fin, password, ',');
				fin >> balance;
				fin.ignore();
				if (isstart == true){
					cout << endl;
				}
				if ((n == userID) && (p == password)){
					if (balance > amount2){
						balance = balance - amount2;
						iswithdraw = true;
					}
					else{
						cout << "Cannot withdraw your withdraw Balnce is greater than the balnce in your account" << endl;
						
					}
					
				}
				fout << companyID << "," << companyName << "," << address << "," << taxNumber
					<< "," << userID << "," << password << "," << balance;
				isstart = true;

			}
			if (iswithdraw){
				cout << "Ammount Withdraw SuccessFul" << endl;
				system("pause");
			}
			else{
				cout << "Wrong id or password" << endl;
				system("pause");
			}
			fin.close();
			fout.close();
			remove("companies.txt");
			rename("temp.txt", "companies.txt");
		}
		else if (c == 2){
			string n, p;
			string amount2;
			cout << "Enter personal UserName: ";
			cin >> n;
			cout << "Enter personal Password: ";
			cin >> p;
			cout << "Enter Withdraw amount: ";
			cin >> amount2;
			c1.depositandwithdraw(amount2, n, p, 2);
		}
		else{
			cout << "Invalid Choice!!" << endl;
		}
	}
	void view_details(){
		int c;
		
		cout << "You want to view your personal account or company account : " << endl;
		cout << "1:Company Account " << endl;
		cout << "2:Personal Account" << endl;
		cout << "Enter choice: ";
		cin >> c;
		if (c == 1){
			bool isstart = false;
			ifstream fin("companies.txt");
			string n, p;
			cout << "Enter Companies UserName: ";
			cin >> n;
			cout << "Enter Companies Password: ";
			cin >> p;
			while (getline(fin, companyID, ',')){

				getline(fin, companyName, ',');
				getline(fin, address, ',');
				getline(fin, taxNumber, ',');
				getline(fin, userID, ',');

				getline(fin, password, ',');
				fin >> balance;
				fin.ignore();

				if ((n == userID) && (p == password)){
					cout << "Company Name: " << companyName << endl;
					cout << "Company Address: " << address << endl;
					cout << "Tax Number: " << taxNumber << endl;
					cout << "Balance: " << balance << endl;
					system("pause");
					isstart = true;
				}
			}
			if (!isstart){
				cout << "Invalid UserName or Password" << endl;
			}
		}
		if (c == 2){
			string n, p;
			
			cout << "Enter personal UserName: ";
			cin >> n;
			cout << "Enter personal Password: ";
			cin >> p;
			c1.showAccountDetails(n, p);
			
		}
	}
	void requestLoan() {
		bool ischeck=false;
		double loanAmount;
		string u, p;
		cout << "Enter Company username: ";
		cin >> u;
		cout << "Enter Company password: ";
		cin >> p;
		cout << "Enter Loan Amount: "; 
		cin >> loanAmount;
		ifstream fin("companies.txt");
		while (getline(fin, companyID, ',')){

			getline(fin, companyName, ',');
			getline(fin, address, ',');
			getline(fin, taxNumber, ',');
			getline(fin, userID, ',');

			getline(fin, password, ',');
			fin >> balance;
			fin.ignore();
			if ((u == userID) && (p == password)){
				ofstream fout("loan.txt", ios::app);
				fout << companyID << "," << companyName << "," << loanAmount << endl;
				ischeck = true;
			}
		}
		if (ischeck){
			cout << "Loan Request Sent for Approval!" << endl;
			system("pause");
		}
		else{
			cout << "invalid company details for loan!!" << endl;
			system("pause");
		}
		
	}
	void approveloan(){
		ifstream fin("loan.txt");
		string id, compname;
		double loan;
		ifstream fin2("companies.txt");
		ofstream fout("temp.txt");
		while(!fin.eof()){
			int c;
			getline(fin, id, ',');
			getline(fin, compname, ',');
			fin >> loan;
			fin.ignore();
			cout << "Company ID: " << id << endl;
			cout << "Company Name: " << compname << endl;
			cout << "Loan Applied of Rs: " << loan << endl;
			system("pause");
			cout << "Approved Loan" << endl;
			cout << "1:Yes" << endl;
			cout << "2:No" << endl;
			cout << "Enter Choice: ";
			cin >> c;
			if (c == 1){
				bool isstart = false;
				while (getline(fin2, companyID, ',')){

					getline(fin2, companyName, ',');
					getline(fin2, address, ',');
					getline(fin2, taxNumber, ',');
					getline(fin2, userID, ',');

					getline(fin2, password, ',');
					fin2 >> balance;
					fin2.ignore();
					if (isstart){
						fout << endl;
					}
					if (companyName==compname){
						balance = balance + loan;
						
					}
					fout << companyID << "," << companyName << "," << address << "," << taxNumber
						<< "," << userID << "," << password << "," << balance;
					isstart = true;
					cout << "Loan Approved" << endl;
					system("pause");
				}
			}
			else{
				cout << "Loan Rejected" << endl;
				system("pause");

			}
		}
		fin.close();
		fin2.close();
		fout.close();
		remove("companies.txt");
		rename("temp.txt", "companies.txt");
	}
	
};

class BankingEmployee{
	transaction t1;
	UserClient u2;
	string name;
	string password;
	CompanyClient cc1;
public:
	BankingEmployee(){

	}
	bool login(){
		
		cout << "Enter Login Name: ";
		cin >> name;
		cout << "Enter Password: ";
		cin >> password;
		BankingEmployee temp;
		ifstream fin("admin.txt");
		if (!fin){
			cout << "File not opened" << endl;
		}
		else{
			while (getline(fin, temp.name, ',')){
				getline(fin,temp.password);
				if ((name == temp.name) && (password == temp.password)){
					return true;
				}
			}
			return false;
		}
	}
	void approvereq(){
	
		u2.reqapprove();
	}
	void approveloan(){
		cc1.approveloan();
	}
	void viewall(){
		t1.viewalltransation_history();
	}
};


