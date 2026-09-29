#include "Dataset1.h"
#include "Dataset2.h"
#include "Dataset3.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;


bool login() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        return true;
    }
    else {
        cout << "Access denied." << endl;
        return false;
    }
}

// combine all data set

void showTotalBillingReport(ArrayPatientList1& dataset1, ArrayPatientList2& dataset2, ArrayPatientList3& dataset3) {
    cout << fixed << setprecision(2);
    cout << "\n=== Total Medical Billing Per Dataset (Task 5a) ===\n";
    cout << string(50, '-') << endl;
    cout << left << setw(20) << "Facility" << right << setw(20) << "Total Cost ($)" << endl;
    cout << string(50, '-') << endl;
    cout << left << setw(20) << "Facility A" << right << setw(20) << dataset1.getTotalBillingForDataset() << endl;
    cout << left << setw(20) << "Facility B" << right << setw(20) << dataset2.getTotalBillingForDataset() << endl;
    cout << left << setw(20) << "Facility C" << right << setw(20) << dataset3.getTotalBillingForDataset() << endl;
    cout << string(50, '-') << endl;
}

void showCombinedDemographicReport(ArrayPatientList1& dataset1, ArrayPatientList2& dataset2, ArrayPatientList3& dataset3) {
    int ranges[5][2] = { {0,17}, {18,25}, {26,45}, {46,60}, {61,100} };
    string labels[5] = { "0-17", "18-25", "26-45", "46-60", "61-100" };

    cout << fixed << setprecision(2);
    cout << "\n=== Combined Patient Demographic & Billing Report (Task 4) ===\n";
    cout << string(70, '-') << endl;
    cout << left << setw(12) << "AgeGroup"
        << setw(12) << "Patients"
        << setw(16) << "Total Cost ($)"
        << "Avg Cost/Patient ($)" << endl;
    cout << string(70, '-') << endl;

    for (int g = 0; g < 5; g++) {
        int minAge = ranges[g][0];
        int maxAge = ranges[g][1];

        int totalPatients = dataset1.getPatientCountInAgeGroup(minAge, maxAge)
            + dataset2.getPatientCountInAgeGroup(minAge, maxAge)
            + dataset3.getPatientCountInAgeGroup(minAge, maxAge);

        double totalCost = dataset1.getTotalCostInAgeGroup(minAge, maxAge)
            + dataset2.getTotalCostInAgeGroup(minAge, maxAge)
            + dataset3.getTotalCostInAgeGroup(minAge, maxAge);

        double avgCost = (totalPatients == 0) ? 0.0 : totalCost / totalPatients;

        cout << left << setw(12) << labels[g]
            << setw(12) << totalPatients
            << setw(16) << totalCost
            << avgCost << endl;
    }
    cout << string(70, '-') << endl;
}

void showExpenditureDurationComparison(ArrayPatientList1& dataset1, ArrayPatientList2& dataset2, ArrayPatientList3& dataset3) {
    int ranges[5][2] = { {0,17}, {18,25}, {26,45}, {46,60}, {61,100} };
    string labels[5] = { "0-17", "18-25", "26-45", "46-60", "61-100" };

    cout << fixed << setprecision(2);
    cout << "\n=== Expenditure Comparison Across Datasets (Task 5c) ===\n";
    cout << string(90, '-') << endl;
    cout << left << setw(12) << "AgeGroup"
        << setw(13) << "A-Cost($)" << setw(11) << "A-Dur(hrs)"
        << setw(13) << "B-Cost($)" << setw(11) << "B-Dur(hrs)"
        << setw(13) << "C-Cost($)" << setw(11) << "C-Dur(hrs)" << endl;
    cout << string(90, '-') << endl;

    for (int g = 0; g < 5; g++) {
        int minAge = ranges[g][0];
        int maxAge = ranges[g][1];

        cout << left << setw(12) << labels[g]
            << setw(13) << dataset1.getTotalCostInAgeGroup(minAge, maxAge)
            << setw(11) << dataset1.getAverageDuration(minAge, maxAge)
            << setw(13) << dataset2.getTotalCostInAgeGroup(minAge, maxAge)
            << setw(11) << dataset2.getAverageDuration(minAge, maxAge)
            << setw(13) << dataset3.getTotalCostInAgeGroup(minAge, maxAge)
            << setw(11) << dataset3.getAverageDuration(minAge, maxAge)
            << endl;
    }
    cout << string(90, '-') << endl;
}

