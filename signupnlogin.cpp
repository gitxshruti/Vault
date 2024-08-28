#include <iostream>
#include <mysql/mysql.h>
#include <mysql_error.h>
#include <windows.h> // Ensure Windows.h is necessary or replace with appropriate headers if on other OS
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = " "; // Ensure to set a proper password or leave empty as needed
const char* DB = "mydb";

class Login {
private:
    string Id, PW;
public:
    Login() : Id(""), PW("") { }

    void setId(string id) {
        Id = id;
    }

    void setPW(string pw) {
        PW = pw;
    }

    string getId() {
        return Id;
    }

    string getPW() {
        return PW;
    }
};

int main() {
    Login l;
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return 1;
    }
    cout << "Logged In Database!" << endl;

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "1. Signup." << endl;
        cout << "2. Login." << endl;
        cout << "0. Exit." << endl;
        cout << "ENTER CHOICE: ";
        int val;
        cin >> val;
        cout << endl;

        if (val == 1) {
            system("cls");
            string id, pw;
            cout << "Enter Email or Phone Number: ";
            cin >> id;
            l.setId(id);
            cout << "Enter A Strong Password: ";
            cin >> pw;
            l.setPW(pw);

            string Sup = "INSERT INTO password(Id,PW) VALUES('" + l.getId() + "','" + l.getPW() + "')";
            if (mysql_query(conn, Sup.c_str())) {
                cout << "Error: " << mysql_error(conn) << endl;
            } else {
                cout << "Signup Successfully" << endl;
            }
            Sleep(3000);

        } else if (val == 2) {
            system("cls");
            string id, pw;
            cout << "Enter Your ID: ";
            cin >> id;
            cout << "Enter Your Password: ";
            cin >> pw;

            string Sin = "SELECT Id, PW FROM password WHERE Id='" + id + "' AND PW='" + pw + "'";
            if (mysql_query(conn, Sin.c_str())) {
                cout << "Error: " << mysql_error(conn) << endl;
            } else {
                MYSQL_RES* res = mysql_store_result(conn);
                if (res) {
                    int row = mysql_num_rows(res);
                    if (row == 1) {
                        cout << "WELCOME" << endl;
                    } else if (row == 0) {
                        cout << "Oops! Incorrect ID or Password. Please Try Again." << endl;
                    }
                    mysql_free_result(res);
                }
            }
            Sleep(3000);

        } else if (val == 0) {
            exit = true;
            cout << "Bye!" << endl;
            Sleep(3000);

        } else {
            cout << "Invalid Input" << endl;
            Sleep(3000);
        }
    }

    mysql_close(conn);
    return 0;
}
