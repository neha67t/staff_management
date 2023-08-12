/*Employee Database*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std; 
class emp
{
	private :
		int empno ;
		char name[20] ;
		float salary;
	public:
		emp(){}
		emp(char *name , int empno , float salary)
		{
			strcpy(this->name , name ) ;
			this->empno = empno ;
			this->salary = salary ;
		}
		void getdata( )
		{
			cout<< "Enter new employee details"; 
			cout << " Enter employee name";
			cin.sync();
			cin.getline(this->name,20);

			cout << "Enter employee number" ;
			cin >> this->empno;

			cout << "Enter employee salary" ;
			cin >> this->salary ;
		}

		void setdata(char *name , int empno , float salary)
		{
			strcpy(this->name , name ) ;
			this->empno = empno ;
			this->salary = salary ;
		}

		void display()
		{
			cout << endl << "Employee information";
			cout << endl << "Employee name = " << this->name ;
			cout << endl << "Employee number = " << this->empno ;
			cout << endl << "Employee salary = " << this->salary ;
		}

		char * getname()
		{
			return this->name;
		}
		int getempno()
		{
			return this->empno; 
		}
		float getsalary()
		{
			return this->salary;
		}
} ;


int main()
{
	fstream emp_file;
	ofstream outfile;
	emp_file.open("./emp_file/myfile1.txt",ios::in|ios::out|ios::binary);
	if (!emp_file.is_open()) 
	{
		emp_file.open("./emp_file/myfile1.txt",ios::in|ios::out|ios::trunc| ios::binary);
		if (!emp_file.is_open()) 
		{
			cout << " unable to open file" ;	
			return 0;
		}
	}
	int choice, s  ;
	char name[20];
	emp e;
	do
	{
		system("cls");
		
		cout <<"\t\t\t\t\t\t Employee Management System \t\t\t\t\t\t/n"; 
		
		cout << "\n1. display records" ;
		cout << "\n2. add records";
		cout << "\n3. modify record";
		cout << "\n4. delete record";
		cout << "\n5. exit" ;
		cout << "\nEnter your choice";
		cin >> choice ;
		switch(choice)
		{
			case 1:
				emp_file.seekg(0L,ios::beg);
				while (emp_file.read( (char*) &e , sizeof(e)) )
				{	
					if ( emp_file.good()) 
						e.display();
				}
				emp_file.clear() ; 
				system("pause");
			break;
			case 2:
				char another ;
				do
				{
					emp_file.seekp(0L,ios::end);
					e.getdata();
					emp_file.write((char*)&e,sizeof(e));
					emp_file.clear(); 
					cout << "enter another record press-(y/n)" ;
					another = getche(); // cin >> another;
				}while(another  == 'y');
			break;
			case 3: 
				emp_file.clear();
				s = -28 ; 
				cout << "Enter employee name" ;
				cin.sync(); 
				cin.getline(name,20);
				emp_file.seekg(0L,ios::beg);
				while (emp_file.read( (char*) &e , sizeof(e)) )
				{				
					s = s + 28;
					if ( strcmp(name , e.getname()) == 0 )
						  break;
				}
				emp_file.seekp( s , ios::beg);
				e.getdata();
				emp_file.write((char*)&e,sizeof(e));
				break;
				
			case 4:
				emp_file.clear();
				cout << "Enter employee name" ;
				cin.sync(); 
				cin.getline(name,20);
				emp_file.seekg(0L,ios::beg);
				outfile.open("./myfile1/temp1.txt",ios::binary|ios::out);
				while ( emp_file.read( (char*) &e , sizeof(e)))
				{
					if ( strcmp(name , e.getname()) != 0 )
						outfile.write((char*)&e,sizeof(e));
				}
				outfile.close();
				emp_file.close();
				remove("./emp_file/myfile1.txt");
				rename("./emp_file/temp1.txt","./emp_file/myfile1.txt");
				emp_file.open("./emp_file/myfile1.txt",ios::in|ios::out|ios::binary);
				
			break;
			case 5: 
				exit(0);
		}
   
		
	}while( true);
}
