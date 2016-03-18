/*Sara Sheehan
  CSCI 310
  HW 1
*/

#include<iostream>
#include<string.h>
#include<stdlib.h>


using namespace std;

void PrintTable(int low, int high, char operation);
void Usage(char * argv[]);
void GetOperation(int argc, char * argv[], char& operation);
void GetHighLow(int argc, char * argv[], int& low, int& high);
void GetUser(int argc, char * argv[], char * envp[]);
int GetValue(int x, int y, char operation);

int main(int argc, char * argv[], char * envp[]) {
	
	int low = 0;
	int high = 9;
	char operation = 'x';
		
	GetOperation(argc, argv, operation);

	GetHighLow(argc, argv, low, high);
	
	GetUser(argc, argv, envp);
	
	PrintTable(low, high, operation);


	for (int j = 1; j < argc; j++) {
		
		if (!strcmp(argv[j], "-h")) {
			Usage(argv);
		} else if (!strcmp(argv[j], "--help")) {
			Usage(argv);
		}
	}


	return 0;

}

void GetOperation(int argc, char * argv[], char& operation) {
	operation = 'x';
	int setOp = 0;

	
	
	for (int i = 1; i < argc; i++) {

		
		if ((!strcmp(argv[i], "-p")) || (!strcmp(argv[i], "--plus"))) {
			operation = '+';
			setOp++;
		} else if ((!strcmp(argv[i], "-m")) || (!strcmp(argv[i], "--minus"))) {
			operation = '-';
			setOp++;
		} else if ((!strcmp(argv[i], "-d")) || (!strcmp(argv[i], "--divide"))) {
			operation = '/';
			setOp++;
		} else if ((!strcmp(argv[i], "-o")) || (!strcmp(argv[i], "--mod"))) {
			operation = '%';
			setOp++;
		} else {
			operation = 'x';
		}
		
	}	

	
	
	
	if (setOp > 1) {
		cout << "ERROR: only one operation may be specified" << endl;
		Usage(argv);
		exit(-1);
	}

	return;
	
}

void GetHighLow(int argc, char * argv[], int& low, int& high) {
	int i = 1;
	
	while (i < argc) {
		if ((!strcmp(argv[i], "-i")) || (!strcmp(argv[i], "--high"))) {
			i++;
			if (i < argc) {
				high = atoi(argv[i]);
				i++;
			}
			else {
				cout << "ERROR: the option " << argv[i-1] << " requires a value, none given" << endl;
				Usage(argv);
			}
		} else if ((!strcmp(argv[i], "-l")) || (!strcmp(argv[i], "--low"))) {
			i++;
			if (i < argc) {
				low = atoi(argv[i]);
				i++;
			}
			else {
				cout << "ERROR: the option " << argv[i-1] << " requires a value, none given" << endl;
				Usage(argv);
			}
		} else if ((!strcmp(argv[i], "-r")) || (!strcmp(argv[i], "--range"))) {
			i++;
			if (i < argc) {
				low = atoi(argv[i]);
				i++;
				if (i < argc) {
					high = atoi(argv[i]);
					i++;
				} else {
					cout << "ERROR: the option " << argv[i-2] << " requires two values, one given" << endl;
					Usage(argv);
				}
			} else {
					cout << "ERROR: the option " << argv[i-1] << " requires two values, none given" << endl;
					Usage(argv);
			}
		} else {
			i++;
		}
		
	}
	
	if (low >= high) {
		cout << "ERROR: low value must not meet or exceed high value" << endl;
		exit(-1);
	}

	return;
	
}

void GetUser(int argc, char * argv[], char * envp[]) {
	string username = "Generic User";
	int setUser = 0;
	int i = 1;
	
	for(int i=0; envp[i]!=NULL; i++) {
			string line;
			int pos;
			string var;
			string value;
			
			line = envp[i];
			pos = line.find('=');
			var = line.substr(0,pos);
			value = line.substr(pos+1,line.size());
		
			if (var=="PROGRAM_ONE_USER") {
				username = value;
			}
	}
	
	while (i < argc) {
		
		if ((!strcmp(argv[i], "-u")) || (!strcmp(argv[i], "--user")))  {
			i++;
			if (i < argc) {
				username = argv[i];
				setUser++;
				i++;
			} else {
				cout << "ERROR: the option " << argv[i-1] << " requires a string value, none given" << endl;
				Usage(argv);
				exit(-1);
			}
			
		} else {
			i++;
		}
		

	}
		
	if (setUser <=1) {
			cout << "Hello " << username << "." << endl;
	} else {
		cout << "ERROR: only one operation may be specified" << endl;
		Usage(argv);
		exit(-1);
	}
		
	
	
	return;
	
}


void Usage(char * argv[]) {
	
	cout << "****************************************************************************************" << endl;
	cout << "*                                                                                       *" << endl;
	cout << "*  This program is called " << argv[0] << endl;
	cout << "*                                                                                       *" << endl;
	cout << "*  Please use the following commands:                                                   *" << endl;
	cout << "*                                                                                       *" << endl;
	cout << "* -p or --plus (addition table)                                                         *" << endl;
	cout << "* -m or --minus (subtraction table)                                                     *" << endl;
	cout << "* -t or --times (multiplication table)                                                  *" << endl;
	cout << "* -d or --divide (division table)                                                       *" << endl;
	cout << "* -o or --mod (modulus table)                                                           *" << endl;
	cout << "* -l or --low, followed by a value (will change the minimum value)                      *" << endl;
	cout << "* -i or --high, followed by a value (will change the maximum value)                     *" << endl;
	cout << "* -r or --range, followed by two values (will change the minimum and maximum values)    *" << endl;
	cout << "* -u or --user, followed by a value (will greet the user by name)                       *" << endl;
	cout << "*                                                                                       *" << endl;
	cout << "* Have a nice day!                                                                      *" << endl;
	cout << "*                                                                                       *" << endl;
	cout << "*****************************************************************************************" << endl;
	
	return;
	
}

int GetValue(int x, int y, char operation) {
	int i = 0;
	
	switch (operation) {
		case '+' :
			i = y + x;
			break;
		case '-' :
			i = y - x;
			break;
		case 'x' :
			i = y * x;
			break;
		case '/' :
			if (x == 0) {
				i = -1;
			} else {
				i = y / x;
			}
			break;
		case '%' :
			if (x == 0) {
				i = -1;
			} else {
				i = y % x;
			}
			break;
		
	}
	
	return i;
	
}

void PrintTable(int low, int high, char operation){
	
	
	cout << operation << "|";
	
	for (int x = low; x <=high; x++) {
		
			cout << " " << x << '\t';
	}
	
	cout << endl;
	
	
	cout << "-+";
	
	for (int x = low; x <= high; x++) {
		cout << "--------";
	}
	
	cout << endl;
	
	
	
	for (int x = low; x <=high; x++) {
		cout << x << "|";
		for (int y = low; y <=high; y++) {
			cout << " " <<  GetValue(x, y, operation) << '\t';
		}
		cout << endl;
	}
	
	
	
	return;
}