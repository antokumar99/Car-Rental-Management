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
    bool isAvailable() { return available; }

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

    int getEngineCC()
    {
        return engineCC;
    }
};

class Truck : public Vehicle
{
private:
    double cargoCapacity;

public:
    Truck(int i, string b, string m, double price, double capacity) : Vehicle(i, b, m, price, "Truck"), cargoCapacity(capacity) {};

    void displayVehicle() override
    {
        Vehicle::displayVehicle();
        cout << " |Cargo Capacity: " << cargoCapacity << " ton " << endl;
    }

    string toFileString() override
    {

        string docs = Vehicle::toFileString() + " , " + to_string(cargoCapacity);

        return docs;
    }

    double getCargoCapacity()
    {
        return cargoCapacity;
    }
};

class Customer
{
private:
    int id;
    string name;

public:
    Customer(int id, string name)
    {
        id = id;
        name = name;
    }

    int getId() { return id; }
    string getName() { return name; }

    void displayCustomer()
    {
        cout << "customer ID: " << id << " | Name: " << name << endl;
    }

    string toFileString()
    {
        return to_string(id) + "," + name;
    }
};

class RentalSystem
{
private:
    vector<Vehicle *> vehicles;
    vector<Customer> customers;

public:
    ~RentalSystem()
    {
        for (auto vehicle : vehicles)
        {
            delete vehicle;
        }
    }

    void addCar(int id, string brand, string model, double price, int doors)
    {

        Car *car = new Car(id, brand, model, price, doors);
        vehicles.push_back(car);

        cout << "Car added successfully!\n";
    }

    void addMotorcycle(int id, string brand, string model, double price, int cc)
    {
        Motorcycle *motorcycle = new Motorcycle(id, brand, model, price, cc);
        vehicles.push_back(motorcycle);

        cout << "Motorcycle added successfully!\n";
    }

    void addTruck(int id, string brand, string model, double price, double capacity)
    {
        Truck *truck = new Truck(id, brand, model, price, capacity);
        vehicles.push_back(truck);
        cout << "Truck added successfully!\n";
    }

    void addCustomer(int id, string name)
    {
        customers.push_back(Customer(id, name));
        cout << "Customer added successfully!\n";
    }

    void showVehicles()
    {
        cout << "\n ---  List of Vehicles ---\n";
        for (auto vehicle : vehicles)
        {
            vehicle->displayVehicle();
        }
    }

    void showCustomers()
    {
        cout << "\n--- List of Customers ---\n";
        for (auto &cust : customers)
        {
            cust.displayCustomer();
        }
    }

    void rentVehicle(int vehicleId, int custId, int days)
    {
        for (auto vehicle : vehicles)
        {
            if (vehicle->getId() == vehicleId)
            {
                if (vehicle->isAvailable())
                {
                    vehicle->rentVehicle();
                    double cost = vehicle->getPrice() * days;
                    cout << vehicle->getType() << "rented successfully to customer " << custId << ". Total cost = $" << cost << endl;
                    return;
                }else {
                    cout<< vehicle->getType() << " is not available. \n";
                    return;
                }
            }
        }
        cout<< "Vehicle not found.\n";
    }

    void returnVehicle(int vehicleId)
    {
        for(auto vehicle: vehicles)
        {
            if(vehicle->getId()== vehicleId){
                if (!vehicle->isAvailable()) {
                    vehicle->returnVehicle();
                    cout<< vehicle->getType() << " returned successfully!\n";
                    return;
                }else {
                    cout<< "This " << vehicle->getType() << "was not rented.\n";
                    return;
                }
            }
        }

        cout<< "Vehicle not found.\n";
    }

    void saveToFile() {
        ofstream vehicleFile("vehicles.txt");
        if(vehicleFile.is_open()) {
            for(auto vehicle : vehicles)
            {
                vehicleFile << vehicle->toFileString() << endl;
            }
            vehicleFile.close();
            cout<< "Vehicles Saved successfully!\n";
        }else{
            cout << "Error: Unable to save vehicles. \n";
        }

        ofstream customerFile("customers.txt");
        if(customerFile.is_open())
        {
            for(auto &customer: customers){
                customerFile << customer.toFileString() << endl;
            }
            customerFile.close();
            cout<< "Customers saved successfully! \n";
        }else {
            cout<< "Error: Unable to save customer.  \n";
        }
    }
};
