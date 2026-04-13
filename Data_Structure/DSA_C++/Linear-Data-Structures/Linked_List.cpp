#include <cassert>
#include <iostream>

using namespace std;

template <typename T> class Circular_Singly_List {
  private:
    struct Node {
        T data;
        Node *next;
    };
    size_t size;
    Node *head;
    Node *tail;

    Node *create_node(T data) { return new Node{data, nullptr}; }

  public:
    Circular_Singly_List() : size(0), head(nullptr), tail(nullptr) {}

    Circular_Singly_List(const Circular_Singly_List &other)
        : size(0), head(nullptr), tail(nullptr) {
        if (!other.head)
            return;
        Node *curr = other.head;
        do {
            insert_at_end(curr->data);
            curr = curr->next;
        } while (curr != other.head);
    }

    Circular_Singly_List &operator=(const Circular_Singly_List &other) {
        if (this == &other)
            return *this;
        clear();
        if (other.head) {
            Node *curr = other.head;
            do {
                insert_at_end(curr->data);
                curr = curr->next;
            } while (curr != other.head);
        }
        return *this;
    }

    void insert_at_beginning(T data) {
        Node *node = create_node(data);
        if (!head) {
            head = tail = node;
            node->next = head;
        } else {
            node->next = head;
            head = node;
            tail->next = head;
        }
        size++;
    }

    void insert_at_end(T data) {
        Node *node = create_node(data);
        if (!head) {
            head = tail = node;
            node->next = head;
        } else {
            tail->next = node;
            tail = node;
            tail->next = head;
        }
        size++;
    }

    void delete_head() {
        if (!head)
            return;
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node *temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        size--;
    }

    void delete_end() {
        if (!head)
            return;
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node *curr = head;
            while (curr->next != tail) {
                curr = curr->next;
            }
            delete tail;
            tail = curr;
            tail->next = head;
        }
        size--;
    }

    void delete_by_value(T value) {
        if (!head)
            return;

        if (head->data == value) {
            delete_head();
            return;
        }

        Node *curr = head;

        while (curr->next != head && curr->next->data != value) {
            curr = curr->next;
        }

        if (curr->next->data == value) {
            Node *to_delete = curr->next;
            if (to_delete == tail) {
                tail = curr;
            }
            curr->next = to_delete->next;
            delete to_delete;
            size--;
        }
    }

    void traverse_print() const {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        Node *curr = head;
        do {
            cout << "[" << curr->data << "] -> ";
            curr = curr->next;
        } while (curr != head);
        cout << "(HEAD)" << endl;
    }

    void clear() {
        while (size > 0)
            delete_head();
    }

    ~Circular_Singly_List() { clear(); }

    size_t count() const { return size; }
};

int main() { return 0; }
