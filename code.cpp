#include <iostream>
#include<fstream>
#include <string>
#include<string.h>
#include<stdlib.h>
#include <cstdlib>

//#include<bits/stdc++.h>
#include <conio.h>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include<ctime>

//#include "stdafx.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

const string server = "tcp://localhost:3306";
const string username = "root";
const string password = "aditya1410";

sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

string s0;
class sqlconnector {
public:
   void connecting(int n,string m,string s1,string s2,string s3) {
       try
       {
           driver = get_driver_instance();
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to server. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       con->setSchema("armydata");

    /*stmt = con->createStatement();
      stmt->execute("DROP TABLE IF EXISTS inventory");
      cout << "Finished dropping table (if existed)" << endl;
      stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY,army_id INTEGER,first_name VARCHAR(50),last_name VARCHAR(50), phone_no VARCHAR(50),passward VARCHAR(50));");
      cout << "Finished creating table" << endl;
       delete stmt;*/

       pstmt = con->prepareStatement("INSERT INTO inventory(army_id,first_name,last_name,phone_no,passward) VALUES(?,?,?,?,?)");
       pstmt->setInt(1,n);
       pstmt->setString(2,s1);
       pstmt->setString(3,s2 );
       pstmt->setString(4,m);
       pstmt->setString(5,s3 );
       pstmt->execute();
       cout << "\nsign up successful" << endl;
       delete pstmt;
       delete con;
       system("pause");
    }
   void printdata(int x) {
       try
       {
           driver = get_driver_instance();
       }
       catch (sql::SQLException e)
       {
           cout << "Could not get a database driver. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       //connect to the DBMS server
       try
       {
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to database. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }
       con->setSchema("armydata");
       // Specify which connection the SQL statement should be executed on

       // Try to query the database
       try
       {
           pstmt = con->prepareStatement("SELECT* FROM inventory WHERE army_id=?;");
           pstmt->setInt(1, x);
           result = pstmt->executeQuery();
       }
       catch (sql::SQLException e)
       {
           cout << "SQL error. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       while (result->next())
       {
           cout << "\narmy id -> ";
           cout << result->getInt(2) << endl; 
           cout << "\nfirst name -> ";
           cout << result->getString(3) << endl; 
           cout << "\nlast name -> ";
           cout << result->getString(4) << endl;
           cout << "\nphone number -> ";
           cout << result->getString(5) << endl<<endl;
       }
       con->setSchema("armydata");
       // Specify which connection the SQL statement should be executed on

       // Try to query the database
       try
       {
           pstmt = con->prepareStatement("SELECT* FROM prodata WHERE armyid=?;");
           pstmt->setInt(1, x);
           result = pstmt->executeQuery();
       }
       catch (sql::SQLException e)
       {
           cout << "SQL error. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       while (result->next())
       {
           //cout << "\narmy id -> ";
           //cout << result->getInt(1) << endl;
           cout << "\ndate of joining -> ";
           cout << result->getString(2) << endl;
           cout << "\ndate of birth -> ";
           cout << result->getString(3) << endl;
           cout << "\nemail address -> ";
           cout << result->getString(4) << endl;
           cout << "\nmarital status -> ";
           cout << result->getString(5) << endl;
           cout << "\ngender -> ";
           cout << result->getString(6) << endl << endl;
           s0 = result->getString(2);
       }

       // Clean up
       delete result;
       delete pstmt;
       delete con;    
   }
   void profileadd(int x,string n, string s1, string s2, string m, string s3) {
       try
       {
           driver = get_driver_instance();
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to server. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       con->setSchema("armydata");

     /*stmt = con->createStatement();
         stmt->execute("DROP TABLE IF EXISTS prodata");
         cout << "Finished dropping table (if existed)" << endl;
         stmt->execute("CREATE TABLE prodata (army_id INT,DOJ VARCHAR(50),DOB VARCHAR(50),email VARCHAR(50), marital_status VARCHAR(50),gender VARCHAR(50);");
         cout << "Finished creating table" << endl;
          delete stmt;*/

       pstmt = con->prepareStatement("INSERT INTO prodata(armyid,DOJ,DOB,email,marital_status,gender) VALUES(?,?,?,?,?,?)");
       pstmt->setInt(1, x);
       pstmt->setString(2, n);
       pstmt->setString(3, s1);
       pstmt->setString(4, s2);
       pstmt->setString(5, m);
       pstmt->setString(6, s3);
       pstmt->execute();
       cout << "\nprofile updated sucessfully" << endl;
       delete pstmt;
       delete con;
       system("pause");
   }
   bool reading(int x, string y) {
       try
       {
           driver = get_driver_instance();
           //for demonstration only. never save password in the code!
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to server. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       con->setSchema("armydata");

       //select  
       pstmt = con->prepareStatement("SELECT* FROM inventory WHERE army_id=?;");
       pstmt->setInt(1, x);
       result = pstmt->executeQuery();

       while (result->next()) {
           if ( y == result->getString(6).c_str()) {
               return true;
           }
           else if ( y!= result->getString(6).c_str()) {
               //cout << "incorrect passward please try again" << endl;
               return false;
           }
           else
               return false;
      // printf("Reading from table=(%d, %s)\n", result->getInt(1), result->getString(2).c_str());
   }

       delete result;
       delete pstmt;
       delete con;
       system("pause");
   }
   void updating(int n,string a, string b,string c) {
       try
       {
           driver = get_driver_instance();
           //for demonstration only. never save password in the code!
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to server. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       con->setSchema("armydata");

       //update
       pstmt = con->prepareStatement("UPDATE prodata SET DOJ = ? WHERE armyid = ?");
       pstmt->setString(1, a);
       pstmt->setInt(2, n);
       pstmt->executeQuery();
       pstmt = con->prepareStatement("UPDATE prodata SET email = ? WHERE armyid = ?");
       pstmt->setString(1, b);
       pstmt->setInt(2, n);
       pstmt->executeQuery();
       pstmt = con->prepareStatement("UPDATE prodata SET marital_status = ? WHERE armyid = ?");
       pstmt->setString(1, c);
       pstmt->setInt(2, n);
       pstmt->executeQuery();
       printf("Row updated\n");

       delete con;
       delete pstmt;
       system("pause");
   }
   void deleteing(long long int x) {
       try
       {
           driver = get_driver_instance();
           //for demonstration only. never save password in the code!
           con = driver->connect(server, username, password);
       }
       catch (sql::SQLException e)
       {
           cout << "Could not connect to server. Error message: " << e.what() << endl;
           system("pause");
           exit(1);
       }

       con->setSchema("armydata");

       //delete
       pstmt = con->prepareStatement("DELETE FROM inventory WHERE army_id = ?");
       pstmt->setInt(1,x);
       result = pstmt->executeQuery();

       con->setSchema("armydata");

       //delete
      pstmt = con->prepareStatement("DELETE FROM prodata WHERE armyid = ?");
       pstmt->setInt(1, x);
       result = pstmt->executeQuery();
       printf("Row deleted\n");

       delete pstmt;
       delete con;
       delete result;
       system("pause");
   }
};

// abstract base class
class agniveer
{
public:

    // default constructor
    agniveer() {}
    // virtual functions
    virtual void signup() {}
    virtual void login() {}
    virtual void notice() {}
    virtual void rules() {}
    virtual void job() {}
    virtual void privilages() {}
    virtual void help() {}
};
class pinfo : public agniveer
{
public:
    pinfo()
    {
    }
    void salary(int n) {

    }
    void signup()
    {
        sqlconnector o1;
        string s1, s2, s3, s4,n2;
        long long int n1;
        fflush(stdin);
       cout << "enter your first name" << endl;
       cin >> s1;
       fflush(stdin);
       cout << "enter your last name"<<endl;
       cin >> s2;
        fflush(stdin);
        cout << "enter your army id number" << endl;
        cin >> n1;
        fflush(stdin);
        cout << "enter your phone number" << endl;
        cin >> n2;
        fflush(stdin);
    tryz:
        fflush(stdin);
        cout << "enter passward" << endl;
        cin >> s3;
        fflush(stdin);
        cout << "confirm your passward" << endl;
        cin >> s4;
        fflush(stdin);
        if (s3 == s4)
        {
            o1.connecting(n1,n2,s1,s2,s3);
            cout << "your id has been created please login with this id" << endl;
        }
        else
        {
            cout << "\n\npassward is not matched \n please try again -\n"
                << endl;
            goto tryz;
        }
    }
    void login()
    {
        sqlconnector o2;
        long long int m1;
        string g1;
        cout << "enter your army id" << endl;
        cin >> m1;
        fflush(stdin);
        cout << "enter your passward" << endl;
        cin >> g1;
        if (!o2.reading(m1, g1)) {
            cout << "incorrect id or passward" << endl;
        }
        else {
            cout << "id passward matched \n" << endl;
            int ni;
            cout << "\n press\n 0- to complete your profile if not completed\n 1- to show your profile\n 2- if you want to delete your id from the database\n 3- to modify your information " << endl;
            fflush(stdin);
            cin >> ni;
            fflush(stdin);
            if (ni == 1) {
                o2.printdata(m1);
                cout << "yor monthly salary :- \n" << endl;
                long long int base_salary = 30000;
                cout << "base salary -> " << base_salary << endl;
                int allowances = 5000;
                cout << "monthly allowances -> " << allowances << endl<<endl;
                cout << "your yearly increment :- \n" << endl;
                string month = "05";
                string year = "2023";
                string str= "";
                string str1 ="";
                str1 += s0.at(3);
                str1 += s0.at(4);
                str += s0.at(6);
                str += s0.at(7);
                str += s0.at(8);
                str += s0.at(9);
                int a1 = (month.at(0) - '0') * 10 + (month.at(1) - '0');
                int a2 = (str1.at(0) - '0') * 10 + (str1.at(1) - '0');
                int y = (s0.at(8) - '0') * 10 + (s0.at(9) -'0');
                int z = (year.at(2)-'0') * 10 + (year.at(3)-'0');
                int w = z - y;
                int w1 = a2 - a1;
                int x1 = w * 12;

                int monthCount = 0;
                while (true)
                {
                    if (y == z)
                    {
                        if (a1 == a2)
                            break;
                    }

                    monthCount++;
                    a2++;
                    if (a2 > 12)
                    {
                        a2 = 1;
                        y++;
                    }
                }
                int yearcount = monthCount / 12;
                if (yearcount > 0 && yearcount < 5) {
                    cout << "you got an increment of " << yearcount << "0 percent for completing your " << yearcount << " years of service on your base salary" << endl;
                    cout << "now your salary is -> " << base_salary + allowances + (base_salary * yearcount) / 10 << " per month" << endl << endl;
                    cout << "\n you had completed -> " << monthCount << " months as an agniveeer\n\n";
                }
                else if(yearcount ==0 && monthCount>=6){
                    cout << "you had completed 6 months of your service and you had got 5 percent of increment" << endl;
                    cout << "now your salary is -> " << base_salary + allowances + (base_salary ) / 20 << " per month" << endl << endl;
                    cout << "\n you had completed -> " << monthCount << " months as an agniveeer\n\n";
               }
                else if (yearcount >= 5) {
                    cout << "you are retired ..... you had complted your 5 year service as agniveer ......" << endl << endl;
               } 
               else {
                    cout << "you had given a wrong date of joining" << endl;
               }
               
            }
            else if (ni == 2) {
                o2.deleteing(m1);
                cout << "\n\n                      your id has been successfully deleted\n\n";
            }
            else if (ni == 3) {
                string g1, g2, g3;
                cout << "\n you can only modify your date of joining, email address and marital status\n" << endl;
                cout << "date of joining" << endl;
                cin >> g1;
                cout << "email address" << endl;
                cin >> g2;
                cout << "marital status" << endl;
                cin >> g3;
                cout << "\n";
                o2.updating(m1,g1,g2,g3);
            }
            else {
                cout << "PLEASE COMPLETE YOUR PROFILE \n" << endl;
                string b1, b2, b3, b4, b5;
                cout << "please use the DD/MM/YYYY format for dates \n" << endl;
                cout << "enter your date of joining" << endl;
                fflush(stdin);
                cin >> b1;
                cout << "enter your date of birth" << endl;
                fflush(stdin);
                cin >> b2;
                cout << "enter your email address" << endl;
                fflush(stdin);
                cin >> b3;
                fflush(stdin);
                cout << "enter your marital status" << endl;
                cin >> b4;
                fflush(stdin);
                cout << "enter your gender" << endl;
                cin >> b5;
                fflush(stdin);
                o2.profileadd(m1, b1, b2, b3, b4, b5);
            }
        }
    }
};
class geninfo : public agniveer
{
public:
    geninfo()
    {
    }
    void notice()
    {
        string g5;
        ifstream in("notice1.txt");
        while (in.eof() == 0) {
            fflush(stdin);
            getline(in, g5);
            cout << g5 << "\n";
        }
        in.close();
    }
    void rules()
    {
        string g4;
        ifstream in("rulebook.txt");
        while (in.eof() == 0) {
            fflush(stdin);
            getline(in, g4);
            cout << g4 << "\n";
        }
        in.close();
    }
};
class future : public agniveer
{
public:
    future()
    {
    }
    void job()
    {
        string g3;
        ifstream in("job1.txt");
        while (in.eof() == 0) {
            fflush(stdin);
            getline(in, g3);
            cout << g3 << "\n";
        }
        in.close();
    }
    void privilages()
    {
        
        string g1;
        ifstream in("privilage1.txt");
        while (in.eof() == 0) {
            fflush(stdin);
            getline(in, g1);
            cout << g1<<"\n";
        }
        in.close();
    }
};
class helpdesk : public agniveer
{
public:
    helpdesk()
    {
    }
    void help()
    {
       

        string hd;
        string hd2;
        cout << "----------- WELCOME TO AGNIVEER'S HELPDESK --------------" << endl;
        cout << "\n please enter your querry, we will be soon in contact with you." << endl<<endl;
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        ofstream out("helpdaat.txt");
        getline(cin, hd);
        getline(cin, hd);
        out << hd;
        fflush(stdin);
        cout << "\n\n";
        out.close();
        ifstream in("helpdesk1.txt");
       while (in.eof() == 0) {
           fflush(stdin);
           getline(in, hd2);
            cout << hd2 << "\n";
       }
        in.close();
       
    }
};
int main()
{
    int n, q, w, e;
    agniveer* obj;
    pinfo obj1;
    geninfo obj2;
    future obj3;
    helpdesk obj4;
tryx:
    srand(time(0));
    n = rand();
    cout << "please enter the captcha shown on your screen -> " << n << endl;
    fflush(stdin);
    cin >> q;
    fflush(stdin);
    system("CLS");
    if (n != q)
    {
        // including captcha, so that you will be protected from spam and password decryption
        cout << "invalid captcha" << endl;
        cout << "press 1 to try again or 0 to exit" << endl;
        cin >> w;
        if (w == 0)
            return 0;
        else
            goto tryx;
    }
    no:
    cout << "                           *********************" << endl;
    cout << "*************************  WELCOME TO AGNIPORTAL  *****************************" << endl;
    cout << "                           *********************" << endl
        << endl;
    cout << "                           *********************" << endl;
    cout << "                           GOVERNMENT OF INDIA" << endl;
    cout << "                           *********************" << endl
        << endl;
    cout << "please select your choice from the following -" << endl
        << endl;
    cout << "1- SIGNUP WINDOW FOR NEW AGNIVEERS" << endl;
    cout << "2- AGNIVEER LOGIN WINDOW" << endl;
    cout << "3- NOTICES FOR AGNIVEERS" << endl;
    cout << "4- RULES AND REGULATIONS" << endl;
    cout << "5- JOB VACANCES AND AGNIVEER QUOTA(*)" << endl;
    cout << "6- PRIVILAGES AFTER SERVICE(*)" << endl;
    cout << "7- HELP OR QUARRIES" << endl
        << endl;
    cout << "* -> only for the agniveers who had completed their 4 year service" << endl
        << endl;
    fflush(stdin);
    cin >> e;
    fflush(stdin);
    system("CLS");
    switch (e)
    {
    case 1:
        obj = &obj1; 
        obj->signup();
        int x0;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x0;
        system("CLS");
        if (x0 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 2:
        obj = &obj1;
        obj->login();
        int x1;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x1;
        system("CLS");
        if (x1 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 3:
        obj = &obj2;
        obj->notice();
        int x2;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x2;
        system("CLS");
        if (x2 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 4:
        obj = &obj2;
        obj->rules();
        int x3;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x3;
        system("CLS");
        if (x3 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 5:
        obj = &obj3;
        obj->job();
        int x4;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x4;
        system("CLS");
        if (x4 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 6:
        obj = &obj3;
        obj->privilages();
        int x5;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x5;
        system("CLS");
        if (x5 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    case 7:
        obj = &obj4;
        obj->help();
        int x6;
        cout << "press 1 to go to the main window or 0 to exit" << endl;
        fflush(stdin);
        cin >> x6;
        system("CLS");
        fflush(stdin);
        if (x6 == 1) {
            goto no;
        }
        else
            return 0;
        break;
    }
    return 0;
}
