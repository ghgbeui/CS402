#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readfile.h"
//#include "readfile.c"

#define MAXIMUNNAME_LENGTH 128
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

void removeemployee(struct Employee employees[], int *num_employees, int removeid)
{
    int found=0;
    char confirm;
    for(int i=0; i < *num_employees;i++)
    {
        if(employees[i].id == removeid)
        {
            found = 1;
            printf("Are you sure you want to remove this employee?(Y/N): ");
            scanf(" %c", &confirm);
            if(confirm == 'y' || confirm == 'Y')
            {
                for (int j = i; j < *num_employees - 1; j++) 
                {
                    employees[j] = employees[j + 1];
                }
                (*num_employees)--; // Decrement the number of employees
                printf("Employee with ID %d removed successfully.\n", removeid);
            }
            else if (confirm == 'n' || confirm == 'N')
            {
                printf("Removal cancel.\n");
            }
            break;
        }
    }
    if(!found)
    {
        printf("The ID is not found!\n");
    }
}

void updateinfo(struct Employee employees[], int num_employees, int updateid)
{
    int found = 0;
    int updateintfo;
    int update_successful = 0; 

    for(int i=0; i < num_employees;i++)
    {
        if(employees[i].id == updateid)
        {
            int newid,newsalary;
            char  newfirstname[MAXIMUNNAME_LENGTH], newlastname[MAXIMUNNAME_LENGTH];
            int len;
            found = 1;
            printf("What you want to update?\n(1) ID\n(2) First name\n(3) Last name\n(4) Salary\n(5) All");
            printf("\nEnter the number to choose what you want to do: ");
            scanf("%d", &updateintfo);
            switch (updateintfo)
            {
            case 1:
                printf("Enter the new id: ");
                scanf(" %d", &newid);
                employees[i].id = newid;
                printf("Data update successfully.\n");
                break;
            case 2:
                printf("Enter the new first name: ");
                scanf(" %s", newfirstname);
                if(strlen(newfirstname)>strlen(employees[i].firstname))
                {
                    len = strlen(newfirstname);
                }
                else
                {
                    len = strlen(employees[i].firstname);
                }
                for(int j=0;j<len;j++)
                {
                    employees[i].firstname[j] = newfirstname[j];
                }
                printf("Data update successfully.\n");
                break;
            case 3:
                printf("Enter the new last name: ");
                scanf(" %s", newlastname);
                if(strlen(newlastname)>strlen(employees[i].lastname))
                {
                    len = strlen(newlastname);
                }
                else
                {
                    len = strlen(employees[i].lastname);
                }
                
                for(int j=0;j<len;j++)
                {
                    employees[i].lastname[j] = newlastname[j];
                }
                printf("Data update successfully.\n");
                break;
            case 4:
                printf("Enter the new salary: ");
                scanf(" %d", &newsalary);
                employees[i].salary = newsalary;
                printf("Data update successfully.\n");
                break;
            case 5:
                int len_first = strlen(newfirstname);
                int len_last = strlen(newlastname);
                int len2 = (len_first > len_last) ? len_first : len_last;

                printf("Enter the new id: ");
                scanf("%d", &newid);
                printf("Enter the new first name: ");
                scanf("%s", newfirstname);
                printf("Enter the new last name: ");
                scanf("%s", newlastname);
                printf("Enter the new salary: ");
                scanf("%d", &newsalary);
                
                employees[i].id = newid;

                for(int j = 0; j < len2; j++)
                {
                    if (j < len_first)
                        employees[i].firstname[j] = newfirstname[j];
                    if (j < len_last)
                        employees[i].lastname[j] = newlastname[j];
                }

                employees[i].firstname[len2] = '\0';  // Ensure null-termination
                employees[i].lastname[len2] = '\0';   // Ensure null-termination

                employees[i].salary = newsalary;
                update_successful = 1; 
                break;
            }
            break;
        }
    }
    if(!found)
    {
        printf("The ID is not found!\n");
    }
    if(update_successful)
    {
        printf("Data update successfully.\n");
    }
}

