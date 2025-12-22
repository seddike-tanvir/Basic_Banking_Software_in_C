#include <stdio.h>
#include <string.h>

/* structure */
struct Account {
    char username[20];
    char password[20];
    int balance;
    char mobile[11];
};

/* function declaration */
int login(struct Account users[], int *userCount, int *currentUser);
void registerUser(struct Account users[], int *userCount);
void showMenu();
int checkPassword(struct Account acc);
void showBalance(struct Account acc);
void addMoney(struct Account *acc);
void cashOut(struct Account *acc);
void updateFile(struct Account users[], int userCount);
void fundTransfer(struct Account users[], int userCount, int currentUser);





// !--------------------------| new user registration function |-----------------------------------------------------------------------------------
void registerUser(struct Account users[], int *userCount) {
    struct Account newUser;
    int i;

    if (*userCount >= 10) {
        printf("User limit reached!\n");
        return;
    }

    printf("\n--- Register New Account ---\n");

    printf("Set Username: ");
    scanf(" %[^\n]", newUser.username);

    // username duplicate check
    for (i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Username already exists!\n");
            return;
        }
    }

    printf("Set Password: ");
    scanf("%s", newUser.password);

    printf("Add Mobile Number: ");
    scanf("%s", newUser.mobile);

    newUser.balance = 0;   // default balance

    users[*userCount] = newUser;
    (*userCount)++;

    updateFile(users, *userCount);

    printf("\nRegistration Successful!\n");
}






// !--------------------------| outer menu function |-----------------------------------------------------------------------------------
void showOuterMenu() {
    printf("\n\n  ------<  Now,  >------\n");
    printf("  [1] Login\n");
    printf("  [2] Register\n");
    printf("  [0] Exit\n");
    printf("\nEnter your choice: ");
}






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
        fscanf(fp, " \"%[^\"]\" %s %d %s",
                users[i].username,
                users[i].password,
                &users[i].balance,
                users[i].mobile) == 4 ){

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


    // printf("\n         - - -<         Welcome to BASIC BANK         >- - -\n");
    // printf("\n ---------------------------------------------------------------------\n\n\n");

    printf("\n\nEnter credentials to login - \n\n");
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
    printf("  [3] Fund Transfer   \n");
    printf("  [4] Show Balance   \n");
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
    } 
    
    else {
        acc->balance = acc->balance - amount;
        printf("Cash Out Successful!\n");
        showBalance(*acc);
    }
}








// !--------------------------| fund transfer function |-----------------------------------------------------------------------------------
void fundTransfer(struct Account users[], int userCount, int currentUser) {
    char targetMobile[15];
    int amount, i, found = -1;

    printf("Enter Receiver Mobile Number: ");
    scanf("%s", targetMobile);

    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].mobile, targetMobile) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nReceiver not found!\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%d", &amount);

    if (!checkPassword(users[currentUser])) {
        return;
    }

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (amount > users[currentUser].balance) {
        printf("Insufficient Balance!\n");
        return;
    }

    users[currentUser].balance -= amount;
    users[found].balance += amount;

    printf("Fund Transfer Successful!\n");
    showBalance(users[currentUser]);
}







// !--------------------------| update file function |-----------------------------------------------------------------------------------
void updateFile(struct Account users[], int userCount) {
    FILE *fp;
    int i;

    fp = fopen("info_DB.txt", "a");

    for (i = 0; i < userCount; i++) {
        fprintf(fp, "\"%s\" %s %d %s\n",
                users[i].username,
                users[i].password,
                users[i].balance,
                users[i].mobile);
    }

    fclose(fp);
}









// !--------------------------| main function |-----------------------------------------------------------------------------------
int main() {
    struct Account users[10];
    int userCount = 0;
    int currentUser;
    int choice;
    int startChoice;


    printf("\n         - - -<         Welcome to BASIC BANK         >- - -\n");
    printf("\n ---------------------------------------------------------------------\n");

    while (1) {

        showOuterMenu();
        scanf("%d", &startChoice);

        if (startChoice == 0) {
            printf("\nThank you for being with BASIC BANK.\n");
            return 0;
        }

        else if (startChoice == 2) {
            registerUser(users, &userCount);
            continue;   // 🔥 আবার outer menu তে ফিরে যাবে
        }

        else if (startChoice == 1) {
            if (login(users, &userCount, &currentUser) == 0) {
                continue;   // login fail → outer menu
            }

            printf("\nLogin Successful!\n");

            // -------- inner banking menu --------
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
                    fundTransfer(users, userCount, currentUser);
                    updateFile(users, userCount);
                }
                else if (choice == 4) {
                    showBalance(users[currentUser]);
                }
                else if (choice == 0) {
                    printf("\nLogging out...\n");
                    break;   // 🔥 logout → outer menu
                }
                else {
                    printf("\nInvalid Choice!\n");
                }
            }
        }

        else {
            printf("\nInvalid Choice!\n");
        }
    }
}

