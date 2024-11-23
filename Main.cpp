#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
// global variable declaration
int lcounter = 0, ex, exm = 1;
// function declaration
void add_customer();
void update_customer_record();
void delete_customer_record();
void add_daily_milk_data();
void calculate_bill();
void print_line()
{
    cout << "===========================================================================================================================================";
}
void print_hash()
{
    cout << "###########################################################################################################################################";
}
void home_page()
{
    string user_name, password;
// goto reference
reference:
    system("cls");
    print_line();
    cout << endl
         << endl;
    print_hash();
    cout << "\t\t\t\t\t\t\t\tDairy Management System" << endl;
    print_line();
    cout << endl
         << endl;
    print_hash();
    cout << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t\t....Login Details...." << endl
         << endl;
    cout << "\t\t\t\t\t\tEnter Username : \t";
    cin >> user_name;
    cout << "\t\t\t\t\t\tEnter Password : \t";
    cin >> password;
    if (user_name == "DairyAdmin" && password == "Gokul_Dairy")
    {
        sleep(2);
        cout << "\t\t\tLogin Sucessful";
        ex = 2;
    }
    else
    {
        cout << "\t\t\tLogin Unsucessful" << endl
             << "\t\t\tTry again Later................" << endl
             << "Enter 1 TO try Again" << endl
             << "Enter 0 TO EXIT" << endl;
        cin >> ex;
    }
    if (ex == 1)
    {
        goto reference;
    }
    else
    {
        system("exit");
    }
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    print_line();
}
class milk_dairy
{
    int choice, rc = 1;

public:
    milk_dairy()

