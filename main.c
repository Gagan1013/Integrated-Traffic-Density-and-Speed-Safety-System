#include <stdio.h>
#include <string.h>

int main() {
    int numLanes;

    printf("=================================================================\n");
    printf("  INTELLIROAD: DYNAMIC ROADWAY TRAFFIC & SPEED SYSTEM            \n");
    printf("=================================================================\n");
    
    // Ask the user to define the type/number of roadways at this intersection
    printf("Enter the number of roads/lanes at this intersection (e.g., 3 for T-Junction, 4 for Crossroad, 5 for Roundabout): ");
    fflush(stdout);
    scanf("%d", &numLanes);

    // Input validation for lane count
    while (numLanes <= 0 || numLanes > 10) {
        printf("Invalid intersection size! Please enter between 1 and 10 roads: ");
        scanf("%d", &numLanes);
    }

    // Declare arrays with a safe maximum capacity (e.g., 10), but use 'numLanes'
    char lanes[10][30];
    int vehicleCounts[10];
    int averageSpeeds[10];
    int emergencyStatus[10];

    // Initialize default names and values based on user input
    for (int i = 0; i < numLanes; i++) {
        sprintf(lanes[i], "Roadway %d", i + 1); // Automatically names them Roadway 1, 2, etc.
        vehicleCounts[i] = 100 + (i * 25);       // Sample default count
        averageSpeeds[i] = 50 + (i * 10);        // Sample default speed
        emergencyStatus[i] = (i == 1) ? 1 : 0;   // Put an emergency on Roadway 2 as a demo
    }

    int SPEED_LIMIT = 60; // Safe speed limit in km/h
    int choice;

    do {
        printf("\n=================================================================\n");
        printf("                       MAIN CONTROL MENU                         \n");
        printf("=================================================================\n");
        printf("1. View Smart Signal Status (Emergency -> Density -> Speed)\n");
        printf("2. View Speed Violation & Fine Safety Report\n");
        printf("3. Update Live Traffic, Speed & Emergency Data\n");
        printf("4. Run System Diagnostic & Risk Analysis\n");
        printf("5. Exit System\n");
        printf("Enter choice (1-5): ");
        scanf("%d", &choice);

        printf("\n");

        // OPTION 1: Main Control Logic
        if (choice == 1) {
            printf("--- TRAFFIC SIGNAL & PRIORITY CONTROL DASHBOARD (%d Roads) ---\n\n", numLanes);

            for (int i = 0; i < numLanes; i++) {
                printf("Lane %d [%s]:\n", i + 1, lanes[i]);

                // STEP 1: EMERGENCY CHECK (Highest Priority)
                if (emergencyStatus[i] == 1) {
                    printf("   [!] EMERGENCY DETECTED (Ambulance/VIP)!\n");
                    printf("   -> SIGNAL STATUS: INSTANT GREEN LIGHT (60 Seconds) [OVERRIDE ACTIVE]\n");
                } 
                // STEP 2: DENSITY CHECK
                else {
                    printf("   Vehicles: %d | Avg Speed: %d km/h\n", vehicleCounts[i], averageSpeeds[i]);
                    
                    if (vehicleCounts[i] > 150) {
                        printf("   -> Status: HEAVY CONGESTION | Green Light: 50 Seconds\n");
                    } 
                    else if (vehicleCounts[i] >= 80) {
                        printf("   -> Status: MODERATE TRAFFIC | Green Light: 30 Seconds\n");
                    } 
                    else {
                        printf("   -> Status: SMOOTH FLOW     | Green Light: 15 Seconds\n");
                    }
                }
                printf("-----------------------------------------------------------------\n");
            }
        } 
        // OPTION 2: Speed Violations
        else if (choice == 2) {
            printf("--- SPEED VIOLATION MONITORING (Speed Limit: %d km/h) ---\n\n", SPEED_LIMIT);
            
            for (int i = 0; i < numLanes; i++) {
                printf("Lane [%s] Speed: %d km/h -> ", lanes[i], averageSpeeds[i]);
                
                if (averageSpeeds[i] > SPEED_LIMIT) {
                    printf("WARNING: OVER-SPEEDING DETECTED! (Automated Fine Issued)\n");
                } else {
                    printf("SAFE: Normal Driving Speed\n");
                }
            }
        } 
        // OPTION 3: Input Custom Data
        else if (choice == 3) {
            printf("--- MANUAL DATA UPDATE MODE ---\n");
            
            for (int i = 0; i < numLanes; i++) {
                printf("\nEnter custom name for Road %d (e.g., North-Gate): ", i + 1);
                scanf("%s", lanes[i]); // Note: scanf reads single-word names safely

                printf("Is an Emergency Vehicle present on %s? (1 for Yes, 0 for No): ", lanes[i]);
                scanf("%d", &emergencyStatus[i]);

                printf("Enter vehicle count for %s: ", lanes[i]);
                scanf("%d", &vehicleCounts[i]);

                printf("Enter average vehicle speed for %s (km/h): ", lanes[i]);
                scanf("%d", &averageSpeeds[i]);
            }
            printf("\nData successfully updated for all %d roadways!\n", numLanes);
        } 
        // OPTION 4: Diagnostic Summary
        else if (choice == 4) {
            printf("--- COMPREHENSIVE SYSTEM DIAGNOSTIC REPORT ---\n");
            
            int totalVehicles = 0;
            int maxTrafficIndex = 0;
            int maxVehicles = -1;

            for (int i = 0; i < numLanes; i++) {
                totalVehicles += vehicleCounts[i];

                if (vehicleCounts[i] > maxVehicles) {
                    maxVehicles = vehicleCounts[i];
                    maxTrafficIndex = i;
                }
            }

            printf("Total Active Vehicles Across %d Roads: %d\n", numLanes, totalVehicles);
            printf("Main Traffic Bottleneck Road        : %s (%d vehicles)\n", lanes[maxTrafficIndex], vehicleCounts[maxTrafficIndex]);
            
            if (averageSpeeds[maxTrafficIndex] > SPEED_LIMIT) {
                printf("Hazard Status                       : HIGH RISK (Heavy Traffic + Speeding!)\n");
            } else {
                printf("Hazard Status                       : MODERATE (High Traffic, Safe Speeds)\n");
            }
        } 
        else if (choice == 5) {
            printf("Exiting IntelliRoad Traffic System. Drive safely!\n");
        } 
        else {
            printf("Invalid Choice! Please enter a number from 1 to 5.\n");
        }

    } while (choice != 5);

    return 0;
}