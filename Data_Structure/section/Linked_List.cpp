#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};
class Linked_List {
  private:
    int size = 0;
    Node *head = new Node;

  public:
    Linked_List(int data) {
        size = 1;
        head->data = data;
        head->next = nullptr;
    }
    Node *create_node(int data) {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->next = nullptr;
        return new_node;
    }
    void add_node_to_end(Node *node) {
        Node *current_node = head;
        while (current_node->next != nullptr) {
            current_node = current_node->next;
        }
        current_node->next = node;
        size++;
    }
    void add_to_head(Node *node) {
        node->next = head;
        head = node;
        size++;
    }
    void traverse_print_list() {
        Node *current_node = head;
        while (current_node != nullptr) {
            cout << "[" << current_node->data << "] -> ";
            current_node = current_node->next;
        }
        cout << "NULL" << endl;
    }
    void insert_at_position(Node *node, int position) {
        Node *current_node = head;
        Node *temp;
        if (size < position) {
            cout << "Invalid position" << endl;
            return;
        }
        for (int i = 0; i < position - 1; i++) {
            current_node = current_node->next;
        }
        temp = current_node->next;
        current_node->next = node;
        node->next = temp;
        size++;
    }
    void search_by_value(int value) {
        Node *current_node = head;
        int count = 0;
        bool flag = false;
        while (current_node->next != nullptr) {
            if (current_node->data == value) {
                flag = true;
                break;
            }
            current_node = current_node->next;
            count++;
        }
        if (flag) {
            cout << "Node found at index " << count << endl;
        } else {
            cout << "Element was not found" << endl;
        }
    }
    // ~Linked_List() {
    //     Node *current_node = head;
    //     Node *temp;
    //     while (current_node->next != nullptr) {
    //         temp = current_node->next;
    //         delete current_node;
    //         current_node = temp;
    //     }
    // }
    void count() { cout << "The Linked List Size Is " << size << endl; }
};

int main() {
    cout << "Welcome to my linked list app." << endl;
    Linked_List linked_list = Linked_List(5);
    Node *new_node = linked_list.create_node(9);
    Node *new_node1 = linked_list.create_node(8);
    Node *new_node2 = linked_list.create_node(7);

    linked_list.add_node_to_end(new_node);
    linked_list.traverse_print_list();

    linked_list.insert_at_position(new_node1, 1);
    linked_list.traverse_print_list();

    linked_list.add_node_to_end(new_node2);
    linked_list.traverse_print_list();

    linked_list.search_by_value(8);

    linked_list.count();

    delete new_node;
    delete new_node1;
    delete new_node2;
    return 0;
}
