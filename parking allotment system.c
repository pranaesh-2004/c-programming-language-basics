#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct vehicle {
    char vehicle_no[20];
    char vehicle_type[20];
    char owner_name[50];
    int entry_day;
    int entry_month;
    int entry_year;
    int entry_hour;
    int entry_minute;
    int exit_day;
    int exit_month;
    int exit_year;
    int exit_hour;
    int exit_minute;
};

struct parking {
    char vehicle_no[20];
    char vehicle_type[20];
    int parking_hours;
    int charges;
};

int calculate_hours(struct vehicle v) {
    int total_hours = (v.exit_day - v.entry_day) * 24 + (v.exit_hour - v.entry_hour);
    return total_hours;
}

int calculate_charges(char *vehicle_type, int hours) {
    int rate_per_hour;
    if (strcmp(vehicle_type, "Car") == 0) {
        rate_per_hour = 10;
    } else if (strcmp(vehicle_type, "Bike") == 0) {
        rate_per_hour = 5;
    } else if (strcmp(vehicle_type, "Truck") == 0) {
        rate_per_hour = 15;
    } else {
        rate_per_hour = 8; // Default rate for other types
    }
    return hours * rate_per_hour;
}

int main() {
    struct vehicle v[1000];
    struct parking p[1000];
    int n = 0, i = 0, choice, datachoice;
    FILE *fp, *ok;

    printf("\n==================================================================================");
    printf("\n\t\t\tPARKING ALLOTMENT SYSTEM");
    printf("\n==================================================================================");

    printf("\nEnter the number of vehicles: ");
    scanf("%d", &n);
    int *ptr = &n;

    fp = fopen("vehicledetails.txt", "a+");
    for (i = 0; i < n; i++) {
        printf("Enter the vehicle number for vehicle %d: ", i + 1);
        scanf("%s", v[i].vehicle_no);
        fprintf(fp, "\n\n%s", v[i].vehicle_no);

        printf("Enter the vehicle type for vehicle %d (Car/Bike/Truck/Other): ", i + 1);
        scanf("%s", v[i].vehicle_type);
        fprintf(fp, "\n%s", v[i].vehicle_type);

        printf("Enter the owner's name for vehicle %d: ", i + 1);
        scanf("%s", v[i].owner_name);
        fprintf(fp, "\n%s", v[i].owner_name);

        printf("Enter the entry date (DD MM YYYY) for vehicle %d: ", i + 1);
        scanf("%d %d %d", &v[i].entry_day, &v[i].entry_month, &v[i].entry_year);
        fprintf(fp, "\n%d|%d|%d", v[i].entry_day, v[i].entry_month, v[i].entry_year);

        printf("Enter the entry time (HH MM) for vehicle %d: ", i + 1);
        scanf("%d %d", &v[i].entry_hour, &v[i].entry_minute);
        fprintf(fp, "\n%d|%d", v[i].entry_hour, v[i].entry_minute);

        printf("Enter the exit date (DD MM YYYY) for vehicle %d: ", i + 1);
        scanf("%d %d %d", &v[i].exit_day, &v[i].exit_month, &v[i].exit_year);
        fprintf(fp, "\n%d|%d|%d", v[i].exit_day, v[i].exit_month, v[i].exit_year);

        printf("Enter the exit time (HH MM) for vehicle %d: ", i + 1);
        scanf("%d %d", &v[i].exit_hour, &v[i].exit_minute);
        fprintf(fp, "\n%d|%d", v[i].exit_hour, v[i].exit_minute);
    }
    fclose(fp);

    ok = fopen("parkingrecords.txt", "a+");
    for (i = 0; i < n; i++) {
        strcpy(p[i].vehicle_no, v[i].vehicle_no);
        strcpy(p[i].vehicle_type, v[i].vehicle_type);

        p[i].parking_hours = calculate_hours(v[i]);
        p[i].charges = calculate_charges(p[i].vehicle_type, p[i].parking_hours);

        fprintf(ok, "\n\n%s", p[i].vehicle_no);
        fprintf(ok, "\n%s", p[i].vehicle_type);
        fprintf(ok, "\n%d", p[i].parking_hours);
        fprintf(ok, "\n%d", p[i].charges);

        printf("\nVehicle %d:", i + 1);
        printf("\nVehicle Number: %s", p[i].vehicle_no);
        printf("\nVehicle Type: %s", p[i].vehicle_type);
        printf("\nParking Hours: %d", p[i].parking_hours);
        printf("\nParking Charges: %d", p[i].charges);
    }
    fclose(ok);

    void vehicle_info() {
        printf("\n==================================================================================");
        for (i = 0; i < n; i++) {
            printf("\nThe vehicle number of vehicle %d: %s", i + 1, v[i].vehicle_no);
            printf("\nThe vehicle type of vehicle %d: %s", i + 1, v[i].vehicle_type);
            printf("\nThe owner's name of vehicle %d: %s", i + 1, v[i].owner_name);
            printf("\nThe entry date of vehicle %d: %d|%d|%d", i + 1, v[i].entry_day, v[i].entry_month, v[i].entry_year);
            printf("\nThe entry time of vehicle %d: %d|%d", i + 1, v[i].entry_hour, v[i].entry_minute);
            printf("\nThe exit date of vehicle %d: %d|%d|%d", i + 1, v[i].exit_day, v[i].exit_month, v[i].exit_year);
            printf("\nThe exit time of vehicle %d: %d|%d", i + 1, v[i].exit_hour, v[i].exit_minute);
        }
    }

    void parking_info() {
        printf("\n==================================================================================");
        for (i = 0; i < n; i++) {
            printf("\nVehicle %d's number: %s", i + 1, p[i].vehicle_no);
            printf("\nVehicle type: %s", p[i].vehicle_type);
            printf("\nParking hours: %d", p[i].parking_hours);
            printf("\nParking charges: %d", p[i].charges);
        }
    }

    data_info:
    printf("\n\nWhich data do you want?\n1.Vehicle details\n2.Parking information\n3.Exit\nChoice: ");
    scanf("%d", &datachoice);
    switch (datachoice) {
        case 1: vehicle_info();
                goto data_info;
        case 2: parking_info();
                goto data_info;
        case 3: break;
        default: printf("\nInvalid choice! Please enter the correct choice.");
                 goto data_info;
    }

    printf("\n==================================================================================");
    printf("\n\t\t\tTHANK YOU FOR USING OUR SERVICES VISIT AGAIN!!!!");
    return 0;
}
