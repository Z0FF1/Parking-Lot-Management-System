#include <stdio.h>
#include <string.h>
#include <math.h>
#include "billing_fee.h"

#define DATA_FILE "C/PBL/vehicle_data.txt"

struct VehicleRecord {
    char reg_no[20];
    int entry_time;
    int exit_time;
};

int calculate_hours(int entry, int exit) {
    int entry_hr = entry / 100;
    int entry_min = entry % 100;
    int exit_hr = exit / 100;
    int exit_min = exit % 100;

    int total_entry_min = entry_hr * 60 + entry_min;
    int total_exit_min = exit_hr * 60 + exit_min;

    int diff_min = total_exit_min - total_entry_min;
    if (diff_min < 0) {
        printf("Exit time cannot be earlier than entry time.\n");
        return -1;
    }

    int hours = diff_min / 60;
    int rem_min = diff_min % 60;

    if (rem_min > 0) {
        hours += 1; // round up partial hour
    }

    return hours;
}

void billing_fee() {
    char reg_no[20];
    int found = 0;

    printf("Enter Registration Number: ");
    scanf("%19s", reg_no);

    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("Error opening data file.\n");
        return;
    }

    struct VehicleRecord record;
    while (fscanf(fp, "%19s %d %d", record.reg_no, &record.entry_time, &record.exit_time) != EOF) {
        if (strcmp(record.reg_no, reg_no) == 0) {
            found = 1;
            if (record.exit_time == 0) {
                printf("Exit time not recorded yet for this vehicle.\n");
                fclose(fp);
                return;
            }
            int hours = calculate_hours(record.entry_time, record.exit_time);
            if (hours == -1) {
                fclose(fp);
                return;
            }
            int rate_per_hour = 50; // example rate
            int total_fee = hours * rate_per_hour;
            printf("Parking duration: %d hour(s)\n", hours);
            printf("Total fee: %d\n", total_fee);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    if (!found) {
        printf("Registration number not found.\n");
    }
}
