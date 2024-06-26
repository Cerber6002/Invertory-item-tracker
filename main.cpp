#include <iostream>  
#include <fstream>   
#include <vector>    
#include <string>    

using namespace std; 

// ��������� ��� ������������� �������� ���������
struct InventoryItem {
    string name;      
    string category;  
    int quantity;     
    float price;      
};

vector<InventoryItem> inventory; // ���������� ������ ��� �������� ���������

// ��������� �������
void loadInventory();  // ������� �������� ��������� �� �����
void saveInventory(); // ������� ���������� ��������� � ����
void addItem();       
void viewInventory(); 
void updateItem();    
void deleteItem();    

int main() {
    loadInventory(); // �������� ������ ��������� �� ����� ��� ������� ���������

    char choice; // ���������� ��� �������� ������ ������������
    do {
        // ���� ������������
        cout << "\n===== Inventory Management System =====\n";
        cout << "1. Add Item\n";
        cout << "2. View Inventory\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // ���������� ������ ������������

        switch (choice) {
        case '1':
            addItem(); // ����� ������� ���������� ��������
            break;
        case '2':
            viewInventory(); // ����� ������� ��������� ���������
            break;
        case '3':
            updateItem(); // ����� ������� ���������� ��������
            break;
        case '4':
            deleteItem(); // ����� ������� �������� ��������
            break;
        case '5':
            saveInventory(); // ���������� ������ ��������� � ���� ����� �������
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n"; // ��������� ��������� ������
        }
    } while (choice != '5'); // ���� ������������, ���� ������������ �� ������� "�����"

    return 0; // ���������� ���������
}

// ������� �������� ��������� �� �����
void loadInventory() {
    ifstream file("inventory.txt"); // �������� ����� ��� ������
    if (!file) { // �������� �� �������� �������� �����
        cerr << "Error opening file.\n"; // ����� ��������� �� ������
        return; // ����� �� ������� ��� ������
    }

    InventoryItem item; // ���������� ��� ���������� �������� ������ ��������
    while (file >> item.name >> item.category >> item.quantity >> item.price) {
        inventory.push_back(item); // ���������� �������� � ������
    }

    file.close(); // �������� �����
}

// ������� ���������� ��������� � ����
void saveInventory() {
    ofstream file("inventory.txt"); // �������� ����� ��� ������
    if (!file) { // �������� �� �������� �������� �����
        cerr << "Error opening file.\n"; // ����� ��������� �� ������
        return; // ����� �� ������� ��� ������
    }

    // ������ ������� �������� ��������� � ����
    for (const auto& item : inventory) {
        file << item.name << ' ' << item.category << ' ' << item.quantity << ' ' << item.price << '\n';
    }

    file.close(); // �������� �����
}

// ������� ���������� ������ �������� � ���������
void addItem() {
    InventoryItem item; // ���������� ��� ������ ��������
    cout << "Enter item name: ";
    cin >> item.name; // ���� ����� ��������
    cout << "Enter item category: ";
    cin >> item.category; // ���� ��������� ��������
    cout << "Enter item quantity: ";
    cin >> item.quantity; // ���� ���������� ��������
    cout << "Enter item price: ";
    cin >> item.price; // ���� ���� ��������

    inventory.push_back(item); // ���������� �������� � ������
    cout << "Item added successfully.\n"; // ������������� ���������� ��������
}

// ������� ��������� ���� ��������� ���������
void viewInventory() {
    if (inventory.empty()) { // ��������, ���� �� ���������
        cout << "Inventory is empty.\n"; // ����� ��������� � ������ ���������
        return; // ����� �� �������, ���� ��������� ����
    }

    // ����� ������ ��������� ���������
    cout << "===== Inventory List =====\n";
    for (const auto& item : inventory) {
        cout << "Name: " << item.name << ", Category: " << item.category << ", Quantity: " << item.quantity << ", Price: " << item.price << '\n';
    }
}

// ������� ���������� ������ ��������
void updateItem() {
    if (inventory.empty()) { // ��������, ���� �� ���������
        cout << "Inventory is empty. Cannot update.\n"; // ����� ��������� � ������������� ����������
        return; // ����� �� �������, ���� ��������� ����
    }

    string name; // ���������� ��� �������� ����� ��������
    cout << "Enter name of item to update: ";
    cin >> name; // ���� ����� ��������

    bool found = false; // ���� ��� ����������� ���������� ��������
    for (auto& item : inventory) {
        if (item.name == name) { // ����� �������� �� �����
            cout << "Enter new quantity: ";
            cin >> item.quantity; // ���� ������ ����������
            cout << "Enter new price: ";
            cin >> item.price; // ���� ����� ����
            cout << "Item updated successfully.\n"; // ������������� ���������� ��������
            found = true; // ��������� ����� ���������� ��������
            break; // ����� �� ����� ����� ���������� ��������
        }
    }

    if (!found) { // ���� ������� �� ������
        cout << "Item not found.\n"; // ����� ��������� � ������������ ��������
    }
}

// ������� �������� �������� �� ���������
void deleteItem() {
    if (inventory.empty()) { // ��������, ���� �� ���������
        cout << "Inventory is empty. Cannot delete.\n"; // ����� ��������� � ������������� ��������
        return; // ����� �� �������, ���� ��������� ����
    }

    string name; // ���������� ��� �������� ����� ��������
    cout << "Enter name of item to delete: ";
    cin >> name; // ���� ����� ��������

    auto it = inventory.begin(); // ��� ��� ������� �� �������
    while (it != inventory.end()) {
        if (it->name == name) { // ����� �������� �� �����
            it = inventory.erase(it); // �������� �������� � ���������� 
            cout << "Item deleted successfully.\n"; // ������������� �������� ��������
            return; // ����� �� ������� ����� �������� ��������
        }
        else {
            ++it; // ������� � ���������� ��������
        }
    }

    cout << "Item not found.\n"; // ����� ��������� � ������������ ��������
}

