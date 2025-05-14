#include <stdio.h>
#include <string.h>
#include "vehicle_entry.h"

#define DATA_FILE "C/PBL/vehicle_data.txt"

#include "slot_allocation.h"

struct VehicleRecord {
    char reg_no[20];
    int entry_time;
    int exit_time;
    int slot_no;
};

void vehicle_entry() {
    struct VehicleRecord record;
    FILE *fp = fopen(DATA_FILE, "a+");  // append+ mode to create file if not exists
    if (!fp) {
        printf("Error opening data file for writing.\n");
        return;
    }

    int slot = find_nearest_available_slot();
    if (slot == -1) {
        printf("No available parking slots. Entry denied.\n");
        fclose(fp);
        return;
    }

    printf("Enter Registration Number: ");
    scanf("%19s", record.reg_no);

    printf("Enter Entry Time (24hr format as integer, e.g., 1332 for 1:32 PM): ");
    scanf("%d", &record.entry_time);

    record.exit_time = 0; // exit time not known yet
    record.slot_no = slot;

    if (!mark_slot_occupied(slot)) {
        printf("Failed to mark slot as occupied. Entry denied.\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%s %d %d %d\n", record.reg_no, record.entry_time, record.exit_time, record.slot_no);
    fclose(fp);

    printf("Vehicle entry recorded successfully. Your ticket number (slot number) is %d.\n", slot);
}
