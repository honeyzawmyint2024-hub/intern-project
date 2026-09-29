#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cctype>
using namespace std;


class Patient3 {
private:
    string PatientID;
    int age;
    string careTypes;
    double lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;

public:
    // consturctor
    Patient3(string id = "", int a = 0, string care = "", double duration = 0.0,
        double rate = 0.0, int visits = 0)
        : PatientID(id), age(a), careTypes(care),
        lengthOfStay(duration), baseCostPerHour(rate), daysVisitsPerYear(visits) {
    }


    // getters
    string getPatientID() const { return PatientID; }
    int getAge() const { return age; }
    string getCareType() const { return careTypes; }
    double getLengthOfStay() const { return lengthOfStay; }
    double getBaseCostPerHour() const { return baseCostPerHour; }
    int getDaysVisitsPerYear() const { return daysVisitsPerYear; }

    double calculateTotalCost() const {
        return lengthOfStay * baseCostPerHour * daysVisitsPerYear;
    }



};

class ArrayPatientList3 {
private:
    Patient3 patients[201];
    int count;


public:
    ArrayPatientList3() : count(0) {}

    void addPatient(Patient3 p) {
        if (count < 201) {
            patients[count] = p;
            count++;
        }
    }

    int getCount() const { return count; }
    bool isFull() const { return count >= 201; }
    bool isEmpty() const { return count == 0; }

    // changing to lower case

    string toLowerCase(string s) const {
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    // display all

    void displayAll() const {
        cout << left
            << setw(10) << "PatientID"
            << setw(6) << "Age"
            << setw(18) << "CareType"
            << setw(10) << "Duration"
            << setw(10) << "Rate/hr"
            << setw(10) << "Visits"
            << right << setw(14) << "TotalCost"
            << endl;

        cout << string(78, '-') << endl;

        cout << fixed << setprecision(2);
        for (int i = 0; i < count; i++) {
            cout << left
                << setw(10) << patients[i].getPatientID()
                << setw(6) << patients[i].getAge()
                << setw(18) << patients[i].getCareType()
                << setw(10) << patients[i].getLengthOfStay()
                << setw(10) << patients[i].getBaseCostPerHour()
                << setw(10) << patients[i].getDaysVisitsPerYear()
                << right << setw(14) << patients[i].calculateTotalCost()
                << endl;
        }

        cout << string(78, '-') << endl;
    }

    // average cost per patient

    double getAverageCostPerPatient(int minAge, int maxAge) const {
        double total = 0.0;
        int patientCount = 0;

        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                total += patients[i].calculateTotalCost();
                patientCount++;
            }
        }

