#include <cassert>
#include <iostream>
using namespace std;

template <typename T> class Linked_List {
  private:
    struct Node {
        T data;
        Node *next;
    };
    size_t size;
    Node *head;
    Node *tail;

  public:
    Linked_List() {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    Linked_List(T data) {
        size = 1;
        head = create_node(data);
        tail = head;
    }
    Linked_List(const Linked_List &other) {
        if (other.head == nullptr) {
            head = nullptr;
            tail = head;
            size = 0;
            return;
        }

        head = create_node(other.head->data);
        tail = head;
        size = 1;

        Node *current_other = other.head->next;
        while (current_other != nullptr) {
            insert_at_end(current_other->data);
            tail = current_other;
            current_other = current_other->next;
        }
    }

    Linked_List &operator=(const Linked_List &other) {
        if (this == &other)
            return *this;

        while (head != nullptr) {
            delete_head();
        }
        head = tail = nullptr;
        size = 0;

        if (other.head != nullptr) {
            head = create_node(other.head->data);
            tail = head;
            size = 1;
            Node *current_other = other.head->next;
            while (current_other != nullptr) {
                insert_at_end(current_other->data);
                current_other = current_other->next;
            }
        }
        return *this;
    }

    Node *create_node(T data) {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->next = nullptr;
        return new_node;
    }

    void insert_at_end(T data) {
        Node *node = create_node(data);
        if (head && tail) {
            tail->next = node;
            tail = node;
        } else {
            head = node;
            tail = node;
        }
        size++;
    }

    void insert_at_beginning(T data) {
        Node *node = create_node(data);
        node->next = head;
        head = node;
        size++;
        if (size == 1) {
            tail = head;
        }
    }

    void insert_at_index(T data, int index) {
        if (index >= size) {
            cout << "Invalid position" << endl;
        } else if (index == 0) {
            insert_at_beginning(data);
        } else if (index == size) {
            insert_at_end(data);
        } else {
            Node *node = create_node(data);
            Node *current_node = head;
            for (int i = 0; i < index - 1; i++) {
                current_node = current_node->next;
            }
            node->next = current_node->next;
            current_node->next = node;
            size++;
        }
    }

    void modify_at_index(T data, int position) {
        Node *current_node = head;
        if (size < position) {
            cout << "Invalid position" << endl;
            return;
        }
        for (int i = 0; i < position; i++) {
            current_node = current_node->next;
        }
        current_node->data = data;
    }

    void delete_head() {
        if (size < 1) {
            cout << "The linked list is empty." << endl;
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node *temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
        }
        size--;
    }

    void delete_end() {
        if (size < 1) {
            cout << "The linked list is empty." << endl;
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node *current_node = head;
            Node *temp;
            while (current_node->next->next != nullptr) {
                current_node = current_node->next;
            }
            temp = current_node->next;
            current_node->next = nullptr;
            tail = current_node;
            delete temp;
            temp = nullptr;
        }
        size--;
    }

    void delete_by_value(T value) {
        if (size < 1) {
            cout << "The linked list is empty." << endl;
            return;
        } else if (head->data == value) {
            delete_head();
        } else if (tail->data == value) {
            delete_end();
        } else {
            Node *current_node = head;
            while (current_node->next != nullptr) {
                if (current_node->next->data == value) {
                    Node *to_delete = current_node->next;
                    current_node->next = current_node->next->next;
                    delete to_delete;
                    to_delete = nullptr;
                    size--;
                    return;
                }
                current_node = current_node->next;
            }
        }
    }

    void traverse_print_list() const {
        Node *current_node = head;
        while (current_node != nullptr) {
            cout << "[" << current_node->data << "] -> ";
            current_node = current_node->next;
        }
        cout << "NULL" << endl;
    }

    int search_by_value(T value) const {
        Node *current_node = head;
        int count = 0;
        while (current_node != nullptr) {
            if (current_node->data == value) {
                return count;
            }
            current_node = current_node->next;
            count++;
        }
        return -1;
    }

    void reverse() {
        if (size <= 1) {
            cout << "The list is too small" << endl;
        } else {
            tail = head;
            Node *next = nullptr;
            Node *current_node = head;
            Node *prev = nullptr;
            while (current_node != nullptr) {
                next = current_node->next;
                current_node->next = prev;
                prev = current_node;
                current_node = next;
            }
            head = prev;
        }
    }

    ~Linked_List() {
        Node *current_node = head;
        Node *temp;
        while (current_node != nullptr) {
            temp = current_node;
            current_node = current_node->next;
            delete temp;
            temp = nullptr;
        }
    }

    int count() const { return size; }
};

void test_basic_operations() {
    Linked_List<int> list;

    // Test Insertion
    list.insert_at_beginning(10); // [10]
    list.insert_at_end(30);       // [10] -> [30]
    list.insert_at_index(20, 1);  // [10] -> [20] -> [30]

    assert(list.count() == 3);
    assert(list.search_by_value(20) == 1);

    // Test Modification
    list.modify_at_index(25, 1); // [10] -> [25] -> [30]
    assert(list.search_by_value(25) == 1);

    // Test Deletion
    list.delete_head(); // [25] -> [30]
    assert(list.count() == 2);

    list.delete_by_value(30); // [25]
    assert(list.count() == 1);

    list.delete_end(); // Empty
    assert(list.count() == 0);

    cout << "Basic operations passed!" << endl;
}

void test_reverse() {
    Linked_List<int> list;
    list.insert_at_end(1);
    list.insert_at_end(2);
    list.insert_at_end(3);

    list.reverse(); // Should be 3, 2, 1

    assert(list.search_by_value(3) == 0);
    assert(list.search_by_value(2) == 1);
    assert(list.search_by_value(1) == 2);

    cout << "Reverse passed!" << endl;
}

void test_copy_and_assignment() {
    Linked_List<int> list1;
    list1.insert_at_end(100);
    list1.insert_at_end(200);

    // Test Copy Constructor
    Linked_List<int> list2 = list1;
    assert(list2.count() == 2);
    assert(list2.search_by_value(100) == 0);

    // Test Assignment Operator
    Linked_List<int> list3;
    list3 = list1;
    assert(list3.count() == 2);

    // Ensure deep copy (modifying list1 shouldn't affect list3)
    list1.modify_at_index(500, 1);
    assert(list3.search_by_value(100) == 0);

    cout << "Copy and Assignment passed!" << endl;
}

int main() { return 0; }
