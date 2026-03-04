
#include <iostream>
using namespace std;


template<typename T>
class forward_list {
private:
    struct node {
        T data;
        node *next;

        node(const T &value) : data(value), next(nullptr) {}
    };

    node *root;
    std::size_t size;

public:
    forward_list() : root(nullptr), size(0) {
    }

    ~forward_list() {
        clear();
    }

    forward_list(const forward_list &other) : root(nullptr), size(0) {
        node *temp = other.root;
        while (temp != nullptr) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    forward_list& operator=(const forward_list &other) {
        if (this != &other) {
            clear();
            node *temp = other.root;
            while (temp != nullptr) {
                push_back(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    forward_list(forward_list &&other) noexcept : root(nullptr), size(0) {
        root = other.root;
        size = other.size;
        other.root = nullptr;
        other.size = 0;
    }

    forward_list& operator=(forward_list &&other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            size = other.size;
            other.root = nullptr;
            other.size = 0;
        }
        return *this;
    }

    //ИТЕРАТОРЫ

    class iterator {
    public:
        node* ptr;
        iterator(node* ptr) : ptr(ptr) {}
        T& operator*() {
            return ptr->data;
        }
        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        bool operator!=(const iterator &other) {
            return ptr != other.ptr;
        }
    };

    //МЕТОДЫ ДЛЯ ИТЕРАТОРОВ

    iterator begin() {
        return iterator(root);
    }
    iterator end() {
        return iterator(nullptr);
    }
    iterator begin() const {
        return iterator(root);
    }
    iterator end() const {
        return iterator(nullptr);
    }
    iterator cbegin() const {
        return iterator(root);
    }
    iterator cend() const {
        return iterator(nullptr);
    }

    //МЕТОДЫ

    std::size_t get_size() const {
        return size;
    }

    void push_front(const T &value) {
        node *new_node = new node(value);
        new_node->next = root;
        if (root == nullptr) {
            root = new_node;
        } else {
            root = new_node;
        }
        ++size;
    };

    void pop_front() {
        node *temp = root;
        root = temp->next;
        delete temp;
        --size;
    }

    void push_back(const T &value) {
        node *new_node = new node(value);
        new_node->next = nullptr;
        if (root == nullptr) {
            root = new_node;
        } else {
            node *temp = root;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        ++size;
    }

    void pop_back() {
        if (size == 0) {
            return;
        } else if (size == 1) {
            pop_front();
        } else {
            node *temp = root;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            delete temp;
            temp = nullptr;
        }
        --size;
    }

    void clear() {
        while (root != nullptr) {
            pop_front();
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const forward_list &list) {
        node *temp = list.root;
        while (temp != nullptr) {
            os << temp->data << " ";
            temp = temp->next;
        }
        os << endl;
        return os;
    }

    forward_list operator+(const forward_list &other) const {
        forward_list result;
        node *temp = root;
        while (temp != nullptr) {
            result.push_back(temp->data);
            temp = temp->next;
        }
        temp = other.root;
        while (temp != nullptr) {
            result.push_back(temp->data);
            temp = temp->next;
        }
        return result;
    }
};


int main() {

    forward_list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    forward_list<int> list2;
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);

    cout << "Lists:" << endl;
    cout << "List1 (size=" << list1.get_size() << "): " << list1;
    cout << "List2 (size=" << list2.get_size() << "): " << list2;
    cout << endl;

    forward_list<int> concatenated_list = list1 + list2;
    cout << "Conc list (List1 + List2, size="
         << concatenated_list.get_size() << "): " << concatenated_list;
    cout << endl;

    cout << "Iterator: ";
    for (auto it = concatenated_list.cbegin(); it != concatenated_list.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    concatenated_list.clear();
    cout << "clear(): size=" << concatenated_list.get_size() << endl;

    return 0;
}