        if (patientCount == 0) return 0.0;
        return total / patientCount;
    }

    // total cost by care type

    double getTotalCostByCareType(string careType) const {
        double total = 0.0;

        for (int i = 0; i < count; i++) {
            if (patients[i].getCareType() == careType) {
                total += patients[i].calculateTotalCost();
            }
        }
        return total;
    }

    // total bill for data set

    double getTotalBillingForDataset() const {
        double total = 0.0;

        for (int i = 0; i < count; i++) {
            total += patients[i].calculateTotalCost();
        }
        return total;
    }

    // most prefered care type

    string getMostPreferredCareType(int minAge, int maxAge) const {
        string careTypeNames[6] = { "Emergency", "Outpatient", "Inpatient",
                                     "Vaccination", "Rehabilitation", "Routine Checkup" };
        int careTypeCounts[6] = { 0, 0, 0, 0, 0, 0 };

        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                for (int j = 0; j < 6; j++) {
                    if (patients[i].getCareType() == careTypeNames[j]) {
                        careTypeCounts[j]++;
                    }
                }
            }
        }

        // Find which index has the highest count
        int maxIndex = 0;
        for (int j = 1; j < 6; j++) {
            if (careTypeCounts[j] > careTypeCounts[maxIndex]) {
                maxIndex = j;
            }
        }

        return careTypeNames[maxIndex];
    }

    // section - 4 Patient Demographic & Billing Categorization 

    int getPatientCountInAgeGroup(int minAge, int maxAge) const {
        int patientCount = 0;
        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                patientCount++;
            }
        }
        return patientCount;
    }

    double getTotalCostInAgeGroup(int minAge, int maxAge) const {
        double totalCost = 0.0;
        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                totalCost += patients[i].calculateTotalCost();
            }
        }
        return totalCost;
    }

    int getPatientCountInAgeGroupByCareType(int minAge, int maxAge, string careType) const {
        int patientCount = 0;
        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge
                && patients[i].getCareType() == careType) {
                patientCount++;
            }
        }
        return patientCount;
    }

    double getTotalCostInAgeGroupByCareType(int minAge, int maxAge, string careType) const {
        double totalCost = 0.0;
        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge
                && patients[i].getCareType() == careType) {
                totalCost += patients[i].calculateTotalCost();
            }
        }
        return totalCost;
    }

    void showAgeGroupReport() const {
        int ranges[5][2] = {
            {0, 17}, {18, 25}, {26, 45}, {46, 60}, {61, 100}
        };
        string labels[5] = {
            "0-17 (Pediatrics & Adolescents)",
            "18-25 (Young Adults / University Students)",
            "26-45 (Working Adults - Early Career)",
            "46-60 (Working Adults - Late Career)",
            "61-100 (Senior Citizens / Geriatric Care)"
        };
        string careTypeNames[4] = { "Outpatient", "Inpatient", "Vaccination", "Routine Checkup" };

        cout << fixed << setprecision(2);

        for (int g = 0; g < 5; g++) {
            int minAge = ranges[g][0];
            int maxAge = ranges[g][1];

            cout << "\nAge Group: " << labels[g] << endl;
            cout << string(78, '-') << endl;
            cout << left << setw(18) << "Care Type"
                << setw(16) << "Patient Count"
                << setw(16) << "Total Cost ($)"
                << "Average Cost per Patient ($)" << endl;
            cout << string(78, '-') << endl;

            for (int c = 0; c < 4; c++) {
                int pCount = getPatientCountInAgeGroupByCareType(minAge, maxAge, careTypeNames[c]);
                double pTotal = getTotalCostInAgeGroupByCareType(minAge, maxAge, careTypeNames[c]);
                double pAvg = (pCount == 0) ? 0.0 : pTotal / pCount;

                cout << left << setw(18) << careTypeNames[c]
                    << setw(16) << pCount
                    << setw(16) << pTotal
                    << pAvg << endl;
            }

            cout << string(78, '-') << endl;
            cout << "Total Billing for Age Group: $"
                << getTotalCostInAgeGroup(minAge, maxAge) << endl;
            cout << "Most Preferred Care Type: "
                << getMostPreferredCareType(minAge, maxAge) << endl;
            cout << string(78, '-') << "\n" << endl;
        }
    }

    // section - 5 
    // b
    void showCareTypeBillingReport() const {
        string careTypeNames[4] = { "Outpatient", "Inpatient", "Vaccination", "Routine Checkup" };

        cout << fixed << setprecision(2);
        cout << "\nMedical Costs Grouped by Care Type (Facility C - Dataset 3)" << endl;
        cout << string(50, '-') << endl;
        cout << left << setw(20) << "Care Type"
            << right << setw(15) << "Total Cost ($)" << endl;
        cout << string(50, '-') << endl;

        for (int c = 0; c < 4; c++) {
            double typeTotal = getTotalCostByCareType(careTypeNames[c]);
            cout << left << setw(20) << careTypeNames[c]
                << right << setw(15) << typeTotal << endl;
        }

        cout << string(50, '-') << endl;
        cout << left << setw(20) << "TOTAL BILLING"
            << right << setw(15) << getTotalBillingForDataset() << endl;
        cout << string(50, '-') << endl;
    }

    // c

    double getAverageDuration(int minAge, int maxAge) const {
        double totalDuration = 0.0;
        int patientCount = 0;

        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                totalDuration += patients[i].getLengthOfStay();
                patientCount++;
            }
        }

        if (patientCount == 0) return 0.0;
        return totalDuration / patientCount;
    }

    // section - 6 sorting experiment
    // Merge sort

    void merge(int low, int mid, int high) {
        int leftSize = mid - low + 1;
        int rightSize = high - mid;

        Patient3* leftArr = new Patient3[leftSize];
        Patient3* rightArr = new Patient3[rightSize];

        for (int i = 0; i < leftSize; i++) leftArr[i] = patients[low + i];
        for (int i = 0; i < rightSize; i++) rightArr[i] = patients[mid + 1 + i];

        int i = 0, j = 0, k = low;

        while (i < leftSize && j < rightSize) {
            if (leftArr[i].getCareType() <= rightArr[j].getCareType()) {
                patients[k] = leftArr[i];
                i++;
            }
            else {
                patients[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < leftSize) { patients[k] = leftArr[i]; i++; k++; }
        while (j < rightSize) { patients[k] = rightArr[j]; j++; k++; }

        delete[] leftArr;
        delete[] rightArr;
    }

    void mergeSort(int low, int high) {
        if (low < high) {
            int mid = (low + high) / 2;
            mergeSort(low, mid);
            mergeSort(mid + 1, high);
            merge(low, mid, high);
        }
    }

    void sortByCareType() {
        auto start = chrono::high_resolution_clock::now();

        mergeSort(0, count - 1);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "sortByCareType() (Merge Sort) took: " << duration.count() << " microseconds" << endl;
    }

    // Insertion sort

    long long sortByTotalCost() {
        auto start = chrono::high_resolution_clock::now();

        for (int i = 1; i < count; i++) {
            Patient3 key = patients[i];
            int j = i - 1;

            while (j >= 0 && patients[j].calculateTotalCost() > key.calculateTotalCost()) {
                patients[j + 1] = patients[j];
                j--;
            }

            patients[j + 1] = key;
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "sortByTotalCost() (Insertion Sort) took: " << duration.count() << " microseconds" << endl;
        return duration.count();
    }

    // section - 7 searching experiment
    // Linear search (unsorded data)

    long long linearSearchByTotalCost(double targetCost) const {
        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < count; i++) {
            if (patients[i].calculateTotalCost() == targetCost) {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Found: " << patients[i].getPatientID() << endl;
                cout << "linearSearchByTotalCost() took: " << duration.count() << " microseconds" << endl;
                return duration.count();
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Not found." << endl;
        cout << "linearSearchByTotalCost() took: " << duration.count() << " microseconds" << endl;
        return duration.count();
    }

    long long linearSearchByCareType(string targetCareType) const {
        auto start = chrono::high_resolution_clock::now();
        string targetLower = toLowerCase(targetCareType);

        for (int i = 0; i < count; i++) {
            if (toLowerCase(patients[i].getCareType()) == targetLower) {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Found: " << patients[i].getPatientID() << endl;
                cout << "linearSearchByCareType() took: " << duration.count() << " microseconds" << endl;
                return duration.count();
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Not found." << endl;
        cout << "linearSearchByCareType() took: " << duration.count() << " microseconds" << endl;
        return duration.count();
    }

    // binary search (sorted data by insertion/ counting sort)

    long long binarySearchByTotalCost(double targetCost) const {
        auto start = chrono::high_resolution_clock::now();

        int low = 0;
        int high = count - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (patients[mid].calculateTotalCost() == targetCost) {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Found: " << patients[mid].getPatientID() << endl;
                cout << "binarySearchByTotalCost() took: " << duration.count() << " microseconds" << endl;
                return duration.count();
            }
            else if (patients[mid].calculateTotalCost() < targetCost) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Not found!" << endl;
        cout << "binarySearchByTotalCost() took: " << duration.count() << " microseconds" << endl;
        return duration.count();
    }

    long long BinarySearchByCareType(string targetCareType) const {
        auto start = chrono::high_resolution_clock::now();
        string targetLower = toLowerCase(targetCareType);

        int low = 0;
        int high = count - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            string midLower = toLowerCase(patients[mid].getCareType());

            if (midLower == targetLower) {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Found: " << patients[mid].getPatientID() << endl;
                cout << "binarySearchByCareType() took: " << duration.count() << " microseconds" << endl;
                return duration.count();
            }
            else if (midLower < targetLower) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Not found!" << endl;
        cout << "binarySearchByCareType() took: " << duration.count() << " microseconds" << endl;
        return duration.count();
    }

    // print out for care type

    void compareCareTypeSearch(string targetCareType) {
    
        cout << "\nSearch Performance Report (Care Type = " << targetCareType << ")" << endl;
        cout << "\n--- Linear Search (Unsorted Data) ---" << endl;
        long long linearTime = linearSearchByCareType(targetCareType);

        sortByCareType();  // binary search requires data sorted by care type first (merge sort)

        cout << "\n--- Binary Search (Sorted Data) ---" << endl;
        long long binaryTime = BinarySearchByCareType(targetCareType);

        if (binaryTime < linearTime) {
            cout << "Binary search was faster by " << (linearTime - binaryTime) << " microseconds." << endl;
        }
        else if (linearTime < binaryTime) {
            cout << "Linear search was faster by " << (binaryTime - linearTime) << " microseconds." << endl;
        }
        else {
            cout << "Both methods took the same time." << endl;
        }
    }


    // compare total cost 

    void compareTotalCostSearch(double targetCost) {
        cout << "\n=== Searching for patients with Total Cost = " << targetCost << " ===" << endl;

        cout << "\n--- Linear Search (Unsorted Data) ---" << endl;
        long long linearTime = linearSearchByTotalCost(targetCost);

        sortByTotalCost();  // binary search requires data sorted by total cost first (insertion sort)

        cout << "\n--- Binary Search (Sorted Data) ---" << endl;
        long long binaryTime = binarySearchByTotalCost(targetCost);

        if (binaryTime < linearTime) {
            cout << "Binary search was faster by " << (linearTime - binaryTime) << " microseconds." << endl;
        }
        else if (linearTime < binaryTime) {
            cout << "Linear search was faster by " << (binaryTime - linearTime) << " microseconds." << endl;
        }
        else {
            cout << "Both methods took the same time." << endl;
        }
    }

    // 8 a
    void showMemoryFootprint() const {
        size_t usedMemory = count * sizeof(Patient3);
        size_t allocatedMemory = 201 * sizeof(Patient3);   // fixed capacity, always 201
        size_t wastedMemory = allocatedMemory - usedMemory;

        cout << "\nMemory Footprint (Array - Dataset 3)" << endl;
        cout << string(50, '-') << endl;
        cout << left << setw(25) << "Size of one Patient3" << right << setw(15) << sizeof(Patient3) << " bytes" << endl;
        cout << left << setw(25) << "Patients stored (count)" << right << setw(15) << count << endl;
        cout << left << setw(25) << "Fixed array capacity" << right << setw(15) << 201 << endl;
        cout << left << setw(25) << "Memory used" << right << setw(15) << usedMemory << " bytes" << endl;
        cout << left << setw(25) << "Memory allocated" << right << setw(15) << allocatedMemory << " bytes" << endl;
        cout << left << setw(25) << "Wasted (unused) memory" << right << setw(15) << wastedMemory << " bytes" << endl;
        cout << string(50, '-') << endl;
    }

    // choose action
    int chooseActionDataset3() {
        int choice;
        while (true) {
            cout << "\n=== Select Action (Facility C) ===\n";
            cout << "1. Display All\n";
            cout << "2. Sort by Total Cost (Insertion Sort)\n";
            cout << "3. Sort by Care Type (Merge Sort)\n";
            cout << "4. Compare Search by Care Type (Linear vs Binary)\n";
            cout << "5. Compare Search by Total Cost (Linear vs Binary)\n";
            cout << "6. Age Group Report (Task 4)\n";
            cout << "7. Care Type Billing Report (Task 5b)\n";
            cout << "8. Show Overall Analysis (Total Billing)\n";
            cout << "9. Show Memory Footprint (Task 8a)\n";
            cout << "10. Back to Dataset Menu\n";
            cout << "Choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            if (choice < 1 || choice > 10) {
                cout << "Invalid choice! Please enter 1-9.\n";
                continue;
            }
            return choice;
        }
    }
};



void loadDataset3(ArrayPatientList3& dataset3) {
    ifstream file("dataset3.csv");
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, ageStr, careTypeStr, durationStr, rateStr, visitsStr;

        getline(ss, idStr, ',');
        getline(ss, ageStr, ',');
        getline(ss, careTypeStr, ',');
        getline(ss, durationStr, ',');
        getline(ss, rateStr, ',');
        getline(ss, visitsStr, ',');

        int age = stoi(ageStr);
        double duration = stod(durationStr);
        double rate = stod(rateStr);
        int visits = stoi(visitsStr);


        Patient3 p(idStr, age, careTypeStr, duration, rate, visits);
        dataset3.addPatient(p);
    }



};



