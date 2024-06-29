#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define a structure for each room
struct Room {
    string description;
    map<string, int> exits; // Exits to other rooms
    vector<string> items;   // Items present in the room
};

// Define a structure for items
struct Item {
    string name;
    string description;
};

// Function prototypes
void displayRoom(const Room& room);
void displayItems(const vector<string>& items);
void displayInventory(const vector<Item>& inventory);

int main() {
    // Define rooms
    vector<Room> rooms = {
        {"You are in the living room. There is a couch and a TV.", {{"east", 1}}, {"key"}},
        {"You are in the kitchen. You see a knife on the counter.", {{"west", 0}, {"east", 2}}, {"knife"}},
        {"You are in the bedroom. There is a bed and a wardrobe.", {{"west", 1}}, {"note"}},
    };

    // Define items
    vector<Item> inventory;

    int currentRoom = 0; // Starting room

    // Game loop
    while (true) {
        displayRoom(rooms[currentRoom]);

        // Player input
        cout << ">> ";
        string command;
        cin >> command;

        // Convert command to lowercase
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        // Movement commands
        if (command == "go") {
            string direction;
            cin >> direction;
            if (rooms[currentRoom].exits.find(direction) != rooms[currentRoom].exits.end()) {
                currentRoom = rooms[currentRoom].exits[direction];
            } else {
                cout << "You cannot go that way." << endl;
            }
        } 
        // Command to display items in the room
        else if (command == "look") {
            displayItems(rooms[currentRoom].items);
        } 
        // Command to take an item
        else if (command == "take") {
            string itemName;
            cin >> itemName;
            auto it = find(rooms[currentRoom].items.begin(), rooms[currentRoom].items.end(), itemName);
            if (it != rooms[currentRoom].items.end()) {
                cout << "You take the " << itemName << "." << endl;
                inventory.push_back({itemName, "Description"});
                rooms[currentRoom].items.erase(it);
            } else {
                cout << "There is no " << itemName << " here." << endl;
            }
        } 
        // Command to display inventory
        else if (command == "inventory") {
            displayInventory(inventory);
        } 
        // Quit the game
        else if (command == "quit") {
            cout << "Exiting game. Goodbye!" << endl;
            break;
        } 
        // Unknown command
        else {
            cout << "Unknown command." << endl;
        }
    }

    return 0;
}

// Function to display the current room description and exits
void displayRoom(const Room& room) {
    cout << room.description << endl;
    cout << "Exits: ";
    for (auto exit : room.exits) {
        cout << exit.first << " ";
    }
    cout << endl;
}

// Function to display items in the room
void displayItems(const vector<string>& items) {
    cout << "Items in the room: ";
    for (auto item : items) {
        cout << item << " ";
    }
    cout << endl;
}

// Function to display the player's inventory
void displayInventory(const vector<Item>& inventory) {
    cout << "Inventory: ";
    for (auto item : inventory) {
        cout << item.name << " ";
    }
    cout << endl;
}