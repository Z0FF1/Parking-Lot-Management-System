#include <stdio.h>
#include <string.h>
#include "vehicle_exit.h"

#define DATA_FILE "datafiles/vehicle_data.txt"

#include "slot_allocation.h"

struct VehicleRecord {
    char reg_no[20];
    int entry_time;
    int exit_time;
    int slot_no;
};

void vehicle_exit() {
    char reg_no[20];
    int exit_time;
    int slot_no;
    int found = 0;

    printf("Enter Registration Number: ");
    scanf("%19s", reg_no);

    printf("Enter Slot Number: ");
    scanf("%d", &slot_no);

    printf("Enter Exit Time (24hr format as integer, e.g., 1432 for 2:32 PM): ");
    scanf("%d", &exit_time);

    FILE *fp = fopen(DATA_FILE, "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    if (!fp || !temp_fp) {
        printf("Error opening data file.\n");
        if (fp) fclose(fp);
        if (temp_fp) fclose(temp_fp);
        return;
    }

    struct VehicleRecord record;
    while (fscanf(fp, "%19s %d %d %d", record.reg_no, &record.entry_time, &record.exit_time, &record.slot_no) != EOF) {
        if (strcmp(record.reg_no, reg_no) == 0 && record.slot_no == slot_no) {
            record.exit_time = exit_time;
            found = 1;
        }
        fprintf(temp_fp, "%s %d %d %d\n", record.reg_no, record.entry_time, record.exit_time, record.slot_no);
    }

    fclose(fp);
    fclose(temp_fp);

    if (!found) {
        printf("Registration number and slot number not found.\n");
        remove("temp.txt");
        return;
    }

    if (!mark_slot_available(slot_no)) {
        printf("Failed to mark slot as available.\n");
        return;
    }

    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    printf("Exit time updated successfully.\n");
}
