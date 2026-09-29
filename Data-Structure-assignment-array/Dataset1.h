#include <iostream>
#include <iomanip>
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

class Patient1 {
private:
	string PatientID;
	int age;
	string careTypes;
	double lengthOfStay;
	double baseCostPerHour;
	int daysVisitsPerYear;

public:
	// consturctor
	Patient1(string id = "", int a = 0, string care = "", double duration = 0.0,
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

class ArrayPatientList1 {
private:
	Patient1* patients;
	int count = 0;
	int capacity;


public:
	ArrayPatientList1() {
		capacity = 10;
		patients = new Patient1[capacity];

	}

	~ArrayPatientList1() {
		delete[] patients;
	}

	void addPatient(Patient1 p) {
		if (count == capacity) {
			resize();
		}
		patients[count] = p;
		count++;
	}

	void resize() {
		int newCapacity = capacity * 2;
		Patient1* newArray = new Patient1[newCapacity];

		for (int i = 0; i < count; i++) {
			newArray[i] = patients[i];
		}

		delete[] patients;
		patients = newArray;
		capacity = newCapacity;
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

	// Average cost per patient

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

	// total billing for data set 1

	double getTotalBillingForDataset() const {
		double total = 0.0;

		for (int i = 0; i < count; i++) {
			total += patients[i].calculateTotalCost();
		}
		return total;
	}

	// most prefered care type

	string getMostPreferredCareType(int minAge, int maxAge) const {
		string careTypeNames[3] = { "Emergency", "Outpatient", "Inpatient" };
		int careTypeCounts[3] = { 0, 0, 0};

		for (int i = 0; i < count; i++) {
			if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
				for (int j = 0; j < 3; j++) {
					if (patients[i].getCareType() == careTypeNames[j]) {
						careTypeCounts[j]++;
					}
				}
			}
		}

		// Find which index has the highest count
		int maxIndex = 0;
		for (int j = 1; j < 3; j++) {
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
		int ranges[3][2] = {
			{26, 45}, {46, 60}, {61, 100}
		};
		string labels[3] = {
			"26-45 (Working Adults - Early Career)",
			"46-60 (Working Adults - Late Career)",
			"61-100 (Senior Citizens / Geriatric Care)"
		};
		string careTypeNames[3] = { "Emergency", "Outpatient", "Inpatient"};

		cout << fixed << setprecision(2);

		for (int g = 0; g < 3; g++) {
			int minAge = ranges[g][0];
			int maxAge = ranges[g][1];

			cout << "\nAge Group: " << labels[g] << endl;
			cout << string(78, '-') << endl;
			cout << left << setw(18) << "Care Type"
				<< setw(16) << "Patient Count"
				<< setw(16) << "Total Cost ($)"
				<< "Average Cost per Patient ($)" << endl;
			cout << string(78, '-') << endl;

			for (int c = 0; c < 3; c++) {
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


	// section 5 
	// b
	void showCareTypeBillingReport() const {
		string careTypeNames[3] = { "Emergency", "Outpatient", "Inpatient"};

		cout << fixed << setprecision(2);

		cout << "\nMedical Costs Grouped by Care Type (Facility A - Dataset 1)" << endl;
		cout << string(50, '-') << endl;
		cout << left << setw(20) << "Care Type"
			<< right << setw(15) << "Total Cost ($)" << endl;
		cout << string(50, '-') << endl;

		for (int c = 0; c < 3; c++) {
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


	// section 6 - sorting experiement 
	// Bubble sort

	void sortByVisitDuration() {
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - 1 - i; j++) {
				if (patients[j].getLengthOfStay() > patients[j + 1].getLengthOfStay()) {
					Patient1 temp = patients[j];
					patients[j] = patients[j + 1];
					patients[j + 1] = temp;
				}

			}
		}
	}

	// Counting sort


	void sortByAge() {
		int countArray[101] = { 0 };

		for (int i = 0; i < count; i++) {
			countArray[patients[i].getAge()]++;
		}

		for (int i = 1; i <= 100; i++) {
			countArray[i] += countArray[i - 1];
		}

		Patient1 output[201];
		for (int i = count - 1; i >= 0; i--) {
			int age = patients[i].getAge();
			output[countArray[age] - 1] = patients[i];
			countArray[age]--;
		}

		for (int i = 0; i < count; i++) {
			patients[i] = output[i];
		}
	}

	// section 7 - searching experiement 
	// Linear search (unsorted)

	long long LinearSearchByAgeGroup(int minAge, int maxAge) const {
		auto start = chrono::high_resolution_clock::now();

		int matches = 0;
		for (int i = 0; i < count; i++) {
			if (patients[i].getAge() >= minAge && patients[i].getAge() <= maxAge) {
				cout << patients[i].getPatientID() << " " << patients[i].getAge()
					<< " " << patients[i].getCareType() << endl;
				matches++;
			}
		}

		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Total matches: " << matches << endl;
		cout << "linearSearchByAgeGroup() took: " << duration.count() << " microseconds" << endl;
		return duration.count();
	}

	// Linear search - duration threshold (e.g. > 24 hours)
	long long LinearSearchByDuration(double targetDuration, char mode) const {
		auto start = chrono::high_resolution_clock::now();
		int matches = 0;

		for (int i = 0; i < count; i++) {
			bool isMatch = false;

			if (mode == '=' && patients[i].getLengthOfStay() == targetDuration) isMatch = true;
			else if (mode == '>' && patients[i].getLengthOfStay() > targetDuration) isMatch = true;
			else if (mode == '<' && patients[i].getLengthOfStay() < targetDuration) isMatch = true;

			if (isMatch) {
				cout << patients[i].getPatientID() << " " << patients[i].getLengthOfStay() << " hrs" << endl;
				matches++;
			}
		}

		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Total matches: " << matches << endl;
		cout << "linearSearchByDuration() took: " << duration.count() << " microseconds" << endl;
		return duration.count();
	}

	// Binary Search (sorted by bubble sort)

	long long BinarySearchByAgeGroup(int minAge, int maxAge) {
		sortByAge();
		auto start = chrono::high_resolution_clock::now();

		int low = 0;
		int high = count - 1;
		int boundary = -1; // index of first patient with age >= minAge

		// Step 1: binary search for the first index where age >= minAge
		while (low <= high) {
			int mid = (low + high) / 2;
			if (patients[mid].getAge() >= minAge) {
				boundary = mid;
				high = mid - 1;   // keep searching left for an earlier boundary
			}
			else {
				low = mid + 1;
			}
		}

		int matches = 0;
		if (boundary != -1) {
			// Step 2: walk forward from boundary while age is still within range
			for (int i = boundary; i < count && patients[i].getAge() <= maxAge; i++) {
				cout << patients[i].getPatientID() << " " << patients[i].getAge()
					<< " " << patients[i].getCareType() << endl;
				matches++;
			}
		}

		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Total matches: " << matches << endl;
		cout << "binarySearchByAgeGroup() took: " << duration.count() << " microseconds" << endl;
		return duration.count();
	}

	// Binary-seaarch data sorted 
	long long BinarySearchByDuration(double targetDuration, char mode) {
		sortByVisitDuration();

		auto start = chrono::high_resolution_clock::now();
		int low = 0;
		int high = count - 1;
		int boundary = -1;

		// Handle exact match separately — different logic than threshold
		if (mode == '=') {
			while (low <= high) {
				int mid = (low + high) / 2;
				if (patients[mid].getLengthOfStay() == targetDuration) {
					auto end = chrono::high_resolution_clock::now();
					auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
					cout << "Found: " << patients[mid].getPatientID() << endl;
					cout << "BinarySearchByDurationThreshold() took: " << duration.count() << " microseconds" << endl;
					return duration.count();
				}
				else if (patients[mid].getLengthOfStay() < targetDuration) {
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
			}
			auto end = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
			cout << "Not found!" << endl;
			cout << "BinarySearchByDurationThreshold() took: " << duration.count() << " microseconds" << endl;
			return duration.count();
		}

		// Threshold logic (< or >) — your existing boundary-finding code
		while (low <= high) {
			int mid = (low + high) / 2;
			bool conditionMet = false;
			if (mode == '<' && patients[mid].getLengthOfStay() < targetDuration) conditionMet = true;
			if (mode == '>' && patients[mid].getLengthOfStay() > targetDuration) conditionMet = true;

			if (conditionMet) {
				boundary = mid;
				if (mode == '<') low = mid + 1;
				else high = mid - 1;
			}
			else {
				if (mode == '<') high = mid - 1;
				else low = mid + 1;
			}
		}

		int matches = 0;
		if (mode == '<') {
			for (int i = 0; i <= boundary; i++) {
				cout << patients[i].getPatientID() << " " << patients[i].getLengthOfStay() << " hrs" << endl;
				matches++;
			}
		}
		else if (mode == '>' && boundary != -1 ) {
			for (int i = boundary; i < count; i++) {
				cout << patients[i].getPatientID() << " " << patients[i].getLengthOfStay() << " hrs" << endl;
				matches++;
			}
		}

		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Total matches: " << matches << endl;
		cout << "BinarySearchByDurationThreshold() took: " << duration.count() << " microseconds" << endl;
		return duration.count();
	}

	// print out duration

	void compareDurationThresholdSearch(double targetDuration, char mode) {
		cout << "\n=== Searching for patients with duration > " << targetDuration << " hrs ===" << endl;

		cout << "\n--- Linear Search (Unsorted Data) ---" << endl;
		long long linearTime = LinearSearchByDuration(targetDuration, mode);

		sortByVisitDuration();  // binary search requires data sorted ascending by duration first

		cout << "\n--- Binary Search (Sorted Data) ---" << endl;
		long long binaryTime = BinarySearchByDuration(targetDuration, mode);

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

	// print out age

	void compareAgeGroupSearch(int minAge, int maxAge) {
		cout << "\n=== Searching for patients aged " << minAge << "-" << maxAge << " ===" << endl;

		cout << "\n--- Linear Search (Unsorted Data) ---" << endl;
		long long linearTime = LinearSearchByAgeGroup(minAge, maxAge);

		sortByAge();  // binary search requires data sorted ascending by age first

		cout << "\n--- Binary Search (Sorted Data) ---" << endl;
		long long binaryTime = BinarySearchByAgeGroup(minAge, maxAge);

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
		size_t usedMemory = count * sizeof(Patient1);
		size_t allocatedMemory = capacity * sizeof(Patient1);
		size_t wastedMemory = allocatedMemory - usedMemory;

		cout << "\nMemory Footprint (Array - Dataset 1)" << endl;
		cout << string(50, '-') << endl;
		cout << left << setw(25) << "Size of one Patient1" << right << setw(15) << sizeof(Patient1) << " bytes" << endl;
		cout << left << setw(25) << "Patients stored (count)" << right << setw(15) << count << endl;
		cout << left << setw(25) << "Array capacity" << right << setw(15) << capacity << endl;
		cout << left << setw(25) << "Memory used" << right << setw(15) << usedMemory << " bytes" << endl;
		cout << left << setw(25) << "Memory allocated" << right << setw(15) << allocatedMemory << " bytes" << endl;
		cout << left << setw(25) << "Wasted (unused) memory" << right << setw(15) << wastedMemory << " bytes" << endl;
		cout << string(50, '-') << endl;
	}

	// choose action

	int chooseActionDataset1() {
		int choice;
		while (true) {
			cout << "\n=== Select Action (Facility A) ===\n";
			cout << "1. Display All\n";
			cout << "2. Sort by Visit Duration (Bubble Sort)\n";
			cout << "3. Sort by Visit Age (Counting Sort)\n";
			cout << "4. Compare Search by Duration (Linear vs Binary)\n";
			cout << "5. Compare Search by Age (Linear vs Binary)\n";
			cout << "6. Age Group Report (Task 4)\n";
			cout << "7. Show Overall Analysis (Total Billing)\n";
			cout << "8. Show Memory Footprint (Task 8a)\n";
			cout << "9. Back to Dataset Menu\n";
			cout << "Choice: ";
			cin >> choice;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input! Please enter a number.\n";
				continue;
			}

			if (choice < 1 || choice > 9) {
				cout << "Invalid input! Please enter 1-8.\n";
				continue;
			}

			return choice;
		}

	}
};



void loadDataset1(ArrayPatientList1& Dataset1) {
	ifstream file("Dataset1.csv");
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


		Patient1 p(idStr, age, careTypeStr, duration, rate, visits);
		Dataset1.addPatient(p);
	}

};