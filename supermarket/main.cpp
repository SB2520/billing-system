#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<cstdio>
#include<stdlib.h>
#include<sstream>
#include <unistd.h>
#include<conio.h>
#include<math.h>
using namespace std;
class electronics
{
	protected:
	int product_no;
	int quantity;
	char product_name[60];
	char description[50];
	float price;
	float discount;
	float tax;
	int stock;
	int flag;
	public:
	electronics()
	{
		flag=0;
	}
	void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax;
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :               "<<product_no;
		cout<<"\n  PRODUCT NAME  :                 "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT  :         "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :         "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) :  "<<discount<<" %";
		cout<<"\n  AVAILABLE STOCK OF PRODUCT      "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
		else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	char* returnproduct_name()
	{
		return product_name;
	}
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
};
electronics electronic;
void introduction()    //introduction function
{
	int i;
  	cout<<"\n\n\n";
 	cout<<"\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
 	cout<<"\n\t\t\t\t\t\t---------------SUPER MARKET BILLING PROJECT----------------\n";
  	cout<<"\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
  	cout<<"\n\n";
  	cout<<"\t\t\t\t\t\tMADE BY:\n\n\t\t\t\t\t\tSUBRAT(21103145) \n\t\t\t\t\t\tUNNATI(21103156) \n\t\t\t\t\t\tVEDANSH(21103159)";
  	cout<<"\n\n\n\t\t\t\t\t\tCOLLEGE:DR B.R AMBEDKAR NATIONAL INSTITUTE OF TECHNOLOGY,JALANDHAR\n";
}
void electronics::write_product()
{
	fstream file1;
	file1.open("electronicdatabase.dat",ios::out|ios::app);
	create_product();
	file1.write((char*)&electronic,sizeof(electronics));
	file1.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!! ";
}
void electronics::display_all()
{
	 fstream file1;
 	 cout<<"\nPRODUCTS AVAILABLE IN electronics AND ACCESSORIES :  \n";
 	 file1.open("electronicdatabase.dat",ios::in);
  	while(file1.read((char*)&electronic,sizeof(electronics)))
  	{
   		 show_product();
    		 cout<<"\n======================================================\n";
  	}
     	file1.close();
}
void electronics::modify_product()
{
	fstream file1;
	int no,f;
	f=0;
	cout<<"\n\n UPDATE A PRODUCT :   ";
	cout<<"\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file1.open("electronicdatabase.dat",ios::in|ios::out);
	while(file1.read((char*)&electronic,sizeof(electronics)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			file1.seekp(-1*sizeof(electronics),ios::cur);
			create_product();
			file1.write((char*)&electronic,sizeof(electronics));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file1.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void electronics::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("electronicdatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&electronic,sizeof(electronics)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{
			show_product();
			f=1;
		}
		file.close();		//to close database file
		if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}  //end of while
}
void electronics::delete_product()		//delete function
{
 	fstream file1,fil2;
  	int product_no;
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file1.open("electronicdatabase.dat",ios::in|ios::out);    //opening original file
  	fil2.open("Temp.dat",ios::out);         //opening temporary file
  	file1.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file1.read((char*)&electronic,sizeof(electronics)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil2.write((char*)&electronic,sizeof(electronics));
     		 }
  	}   //end of while
  	fil2.close();       //closing temporary file
  	file1.close();        //closing original file
  	remove("electronicdatabase.dat");     // deleting original file
  	rename("Temp.dat","electronicdatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
} // end of class electronics
class eatables
{
	protected:
	int product_no;
	int quantity;                         //Quantity in Kg or Litre as per product
	char product_name[60];
	char description[50];
	float price;                          //price per kg or litre
	float discount;
	float tax;
	int stock;
	int flag;		             //Stock in Kg or Litre as per product
	char expiry[10];
	char day[2];
	char month[2];
	char year[4];
	public:
	eatables()
	{
	 flag=0;
    }
void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax;
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER EXPIRY DATE OF PRODUCT(DAY/MONTH/YEAR) : ";
		cin>>expiry;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :                            "<<product_no;
		cout<<"\n  PRODUCT NAME  :                              "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT(PER KG OR PER LITRE)  : "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :                      "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) :               "<<discount<<" %";
		cout<<"\n  DATE OF EXPIRY :                             "<<expiry;
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :                 "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
		else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}
	int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day);
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}

	char* returnproduct_name()
	{
		return product_name;
	}
	char* returnexpiry()
	{
		return expiry;
	}
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
};
eatables eatable;
void eatables::write_product()
{
	fstream file3;
	file3.open("eatabledatabase.dat",ios::out|ios::app);
	create_product();
	file3.write((char*)&eatable,sizeof(eatables));
	file3.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!! ";
}
void eatables::display_all()
{
	 fstream file3;
 	 cout<<"\nPRODUCTS AVAILABLE IN eatable SUPPLIES SECTION :  \n";
 	 file3.open("eatabledatabase.dat",ios::in);
  	while(file3.read((char*)&eatable,sizeof(eatables)))
  	{
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	}
     	file3.close();
}
void eatables::modify_product()
{
	fstream file3;
	int no,f;
	f=0;
	cout<<"\n\n UPDATE A PRODUCT :   ";
	cout<<"\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file3.open("eatabledatabase.dat",ios::in|ios::out);
	while(file3.read((char*)&eatable,sizeof(eatables)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			file3.seekp(-1*sizeof(eatables),ios::cur);
			create_product();
			file3.write((char*)&eatable,sizeof(eatables));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file3.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void eatables::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("eatabledatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&eatable,sizeof(eatables)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{
			show_product();
			f=1;
		}
		file.close();		//to close database file
		if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}
}
void eatables::delete_product()		//delete function
{
 	fstream file3,fil4;
  	int product_no;
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file3.open("eatabledatabase.dat",ios::in|ios::out);    //opening original file
  	fil4.open("Temp.dat",ios::out);         //opening temporary file
  	file3.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file3.read((char*)&eatable,sizeof(eatables)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil4.write((char*)&eatable,sizeof(eatables));
     		 }
  	}   //end of while
  	fil4.close();       //closing temporary file
  	file3.close();        //closing original file
  	remove("eatabledatabase.dat");     // deleting original file
  	rename("Temp.dat","eatabledatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
} // end of class eatables
class cosmetics
{
	protected:
	int product_no;
	int quantity;
	char product_name[60];
	char description[50];
	float price;
	float discount;
	float tax;
	int stock;
	char expiry[10];
	int flag;
	char day[2];
	char month[2];
	char year[4];
	public:
	cosmetics()
	{
		flag=0;
	}
void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
        cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax;
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER EXPIRY DATE OF PRODUCT(DAY/MONTH/YEAR) : ";
		cin>>expiry;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}

	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :              "<<product_no;
		cout<<"\n  PRODUCT NAME IS :              "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT  :        "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :        "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) : "<<discount<<" %";
		cout<<"\n  DATE OF EXPIRY :               "<<expiry;
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :   "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
                else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}


	int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day);
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}

	char* returnproduct_name()
	{
		return product_name;
	}
	char* returnexpiry()
	{
		return expiry;
	}
	float returndiscount()
	{
		return discount;
	}
        int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
}; //end of class cosmetics

