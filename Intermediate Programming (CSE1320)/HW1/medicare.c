#include <stdio.h>

/*  Ethan Chase
    1001457646
    EGC7646
*/
/*Asks the user for the amount of patients in a hospital*/
int patientCount(int hosNum){
    int patients;
    printf("Number of patients in hospital %d: ", hosNum);
    scanf("%d", &patients);

    return patients;
}
/*Asks the user for the ages of each patient in a hospital*/
void ageInput(int hospital[],int size){
    int i;
    for(i = 0; i < size; i++){
        printf("Enter age of patient %d: ", i+1);
        scanf("%d", &hospital[i]);
    }
}
/*Returns the amount of patients that are applicable for medicare in a hospital*/
int medCount(int hospital[], int size){
    int total = 0;
    int i;
    for(i = 0; i < size; i++){
        if(hospital[i] >= 65){
            total ++;
        }
    }

    return total;
}
/*Compares 2 hospitals for their amount of medicare patients*/
void comparePatients(int one, int two){
    if(one > two){
        printf("You should pick hospital 1-they have more Medicare patients.");
    }
    else if(two > one){
        printf("You should pick hospital 2-they have more Medicare patients.");
    }
    else{
        printf("They have the same number of Medicare patients-go for either.");
    }
}

int main(int argc, char **argv){
    int count;
    /*Hospital 1*/
    count = patientCount(1);
    int hospitalOne[count];
    ageInput(hospitalOne,count);
    int oneTotal = medCount(hospitalOne, count);
    printf("\n");
    /*Hospital 2*/
    count = patientCount(2);
    int hospitalTwo[count];
    ageInput(hospitalTwo,count);
    int twoTotal = medCount(hospitalTwo, count);
    printf("\n");
    /*Comparison*/
    comparePatients(oneTotal, twoTotal);
    printf("\n");
    return 0;
}