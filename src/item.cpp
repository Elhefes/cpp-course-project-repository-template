#ifndef ITEMINCPPLOL
#define ITEMINCPPLOL
#include <iostream>
#include <vector>

class Item {
 public:
  Item(std::string name, int quantity) : name(name), quantity(quantity) {}

  void print() {
    std::cout << "Item: " << name << " (Quantity: " << quantity << ")\n";
  }

 private:
  std::string name;
  int quantity;
};

class Inventory {
 public:
  void addItem(Item &item) {
    items.push_back(item);
  }

  void printInventory() {
    if (items.empty()) {
      std::cout << "Inventory is empty.\n";
    } else {
      std::cout << "Inventory Contents:\n";
      for (Item &item : items) {
        item.print();
      }
    }
  }

 private:
  std::vector<Item> items;
};
#endif