/*void searchlastname(struct Employee employees[], int num_employees, char searchlname)
{
    int found=0;

    for(int i=0; i<num_employees;i++)
    {
        int len = strlen(searchlname);
        int match = 1;
        for(int j=0;j<len;j++)
        {
            if(employees[i].lastname[j]!=searchlname[j])
            {
                match = 0;
                break;
            }
            if(match)
            {
                printf("ID: %d, First name: %s, Last name: %s, Salary: %.2f\n", employees[i].id,
               employees[i].firstname, employees[i].lastname, employees[i].salary);
                found = 1;
            }
            
        }
    }
    
    if(!found)
    {
        printf("Can not found the last name\n");
    }
}*/

void findhighestsalary(struct Employee employees[], int num_employees, int m)
{
    int max[num_employees];

    for(int i = 0; i < m; i++) {
        max[i] = employees[i].salary;
    }

    // Find the top m highest salaries
    for(int i = m; i < num_employees; i++)
    {
        // Find the minimum salary among the top m salaries
        int min_index = 0;
        for(int j = 1; j < m; j++)
        {
            if(max[j] < max[min_index])
            {
                min_index = j;
            }
        }

        // Replace the minimum salary if the current employee's salary is higher
        if(employees[i].salary > max[min_index])
        {
            max[min_index] = employees[i].salary;
        }
    }
    storbyid(employees, num_employees);
    for(int i = 0; i < num_employees; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(employees[i].salary == max[j])
            {
                printf("ID: %d, First name: %s, Last name: %s, Salary: %.2f\n", employees[i].id,
                       employees[i].firstname, employees[i].lastname, employees[i].salary);
                break; // Move to the next employee once found
            }
        }
    }
    
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

    printf("(1) Print the Database\n(2) Lookup by ID\n(3) Lookup by Last Name\n(4) Add an Employee\n(5) Quit\n(6) Remove an employee\n(7) Update an employee's information\n(8) Print the M employees with the lowest salaries\n(9) Find all employees with matching last name\n");
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
            int newid, newsalary;
            char newfirstname[MAXIMUNNAME_LENGTH], newlastname[MAXIMUNNAME_LENGTH];
            printf("Enter new employee's ID: ");
            scanf("%d", &newid);
            printf("Enter new employee's first name: ");
            scanf("%s", newfirstname);
            printf("Enter new employee's last name: ");
            scanf("%s", newlastname);
            printf("Enter new employee's salary: ");
            scanf("%d", &newsalary);
            addnewdata(employees, &num_employees, newid, newfirstname, newlastname, newsalary);
            storbyid(employees, num_employees);
            printdata(employees, num_employees);
            printf("Number of employees: %d", num_employees);
            break;
        case 6:
            int removeid;
            printf("Enter an ID of employee that you want to remove: ");
            scanf("%d",&removeid);
            removeemployee(employees, &num_employees, removeid);
            storbyid(employees, num_employees);
            printdata(employees, num_employees);
            printf("Number of employees: %d", num_employees);
            break;
        case 7:
            int updateid;
            printf("Enter an ID of employee that you want to update: ");
            scanf("%d", &updateid);
            updateinfo(employees, num_employees, updateid);
            break;
        case 8:
            int m;
            printf("Enter a number to find how many employees you want to search with the highest salary: ");
            scanf("%d", &m);
            findhighestsalary(employees, num_employees, m);
            break;
        case 9:
            char searchlname[MAXIMUNNAME_LENGTH];
            printf("Enter the last name of employee that you want to search: ");
            scanf(" %s", searchlname);
            lookupbylastname(employees, num_employees, searchlname);
            break;
        default:
            printf("Wrong number!!\n");
            break;
        }
        printf("\n");
        printf("(1) Print the Database\n(2) Lookup by ID\n(3) Lookup by Last Name\n(4) Add an Employee\n(5) Quit\n(6) Remove an employee\n(7) Update an employee's information\n(8) Print the M employees with the lowest salaries\n(9) Find all employees with matching last name\n");
        
    }
    return 0;
}