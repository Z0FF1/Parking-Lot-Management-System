#include <stdio.h>
#include "vehicle_entry.h"
#include "vehicle_exit.h"
#include "billing_fee.h"
#include "report_generator.h"
#include "system_settings.h"

void show_menu() {
    int choice;
    do {
        printf("Main Menu:\n");
        printf("1. Vehicle Entry Module\n");
        printf("2. Vehicle Exit Module\n");
        printf("3. Billing & Fee Calculation Module\n");
        printf("4. Report Generator Module\n");
        printf("5. System Settings Module\n");
        printf("6. Exit / Logout Module\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                vehicle_entry();
                break;
            case 2:
                vehicle_exit();
                break;
            case 3:
                billing_fee();
                break;
            case 4:
                report_generator();
                break;
            case 5:
                system_settings();
                break;
            case 6:
                printf("Exiting. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