    {
        cout << "Enter your choice" << endl;
        cout << "1: Add New Customer" << endl
             << "2: Delete Customer" << endl
             << "3: Update Customer Record" << endl
             << "4: Add Daily Milk Data" << endl
             << "5: Calculate Bill" << endl
             << "6: Al Dairy Data" << endl
             << "7: Go To Home Page " << endl
             << "8: Exit" << endl;
        cin >> choice;
        // condition to enter in the specific method
        switch (choice)
        {
        case 1:
            cout << "Add New Customer";
            add_customer();
            break;
        case 2:
            cout << "Delete Customer";
            delete_customer_record();
            break;
        case 3:
            cout << "Update Customer Record";
            update_customer_record();
            break;
        case 4:
            cout << "Add Daily Milk Data";
            add_daily_milk_data();
            break;
        case 5:
            cout << "Calculate Bill";
            calculate_bill();
            break;
        case 6:
            cout << "All Dairy Data ";
            break;
        case 7:
            cout << "Go To Home Page";
            home_page();
            break;
        case 8:
            cout << " Exit";
            system("exit");
            exm = 0;
            break;
        default:
            cout << "Enter valid choise";
            sleep(2);
            milk_dairy();
            break;
        }
    }
};
int main()
{
    home_page();
    if (ex == 2)
    {
        while (exm)
        {
            print_line();
            milk_dairy m;
        }
    }
    return 0;
}
//=============================Add New Customer ============================
void add_customer()
{ // file pointer
    fstream cfout;
    int phno, id;
    char name[100];
    // opens an existing csv file.
    cfout.open("customer.csv", ios::out | ios::app);
    // open id_counter file in input mode
    ifstream fin("id_counter.txt");
    // read the id from id counter file
    fin >> id;
    cout << "Enter the Details of Customer" << endl;
    cout << "Enter Name of the Customet" << endl;
    cin >> name;
    cout << "Enter Phone Number of the Customet" << endl;
    cin >> phno;
    // Insert the data to file
    cfout << id << "," << name << "," << phno << "\n";
    // increment the id counter and the store it into file
    id = id + 1;
    ofstream fout("id_counter.txt");
    fout << id;
    // close all the opende files
    cfout.close();
    fout.close();
    fin.close();
}
//==================== Update Customer Record ================================
void update_customer_record()
{
    // File pointer
    fstream fin, fout;
    // Open an existing record
    fin.open("customer.csv", ios::in);
    // Create a new file to store updated data
    fout.open("temp.csv", ios::out);
    int id, roll1, count = 0, i;
    char sub;
    int index;
    string name, phno, newvalue;
    string line, word;
    vector<string> row;
    // Get the ID of the user
    cout << "Enter the ID of customer to be updated: ";
    cin >> id;
    // Get the data to be updated
    // Determine the index of the customer to be updated
    cout << "Enter the Data to be Updated" << endl;
    cout << "1: Name \n2: Phone_number" << endl;
    cin >> index;
    // Get the Updated value
    if (index == 1)
    {
        cout << "Enter the name of customer" << endl;
        cin >> name;
        newvalue = name;
    }
    else
    {
        cout << "Enter the Monilr Number of customer" << endl;
        cin >> phno;
        newvalue = phno;
    }
    // Traverse the file
    while (!fin.eof())
    {
        row.clear();
        // getline(fin, line);
        fin >> line;
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        roll1 = stoi(row[0]);
        int row_size = row.size();
        if (roll1 == id)
        {
            count = 1;
            stringstream convert;
            // sending a number as a stream into output string
            convert << newvalue;
            // the str() converts number into string
            row[index] = convert.str();
            if (!fin.eof())
            {
                for (i = 0; i < row_size - 1; i++)
                {
                    // write the updated data
                    // into a new file 'reportcardnew.csv'
                    // using fout
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (!fin.eof())
            {
                for (i = 0; i < row_size - 1; i++)
                {
                    // writing other existing records
                    // into the new file using fout.
                    fout << row[i] << ",";
                }
                // the last column data ends with a '\n'
                fout << row[row_size - 1] << "\n";
            }
        }
        if (fin.eof())
            break;
    }
    if (count == 0)
        cout
            << "Record not found\n";
    fin.close();
    fout.close();
    // removing the existing file
    remove("customer.csv");
    // renaming the updated file with the existing file name
    rename("temp.csv", "customer.csv");
}
//======================= Delete customer Record ============================
void delete_customer_record()
{
    // Open FIle pointers
    fstream fin, fout;
    // Open the existing file
    fin.open("customer.csv", ios::in);
    // Create a new file to store the non-deleted data
    fout.open("customer_temp.csv", ios::out);
    int id, roll1, marks, count = 0, i;
    char sub;
    int index, new_marks;
    string line, word;
    vector<string> row;
    // Get the roll number
    // to decide the data to be deleted
    cout << "Enter the ID of the record to be deleted: ";
    cin >> id;
    // Check if this record exists
    // If exists, leave it and
    // add all other data to the new file
    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        int row_size = row.size();
        roll1 = stoi(row[0]);
        // writing all records,
        // except the record to be deleted,
        // into the new file 'customer_temp.csv'
        // using fout pointer
        if (roll1 != id)
        {
            if (!fin.eof())
            {
                for (i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            count = 1;
        }
        if (fin.eof())
            break;
    }
    if (count == 1)
        cout << "Record deleted\n";
    else
        cout << "Record not found\n";
    // Close the pointers
    fin.close();
    fout.close();
    // removing the existing file
    remove("customer.csv");
    // renaming the new file with the existing file name
    rename("customer_temp.csv", "customer.csv");
}
//============================ Add Daily Milk Data ============================
void add_daily_milk_data()
{
    // file pointer
    fstream fout;
    int id, day, milk_ltr, tid = 0;
    float milk_fat;
    // opens an existing csv file.
    fout.open("milk.csv", ios::out | ios::app);
    // check is entered id is present in the customer table or not

    // id_fout.open("id_counter,txt",ios::in | ios:: out);
    ifstream id_fin("id_counter.txt");
    id_fin >> tid;
    cout << endl
         << tid << endl;
// reference to goto
label:
    cout << endl
         << "Enter Customer ID" << endl;
    cin >> id;
    // checking if id is correct or not
    if (id <= tid)
    {
        sleep(2);
        cout << endl
             << "ID mached with customer details";
    }
    else
    {
        cout << endl
             << "Enter valid ID of Customer";
        goto label;
    }
    cout << "Enter the Day from` month" << endl;
    cin >> day;
    cout << "Enter milk count in liters" << endl;
    cin >> milk_ltr;
    cout << "Enter the fat of the milk" << endl;
    cin >> milk_fat;
    // Insert the data to file
    fout << id << "," << day << "," << milk_ltr << "," << milk_fat << "\n";
    // close all the opende files
    fout.close();
    id_fin.close();
    // fin.close();
}
//===========================Calculate Bill=====================================
void calculate_bill()
{
    // File pointer
    fstream fin;
    // Open an existing file
    fin.open("milk.csv", ios::in);
    // Get the roll number
    // of which the data is required
    int count = 0, c = 0, id, id2, milk = 0;
    float fat, price, total_price = 0;
    cout << "Enter the ID of students to calculate the Bill: ";
    cin >> id;
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    while (!fin.eof())
    {
        // to clear the every first row of the record continue everytime
        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        // getline(fin, line);
        fin >> line;
        // cout<<line;
        // used for breaking words
        stringstream s(line);
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ','))
        {
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        // convert string to integer for comparision
        id2 = stoi(row[0]);
        milk = stoi(row[2]);
        fat = stoi(row[3]);
        // Compare the roll number
        if (id2 == id)
        {
            // claculate the total milk and fat
            // calculate the tots;l pricr of the milk
            price = ((5.6 * fat) * milk);
            total_price = total_price + price;
            // Print the found data
            count = 1;
            c = c + milk;
        }
    }

    if (count == 0)
        cout
            << "Record not found\n";
    // close the file
    fin.close();
    cout << endl
         << "total amount to pay : " << total_price;
    cout << endl
         << "total milk : " << c;
}