#include <stdio.h>
#include <string.h>

/* structure */
struct Account {
    char username[20];
    char password[20];
    int balance;
};

/* function declaration */
int login(struct Account users[], int *userCount, int *currentUser);
void showMenu();
int checkPassword(struct Account acc);
void showBalance(struct Account acc);
void addMoney(struct Account *acc);
void cashOut(struct Account *acc);
void updateFile(struct Account users[], int userCount);






// !--------------------------| pass check function |-----------------------------------------------------------------------------------
int checkPassword(struct Account acc) {
    char pass[50];

    printf("Re-enter password to continue: ");
    scanf("%s", pass);

    if (strcmp(pass, acc.password) == 0) {
        return 1;   // password correct
    } else {
        printf("Wrong password! Transaction cancelled.\n");
        return 0;   // password wrong
    }
}










// !--------------------------| Login Info |-----------------------------------------------------------------------------------
int login(struct Account users[], int *userCount, int *currentUser) {
    FILE *fp;
    char user[50], pass[50];
    int i = 0;

    fp = fopen("info_DB.txt", "r");
    if (fp == NULL) {
        printf("Database file not found!\n");
        return 0;
    }

    // read all users from file
    while (i < 10 &&
        fscanf(fp, " \"%[^\"]\" %s %d",
                users[i].username,
                users[i].password,
                &users[i].balance) == 3) {

        // quotes strip করা
        int len = strlen(users[i].username);
        if (users[i].username[0] == '"' && users[i].username[len-1] == '"') {
            char cleanUser[50];
            strncpy(cleanUser, users[i].username + 1, len - 2);
            cleanUser[len - 2] = '\0';
            strcpy(users[i].username, cleanUser);
        }

        i++;
    }

    fclose(fp);
    *userCount = i;


    printf("\n         - - -<         Welcome to BASIC BANK         >- - -\n");
    printf("\n ---------------------------------------------------------------------\n\n\n");

    printf("Enter credentials to login - \n\n");
    printf("Enter Username: ");
    scanf(" %[^\n]", user);

    printf("Enter Password: ");
    scanf("%s", pass);

    for (i = 0; i < *userCount; i++) {
        if (strcmp(user, users[i].username) == 0) {
            if (strcmp(pass, users[i].password) == 0) {
                *currentUser = i;   // logged user index
                return 1;
            } else {
                printf("\nLogin Failed: Incorrect Password!\n");
                return 0;
            }
        }
    }

    printf("\nLogin Failed: Username not found!\n");
    return 0;
}









// !--------------------------| show Menu function |-----------------------------------------------------------------------------------
void showMenu() {
    printf("\n\n  ------<  MENU  >------\n");
    printf("  [1] Add Money      \n");
    printf("  [2] Cash Out       \n");
    printf("  [3] Show Balance   \n");
    printf("  [0] Exit           \n");
    printf("  ----------------------\n\n");
    printf("Enter your choice: ");
}





// !--------------------------| Show balance function |-----------------------------------------------------------------------------------
void showBalance(struct Account acc) {
    printf("\n>> Your Current Balance is: %d\n", acc.balance);
}







// !--------------------------| add money function |-----------------------------------------------------------------------------------
void addMoney(struct Account *acc) {
    int amount;

    printf("Enter amount to add: ");
    scanf("%d", &amount);

    if (!checkPassword(*acc)) {
        return;   // password wrong → back to menu
    }

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    acc->balance = acc->balance + amount;
    printf("Money Added Successfully!\n");
    showBalance(*acc);
}






// !--------------------------| cash out function |-----------------------------------------------------------------------------------
void cashOut(struct Account *acc) {
    int amount;

    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    if (!checkPassword(*acc)) {
        return;   // password wrong → back to menu
    }

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > acc->balance) {
        printf("Insufficient Balance!\n");
    } else {
        acc->balance = acc->balance - amount;
        printf("Cash Out Successful!\n");
        showBalance(*acc);
    }
}






// !--------------------------| update file function |-----------------------------------------------------------------------------------
void updateFile(struct Account users[], int userCount) {
    FILE *fp;
    int i;

    fp = fopen("info_DB.txt", "w");

    for (i = 0; i < userCount; i++) {
        fprintf(fp, "\"%s\" %s %d\n",
                users[i].username,
                users[i].password,
                users[i].balance);
    }

    fclose(fp);
}









// !--------------------------| main function |-----------------------------------------------------------------------------------
int main() {
    struct Account users[10];
    int userCount = 0;
    int currentUser;
    int choice;

    if (login(users, &userCount, &currentUser) == 0) {
        return 0;
    }

    printf("\nLogin Successful!\n");

    while (1) {
        showMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            addMoney(&users[currentUser]);
            updateFile(users, userCount);
        }
        else if (choice == 2) {
            cashOut(&users[currentUser]);
            updateFile(users, userCount);
        }
        else if (choice == 3) {
            showBalance(users[currentUser]);
        }
        else if (choice == 0) {
            printf("\nThank you for being with BASIC BANK.\n");
            break;
        }
        else {
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
