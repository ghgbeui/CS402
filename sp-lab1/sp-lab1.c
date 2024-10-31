#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readfile.h"
#include "readfile.c"

#define MAXIMUNNAME_LENGTH 64
#define MAX_EMPLOYEES 1024

struct Employee{
    int id;
    char firstname[MAXIMUNNAME_LENGTH];
    char lastname[MAXIMUNNAME_LENGTH];
    float salary;
};

int read_employee(const char *filename, struct Employee employees[], int max_employees) 
{
    if (open_file(filename) != 0)
    {
        printf("Error: Unable to open file '%s'\n", filename);
        return -1;
    }

    int num_employees = 0;
    while (num_employees < max_employees &&
           read_int(&employees[num_employees].id) == 0 &&
           read_string(employees[num_employees].firstname) == 0 &&
           read_string(employees[num_employees].lastname) == 0 &&
           read_float(&employees[num_employees].salary) == 0) 
    {
        num_employees++;
    }

    close_file();

    return num_employees;
}

void storbyid(struct Employee employees[], int num_employees)
{
    for (int i=0;i<num_employees-1;i++)
    {
        for(int j=0;j<num_employees-i-1;j++)
        {
            if(employees[j].id > employees[j + 1].id)
            {
               struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void printdata(struct Employee employees[], int num_employees)
{
    for (int i = 0; i < num_employees; i++) 
    {
        printf("ID: %d, First name: %s, Last name: %s, Salary: %.2f\n", employees[i].id,
               employees[i].firstname, employees[i].lastname, employees[i].salary);
    }
}

void lookupbyid(struct Employee employees[], int num_employees, int lookupid)
{
    int found=0;
    for(int i=0; i<num_employees;i++)
    {
        if(lookupid == employees[i].id)
        {
            printf("ID: %d, First name: %s, Last name: %s, Salary: %.2f\n", employees[i].id,
               employees[i].firstname, employees[i].lastname, employees[i].salary);
            found = 1;
            break;
        } 
    }
    if(!found)
        {
            printf("Error, wrong ID!\n");
        }
}

void lookupbylastname(struct Employee employees[], int num_employees, const char lookuplastname[])
{
    int found = 0;
    for(int i=0;i<num_employees;i++)
    {
        int len = strlen(lookuplastname);
        int match = 1;
        for(int j=0;j<len;j++)
        {
            if(employees[i].lastname[j] != lookuplastname[j])
            {
                match = 0;
                break;
            }
        }
        if(match)
        {
            printf("ID: %d, First name: %s, Last name: %s, Salary: %.2f\n", employees[i].id,
               employees[i].firstname, employees[i].lastname, employees[i].salary);
            found = 1;
            break;
        }
    }
    if(!found)
    {
        printf("Error, can not find the last name!\n");
    }
}

void addnewdata(struct Employee employees[], int *num_employees, int newid, const char newfirstname[], const char newlastname[], int newsalary)
{
    if(*num_employees > MAX_EMPLOYEES)
    {
        printf("The number of employees is too much\n");
    }

    employees[*num_employees].id = newid;
    strncpy(employees[*num_employees].firstname, newfirstname, MAXIMUNNAME_LENGTH - 1);
    employees[*num_employees].firstname[MAXIMUNNAME_LENGTH - 1] = '\0'; // Ensure null-termination
    strncpy(employees[*num_employees].lastname, newlastname, MAXIMUNNAME_LENGTH - 1);
    employees[*num_employees].lastname[MAXIMUNNAME_LENGTH - 1] = '\0'; // Ensure null-termination
    employees[*num_employees].salary = newsalary;

    (*num_employees)++;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Define an array of employee structs
    struct Employee employees[MAX_EMPLOYEES];
    int num_employees = read_employee(argv[1], employees, MAX_EMPLOYEES);
    if (num_employees == -1) {
        return 1; // Error opening or reading from input file
    }

    int x = 0;

    printf("(1) Print the Database\n(2) Lookup by ID\n(3) Lookup by Last Name\n(4) Add an Employee\n(5) Quit\n");
    while (1)
    {
        printf("Enter a number to choose an option: ");
        scanf("%d", &x);
        if(x==5)
        {
            printf("Bye!\n");
            break;
        }
        switch (x)
        {
        case 1:
            storbyid(employees, num_employees);
            printdata(employees, num_employees);
            printf("Number of employees: %d", num_employees);
            break;
        case 2:
            int lookupid;
            printf("Enter the ID that you want to search: ");
            scanf("%d", &lookupid);
            lookupbyid(employees, num_employees, lookupid);
            break;
        case 3:
            char lookuplastname[MAXIMUNNAME_LENGTH];
            printf("Enter the Last name that you want to search: ");
            scanf("%s", lookuplastname);
            lookupbylastname(employees, num_employees, lookuplastname);
            break;
        case 4:
            int newid;
            float newsalary;
            char newfirstname[MAXIMUNNAME_LENGTH], newlastname[MAXIMUNNAME_LENGTH];

            // Automatically assign an ID larger than any existing one
            int max_id = 0;
            for (int i = 0; i < num_employees; i++) 
            {
                if (employees[i].id > max_id) 
                {
                    max_id = employees[i].id;
                }
            }
            newid = max_id + 1;

            // Input first name with validation
            while (1) 
            {
                printf("Enter new employee's first name (no spaces): ");
                scanf("%s", newfirstname);
                if (strlen(newfirstname) > 0 && strlen(newfirstname) < MAXIMUNNAME_LENGTH) 
                {
                    break;
                }
                printf("Invalid first name. Please try again.\n");
            }

            // Input last name with validation
            while (1) 
            {
                printf("Enter new employee's last name (no spaces): ");
                scanf("%s", newlastname);
                if (strlen(newlastname) > 0 && strlen(newlastname) < MAXIMUNNAME_LENGTH) 
                {
                    break;
                }
                printf("Invalid last name. Please try again.\n");
            }

            // Input salary with validation
            while (1) 
            {
                printf("Enter new employee's salary: ");
                if (scanf("%f", &newsalary) == 1 && newsalary > 0) 
                {
                    break;
                }
                printf("Invalid salary. Please enter a positive number.\n");
                // Clear the input buffer if necessary
                while (getchar() != '\n');
            }

            // Display the entered information and ask for confirmation
            printf("New Employee Details:\n");
            printf("ID: %d, First Name: %s, Last Name: %s, Salary: %.2f\n", newid, newfirstname, newlastname, newsalary);
            printf("Do you really want to add this employee? (y/n): ");

            char confirmation;
            while (1) 
            {
                scanf(" %c", &confirmation); // Space before %c to consume any newline character
                if (confirmation == 'y' || confirmation == 'Y') 
                {
                    // Add the new employee to the array
                    addnewdata(employees, &num_employees, newid, newfirstname, newlastname, newsalary);
                    storbyid(employees, num_employees);
                    printdata(employees, num_employees);
                    printf("Number of employees: %d\n", num_employees);
                    break;
                } 
                else if (confirmation == 'n' || confirmation == 'N') 
                {
                    printf("Employee addition canceled.\n");
                    break;
                } 
                else 
                {
                    printf("Invalid input. Please enter 'y' for yes or 'n' for no: ");
                }
            }
            break;
        default:
            printf("Wrong number!!\n");
            break;
        }
        printf("\n");
        printf("(1) Print the Database\n(2) Lookup by ID\n(3) Lookup by Last Name\n(4) Add an Employee\n(5) Quit\n");
        
    }
    
}