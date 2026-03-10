#include <cassert>
#include <iostream>

using namespace std;

template <typename T> class Doubly_Linked_List {
  private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    size_t size;
    Node *head;
    Node *tail;
    Node *create_node(T data) { return new Node{data, nullptr, nullptr}; }

  public:
    Doubly_Linked_List() : size(0), head(nullptr), tail(nullptr) {}

    Doubly_Linked_List(const Doubly_Linked_List &other)
        : size(0), head(nullptr), tail(nullptr) {
        Node *curr = other.head;
        while (curr) {
            insert_at_end(curr->data);
            curr = curr->next;
        }
    }

    Doubly_Linked_List &operator=(const Doubly_Linked_List &other) {
        if (this == &other)
            return *this;
        clear();
        Node *curr = other.head;
        while (curr) {
            insert_at_end(curr->data);
            curr = curr->next;
        }
        return *this;
    }

    void insert_at_beginning(T data) {
        Node *node = create_node(data);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }

    void insert_at_end(T data) {
        Node *node = create_node(data);
        if (!tail) {
            head = tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void insert_at_index(T data, int index) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (index == 0) {
            insert_at_beginning(data);
        } else if (index == size) {
            insert_at_end(data);
        } else {
            Node *node = create_node(data);
            Node *curr = head;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            node->next = curr;
            node->prev = curr->prev;
            curr->prev->next = node;
            curr->prev = node;
            size++;
        }
    }

    void delete_head() {
        if (!head)
            return;
        Node *temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void delete_end() {
        if (!tail)
            return;
        Node *temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    void delete_by_value(T value) {
        Node *curr = head;
        while (curr) {
            if (curr->data == value) {
                if (curr == head)
                    delete_head();
                else if (curr == tail)
                    delete_end();
                else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    size--;
                }
                return;
            }
            curr = curr->next;
        }
    }

    void traverse_forward() const {
        Node *curr = head;
        while (curr) {
            cout << "[" << curr->data << "] <-> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    void traverse_backward() const {
        Node *curr = tail;
        while (curr) {
            cout << "[" << curr->data << "] <-> ";
            curr = curr->prev;
        }
        cout << "NULL" << endl;
    }

    void clear() {
        while (head)
            delete_head();
    }

    ~Doubly_Linked_List() { clear(); }

    size_t count() const { return size; }
};

int main() { return 0; }
