#include <iostream>
#include <iomanip>
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

class Patient2 {
private:
    string PatientID;
    int age;
    string careTypes;
    double lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;

public:
    // consturctor
    Patient2(string id = "", int a = 0, string care = "", double duration = 0.0,
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


class ArrayPatientList2 {
private:
    Patient2* patients;
    int count;
    int capacity;

public:
    ArrayPatientList2() {
        capacity = 10;
        patients = new Patient2[capacity];
        count = 0;
    }

    ~ArrayPatientList2() {
        delete[] patients;
    }

    void resize() {
        int newCapacity = capacity * 2;
        Patient2* newArray = new Patient2[newCapacity];

        for (int i = 0; i < count; i++) {
            newArray[i] = patients[i];
        }

        delete[] patients;
        patients = newArray;
        capacity = newCapacity;
    }

    void addPatient(Patient2 p) {
        if (count == capacity) {
            resize();
        }

        // find the correct position to insert p, keeping array sorted by cost
        int insertPos = count;
        while (insertPos > 0 && patients[insertPos - 1].calculateTotalCost() > p.calculateTotalCost()) {
            patients[insertPos] = patients[insertPos - 1];   // shift right
            insertPos--;
        }
        patients[insertPos] = p;
        count++;
    }

    // add patient input
    void addPatientFromInput(ArrayPatientList2& dataset2) {
        string id, careType;
        int age, visits;
        double duration, rate;

        cout << "Patient ID: ";
        cin >> id;
        cout << "Age (0-100): ";
        cin >> age;
        cout << "Care Type (Emergency/Outpatient/Vaccination/Rehabilitation/Routine Checkup): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, careType);
        cout << "Length of stay (hours): ";
        cin >> duration;
        cout << "Base cost per hour: ";
        cin >> rate;
        cout << "Visits per year: ";
        cin >> visits;

        if (cin.fail() || age < 0 || age > 100 || duration < 0 || rate < 0 || visits < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Patient not added.\n";
            return;
        }

        Patient2 p(id, age, careType, duration, rate, visits);
        dataset2.addPatient(p);
        if (appendPatientToCSV("dataset2.csv", p))
            cout << "Patient added and saved to dataset2.csv\n";
    }

    // append 
    bool appendPatientToCSV(const string& filename, Patient2 p) {
        ofstream file(filename, ios::app);      
        if (!file.is_open()) {
            cout << "Error: could not open " << filename << endl;
            return false;
        }
        file << p.getPatientID() << ","
            << p.getAge() << ","
            << p.getCareType() << ","
            << p.getLengthOfStay() << ","
            << p.getBaseCostPerHour() << ","
            << p.getDaysVisitsPerYear() << "\n";
        return true;
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

    // Average cost per patient - for section 4

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

    // total billing for data set 2

    double getTotalBillingForDataset() const {
        double total = 0.0;

        for (int i = 0; i < count; i++) {
            total += patients[i].calculateTotalCost();
        }
        return total;
    }

    // most prefered care type

    string getMostPreferredCareType(int minAge, int maxAge) const {
        string careTypeNames[5] = { "Emergency", "Outpatient", "Vaccination", "Rehabilitation", "Routine Checkup" };
        int careTypeCounts[5] = { 0, 0, 0, 0, 0 };

        for (int i = 0; i < count; i++) {
            if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
                for (int j = 0; j < 5; j++) {
                    if (patients[i].getCareType() == careTypeNames[j]) {
                        careTypeCounts[j]++;
                    }
                }
            }
        }

        // Find which index has the highest count
        int maxIndex = 0;
        for (int j = 1; j < 5; j++) {
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
        int ranges[2][2] = {
            {0, 17}, {18, 25}
        };
        string labels[2] = {
            "0-17 (Pediatrics & Adolescents)",
            "18-25 (Young Adults / University Students)",
        };
        string careTypeNames[5] = { "Emergency", "Outpatient","Vaccination", "Rehabilitation", "Routine Checkup"};

        cout << fixed << setprecision(2);

        for (int g = 0; g < 2; g++) {
            int minAge = ranges[g][0];
            int maxAge = ranges[g][1];

            cout << "\nAge Group: " << labels[g] << endl;
            cout << string(78, '-') << endl;
            cout << left << setw(18) << "Care Type"
                << setw(16) << "Patient Count"
                << setw(16) << "Total Cost ($)"
                << "Average Cost per Patient ($)" << endl;
            cout << string(78, '-') << endl;

            for (int c = 0; c < 5; c++) {
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
        string careTypeNames[5] = { "Emergency", "Outpatient","Vaccination", "Rehabilitation", "Routine Checkup" };

        cout << fixed << setprecision(2);
        cout << "\nMedical Costs Grouped by Care Type (Facility B - Dataset 2)" << endl;
        cout << string(50, '-') << endl;
        cout << left << setw(20) << "Care Type"
            << right << setw(15) << "Total Cost ($)" << endl;
        cout << string(50, '-') << endl;

        for (int c = 0; c < 5; c++) {
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

    // section - 7 searching experiment
    // linear search (sorted data)

    long long LinearSearchByTotalCost(double targetCost) const {
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

    // binary search

    long long BinarySearchByTotalCost(double targetCost) const {
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

    // print out

    void compareTotalCostSearch(double targetCost) {
        cout << "\n=== Searching for patients with total cost = " << targetCost << " ===" << endl;

        cout << "\n--- Linear Search ---" << endl;
        long long linearTime = LinearSearchByTotalCost(targetCost);

        cout << "\n--- Binary Search (data always sorted by cost) ---" << endl;
        long long binaryTime = BinarySearchByTotalCost(targetCost);

        cout << "\nSearch Performance Report (Total Cost = " << targetCost << ")" << endl;
        cout << string(45, '-') << endl;
        cout << left << setw(25) << "Method" << right << setw(20) << "Time (microsec)" << endl;
        cout << string(45, '-') << endl;
        cout << left << setw(25) << "Linear Search" << right << setw(20) << linearTime << endl;
        cout << left << setw(25) << "Binary Search" << right << setw(20) << binaryTime << endl;
        cout << string(45, '-') << endl;

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
        size_t usedMemory = count * sizeof(Patient2);
        size_t allocatedMemory = capacity * sizeof(Patient2);
        size_t wastedMemory = allocatedMemory - usedMemory;

        cout << "\nMemory Footprint (Array - Dataset 1)" << endl;
        cout << string(50, '-') << endl;
        cout << left << setw(25) << "Size of one Patient1" << right << setw(15) << sizeof(Patient2) << " bytes" << endl;
        cout << left << setw(25) << "Patients stored (count)" << right << setw(15) << count << endl;
        cout << left << setw(25) << "Array capacity" << right << setw(15) << capacity << endl;
        cout << left << setw(25) << "Memory used" << right << setw(15) << usedMemory << " bytes" << endl;
        cout << left << setw(25) << "Memory allocated" << right << setw(15) << allocatedMemory << " bytes" << endl;
        cout << left << setw(25) << "Wasted (unused) memory" << right << setw(15) << wastedMemory << " bytes" << endl;
        cout << string(50, '-') << endl;
    }

    // choose action

    int chooseActionDataset2() {
        int choice;
        while (true) {
            cout << "\n=== Select Action (Facility B) ===\n";
            cout << "1. Display All\n";
            cout << "2. Compare Search by Total (Linear vs Binary)\n";
            cout << "3. Age Group Report (Task 4)\n";
            cout << "4. Show Overall Analysis (Total Billing)\n";
            cout << "5. Show Memory Footprint (Task 8a)\n";
            cout << "6. Add Patient\n";
            cout << "7. Back to Dataset Menu\n";
            cout << "Choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (choice < 1 || choice > 7) {
                cout << "Invalid choice. Please enter 1-5.\n";
                continue;
            }
            return choice;
        }
    }
};



void loadDataset2(ArrayPatientList2& dataset2) {
    ifstream file("dataset2.csv");
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


        Patient2 p(idStr, age, careTypeStr, duration, rate, visits);
        dataset2.addPatient(p);
    }



};
