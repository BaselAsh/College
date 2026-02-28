#include <iostream>
using namespace std;

template <typename T> class Linked_List {
  private:
    struct Node {
        T data;
        Node *next;
    };
    int size;
    Node *head;

  public:
    Linked_List() {
        size = 0;
        head = nullptr;
    }
    Linked_List(T data) {
        size = 1;
        head = create_node(data);
    }
    Linked_List(const Linked_List &other) {
        if (other.head == nullptr) {
            head = nullptr;
            size = 0;
            return;
        }

        head = create_node(other.head->data);
        size = 1;

        Node *current_other = other.head->next;
        while (current_other != nullptr) {
            insert_at_end(current_other->data);
            current_other = current_other->next;
        }
    }

    Linked_List &operator=(const Linked_List &other) {
        if (this == &other)
            return *this;

        while (head != nullptr) {
            delete_head();
        }

        if (other.head != nullptr) {
            head = create_node(other.head->data);
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
        if (!head) {
            head = node;
            return;
        } else {
            Node *current_node = head;
            while (current_node->next != nullptr) {
                current_node = current_node->next;
            }
            current_node->next = node;
        }
        size++;
    }

    void insert_at_beginning(T data) {
        Node *node = create_node(data);
        node->next = head;
        head = node;
        size++;
    }

    void insert_at_index(T data, int index) {
        if (index >= size) {
            cout << "Invalid position" << endl;
        } else if (index == 0) {
            insert_at_beginning(data);
        } else if (index == size - 1) {
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

    void modify_at_position(T data, int position) {
        Node *current_node = head;
        if (size < position) {
            cout << "Invalid position" << endl;
            return;
        }
        for (int i = 0; i < position - 1; i++) {
            current_node = current_node->next;
        }
        current_node->data = data;
    }

    void delete_head() {
        if (size < 1) {
            cout << "There linked list is empty." << endl;
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node *temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
        }
        size--;
    }

    void delete_end() {
        Node *current_node = head;
        Node *temp;
        if (size < 1) {
            cout << "There linked list is empty." << endl;
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            while (current_node->next->next != nullptr) {
                current_node = current_node->next;
            }
            temp = current_node->next;
            current_node->next = nullptr;
            delete temp;
            temp = nullptr;
        }
        size--;
    }

    void delete_by_value(T value) {
        if (size < 1) {
            cout << "There linked list is empty." << endl;
            return;
        } else if (size == 1 && head->data == value) {
            delete_head();
        } else if (head->data == value) {
            delete_head();
        } else {
            Node *current_node = head;
            while (current_node->next != nullptr) {
                if (current_node->next->data == value) {
                    current_node->next = current_node->next->next;
                    Node *to_delete = current_node->next;
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
        bool flag = false;
        while (current_node != nullptr) {
            if (current_node->data == value) {
                flag = true;
                break;
            }
            current_node = current_node->next;
            count++;
        }
        if (flag) {
            cout << "Node found at index " << count << endl;
            return count;
        } else {
            cout << "Element was not found" << endl;
            return -1;
        }
    }

    void reverse() {
        if (size <= 1) {
            cout << "The list is too small" << endl;
        }
        if (size == 2) {
            Node *temp = head->next;
            head->next->next = head;
            head->next = nullptr;
            head = temp;
        } else {
            Node *next = nullptr;
            Node *current = head;
            Node *prev = nullptr;
            while (current != nullptr) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
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

int main() {
    Linked_List<int> linked_list;

    linked_list.insert_at_end(9);
    linked_list.insert_at_end(2);
    linked_list.insert_at_end(5);
    linked_list.insert_at_end(7);
    linked_list.insert_at_end(8);
    linked_list.traverse_print_list();

    linked_list.reverse();
    linked_list.traverse_print_list();

    return 0;
}