// 9 a
void comparePreferredCareType(ArrayPatientList1& dataset1, ArrayPatientList2& dataset2, ArrayPatientList3& dataset3) {
    int ranges[5][2] = { {0, 17}, {18, 25}, {26, 45}, {46, 60}, {61, 100} };
    string labels[5] = { "0-17", "18-25", "26-45", "46-60", "61-100" };

    cout << "\n=== Cross-Dataset Comparison: Preferred Care Type by Age Group ===" << endl;
    cout << string(70, '-') << endl;
    cout << left << setw(12) << "Age Group"
        << setw(18) << "Facility A" << setw(18) << "Facility B" << "Facility C" << endl;
    cout << string(70, '-') << endl;

    for (int g = 0; g < 5; g++) {
        int minAge = ranges[g][0];
        int maxAge = ranges[g][1];

        cout << left << setw(12) << labels[g]
            << setw(18) << dataset1.getMostPreferredCareType(minAge, maxAge)
            << setw(18) << dataset2.getMostPreferredCareType(minAge, maxAge)
            << dataset3.getMostPreferredCareType(minAge, maxAge) << endl;
    }
    cout << string(70, '-') << endl;
}

// 9 b
void showClinicalInsights(ArrayPatientList1& dataset1, ArrayPatientList2& dataset2, ArrayPatientList3& dataset3) {
    int ranges[5][2] = {
        {0, 17}, {18, 25}, {26, 45}, {46, 60}, {61, 100}
    };
    string labels[5] = {
        "0-17", "18-25", "26-45", "46-60", "61-100"
    };
    string careTypeNames[6] = { "Emergency", "Outpatient", "Inpatient",
                                 "Vaccination", "Rehabilitation", "Routine Checkup" };

    cout << fixed << setprecision(2);
    cout << "\n=== Clinical Insights ===" << endl;

    // Find highest-billing age group (summed across all 3 datasets)
    double highestCost = -1.0;
    string highestAgeGroup;

    for (int g = 0; g < 5; g++) {
        int minAge = ranges[g][0];
        int maxAge = ranges[g][1];
        double totalCost = dataset1.getTotalCostInAgeGroup(minAge, maxAge)
            + dataset2.getTotalCostInAgeGroup(minAge, maxAge)
            + dataset3.getTotalCostInAgeGroup(minAge, maxAge);

        if (totalCost > highestCost) {
            highestCost = totalCost;
            highestAgeGroup = labels[g];
        }
    }

    cout << "Highest Healthcare Billing Age Group: " << highestAgeGroup
        << " (Total: $" << highestCost << ")" << endl;

    // Find highest-traffic care type (summed across all 3 datasets)
    int highestTraffic = -1;
    string highestCareType;

    for (int c = 0; c < 6; c++) {
        int countA = dataset1.getPatientCountInAgeGroupByCareType(0, 100, careTypeNames[c]);
        int countB = dataset2.getPatientCountInAgeGroupByCareType(0, 100, careTypeNames[c]);
        int countC = dataset3.getPatientCountInAgeGroupByCareType(0, 100, careTypeNames[c]);
        int totalPatients = countA + countB + countC;

        if (totalPatients > highestTraffic) {
            highestTraffic = totalPatients;
            highestCareType = careTypeNames[c];
        }
    }

    cout << "Highest Patient Traffic Care Type: " << highestCareType
        << " (" << highestTraffic << " patients across all facilities)" << endl;
}

// choose dataset

int chooseDataset() {
    int choice;
    while (true) {
        cout << "\n=== Select Dataset ===\n";
        cout << "1. Facility A\n2. Facility B\n3. Facility C\n4. All Combined\n5. Exit Program\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid choice! Please enter 1-5.\n";
            continue;
        }

        return choice;
    }
}

// main program

