#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class Vehicle{

protected:
    int id;
    string brand;
    string model;
    double pricePerDay;
    bool available;
    string vehicleType;

public:
    Vehicle(int i, string b, string m, double price, string type){
        id = i;
        brand= b;
        model = m;
        pricePerDay =price;
        vehicleType = type;
    }

};