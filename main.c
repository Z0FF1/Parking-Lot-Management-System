#include <stdio.h>
#include "authentication.h"

void show_menu();

int main() {
    if (!load_users("C/PBL/authentication.txt")) {
        printf("Failed to load user data. Exiting.\n");
        return 1;
    }

    int authenticated = authenticate_user();

    if (authenticated==0) {
        printf("Access denied. Invalid credentials.\n");
        return 1;
    }
    else
    show_menu();

    return 0;
}
