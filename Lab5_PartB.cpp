#include <iostream>
#include <string>
#include <utility>
using namespace std;

// ========================================
// Car Node
// ========================================
struct CarNode
{
    int carID;
    string model;
    int dailyRate;
    CarNode* next;
};

// ========================================
// Linked List Class
// ========================================
class LinkedList
{
private:
    CarNode* head;
    int count;

    CarNode* GetNodeAt(int index)
    {
        CarNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++)
            current = current->next;
        return current;
    }

    void CopyCarData(CarNode* a, CarNode* b)
    {
        swap(a->carID, b->carID);
        swap(a->model, b->model);
        swap(a->dailyRate, b->dailyRate);
    }

public:
    LinkedList()
    {
        head = nullptr;
        count = 0;
    }

    int Size() { return count; }

    bool IsEmpty() { return head == nullptr; }
    bool IsNotEmpty() { return head != nullptr; }

    // Insert a car at the head
    void Insert(CarNode* car)
    {
        if (car == nullptr)
            return;
        car->next = head;
        head = car;
        count++;
    }

    // Remove a car from the head
    CarNode* Remove()
    {
        if (IsEmpty())
            return nullptr;
        CarNode* car = head;
        head = head->next;
        car->next = nullptr;
        count--;
        return car;
    }

    // Insert at a specified index
    void InsertAt(CarNode* car, int index)
    {
        if (car == nullptr)
            return;
        if (index < 0)
            index = 0;
        if (index > count)
            index = count;
        if (index == 0)
        {
            Insert(car);
            return;
        }
        CarNode* previous = GetNodeAt(index - 1);
        car->next = previous->next;
        previous->next = car;
        count++;
    }

    // Remove at a specified index
    CarNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return nullptr;
        if (index < 0)
            index = 0;
        if (index >= count)
            index = count - 1;
        if (index == 0)
            return Remove();
        CarNode* previous = GetNodeAt(index - 1);
        CarNode* car = previous->next;
        previous->next = car->next;
        car->next = nullptr;
        count--;
        return car;
    }

    // Swap car data at two indexes
    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count)
            return;
        if (index1 == index2)
            return;
        CarNode* first = GetNodeAt(index1);
        CarNode* second = GetNodeAt(index2);
        CopyCarData(first, second);
    }

    // Sort cars by car ID in ascending order
    void Sort()
    {
        for (CarNode* i = head; i != nullptr; i = i->next)
        {
            for (CarNode* j = i->next; j != nullptr; j = j->next)
            {
                if (i->carID > j->carID)
                    CopyCarData(i, j);
            }
        }
    }

    // Reverse the linked list
    void Reverse()
    {
        CarNode* previous = nullptr;
        CarNode* current = head;
        CarNode* next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }

    // Display all cars
    void Print()
    {
        CarNode* current = head;
        int index = 0;
        cout << "\nIndex\tCar ID\tModel\t\tRate/Day (PKR)\n";
        cout << "-----------------------------------\n";
        while (current != nullptr)
        {
            cout << index << "\t"
                 << current->carID << "\t"
                 << current->model << "\t" << current->dailyRate << endl;
            current = current->next;
            index++;
        }
        cout << "Total cars: " << count << endl;
    }

    // Copy constructor: create independent nodes
    LinkedList(const LinkedList& other)
    {
        head = nullptr;
        count = 0;
        CarNode* current = other.head;
        while (current != nullptr)
        {
            CarNode* copy = new CarNode{ current->carID, current->model, current->dailyRate, nullptr };
            InsertAt(copy, count);
            current = current->next;
        }
    }

    // Assignment operator: replace this list's contents
    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;
        while (!IsEmpty())
            delete Remove();
        CarNode* current = other.head;
        while (current != nullptr)
        {
            CarNode* copy = new CarNode{ current->carID, current->model, current->dailyRate, nullptr };
            InsertAt(copy, count);
            current = current->next;
        }
        return *this;
    }

    // Destructor: release all remaining nodes
    ~LinkedList()
    {
        while (!IsEmpty())
            delete Remove();
    }
};

CarNode* CreateCar(int id, string model, int rate)
{
    CarNode* car = new CarNode;
    car->carID = id;
    car->model = model;
    car->dailyRate = rate;
    car->next = nullptr;
    return car;
}


int main()
{
    LinkedList fleet;

    cout << "=== CAR RENTAL FLEET (Singly Linked List) ===";
    fleet.InsertAt(CreateCar(203, "Toyota Corolla", 8000), 0);
    fleet.InsertAt(CreateCar(201, "Honda Civic", 10000), 1);
    fleet.InsertAt(CreateCar(205, "Suzuki Alto", 4500), 2);
    fleet.InsertAt(CreateCar(202, "Toyota Fortuner", 20000), 3);
    fleet.InsertAt(CreateCar(204, "Suzuki Cultus", 5000), 4);
    cout << "\nINITIAL FLEET";
    fleet.Print();

    fleet.InsertAt(CreateCar(206, "Honda City", 7500), 2);
    cout << "\nAFTER ADDING A NEW CAR AT INDEX 2";
    fleet.Print();

    CarNode* removed = fleet.RemoveAt(1);
    if (removed != nullptr)
    {
        cout << "\nRemoved from fleet (sold): " << removed->model << endl;
        delete removed;
    }
    cout << "\nAFTER REMOVING INDEX 1";
    fleet.Print();

    fleet.Swap(0, 2);
    cout << "\nAFTER SWAPPING INDEX 0 AND INDEX 2";
    fleet.Print();

    fleet.Sort();
    cout << "\nAFTER SORTING BY CAR ID";
    fleet.Print();

    fleet.Reverse();
    cout << "\nAFTER REVERSING THE LIST";
    fleet.Print();

    fleet.Insert(CreateCar(200, "Toyota Yaris", 7000));
    cout << "\nAFTER INSERTING AT THE HEAD";
    fleet.Print();

    removed = fleet.Remove();
    if (removed != nullptr)
    {
        cout << "\nRemoved from head: " << removed->model << endl;
        delete removed;
    }
    cout << "\nFINAL FLEET";
    fleet.Print();

    cout << "\nIs fleet empty? " << (fleet.IsEmpty() ? "Yes" : "No") << endl;
    return 0;
}
