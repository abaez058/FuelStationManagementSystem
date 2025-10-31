#include <stdio.h>
#include <stdlib.h>

const char* getStockStatus(float stock) {
    if (stock < 50.0) {
        return "CRITICAL";
    } else if (stock < 200.0) {
        return "LOW";
    } else {
        return "NORMAL";
    }
}

int main(){
    int mainChoice = 0;
    int subChoice = 0;
    int fuelChoice = 0;
    int vehicleChoice= 0;
    int loyaltyChoice = 0;
    int fuelAmount = 0;
    int customerNumber = 1;
    
    // Count
    int motorcycleCount = 0;
    int carCount = 0;
    int truckCount = 0;

    // Daily Summary
    int totalCustomers = 0;
    float totalFuelSold = 0.0;     
    float totalRevenue = 0.0;       
    float totalStateTax = 0.0;      
    float totalDiscounts = 0.0;
    float totalCustomerPayments = 0.0;
    float stationNetIncome = 0.0;   

    // Calculations
    float bulkDiscount = 0.0;  
    float loyaltyDiscount = 0.0; 
    
    float regularPrice = 3.00, premiumPrice = 4.00, dieselPrice = 3.50;
    float regularStock = 1000.0, premiumStock = 1000.0, dieselStock = 1000.0;
    
    printf("=========================================================\n");
    printf("   WELCOME TO TurboFill FUEL STATION MANAGEMENT SYSTEM     \n");
    printf("=========================================================\n");

    printf("\n========= CURRENT PRICING & POLICIES =========\n");
    printf("Fuel Rates:\n");
    printf("  Regular Gas : $%.2f/gal (Max: 200 gal/transaction)\n", regularPrice);
    printf("  Premium Gas : $%.2f/gal (Max: 200 gal/transaction)\n", premiumPrice);
    printf("  Diesel      : $%.2f/gal (Max: 400 gal/transaction)\n", dieselPrice);

    printf("\nState Fuel Tax Rates:\n");
    printf("  Motorcycle  : 2%%\n");
    printf("  Car         : 3%%\n");
    printf("  Truck       : 1%%\n");

    printf("\nBulk Discount Rates:\n");
    printf("  30+ gallons : 5%% off total\n");
    printf("  50+ gallons : 10%% off total\n");

    printf("\nLoyalty Program: Additional 2%% off total\n");
    printf("=============================================\n\n");


    while (1) {
        printf("\n========= SYSTEM MODE SELECTION =========\n");
        printf("1. Daily Operations (Customer Service)\n");
        printf("2. Station Management (Administrative)\n");
        printf("3. Exit System\n");
        printf("=========================================\n");
        printf("Select Mode: ");
        scanf("%d", &mainChoice);
        
        switch (mainChoice) {
            case 1:
                while (1) {
                    printf("\n========= DAILY OPERATIONS MODE =========\n");
                    printf("1. Serve New Customer\n");
                    printf("2. View Current Day Summary\n");
                    printf("3. Return to Main Menu\n");
                    printf("=========================================\n");
                    printf("Choice: ");
                    scanf(" %d", &subChoice);  
                    

                    if (subChoice == 1) {
                        printf("\n--- CUSTOMER #%d ---\n", customerNumber);
                        // ===== Fuel Choice =====
                        do {
                            printf("Select Fuel Type:\n");
                            printf("1. Regular Gas ($%.2f/gal) - Stock: %.1f gal\n", regularPrice, regularStock);
                            printf("2. Premium Gas ($%.2f/gal) - Stock: %.1f gal\n", premiumPrice, premiumStock);
                            printf("3. Diesel ($%.2f/gal)      - Stock: %.1f gal\n", dieselPrice, dieselStock);

                            printf("Fuel Choice: ");
                            scanf(" %d", &fuelChoice);

                            if (fuelChoice < 1 || fuelChoice > 3) {
                                printf("Invalid choice. Please try again.\n");
                                continue;  
                            }

                            // Check if stock is available
                            if ((fuelChoice == 1 && regularStock <= 0) ||
                                (fuelChoice == 2 && premiumStock <= 0) ||
                                (fuelChoice == 3 && dieselStock <= 0)) {
                                printf("Error: Selected fuel is OUT OF STOCK. Please choose another type.\n\n");
                                fuelChoice = 0;  
                            }

                        } while (fuelChoice < 1 || fuelChoice > 3);

                        // ===== Fuel Amount =====
                        do {
                            int maxLimit = (fuelChoice == 3 ? 400 : 200);
                            printf("Enter quantity in gallons (Max: %d): ", maxLimit);
                            scanf(" %d", &fuelAmount);
                            
                            if (fuelAmount <= 0) {
                                printf("Invalid quantity! Enter a proper amount (max %d gal): ", maxLimit);
                            } else if ((fuelChoice == 1 && fuelAmount > regularStock) ||
                                    (fuelChoice == 2 && fuelAmount > premiumStock) ||
                                    (fuelChoice == 3 && fuelAmount > dieselStock) ||
                                    (fuelAmount > maxLimit)) {
                                printf("Invalid quantity! Enter a proper amount (max %d gal): ", maxLimit);
                            } else {
                                break; 
                            }
                        } while (1);

                        // ===== Vehicle Choice =====
                        int cancelTransaction = 0;   
                        do {
                            printf("\nSelect Vehicle type:\n");
                            printf("1. Motorcycle (2%% state fuel tax)\n");
                            printf("2. Car (3%% state fuel tax)\n");
                            printf("3. Truck (1%% state fuel tax)\n");
                            printf("Vehicle Choice: ");
                            scanf(" %d", &vehicleChoice);
                            
                            if (vehicleChoice < 1 || vehicleChoice > 3) {
                                printf("Invalid choice. Please try again.\n\n");
                            } 
                            else {
                                // Compatibility rules
                                if (vehicleChoice == 1 && fuelChoice == 3) {  
                                    printf("Invalid combination! Motorcycles cannot use diesel fuel.\n");
                                    printf("Please select gasoline fuel for your motorcycle.\n");
                                    vehicleChoice = 0;  
                                }
                                else if (vehicleChoice == 2 && fuelChoice == 3) {
                                    int confirmDiesel;
                                    printf("\nNote: Most cars use gasoline. Are you sure this car uses diesel? (1=Yes, 0=No): ");
                                    scanf("%d", &confirmDiesel);

                                    if (confirmDiesel == 0) {
                                        printf("\nPlease select gasoline fuel for your car.\n");
                                        cancelTransaction = 1;  
                                        break;                   
                                    }
                                }
                                else if (vehicleChoice == 3 && fuelChoice != 3) {  
                                    printf("\nInvalid combination! Trucks must use Diesel fuel.\n");
                                    vehicleChoice = 0;  
                                }
                            }
                        } while (vehicleChoice < 1 || vehicleChoice > 3);

                        // If transaction was cancelled, skip rest and go back to menu
                        if (cancelTransaction) {
                            break;   // exits customer logic ? goes back to DAILY OPERATIONS menu
                        }

                        // ===== Loyalty Choice =====
                        do {
                            printf("Is customer a loyalty member? (1=Yes, 0=No): ");
                            scanf(" %d", &loyaltyChoice);
                            

                            if (loyaltyChoice != 0 && loyaltyChoice != 1) {
                                printf("Invalid choice. Please enter 1 or 0.\n\n");
                            }
                        } while (loyaltyChoice != 0 && loyaltyChoice != 1);

                        // ==== Calculations ====
                        float fuelPrices[3] = {regularPrice, premiumPrice, dieselPrice};
                        float fuelPrice = fuelPrices[fuelChoice - 1];

                        float baseCost = fuelAmount * fuelPrice;
                        float taxRates[3] ={0.02, 0.03, 0.01};
                        float stateTax = baseCost * taxRates[vehicleChoice - 1];
                        
                        bulkDiscount = 0.0;
                        if(fuelAmount >= 50) bulkDiscount = (baseCost + stateTax) * 0.10;
                        else if(fuelAmount >= 30) bulkDiscount = (baseCost + stateTax) * 0.05;

                        loyaltyDiscount = 0.0;   
                        if(loyaltyChoice == 1){
                            loyaltyDiscount = (baseCost + stateTax - bulkDiscount) * 0.02;
                        }

                        float totalPayable = baseCost + stateTax - bulkDiscount - loyaltyDiscount;

                        if(vehicleChoice == 1) motorcycleCount++;
                        else if(vehicleChoice == 2) carCount++;
                        else truckCount++;

                        if (fuelChoice == 1) regularStock -= fuelAmount;
                        else if (fuelChoice == 2) premiumStock -= fuelAmount;
                        else dieselStock -= fuelAmount;

                        //Summary 
                        totalCustomers++;
                        totalFuelSold += fuelAmount;
                        totalRevenue += baseCost;
                        totalStateTax += stateTax;
                        totalDiscounts += (bulkDiscount + loyaltyDiscount);
                        totalCustomerPayments += totalPayable;
                        stationNetIncome = totalCustomerPayments - totalStateTax;
                        
                        printf("\n==========================================\n");
                        printf("           FUEL RECEIPT #%03d\n", customerNumber);
                        printf("==========================================\n");
                        printf(" Fuel Type    : %s\n", (fuelChoice==1?"Regular Gas":fuelChoice==2?"Premium Gas":"Diesel"));
                        printf(" Vehicle Type : %s\n", (vehicleChoice==1?"Motorcycle":vehicleChoice==2?"Car":"Truck"));
                        printf(" Quantity     : %.2f   gal\n", (float)fuelAmount);
                        printf(" Rate         : $%.2f  /gal\n", fuelPrice);
                        printf(" Loyalty      : %s\n", (loyaltyChoice==1?"Yes":"No"));
                        printf("==========================================\n");
                        printf(" Base Cost    : $%.2f\n", baseCost);
                        printf(" State Tax    : $%.2f\n", stateTax);
                        if(bulkDiscount > 0) printf(" Bulk Discount: -$%.2f\n", bulkDiscount);
                        if(loyaltyDiscount > 0) printf(" Loyalty Disc.: -$%.2f\n", loyaltyDiscount);
                        printf("==========================================\n");
                        printf(" TOTAL PAYABLE: $%.2f\n", totalPayable);
                        printf("==========================================\n");
                        printf("Transaction completed successfully!\n");
                        customerNumber++;
                        
                        // ===== STOCK ALERTS AFTER RECEIPT =====

                        if (regularStock < 200.0) {
                            if (regularStock < 50.0) {
                                printf("*** CRITICAL ALERT: Emergency fuel stock level! ***\n");
                            } else {
                                printf("*** LOW STOCK WARNING ***\n");
                            }
                            printf("   Regular Gas: %.1f gal remaining\n", regularStock);
                        }

                        if (premiumStock < 200.0) {
                            if (premiumStock < 50.0) {
                                printf("*** CRITICAL ALERT: Emergency fuel stock level! ***\n");
                            } else {
                                printf("*** LOW STOCK WARNING ***\n");
                            }
                            printf("   Premium Gas: %.1f gal remaining\n", premiumStock);
                        }

                        if (dieselStock < 200.0) {
                            if (dieselStock < 50.0) {
                                printf("*** CRITICAL ALERT: Emergency fuel stock level! ***\n");
                            } else {
                                printf("*** LOW STOCK WARNING ***\n");
                            }
                            printf("   Diesel      : %.1f gal remaining\n", dieselStock);
                        }


                  } else if (subChoice == 2) {
                    // ====== Print Daily Summary ======
                    printf("\n==========================================\n");
                    printf("          CURRENT DAY SUMMARY         \n");
                    printf("==========================================\n");
                    printf(" Total Customers    : %-10d\n", totalCustomers);
                    printf(" Total Fuel Sold    : %-8.1f gal\n", totalFuelSold);
                    printf(" Sales Revenue      : $%-10.2f\n", totalRevenue);
                    printf(" State Tax Collected: $%-10.2f\n", totalStateTax);
                    printf(" Total Discounts    : $%-10.2f\n", totalDiscounts);
                    printf(" Customer Payments  : $%-10.2f\n", totalCustomerPayments);
                    printf(" Station Net Income : $%-10.2f\n", stationNetIncome);
                    printf("==========================================\n");
                    printf(" Vehicle Distribution:                \n");
                    printf(" Motorcycles        : %-10d\n", motorcycleCount);
                    printf(" Cars               : %-10d\n", carCount);
                    printf(" Trucks             : %-10d\n", truckCount);
                    if (totalCustomers > 0) {
                        printf("==========================================\n");
                        printf(" Average Payment    : $%-10.2f\n", totalCustomerPayments / totalCustomers);
                        printf(" Avg Fuel/Customer  : %-8.2f gal\n", totalFuelSold / totalCustomers);
                    }
                    printf("==========================================\n");
                } else if (subChoice == 3) {
                    break;  
                } else {
                    printf("Invalid option! Please try again.\n");
                }
                }
                break; 

            case 2: {
                int stationChoice;
                do {
                    printf("\n========= STATION MANAGEMENT =========\n");
                    printf("1. Fuel Inventory Status\n");
                    printf("2. Return to Main Menu\n");
                    printf("======================================\n");
                    printf("Choice: ");
                    scanf("%d", &stationChoice);

                    switch (stationChoice) {
                        case 1:
                            printf("\n==========================================\n");
                            printf("          FUEL INVENTORY STATUS\n");
                            printf("==========================================\n");
                            printf(" Stock Status Thresholds:\n");
                            printf("  CRITICAL: < 50 gallons\n");
                            printf("  LOW: < 200 gallons\n");
                            printf("  NORMAL: >= 200 gallons\n");
                            printf("==========================================\n");

                            printf(" REGULAR GAS:\n");
                            printf("  Current Stock : %.1f gal\n", regularStock);
                            printf("  Sold Today    : %.1f gal\n", 1000.0 - regularStock);  
                            printf("  Stock Status  : %s\n", getStockStatus(regularStock));
                            printf("==========================================\n");

                            printf(" PREMIUM GAS:\n");
                            printf("  Current Stock : %.1f gal\n", premiumStock);
                            printf("  Sold Today    : %.1f gal\n", 1000.0 - premiumStock);
                            printf("  Stock Status  : %s\n", getStockStatus(premiumStock));
                            printf("==========================================\n");

                            printf(" DIESEL:\n");
                            printf("  Current Stock : %.1f gal\n", dieselStock);
                            printf("  Sold Today    : %.1f gal\n", 1000.0 - dieselStock);
                            printf("  Stock Status  : %s\n", getStockStatus(dieselStock));
                            printf("==========================================\n");
                            break;

                        case 2:
                            break;

                        default:
                            printf("Invalid choice! Try again.\n");
                            break;
                    }
                } while (stationChoice != 2);
                break;
            }


            case 3: {
                int confirmExit;
                printf("Are you sure you want to exit? (1=Yes, 0=No): ");
                scanf("%d", &confirmExit);

                if (confirmExit == 1) {
                    printf("\n==========================================\n");
                    printf(" Thank you for using TurboFill Fuel Station!\n");
                    printf("            System Exiting...\n");
                    printf("==========================================\n");
                    exit(0);
                } else {
                    printf("Exit canceled. Returning to main menu...\n");
                }
                break;
            }
        }
    }
    return 0;
}

