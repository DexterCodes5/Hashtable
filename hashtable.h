#include <windows.h>

template <typename T> 
class Node {
public:
    std::string key;
    T value;
    Node *next;
    
    Node(std::string s, T val) :key{s}, value{val}, next{nullptr} {} 
    ~Node() {
        if (next != nullptr)
            delete next;
    }
};

template <typename T> 
class Hashtable {
    
    Node<T> **table;
    int cs; // total entries that have been inserted
    int ts; // size of table
    
    int hashFn(std::string s) {
        int idx{};
        int pw{1};
        
        for (auto c: s) {
            idx = (idx + c*pw) % ts;
            pw = (pw*29) % ts;
        }
        return idx;
    }
    
    void rehash() {
        // Save the ptr to the oldTable and we will do insertions in the new table
        std::cout << "In rehash method\n";
        
        Node<T> **oldTable = table;
        
        // increase table size
        cs = 0;
        int oldTs = ts;
        ts = 2*ts + 1;
        table = new Node<T>*[ts]; // you should make it prime
        
        for (int i = 0; i < ts; i++) {
            table[i] = nullptr;
        }
        
        // Copy elements from old table to new table
        for (int i = 0; i < oldTs; i++) {
            
            Node<T> *temp = oldTable[i];
            
            while (temp != nullptr) {
                std::string k = temp->key;
                T v = temp->value;
                // happen in the new table
                insert(k,v);
                temp = temp->next;
            }
            
            // destroy the ith linked list
            if (oldTable[i] != nullptr) {
                delete oldTable[i];
            }
        }
        delete[] oldTable;
    }
public:
    Hashtable(int def_s = 7) :cs{0}, ts{def_s} {
        table = new Node<T>*[ts];
        
        for (int i = 0; i < ts; i++) {
            table[i] = nullptr;
        }
    }
    
    T& operator[](std::string k) {
        // return the value
        // if key is not found then create a new node and return
        // return the existing node
        
        T *val = search(k);
        if (val == nullptr) {
            T obj;
            insert(k,obj);
            val = search(k);
        }
        
        return *val;
        
    }
    
    
    void insert(std::string s, T val) {
        
        int idx = hashFn(s);
        
        Node<T> *n = new Node<T>(s,val);
        
        // Insertion at the head of the linked list
        n->next = table[idx];
        table[idx] = n;
        
        cs++;
        float load_factor = cs/float(ts);
        
        if (load_factor > 0.7) {
            rehash();
        }
    }
    
    bool isPresent(std::string k) {
        int idx = hashFn(k);
        
        Node<T> *temp = table[idx];
        while (temp != nullptr) {
            if (temp->key == k) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    
    T *search(std::string k) {
        if (!isPresent(k)) {
            std::cout << "Error " << k << " is not in the table\n";
            return nullptr;
        }
        int idx = hashFn(k);
        
        Node<T> *temp = table[idx];
        while (temp != nullptr) {
            if (temp->key == k) {
                return &temp->value;
            }
            temp = temp->next;
        }
        
    }
    
    void erase(std::string k) {
        if (!isPresent(k)) {
            std::cout << "Error " << k << " isn't in the table\n";
            return;
        }
        int idx = hashFn(k);
        
        Node<T> *table_it = table[idx];
        
        if (table_it->key == k && table_it->next == nullptr) {
            table_it->key = "0";
            delete table_it;
            table_it = nullptr;
            
            return;
        }
        while (table_it != nullptr) {
            if (table_it->next->key == k) {
                break;
            }
            table_it = table_it->next;
        }
        
        Node<T> *temp = table_it->next;
        table_it->next = table_it->next->next;
        temp->next = nullptr;
        delete temp;
    }
    
    void print() {
        for (int i = 0; i < ts; i++) {
            std::cout << "Bucket " << i << "->";
            Sleep(100);
            Node<T> *n = table[i];
            while (n != nullptr) {
                std::cout << "Key = " << n->key << ", Value = " << n->value << "->";
                n = n->next;
                Sleep(100);
            }
            std::cout << "null\n";
        }
    }
};