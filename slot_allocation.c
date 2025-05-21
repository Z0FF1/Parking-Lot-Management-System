#include <stdio.h>
#include <stdlib.h>
#include "slot_allocation.h"

#define SLOT_FILE "C/PBL/datafiles/slot_availability.txt"
#define MAX_SLOTS 10

// Find the nearest available slot, return slot number or -1 if none available
int find_nearest_available_slot() {
    FILE *fp = fopen(SLOT_FILE, "r");
    if (!fp) {
        printf("Error: Could not open slot availability file.\n");
        return -1;
    }

    int slot_no;
    int status;
    while (fscanf(fp, "%d %d", &slot_no, &status) != EOF) {
        if (status == 0) { // 0 means available
            fclose(fp);
            return slot_no;
        }
    }
    fclose(fp);
    return -1; // no available slot
}

// Mark a slot as occupied (1), return 1 on success, 0 on failure
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
    int status;
    int found = 0;
    while (fscanf(fp, "%d %d", &curr_slot, &status) != EOF) {
        if (curr_slot == slot_no) {
            fprintf(temp_fp, "%d 1\n", curr_slot); // 1 means occupied
            found = 1;
        } else {
            fprintf(temp_fp, "%d %d\n", curr_slot, status);
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

// Mark a slot as available (0), return 1 on success, 0 on failure
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
    int status;
    int found = 0;
    while (fscanf(fp, "%d %d", &curr_slot, &status) != EOF) {
        if (curr_slot == slot_no) {
            fprintf(temp_fp, "%d 0\n", curr_slot); // 0 means available
            found = 1;
        } else {
            fprintf(temp_fp, "%d %d\n", curr_slot, status);
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
