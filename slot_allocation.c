#include <stdio.h>
#include <stdlib.h>
#include "slot_allocation.h"

#define SLOT_FILE "C/PBL/slot_availability.txt"
#define MAX_SLOTS 10

// Find the nearest available slot, return slot number or -1 if none available
int find_nearest_available_slot() {
    FILE *fp = fopen(SLOT_FILE, "r");
    if (!fp) {
        printf("Error: Could not open slot availability file.\n");
        return -1;
    }

    int slot_no;
    char status;
    while (fscanf(fp, "%d %c", &slot_no, &status) != EOF) {
        if (status == 'A') {
            fclose(fp);
            return slot_no;
        }
    }
    fclose(fp);
    return -1; // no available slot
}

// Mark a slot as occupied ('N'), return 1 on success, 0 on failure
int mark_slot_occupied(int slot_no) {
    FILE *fp = fopen(SLOT_FILE, "r");
    FILE *temp_fp = fopen("temp_slot.txt", "w");
    if (!fp || !temp_fp) {
        if (fp) fclose(fp);
        if (temp_fp) fclose(temp_fp);
        printf("Error: Could not open slot availability file.\n");
        return 0;
    }

    int curr_slot;
    char status;
    int found = 0;
    while (fscanf(fp, "%d %c", &curr_slot, &status) != EOF) {
        if (curr_slot == slot_no) {
            fprintf(temp_fp, "%d N\n", curr_slot);
            found = 1;
        } else {
            fprintf(temp_fp, "%d %c\n", curr_slot, status);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (!found) {
        remove("temp_slot.txt");
        printf("Error: Slot number %d not found.\n", slot_no);
        return 0;
    }

    remove(SLOT_FILE);
    rename("temp_slot.txt", SLOT_FILE);
    return 1;
}

// Mark a slot as available ('A'), return 1 on success, 0 on failure
int mark_slot_available(int slot_no) {
    FILE *fp = fopen(SLOT_FILE, "r");
    FILE *temp_fp = fopen("temp_slot.txt", "w");
    if (!fp || !temp_fp) {
        if (fp) fclose(fp);
        if (temp_fp) fclose(temp_fp);
        printf("Error: Could not open slot availability file.\n");
        return 0;
    }

    int curr_slot;
    char status;
    int found = 0;
    while (fscanf(fp, "%d %c", &curr_slot, &status) != EOF) {
        if (curr_slot == slot_no) {
            fprintf(temp_fp, "%d A\n", curr_slot);
            found = 1;
        } else {
            fprintf(temp_fp, "%d %c\n", curr_slot, status);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (!found) {
        remove("temp_slot.txt");
        printf("Error: Slot number %d not found.\n", slot_no);
        return 0;
    }

    remove(SLOT_FILE);
    rename("temp_slot.txt", SLOT_FILE);
    return 1;
}