cosmetics cosmetic;
void cosmetics::write_product()
{
	fstream file4;
	file4.open("cosmeticsdatabase.dat",ios::out|ios::app);
	create_product();
	file4.write((char*)&cosmetic,sizeof(cosmetics));
	file4.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY ADDED !!!! ";
}

void cosmetics::display_all()
{
	 fstream file4;
 	 cout<<"\nPRODUCT AVAILABLE IN COSMETICS SECTION : \n";
 	 file4.open("cosmeticsdatabase.dat",ios::in);
  	 while(file4.read((char*)&cosmetic,sizeof(cosmetics)))
  	 {
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	 }
     	file4.close();

}

void cosmetics::modify_product()
{
	fstream file4;
	int no,f;
	f=0;
	cout<<"\n\nUPDATE A PRODUCT ";
	cout<<"\n\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
        file4.open("cosmeticsdatabase.dat",ios::in|ios::out);
	while(file4.read((char*)&cosmetic,sizeof(cosmetics)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			cosmetic.show_product();
			cout<<"\n ENTER NEW DETAILS OF PRODUCT";
			cosmetic.create_product();
			//int pos=-1*sizeof(cosmetics);
			file4.seekp(-1*sizeof(cosmetics),ios::cur);
			//file.seekp(pos,ios::cur);
			file4.write((char*)&cosmetic,sizeof(cosmetics));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file4.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void cosmetics::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("cosmeticsdatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&cosmetic,sizeof(cosmetics)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{
			show_product();
			f=1;
		}
		file.close();		//to close database file
                if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}  //end of while
}
void cosmetics::delete_product()		//delete function
{
 	fstream file4,fil5;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file4.open("cosmeticsdatabase.dat",ios::in|ios::out);    //opening original file
  	fil5.open("Temp.dat",ios::out);         //opening temporary file
  	file4.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file4.read((char*)&cosmetic,sizeof(cosmetics)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil5.write((char*)&cosmetic,sizeof(cosmetics));
     		 }
  	}   //end of while
  	fil5.close();       //closing temporary file
  	file4.close();        //closing original file
  	remove("cosmeticsdatabase.dat");     // deleting original file
  	rename("Temp.dat","cosmeticsdatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!!";

} // end of class cosmetics
class placeorder:public electronics,public eatables,public cosmetics
{
	int prod_number5[100],quantity5[100], prod_number[100],quantity[100],prod_number1[100],quantity1[100],quantity4[100],prod_number4[100],prod_number2[100],quantity2[100],prod_number3[100],quantity3[100];
	int c,n,p,choice,choice1;
	double amount1,amount3,amount4,amount_after_dis1,amount_after_dis3,amount_after_dis4;
	double total1,total3,total4,total,saving1,saving3,saving4,saving;
	char ch,ch1,ch2,ch3,ch4,ch5;
	char date1[12];
	char date2[10];
	char date3[10];
	//menu();
	public:
	placeorder()
	{
		c=0;
		n=0;
		p=0;
		total=0;
		saving1=0,saving3=0,saving4=0;
		saving=0;
		ch='Y';
	}
	void  place_order();
};
void placeorder:: place_order()
	{
		fstream file,file1,file2;
		char str[3]="am";
		char str1[3]="pm";
		char str3[4];
		int count1;
		char customer_name[20];
		time_t currentTime;
  		struct tm *localTime;
 		time( &currentTime );                   // Get the current time
  		localTime = localtime( &currentTime );  // Convert the current time to the local time
		 int Day    = localTime->tm_mday;
 		 int Month  = localTime->tm_mon+1;
 		 int Year   = localTime->tm_year+1900;
  		 int Hour   =localTime->tm_hour;
  		 int Min    = localTime->tm_min;
		if(Hour>=12)
		{
			strcpy(str3,str1);
		}
		else
		{
			strcpy(str3,str);
		}
		if(Hour>12)
		{
			Hour =localTime->tm_hour-12;
		}
		else
		{
			Hour =localTime->tm_hour;
		}
		cout<<"\n\t\tPLACE YOUR ORDER\t\t\n";
		cout<<"\n ENTER NAME OF CUSTOMER : ";
		cin.ignore();
		cin.getline(customer_name,20);
		labelorder:
			    system("cls");
		cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.EATABLES SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.PROCEED FOR INVOICE";
		cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
		cin>>choice;
		try
		{
			if(choice>4 ||choice==0)
			{
				throw(choice);
			}
		}
		catch(int x)
		{
			cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
			cout<<"\n\nENTER YOUR CHOICE : ";
			cin>>choice;
		}
		switch(choice)
		{
		case 1:{
				labelorderelectronics: system("cls");
				cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS\n\n\n\t\t\t\t\t\t\t\t2.GO BACK";
				cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
				cin>>choice1;
				try
				{
					if(choice1>2 ||choice1==0)
					{
						throw(choice1);
					}
				}
				catch(int x)
				{
					cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
					cout<<"\n\nENTER YOUR CHOICE : ";
					cin>>choice1;
				}
				switch(choice1)
				{
					case 1:	{
						do
						{
							system("cls");
							electronic.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number[c];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity[c];
							c++;
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch;

						}while(ch=='y' || ch=='Y');
						count1=1;
						goto labelorderelectronics;
						break;
						}
					case 2:count1=1;
						goto labelorder;
				}
			}
		case 2:{
				labelordergrocery: system("cls");
				cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING\n\n\n\t\t\t\t\t\t\t\t1.EATABLES SUPPLLIES STORE\n\n\n\t\t\t\t\t\t\t\t2.GO BACK";
				cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
				cin>>choice1;
				try
				{
					if(choice1>2 ||choice1==0)
					{
						throw(choice1);
					}
				}
				catch(int x)
				{
					cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-2)";
					cout<<"\n\nENTER YOUR CHOICE : ";
					cin>>choice1;
				}
				switch(choice1)
				{
					case 1:{

						do
						{
							system("cls");
							eatable.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number2[n];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity2[n];
							n++;
							cout<<n;
							cout<<"\n"<<prod_number2[n];
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch2;

						}while(ch2=='y' || ch2=='Y');
						count1=1;
						goto labelordergrocery;
					       }
					case 2: count1=1;
						goto labelorder;

				}

			}
		case 3:{
			do
			{
				system("cls");
				cosmetic.display_all();
				cout<<"\n\n\n Enter the product number:";
				cin>>prod_number3[p];
				cout<<" Enter the quantity in number : ";
				cin>>quantity3[p];
				p++;
				cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
				cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
				cin>>ch3;

			}while(ch3=='y' || ch3=='Y');
			goto labelorder;
			}
		case 4:goto invoice;

		}
		invoice: system("cls");
		cout<<"\n\n"<<setfill('*')<<setw(80)<<"*"<<"INVOICE"<<setfill('*')<<setw(80)<<"*"<<"\n\n";
		cout<<"CUSTOMER NAME : "<<customer_name<<endl;
		cout<<setfill(' ')<<setw(150)<<"DATE = "<<Day<<"/"<<Month<<"/"<<Year<<" "<<endl;
		cout<<setfill(' ')<<setw(150)<<"TIME = "<<Hour<<":"<<Min<<str3<<" ";
		cout<<"\n"<<setfill('=')<<setw(170)<<"=";
		cout<<setfill(' ')<<setw(25)<<"\nPRODUCT NUMBER"<<setw(28)<<"PRODUCT NAME"<<setw(20)<<"QUANTITY"<<setw(19)<<"PRICE"<<setw(16)<<"AMOUNT"<<setw(13)<<"TAX"<<setw(14)<<"DISCOUNT"<<setw(45)<<"AMOUNT AFTER DISCOUNT AND TAXES\n\n";
		cout<<setfill('=')<<setw(170)<<"=";
		for(int i=0;i<c;i++)
		{
			file.open("electronicdatabase.dat",ios::in);
			file.read((char*)&electronic,sizeof(electronics));
			while(!file.eof())
			{
			if(electronic.returnproduct_no()==prod_number[i])
			{
				amount1=electronic.returnprice()*quantity[i];
				amount_after_dis1=amount1-(amount1*electronic.returndiscount()/100)+(amount1*electronic.returntax()/100);

				cout<<setfill(' ')<<"\n"<<setw(5)<<prod_number[i]<<setw(40)<<electronic.returnproduct_name()<<setw(15)<<quantity[i]<<setw(20)<<electronic.returnprice()<<" Rs"<<setw(12)<<amount1<<" Rs"<<setw(10)<<electronic.returntax()<<" %"<<setw(10)<<electronic.returndiscount()<<" %"<<setw(20)<<amount_after_dis1<<" Rs";
				total1+=amount_after_dis1;
				saving1=saving1+(amount1-amount_after_dis1);
			}
			file.read((char*)&electronic,sizeof(electronics));
			}
		file.close();
		}
		for(int k=0;k<n;k++)
		{
			file2.open("eatabledatabase.dat",ios::in);
			file2.read((char*)&eatable,sizeof(eatables));
			while(!file2.eof())
			{

			if(eatable.returnproduct_no()==prod_number2[k])
			{
				amount3=eatable.returnprice()*quantity2[k];
				amount_after_dis3=amount3-(amount3*eatable.returndiscount()/100)+(amount3*eatable.returntax()/100);
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number2[k]<<setw(40)<<eatable.returnproduct_name()<<setw(15)<<quantity2[k]<<setw(20)<<eatable.returnprice()<<" Rs"<<setw(12)<<amount3<<" Rs"<<setw(10)<<eatable.returntax()<<" %"<<setw(10)<<eatable.returndiscount()<<" %"<<setw(20)<<amount_after_dis3<<" Rs";
				total3+=amount_after_dis3;
				saving3=saving3+(amount3-amount_after_dis3);
			}

			file2.read((char*)&eatable,sizeof(eatables));
			}
		file2.close();
		}
		for(int i=0;i<p;i++)
		{
			ifstream file3;
			file3.open("cosmeticsdatabase.dat",ios::in);
			file3.read((char*)&cosmetic,sizeof(cosmetics));
			while(!file3.eof())
			{

			if(cosmetic.returnproduct_no()==prod_number3[i])
			{
				amount4=cosmetic.returnprice()*quantity3[i];
				amount_after_dis4=amount4-(amount4*cosmetic.returndiscount()/100)+(amount4*cosmetic.returntax()/100);

				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number3[i]<<setw(40)<<cosmetic.returnproduct_name()<<setw(15)<<quantity3[i]<<setw(20)<<cosmetic.returnprice()<<" Rs"<<setw(12)<<amount4<<" Rs"<<setw(10)<<cosmetic.returntax()<<" %"<<setw(10)<<cosmetic.returndiscount()<<" %"<<setw(20)<<amount_after_dis4<<" Rs";
				total4+=amount_after_dis4;
				saving4=saving4+(amount4-amount_after_dis4);
			}

			file3.read((char*)&cosmetic,sizeof(cosmetics));
			}
		file3.close();
		}
		c=0;
		n=0;
		p=0;
		cout<<"\n"<<setfill('-')<<setw(170)<<"-";
		total=total1+total3+total4;
		saving=saving1+saving3+saving4;
		cout<<"\n\n\n\t\tYOUR TOTAL SAVINGS : "<<abs(saving)<<" Rs"<<" !!!";
		cout<<"\n\n\n\t\t\tTOTAL= "<<total<<" Rs"<<"\n";
		cout<<"\n\n\t\tTHANK YOU FOR PLACING YOUR ORDER !!!!";
	}
