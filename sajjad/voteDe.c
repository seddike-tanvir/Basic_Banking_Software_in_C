#include <stdio.h>
#include <string.h>

void giveVote(){
            char vote;
            printf("\n--- Select Vote Options ---\n");
            printf("> A\n> B\n> C\n> D\n");
            printf("Enter your choice: ");
            scanf(" %c", &vote);

            if (vote == 'A' || vote == 'B' || vote == 'C' || vote == 'D') {
                printf("\nCongratulations, your vote is done!\n");
            } else {
                printf("\nInvalid selection.\n");
                giveVote();
            }
}

int main() {
    char name[20];
    int nid;


    char name1[] = "Sajjad";
    char name2[] = "Rafi";
    char name3[] = "Tanvir";
    char name4[] = "Fahim";
    char name5[] = "Kuddus";
    char name6[] = "Peal";


    int nid1 = 101, nid2 = 102, nid3 = 103, nid4 = 104, nid5 = 105, nid6 = 106;

    printf("Enter your Name: ");
    scanf("%s", name);

    printf("Enter your NID number: ");
    scanf("%d", &nid);


    if ((strcmp(name, name1) == 0 && nid == nid1) ||
        (strcmp(name, name2) == 0 && nid == nid2) ||
        (strcmp(name, name3) == 0 && nid == nid3) ||
        (strcmp(name, name4) == 0 && nid == nid4) ||
        (strcmp(name, name5) == 0 && nid == nid5) ||
        (strcmp(name, name6) == 0 && nid == nid6))    {

        int birthYear;
        printf("\nEnter your Birth Year: ");
        scanf("%d", &birthYear);

        if (birthYear > 2006) {
            printf("\nYou are not eligible for Voting.\n");
        } else {
            giveVote();
        }

    } else {
        printf("\nWrong information! try again.\n");
    }

    return 0;
}