int main() {
    if (!login()) {
        return 0;
    }

    ArrayPatientList1 dataset1;
    loadDataset1(dataset1);

    ArrayPatientList2 dataset2;
    loadDataset2(dataset2);

    ArrayPatientList3 dataset3;
    loadDataset3(dataset3);

    bool exitProgram = false;
    while (!exitProgram) {
        int datasetChoice = chooseDataset();

        if (datasetChoice == 5) {
            exitProgram = true;
        }
        // data set 1
        else if (datasetChoice == 1) {
            bool backToDatasetMenu = false;
            while (!backToDatasetMenu) {
                int actionChoice = dataset1.chooseActionDataset1();

                switch (actionChoice) {
                case 1:
                    dataset1.displayAll();
                    break;
                case 2:
                    dataset1.sortByVisitDuration();
                    dataset1.displayAll();
                    break;
                case 3: {
                    dataset1.sortByAge();
                    dataset1.displayAll();
                    break;
                }
                case 4: {
                    double target;
                    char mode;
                    cout << "Enter duration to search: ";
                    cin >> target;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\n";
                        break;
                    }
                    cout << "Comparison type (=, >, <): ";
                    cin >> mode;
                    dataset1.compareDurationThresholdSearch(target, mode);
                    break;
                }
                case 5: {
                    int minAge, maxAge;
                    cout << "Enter min age: ";
                    cin >> minAge;
                    cout << "Enter max age: ";
                    cin >> maxAge;
                    dataset1.compareAgeGroupSearch(minAge, maxAge);
                    break;
                }
                case 6:
                    dataset1.showAgeGroupReport();
                    break;
                case 7:
                    cout << "Total Billing: " << dataset1.getTotalBillingForDataset() << endl;
                    break;
                case 8:
                    dataset1.showMemoryFootprint();
                    break;
                case 9:
                    backToDatasetMenu = true;
                    break;
                }
            }
        }
        // data set 2
        else if (datasetChoice == 2) {
            bool backToDatasetMenu = false;
            while (!backToDatasetMenu) {
                int actionChoice = dataset2.chooseActionDataset2();

                switch (actionChoice) {
                case 1:
                    dataset2.displayAll();
                    break;
                case 2: {
                    double target;
                    cout << "Enter Total Cost to search: ";
                    cin >> target;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\n";
                        break;
                    }
                    dataset2.compareTotalCostSearch(target);
                    break;
                }
                case 3:
                    dataset2.showAgeGroupReport();
                    break;
                case 4:
                    cout << "Total Billing: " << dataset2.getTotalBillingForDataset() << endl;
                    break;
                case 5:
                    dataset2.showMemoryFootprint();
                    break;
                case 6:
                    dataset2.addPatientFromInput(dataset2);
                    break;
                case 7:
                    backToDatasetMenu = true;
                    break;
                }
            }
        }
        else if (datasetChoice == 3) {
            bool backToDatasetMenu = false;
            while (!backToDatasetMenu) {
                int actionChoice = dataset3.chooseActionDataset3();

                switch (actionChoice) {
                case 1:
                    dataset3.displayAll();
                    break;
                case 2:
                    dataset3.sortByTotalCost();
                    dataset3.displayAll();
                    break;
                case 3: {
                    dataset3.sortByCareType();
                    dataset3.displayAll();
                    break;
                }
                case 4: {
                    string type;
                    cout << "Enter Care Type: ";
                    cin >> type;
                    dataset3.compareCareTypeSearch(type);
                    break;
                }
                case 5: {
                    double targetCost;
                    cout << "Enter Total Cost: ";
                    cin >> targetCost;
                    dataset3.compareTotalCostSearch(targetCost);
                    break;
                }
                case 6:
                    dataset3.showAgeGroupReport();
                    break;
                case 7:
                    dataset3.showCareTypeBillingReport();
                    break;
                case 8:
                    cout << "Total Billing: " << dataset3.getTotalBillingForDataset() << endl;
                    break;
                case 9:
                    dataset3.showMemoryFootprint();
                    break;
                case 10:
                    backToDatasetMenu = true;
                    break;
                }
            }
        }
        // combine all

        else if (datasetChoice == 4) {
            bool backToDatasetMenu = false;
            while (!backToDatasetMenu) {
                int reportChoice;
                cout << "\n=== All Combined Reports ===\n";
                cout << "1. Total Billing per Dataset\n";
                cout << "2. Combined Demographic & Billing Report\n";
                cout << "3. Expenditure & Duration Comparison\n";
                cout << "4. Compare Preferred CareTypeAcross Datasets\n";
                cout << "5. Show Clinical Insights\n";
                cout << "6. Back to Dataset Menu\n";
                cout << "Choice: ";
                cin >> reportChoice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                switch (reportChoice) {
                case 1:
                    showTotalBillingReport(dataset1, dataset2, dataset3);
                    break;
                case 2:
                    showCombinedDemographicReport(dataset1, dataset2, dataset3);
                    break;
                case 3:
                    showExpenditureDurationComparison(dataset1, dataset2, dataset3);
                    break;
                case 4:
                    comparePreferredCareType(dataset1, dataset2, dataset3);
                    break;
                case 5:
                    showClinicalInsights(dataset1, dataset2, dataset3);
                    break;
                case 6:
                    backToDatasetMenu = true;
                    break;
                default:
                    cout << "Invalid choice. Please enter 1-4.\n";
                }
            }
        }
    }

    cout << "Program exited.\n";
    return 0;
}