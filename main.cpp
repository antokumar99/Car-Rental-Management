#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Vehicle
{

protected:
    int id;
    string brand;
    string model;
    double pricePerDay;
    bool available;
    string vehicleType;

public:
    Vehicle(int i, string b, string m, double price, string type)
    {
        id = i;
        brand = b;
        model = m;
        pricePerDay = price;
        vehicleType = type;
    }

    virtual ~Vehicle() {}

    int getId() { return id; }
    string getBrand() { return brand; }
    string getModel() { return model; }
    double getPrice() { return pricePerDay; }
    string getType() { return vehicleType; }

    void rentVehicle() { available = false; }
    void returnVehicle() { available = true; }

    virtual void displayVehicle()
    {
        cout << vehicleType << " ID: " << id
             << " | " << brand << " " << model
             << " | Price per day: $" << pricePerDay
             << " | Available: " << (available ? "Yes" : "No");
    }

    virtual string toFileString()
    {
        string docs = vehicleType + "," + to_string(id) + "," + brand + "," + model + "," + to_string(pricePerDay) + "," + (available ? "YES" : "NO");

        return docs;
    }
};

class Car : public Vehicle
{
private:
    int numDoors;

public:
    Car(int i, string b, string m, double price, int doors = 4) : Vehicle(i, b, m, price, "Car"), numDoors(doors) {}

    void displayVehicle() override
    {
        Vehicle::displayVehicle();
        cout << " | Doors: " << numDoors << endl;
    }

    string toFileString() override
    {
        string docs = Vehicle::toFileString() + "," + to_string(numDoors);

        return docs;
    }
};

class Motorcycle : public Vehicle
{
private:
    int engineCC;

public:
    Motorcycle(int i, string b, string m, double price, int cc) : Vehicle(i, b, m, price, "Motorcycle"), engineCC(cc) {}

    void displayVehicle() override
    {
        Vehicle::displayVehicle(),
            cout << " | Engine: " << engineCC << "cc" << endl;
    }

    string toFileString() override
    {
        string docs = Vehicle::toFileString() + " , " + to_string(engineCC);

        return docs;
    }

    int getEngineCC() {
        return engineCC;
    }
};

class Truck: public Vehicle
{
private:
    double cargoCapacity;
public:
    Truck(int i, string b, string m, double price, double capacity): Vehicle(i,b,m,price,"Truck"), cargoCapacity(capacity) {};

    void displayVehicle() override {
        Vehicle::displayVehicle();
        cout<< " |Cargo Capacity: "<< cargoCapacity<< " ton "<< endl;
    }

    string toFileString() override {

        string docs = Vehicle::toFileString() + " , " + to_string(cargoCapacity);

        return docs;
    }

    double getCargoCapacity() {
        return cargoCapacity;
    }
};

