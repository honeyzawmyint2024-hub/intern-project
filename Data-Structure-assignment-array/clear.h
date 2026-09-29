#include <iostream>
#include <string>
using namespace std;

class ArrayPatientList3 {
private:
    string PatientID[200];
    string names[200];
    int ages[200];
    string careTypes[200];
    double lengthOfStay[200];
    double baseCostPerHour[200];
    int daysVisitsPerYear[200];
    int count;

public:
    void addPatient(string id, string name, int age, string care, double duration, double rate, int visits) {
        if (count < 200) {
            PatientID[count] = id;
            names[count] = name;
            ages[count] = age;
            careTypes[count] = care;
            lengthOfStay[count] = duration;
            baseCostPerHour[count] = rate;
            daysVisitsPerYear[count] = visits;
            count++;
        }
    }


};