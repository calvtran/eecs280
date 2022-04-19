#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "lab04.h"

using namespace std;

int main() {

  // TASK 1: Add code to do the following:
  //  - Create a local EmployeeRecord object
    EmployeeRecord rec;
    string name = "Calvin";
    string gender = "Male";
    int age = 20;
    int rank = 2;

  //  - Initialize the EmployeeRecord using EmployeeRecord_init
    EmployeeRecord_init(&rec, name, gender, age, rank);

  //  - Print the EmployeeRecord using EmployeeRecord_print
    EmployeeRecord_print(&rec);

  // TASK 2: Add code to do the following:
  //  - Create a Company with the name "eecsSoft"
    Company co("eecsSoft");

  //  - Add EXACTLY three Employees to the company, using the Employee
  //    constructor and the Company hire_employee function

    Employee e1("Calvin", "Male", 20, 2);
    co.hire_employee(e1);

    Employee e2("Catherine", "Female", 21, 3);
    co.hire_employee(e2);

    Employee e3("Richard", "Non-Binary", 22, 1);
    co.hire_employee(e3);

  //  - Print the company to cout using the << operator
    cout << co << endl;

  // TASK 2 - Add code to do the following:
  //  - Promote one employee at the company
    co.promote_employee("Calvin");

  //  - Demote one employee at the company
    co.demote_employee("Catherine");

  //  - Print the company to cout using the << operator
    cout << co << endl;


}
