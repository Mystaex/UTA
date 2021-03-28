/*  Ethan Chase
    1001457646 | EGC7646
*/

#include <stdio.h>

/* This function takes in the total amount of workers and their salary. It then calculates the amount of higher-ups and their salaries, as well as total spending. */
float print_out(float* salary,int* num_of_emps){
    /* Checks to see if the amount of workers meets the minimum required */
    while(*num_of_emps < 6){
        printf("Invalid amount of workers. Must be at least 6 total workers. Try again.\n");
        printf("Enter total workers:");
        scanf("%d",num_of_emps);
    }
    float totSpen = (*num_of_emps * *salary) + (*num_of_emps/2 * (*salary * 2.5)) + ((*num_of_emps/2)/3 * (*salary * 5));
    printf("\n**Employee info:**\n");
    printf("Total workers: %d\tMonthly salary: $%0.2f\n", *num_of_emps, *salary);
    printf("Total managers: %d\tMonthly salary: $%0.2f\n", *num_of_emps/2, (*salary * 2.5));
    printf("Total managers: %d\tMonthly salary: $%0.2f\n", (*num_of_emps/6), (*salary * 5));
    printf("Total spent: $%0.2f\n", totSpen);
    return totSpen;
}

/* This function finds the difference between total spending and the budget. It then asks if the user would like to rebudget. */
int rebudget(float* d,float *budget){
    float dif = *budget - *d;
    /* Outputting difference in budget and spending */
    if(dif > 0){
        printf("--This goes UNDER your budget by $%0.2f.\n", dif);
    }
    else if(dif == 0){
        printf("--Your spending and budget are the same value!\n");
    }
    else{
        printf("--This goes OVER your budget by $%0.2f.\n", (-1*dif));
    }

    /* Getting choice for rebudgeting */
    printf("\n--------\n");
    int input = 3;
    while(input != 1 && input != 2){
        printf("Would you like to rebudget? 1 for yes 2 for no.\n");
        scanf("%d",&input);
        if(input != 1 && input != 2){
            printf("Invalid option. Please select again.\n");
        }
    }
    if(input == 2){
        printf("Bye!\n");
    }
    return input%2;
}

/* Main function. Asks the user for information about a company until prompted to stop. */
int main(int argc, char ** argv){
    int i=1;
    float budget, total, salary;
    float *money_ptr=&salary;
    float *total_ptr=&total;
    int employees;
    printf("Enter monthly budget: $");
    scanf("%f", &budget);
    /* Continues until gets the stop value from the rebudget function */
    while(i){
        printf("Enter monthly worker salary: $");
        scanf("%f", &salary);
        printf("Enter total workers:");
        scanf("%d", &employees);
        total=print_out(money_ptr, &employees);
        i=rebudget(total_ptr, &budget);
    }
}