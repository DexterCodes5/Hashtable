#include <iostream>
#include <hashtable.h>

int main(){
    Hashtable<int> h;
    
    h.insert("Mango", 100);
    h.insert("Apple", 120);
    h.insert("Banana", 140);
    h.insert("Orange", 200);
    h.insert("Kiwi", 210);
    h.insert("Papaya", 220);
    h.insert("Peach", 200);
    
    h.print();
    
    std::string f{};
    std::cout << "say Apple\n";
    std::cin >> f; 
    
    int *price = h.search(f);
    if (price) {
        std::cout << "Price is " << *price << "\n";
    }

    h.erase("Orange");
    
    h.print();
    
    h.erase("Apple");
    
    h.print();
    
    h["newFruit"] = 200;
    std::cout << "New fruit cost : " << h["newFruit"] << std::endl;
    
    h["newFruit"] += 20;
    std::cout << "UPDATE: New fruit cost : " << h["newFruit"] << std::endl;
    
    return 0;
}
