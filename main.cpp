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
        available = true;
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
    Customer(int i, string n)
    {
        id = i;
        name = n;
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
                }
                else
                {
                    cout << vehicle->getType() << " is not available. \n";
                    return;
                }
            }
        }
        cout << "Vehicle not found.\n";
    }

    void returnVehicle(int vehicleId)
    {
        for (auto vehicle : vehicles)
        {
            if (vehicle->getId() == vehicleId)
            {
                if (!vehicle->isAvailable())
                {
                    vehicle->returnVehicle();
                    cout << vehicle->getType() << " returned successfully!\n";
                    return;
                }
                else
                {
                    cout << "This " << vehicle->getType() << "was not rented.\n";
                    return;
                }
            }
        }

        cout << "Vehicle not found.\n";
    }

    void saveToFile()
    {
        ofstream vehicleFile("vehicles.txt");
        if (vehicleFile.is_open())
        {
            for (auto vehicle : vehicles)
            {
                vehicleFile << vehicle->toFileString() << endl;
            }
            vehicleFile.close();
            cout << "Vehicles Saved successfully!\n";
        }
        else
        {
            cout << "Error: Unable to save vehicles. \n";
        }

        ofstream customerFile("customers.txt");
        if (customerFile.is_open())
        {
            for (auto &customer : customers)
            {
                customerFile << customer.toFileString() << endl;
            }
            customerFile.close();
            cout << "Customers saved successfully! \n";
        }
        else
        {
            cout << "Error: Unable to save customer.  \n";
        }
    }

    // File Loading.....

    void loadFromFile()
    {
        for (auto vehicle : vehicles)
        {
            delete vehicle;
        }

        vehicles.clear();
        customers.clear();

        ifstream vehicleFile("vehicles.txt");
        if (vehicleFile.is_open())
        {
            string line;
            while (getline(vehicleFile, line))
            {
                stringstream ss(line);
                string type, brand, model, availStr;
                int id;
                double price;

                getline(ss, type, ',');

                ss >> id;
                ss.ignore();
                getline(ss, brand, ',');
                getline(ss, model, ',');
                ss >> price;
                ss.ignore();
                getline(ss, availStr, ',');
                bool available = (availStr == "1");

                if (type == "Car")
                {
                    int doors;
                    ss >> doors;

                    Car *car = new Car(id, brand, model, price, doors);
                    if (!available)
                        car->rentVehicle();
                    vehicles.push_back(car);
                }
                else if (type == "Motorcycle")
                {
                    int cc;
                    ss >> cc;
                    Motorcycle *bike = new Motorcycle(id, brand, model, price, cc);
                    if (!available)
                        bike->rentVehicle();
                    vehicles.push_back(bike);
                }
                else if (type == "Truck")
                {
                    double capacity;
                    ss >> capacity;
                    Truck *truck = new Truck(id, brand, model, price, capacity);
                    if (!available)
                        truck->rentVehicle();
                    vehicles.push_back(truck);
                }
            }

            vehicleFile.close();
            cout << "Vehicles loaded successfull!\n";
        }
        else
        {
            cout << "No previous vehicle data found.\n";
        }

        ifstream customerFile("customers.txt");
        if (customerFile.is_open())
        {
            string line;
            while (getline(customerFile, line))
            {
                stringstream ss(line);
                int id;
                string name;

                ss >> id;
                ss.ignore();
                getline(ss, name);

                customers.push_back(Customer(id, name));
            }

            customerFile.close();
            cout << "Customers loaded successfully!\n";
        }
        else
        {
            cout << "No previous customer data found.\n";
        }
    }
};

int main()
{
    RentalSystem system;
    int choice;

    cout << "Loading existing data....\n";

    system.loadFromFile();

    do
    {
        cout << "\n===== Car Rental Management =====\n";
        cout << "1. Show Vehicles\n";
        cout << "2. Show Customers\n";
        cout << "3. Add Car\n";
        cout << "4. Add Motorcycle\n";
        cout << "5. Add Truck\n";
        cout << "6. Add Customer\n";
        cout << "7. Rent a Vehicle\n";
        cout << "8. Return a Vehicle\n";
        cout << "9. Save Data\n";
        cout << "10. Load Data\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system.showVehicles();
        }
        else if (choice == 2)
        {
            system.showCustomers();
        }
        else if (choice == 3)
        {
            int id, doors;
            string brand, model;
            double price;
            cout << "Enter Car ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Brand : ";
            getline(cin, brand);
            cout << "Enter Model: ";
            getline(cin, model);
            cout << "Enter Price per day: ";
            cin >> price;
            cout << "Enter Number of Doors: ";
            cin >> doors;
            system.addCar(id, brand, model, price, doors);
        }
        else if (choice == 4)
        {
            int id, cc;
            string brand, model;
            double price;
            cout << "Enter Motorcycle ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Brand : ";
            getline(cin, brand);
            cout << "Enter Model: ";
            getline(cin, model);
            cout << "Enter Price per day: ";
            cin >> price;
            cout << "Enter Engine CC: ";
            cin >> cc;
            system.addMotorcycle(id, brand, model, price, cc);
        }
        else if (choice == 5)
        {
            int id;
            string brand, model;
            double price, capacity;
            cout << "Enter Truck ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Brand: ";
            getline(cin, brand);
            cout << "Enter Model: ";
            getline(cin, model);
            cout << "Enter Price per day: ";
            cin >> price;
            cout << "Enter Cargo Capacity (tons): ";
            cin >> capacity;
            system.addTruck(id, brand, model, price, capacity);
        }
        else if (choice == 6)
        {
            int id;
            string name;
            cout << "Enter Customer ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Customer Nmae: ";
            getline(cin, name);

            system.addCustomer(id, name);
        }
        else if (choice == 7)
        {
            int vehicleId, custId, days;
            cout << "Enter Vehicle ID: ";
            cin >> vehicleId;
            cout << "Enter Customer ID: ";
            cin >> custId;
            cout << "Enter Number of Days: ";
            cin >> days;
            system.rentVehicle(vehicleId, custId, days);
        }
        else if (choice == 8)
        {
            int vehicleId;
            cout << "Enter Vehicle ID to return: ";
            cin >> vehicleId;
            system.returnVehicle(vehicleId);
        }
        else if (choice == 9)
        {
            system.saveToFile();
        }
        else if (choice == 10)
        {
            system.loadFromFile();
        }
        else if (choice == 11)
        {
            cout << "Do you want to save before exiting? (1=Yes, 0=No): ";
            int save;
            cin >> save;
            if (save == 1)
            {
                system.saveToFile();
            }
            cout << "Exiting...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 11);

    return 0;
}
