#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "system_settings.h"

int total_slots = 10; // default value
float hourly_rate = 50.0f; // default value

void ensure_datafiles_dir_exists() {
    struct stat st = {0};
    if (stat("C/PBL/datafiles", &st) == -1) {
        if (mkdir("C/PBL/datafiles", 0700) == -1) {
            perror("mkdir");
            printf("Error: Could not create datafiles directory.\n");
        }
    }
}

void change_number_of_slots();
void change_hourly_rate();

void system_settings() {
    int choice;
    int c;
    do {
        printf("\n====================================\n");
        printf("         System Settings Menu        \n");
        printf("====================================\n");
        printf("1. Change number of slots\n");
        printf("2. Change hourly rate\n");
        printf("3. Add new user\n");
        printf("4. Remove a user\n");
        printf("5. Return to Main Menu\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        switch (choice) {
            case 1:
                change_number_of_slots();
                break;
            case 2:
                change_hourly_rate();
                break;
            case 3:
                printf("Add new user selected.\n");
                // Implementation to be added
                break;
            case 4:
                printf("Remove a user selected.\n");
                // Implementation to be added
                break;
            case 5:
                printf("Returning to Main Menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void change_number_of_slots() {
    int new_slots;
    int c;
    ensure_datafiles_dir_exists();
    printf("Enter new number of slots: ");
    if (scanf("%d", &new_slots) != 1 || new_slots <= 0) {
        printf("Invalid number. Please enter a positive integer.\n");
        while ((c = getchar()) != '\n' && c != EOF) {}
    } else {
        total_slots = new_slots;
        printf("Total slots updated to %d.\n", total_slots);

        // Save to settings file
        FILE *settings_file = fopen("C/PBL/datafiles/settings.txt", "w");
        if (settings_file == NULL) {
            printf("Error: Could not open settings file for writing.\n");
            perror("fopen");
            return;
        }
        fprintf(settings_file, "%d %.2f\n", total_slots, hourly_rate);
        fclose(settings_file);

        // Update slot availability file
        FILE *slot_file = fopen("C/PBL/datafiles/slot_availability.txt", "w");
        if (slot_file == NULL) {
            printf("Error: Could not open slot availability file for writing.\n");
            perror("fopen");
            return;
        }
        // Initialize all slots as available (1)
        for (int i = 0; i < total_slots; i++) {
            fprintf(slot_file, "1\n");
        }
        fclose(slot_file);
    }
}

void change_hourly_rate() {
    float new_rate;
    int c;
    ensure_datafiles_dir_exists();
    printf("Enter new hourly rate: ");
    if (scanf("%f", &new_rate) != 1 || new_rate < 0) {
        printf("Invalid rate. Please enter a non-negative number.\n");
        while ((c = getchar()) != '\n' && c != EOF) {}
    } else {
        hourly_rate = new_rate;
        printf("Hourly rate updated to %.2f.\n", hourly_rate);

        // Save to settings file
        FILE *settings_file = fopen("C/PBL/datafiles/settings.txt", "w");
        if (settings_file == NULL) {
            printf("Error: Could not open settings file for writing.\n");
            perror("fopen");
            return;
        }
        fprintf(settings_file, "%d %.2f\n", total_slots, hourly_rate);
        fclose(settings_file);
    }
}

float get_hourly_rate() {
    return hourly_rate;
}
