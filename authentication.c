#include <stdio.h>
#include <string.h>
#include "authentication.h"

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char role; // 'A' for admin, 'U' for user
} User;

User users[MAX_USERS];
int user_count = 0;
int logged_in_user_index = -1; // store index of logged in user

// Load users from file
int load_users(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open user file.\n");
        return 0;
    }
    user_count = 0;
    while (fscanf(file, "%s %s %c", users[user_count].username, users[user_count].password, &users[user_count].role) != EOF) {
        user_count++;
        if (user_count >= MAX_USERS) break;
    }
    fclose(file);
    return 1;
}

// Input user credentials
void input_credentials(char *username, char *password) {
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
}

// Authenticate user: returns 1 if verified, 0 otherwise
int authenticate_user() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("\n====================================\n");
    printf("           User Login Screen         \n");
    printf("====================================\n");

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user_index = i;
            return 1;
        }
    }
    return 0;
}

// Get role of logged in user
char get_logged_in_user_role() {
    if (logged_in_user_index >= 0 && logged_in_user_index < user_count) {
        return users[logged_in_user_index].role;
    }
    return 'U'; // default to normal user if no logged in user
}
