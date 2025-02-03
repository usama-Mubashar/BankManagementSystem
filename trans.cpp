#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class card{
	int id;
	string cardno;
	string pin;
public:
	card(){
		
	}
	string generateCardNumber(){
		string cardNum = "";
		srand(time(0));
		for (int i = 0; i < 16; ++i) {
			cardNum += to_string(rand() % 10);
		}
		return cardNum;

	}
	void addcard(int i, string cn, string p) {
		id = i;
		cardno = cn;
		pin = p;

		ifstream fin("card.txt");
		bool hasData = fin.peek() != ifstream::traits_type::eof(); 
		fin.close();

		ofstream fout("card.txt", ios::app);
		if (hasData) {
			fout << endl; 
		}
		fout << i << "," << cardno << "," << pin;
	}

	void update_pin(string p, int i){
		pin = p;
		bool isstart = false;
		ofstream fout("temp.txt");
		ifstream fin("card.txt");
		card temp;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.cardno, ',');
			getline(fin, temp.pin);
			if (isstart == true){
				fout << endl;
			}
			if (id == i){
				temp.pin = p;
			}
			fout << id << "," << temp.cardno << "," << temp.pin;
			isstart = true;
		}
		fout.close();
		fin.close();
		remove("card.txt");
		rename("temp.txt", "card.txt");
	}
	bool checkpin(string p){
		ifstream fin("card.txt");
		card temp;
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			getline(fin, temp.cardno, ',');
			getline(fin, temp.pin);
			if (p == temp.pin){
				return true;
			}
		}
		return false;
	}

};

class transaction{
	card d;
	string date;
	int id;
	string amount;
	string type;
	int id2;
public:
	transaction(){

	}


	void viewalltransation_history(){
		ifstream fin("transaction.txt");
		if (!fin){
			cout << "File not opend" << endl;

		}
		else{
			transaction temp;
			while (getline(fin, temp.date, ',')){
				

				fin >> temp.id;
				
				fin.ignore();
				getline(fin, temp.amount, ',');
				
				fin >> temp.type;
				
				fin.ignore();
				if (temp.type == "Transfer"){
					
					fin.ignore();
					fin >> temp.id2;
					
					cout << temp.date << "," << temp.id << "," << temp.amount << "," << temp.type << "," << temp.id2 << endl;
				}
				else {
					cout << temp.date << "," << temp.id << "," << temp.amount << "," << temp.type  << endl;
				}
			}
		}
		system("pause");
		}
	
	void specifictransaction_history(int i){
		int count = 0;
		bool istransfer = false;
		string pass;
		cout << "Enter your Card Pin To view Transaction History : ";
		cin >> pass;
		if (d.checkpin(pass)){
			count++;
			ifstream fin("transaction.txt");
			if (!fin){
				cout << "File not opend" << endl;

			}
			else{
				transaction temp;
				while (getline(fin, temp.date, ',')){


					fin >> temp.id;

					fin.ignore();
					getline(fin, temp.amount, ',');

					fin >> temp.type;

					fin.ignore();
					if (temp.type == "Transfer"){

						fin.ignore();
						fin >> temp.id2;
						if (temp.id == i){
							istransfer = true;
							cout << temp.date << "," << temp.id << "," << temp.amount << "," << temp.type << "," << temp.id2 << endl;
							
						}

					}
					else {
						if (temp.id == i){
							istransfer = true;
							cout << temp.date << "," << temp.id << "," << temp.amount << "," << temp.type << endl;
							
						}
					}
				}
			}

		}
	
		else{
			cout << "You Entered Invalid card Pin!!!" << endl;
			
		}
		
		if ((!istransfer)&&(count>0)){
			cout << "You have no tranfer history yet!!" << endl;
			
		}
		system("pause");
	}
	
	
};
class AccountType{
private:

	string accountType;
	
public:
	AccountType(){

	}
	void account_limit(double esitimate_withdraw,int c){
		if (c==1){
			if (esitimate_withdraw <= 100000){
				accountType = "Bronze";
			}
			else if (esitimate_withdraw <= 500000){
				accountType = "Gold";
			}
			else if (esitimate_withdraw <= 20000000){
				accountType = "Bussiness";
			}
		}
		else{
			if (esitimate_withdraw <= 100000){
				accountType = "Bronze";
			}
			else if (esitimate_withdraw <= 500000){
				accountType = "Gold";
			}
		}
		
		
	}
	void givetype(double esitimate_withdraw, int id,int c){
		ifstream fin("accounttype.txt");
		bool hasData = fin.peek() != ifstream::traits_type::eof();
		fin.close();

		ofstream fout("accounttype.txt", ios::app);
		if (hasData) {
			fout << endl;
		}
		account_limit(esitimate_withdraw, c);
		fout << id << "," << accountType;
		fout.close();
		fin.close();
	}
	void explaintype(int i){
		int id;
		ifstream fin("accounttype.txt");
		while (!fin.eof()){
			fin >> id;
			fin.ignore();
			fin >> accountType;
			
			if (id == i){
				cout << "  - Account Type  : " << accountType << endl; 
			}
		}

		
	}
};