class adminmenu
{
public:
	void admin_menu();
};
void adminmenu::admin_menu()
{
	char ch = 'y';
	char str[100];
	string str1;
	for (;;)
	{
		string pass = "";
		char ch;
		cout << "\nENTER PASSWORD : ";
		ch = _getch();
		while (ch != 13)
		{
			pass.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		ifstream fin("password.dat");
		fin >> str1;
		if (str1 == pass)
		{
		label0:
			system("cls");
			int choice, choice1, choice2;
			cout << "\t\t\t\t\t\t\t" << setfill('=') << setw(80) << "=";
			cout << setw(20) << "\n\n\t\t\t\t\t\t\t\t\t\tADMINISTRATION MENU\n";
			cout << "\t\t\t\t\t\t\t" << setfill('=') << setw(80) << "=";
			cout << "\n\n\n\t\t\t\t\t\t\t\t1.ADD A NEW PRODUCT\n\n\n\t\t\t\t\t\t\t\t2.DISPLAY A PRODUCT\n\n\n\t\t\t\t\t\t\t\t3.UPDATE A PRODUCT\n\n\n\t\t\t\t\t\t\t\t4.DELETE A PRODUCT\n\n\n\t\t\t\t\t\t\t\t5.BACK TO MAIN MENU\n\n\t";
			cout << "\n\n\t\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE (1-5) : ";
			cin >> choice;
			try
			{
				if (choice > 5 || choice == 0)
				{
					throw(choice);
				}
			}
			catch (int x)
			{
				cout << "\nPLEASE ENTER CHOICE BETWEEN (1-5)";
				cout << "\n\nENTER YOUR CHOICE : ";
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
			{
			labeladd:
				system("cls");
				cout << "\n\t\t\t\t\t\t\t\tADD A NEW PRODUCT IN PARTICULAR SECTION GIVEN BELOW : ";
				cout << "\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.EATABLES SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
				cout << "\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
				cin >> choice1;
				try
				{
					if (choice1 > 4 || choice1 == 0)
					{
						throw(choice1);
					}
				}
				catch (int x)
				{
					cout << "\nPLEASE ENTER CHOICE BETWEEN (1-4)";
					cout << "\n\nENTER YOUR CHOICE : ";
					cin >> choice1;
				}
				switch (choice1)
				{
				case 1: // FOR ELECTRONICS SECTION
				{
					do
					{
						system("cls");
						cout << "\n\t\t\t\t\t\t\t\tADD PRODUCT IN ELECTRONICS SECTION : \n\n\n";
						electronic.write_product();
						cout << "\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					goto labeladd;
				}
				case 2: // FOR EATABLES SECTION
				{
					do
					{
						system("cls");
						cout << "\n\t\t\t\t\t\t\t\tADD PRODUCT IN EATABLES SECTION : \n\n\n";
						eatable.write_product();
						cout << "\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					goto labeladd;
				}
				case 3: // FOR COSMETICS SECTION
				{
					do
					{
						system("cls");
						cout << "\n\t\t\t\t\t\t\t\tADD PRODUCT IN COSMETICS SECTION : \n\n\n";
						cosmetic.write_product();
						cout << "\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
						cin >> ch;
					} while (ch == 'y' || ch == 'Y');
					goto labeladd;
				}
				case 4:
			    {
			       	goto label0;
			    }}
			}
		case 2:
		{
			system("cls");
		labeldisplay:
			cout << "\n\t\t\t\t\t\t\t\tDISPLAY PRODUCTS IN FOLLOWING SECTION : ";
			cout << "\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.EATABLES SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
			cout << "\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
			cin >> choice1;
			try
			{
				if (choice1 > 4 || choice1 == 0)
				{
					throw(choice1);
				}
			}
			catch (int x)
			{
				cout << "\n\nPLEASE ENTER CHOICE BETWEEN (1-4)";
				cout << "\n\nENTER YOUR CHOICE : ";
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
			{
				system("cls");
				cout << "\n\t\t\t\t\t\t\t\tPRODUCT IN ELECTRONICS SECTION : \n\n\n";
				electronic.display_all();
				goto labeldisplay;
			}
			case 2:
			{
				system("cls");
				cout << "\n\t\t\t\t\t\t\t\tPRODUCT IN EATABLES SECTION : \n\n\n";
				eatable.display_all();
				goto labeldisplay;
			}
			case 3:
			{
				system("cls");
				cout << "\n\t\t\t\t\t\t\t\tPRODUCT IN COSMETICS SECTION : \n\n\n";
				cosmetic.display_all();
				goto labeldisplay;
			}
			case 4:
				goto label0;
			}
		}
		case 3:
		{
		   labelmodify:
			system("cls");
			cout << "\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE UPDATE";
			cout << "\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.EATABLES SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
			cout << "\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
			cin >> choice1;
			try
			{
				if (choice1 > 4 || choice1 == 0)
				{
					throw(choice1);
				}
			}
			catch (int x)
			{
				cout << "\nPLEASE ENTER CHOICE BETWEEN (1-4)";
				cout << "\n\nENTER YOUR CHOICE : ";
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
			{
				system("cls");
				electronic.display_all();
				electronic.modify_product();
				goto labelmodify;
			}
			case 2:
			{
				system("cls");
				eatable.display_all();
				eatable.modify_product();
				goto labelmodify;
			}
			case 3:
			{
				system("cls");
				cosmetic.display_all();
				cosmetic.modify_product();
				goto labelmodify;
			}
			case 4:
				goto label0;
			}
		}
		case 4:
		{
		    labeldelete:
			system("cls");
			cout << "\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE DELETED : \n";
			cout << "\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.EATABLES SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
			cout << "\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
			cin >> choice1;
			try
			{
				if (choice1 > 4 || choice1 == 0)
				{
					throw(choice1);
				}
			}
			catch (int x)
			{
				cout << "\nPLEASE ENTER CHOICE BETWEEN (1-4)";
				cout << "\n\nENTER YOUR CHOICE : ";
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
			{
				system("cls");
				electronic.display_all();
				electronic.delete_product();
				goto labeldelete;
			}
			case 2:
			{
				system("cls");
				eatable.display_all();
				eatable.delete_product();
				goto labeldelete;
			}
			case 3:
			{
				system("cls");
				cosmetic.display_all();
				cosmetic.delete_product();
				goto labeldelete;
			}
			case 4:
			{
				goto label0;
			}
			}
		}
		case 5:
			system("cls");
			break;
		default:
			cout << "\a";
			admin_menu();
		}
		break;
	}
	else
	{
		cout << "\n\nINCORRECT PASSWORD !!! PLEASE TRY AGAIN !!!";
	}
}
}
int main()
{
	introduction();
	int choice1,choice,choice2,m;
	placeorder p;
	fstream file;
	adminmenu a;
	//system("color 1A");
	char str[20];
	char reset_password[20];
	int s=0,count=0;
	for(;;)
	{
		if(count==1)
		{
		main_menu:
		 system("cls");
		}
		cout<<"\n\n\n\n\t\t\t\t\t\t"<<setfill('=')<<setw(59)<<"=";
		cout<<setw(20)<<"\n\n\t\t\t\t\t\t\t\tMAIN MENU";
		cout<<"\n\n\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
		cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ADD PRODUCTS TO CART\n\n\n\t\t\t\t\t\t\t\t2.ADMINISTRATOR\n\n\n\t\t\t\t\t\t\t\t3.EXIT";
		cout<<"\n\n\n\t\t\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE : ";
		cin>>choice1;
		try
		{
			if( choice1>4 || choice1==0)
			{
				throw(choice1);
			}
		}
		catch(int x)
		{
			cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
			cout<<"\n\nENTER YOUR CHOICE : ";
			cin>>choice1;
		}
		switch(choice1)
		{
			case 1:
					system("cls");
					count=1;
					p.place_order();
					cout<<"\n\n\n\n\t1.GO TO MAIN MENU\n\n\t2.EXIT";
					cout<<"\n\n\tENTER YOUR CHOICE : ";
					cin>>choice2;
					try
					{
						if(choice2>2 || choice2==0)
						{
							throw(choice2);
						}
					}
					catch(int x)
					{
						cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-2)";
						cout<<"\n\nENTER YOUR CHOICE : ";
						cin>>choice2;
					}
					switch(choice2)
					{
						case 1:goto main_menu;
							break;
						case 2:
							   exit(0);
					}
					break;
			case 2:
					system("cls");
					a.admin_menu();
					break;
			case 3:
					exit(0);
		}
	}
	return(0);
}

