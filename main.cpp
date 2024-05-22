#include <iostream>  
#include <fstream>   
#include <vector>    
#include <string>    

using namespace std; 

// Структура для представления элемента инвентаря
struct InventoryItem {
    string name;      
    string category;  
    int quantity;     
    float price;      
};

vector<InventoryItem> inventory; // Глобальный вектор для хранения инвентаря

// Прототипы функций
void loadInventory();  // Функция загрузки инвентаря из файла
void saveInventory();  // Функция сохранения инвентаря в файл
void addItem();        // Функция добавления нового элемента
void viewInventory();  // Функция просмотра всех элементов
void updateItem();     // Функция обновления элемента
void deleteItem();     // Функция удаления элемента

int main() {
    loadInventory(); // Загрузка данных инвентаря из файла при запуске программы

    char choice; // Переменная для хранения выбора пользователя
    do {
        // Меню пользователя
        cout << "\n===== Inventory Management System =====\n";
        cout << "1. Add Item\n";
        cout << "2. View Inventory\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Считывание выбора пользователя

        switch (choice) {
        case '1':
            addItem(); // Вызов функции добавления элемента
            break;
        case '2':
            viewInventory(); // Вызов функции просмотра инвентаря
            break;
        case '3':
            updateItem(); // Вызов функции обновления элемента
            break;
        case '4':
            deleteItem(); // Вызов функции удаления элемента
            break;
        case '5':
            saveInventory(); // Сохранение данных инвентаря в файл перед выходом
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n"; // Обработка неверного выбора
        }
    } while (choice != '5'); // Цикл продолжается, пока пользователь не выберет "выйти"

    return 0; // Завершение программы
}

// Функция загрузки инвентаря из файла
void loadInventory() {
    ifstream file("inventory.txt"); // Открытие файла для чтения
    if (!file) { // Проверка на успешное открытие файла
        cerr << "Error opening file.\n"; // Вывод сообщения об ошибке
        return; // Выход из функции при ошибке
    }

    InventoryItem item; // Переменная для временного хранения данных элемента
    while (file >> item.name >> item.category >> item.quantity >> item.price) {
        inventory.push_back(item); // Добавление элемента в вектор
    }

    file.close(); // Закрытие файла
}

// Функция сохранения инвентаря в файл
void saveInventory() {
    ofstream file("inventory.txt"); // Открытие файла для записи
    if (!file) { // Проверка на успешное открытие файла
        cerr << "Error opening file.\n"; // Вывод сообщения об ошибке
        return; // Выход из функции при ошибке
    }

    // Запись каждого элемента инвентаря в файл
    for (const auto& item : inventory) {
        file << item.name << ' ' << item.category << ' ' << item.quantity << ' ' << item.price << '\n';
    }

    file.close(); // Закрытие файла
}

// Функция добавления нового элемента в инвентарь
void addItem() {
    InventoryItem item; // Переменная для нового элемента
    cout << "Enter item name: ";
    cin >> item.name; // Ввод имени элемента
    cout << "Enter item category: ";
    cin >> item.category; // Ввод категории элемента
    cout << "Enter item quantity: ";
    cin >> item.quantity; // Ввод количества элемента
    cout << "Enter item price: ";
    cin >> item.price; // Ввод цены элемента

    inventory.push_back(item); // Добавление элемента в вектор
    cout << "Item added successfully.\n"; // Подтверждение добавления элемента
}

// Функция просмотра всех элементов инвентаря
void viewInventory() {
    if (inventory.empty()) { // Проверка, пуст ли инвентарь
        cout << "Inventory is empty.\n"; // Вывод сообщения о пустом инвентаре
        return; // Выход из функции, если инвентарь пуст
    }

    // Вывод списка элементов инвентаря
    cout << "===== Inventory List =====\n";
    for (const auto& item : inventory) {
        cout << "Name: " << item.name << ", Category: " << item.category << ", Quantity: " << item.quantity << ", Price: " << item.price << '\n';
    }
}

// Функция обновления данных элемента
void updateItem() {
    if (inventory.empty()) { // Проверка, пуст ли инвентарь
        cout << "Inventory is empty. Cannot update.\n"; // Вывод сообщения о невозможности обновления
        return; // Выход из функции, если инвентарь пуст
    }

    string name; // Переменная для хранения имени элемента
    cout << "Enter name of item to update: ";
    cin >> name; // Ввод имени элемента

    bool found = false; // Флаг для обозначения нахождения элемента
    for (auto& item : inventory) {
        if (item.name == name) { // Поиск элемента по имени
            cout << "Enter new quantity: ";
            cin >> item.quantity; // Ввод нового количества
            cout << "Enter new price: ";
            cin >> item.price; // Ввод новой цены
            cout << "Item updated successfully.\n"; // Подтверждение обновления элемента
            found = true; // Установка флага нахождения элемента
            break; // Выход из цикла после нахождения элемента
        }
    }

    if (!found) { // Если элемент не найден
        cout << "Item not found.\n"; // Вывод сообщения о ненахождении элемента
    }
}

// Функция удаления элемента из инвентаря
void deleteItem() {
    if (inventory.empty()) { // Проверка, пуст ли инвентарь
        cout << "Inventory is empty. Cannot delete.\n"; // Вывод сообщения о невозможности удаления
        return; // Выход из функции, если инвентарь пуст
    }

    string name; // Переменная для хранения имени элемента
    cout << "Enter name of item to delete: ";
    cin >> name; // Ввод имени элемента

    auto it = inventory.begin(); // код для прохода по вектору
    while (it != inventory.end()) {
        if (it->name == name) { // Поиск элемента по имени
            it = inventory.erase(it); // Удаление элемента и обновление 
            cout << "Item deleted successfully.\n"; // Подтверждение удаления элемента
            return; // Выход из функции после удаления элемента
        }
        else {
            ++it; // Переход к следующему элементу
        }
    }

    cout << "Item not found.\n"; // Вывод сообщения о ненахождении элемента
}

