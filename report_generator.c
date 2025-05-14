#include <stdio.h>
#include "report_generator.h"

#define DATA_FILE "C/PBL/vehicle_data.txt"

struct VehicleRecord {
    char reg_no[20];
    int entry_time;
    int exit_time;
};

void report_generator() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("Error opening data file.\n");
        return;
    }

    printf("Registration No\tEntry Time\tExit Time\n");
    printf("-------------------------------------------------\n");

    struct VehicleRecord record;
    while (fscanf(fp, "%19s %d %d", record.reg_no, &record.entry_time, &record.exit_time) != EOF) {
        printf("%-15s\t%04d\t\t%04d\n", record.reg_no, record.entry_time, record.exit_time);
    }

    fclose(fp);
}
