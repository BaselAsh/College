#include <iostream>
#include <string>

using namespace std;

struct Node {
    string taskName;
    int priority;
    Node *next;

    Node(string name, int p) : taskName(name), priority(p), next(nullptr) {}
};

class PriorityQueue {
  private:
    Node *head;

  public:
    PriorityQueue() : head(nullptr) {}

    bool isEmpty() { return head == nullptr; }

    void insertTask(string taskName, int priority) {
        Node *newNode = new Node(taskName, priority);

        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
        } else {

            Node *current = head;
            while (current->next != nullptr &&
                   current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    string removeHighestPriority() {
        if (isEmpty()) {
            return "Queue is empty!";
        }

        Node *temp = head;
        string name = temp->taskName;
        head = head->next;
        delete temp;
        return name;
    }

    void peekHighestPriority() {
        if (isEmpty()) {
            cout << "Nothing to peek, queue is empty." << endl;
        } else {
            cout << "Highest Priority Task: " << head->taskName << " ["
                 << head->priority << "]" << endl;
        }
    }

    void displayTasks() {
        if (isEmpty()) {
            cout << "Queue is currently empty." << endl;
            return;
        }

        Node *current = head;
        cout << "\n--- Current Task Queue ---" << endl;
        while (current != nullptr) {
            cout << "Task: " << current->taskName
                 << " | Priority: " << current->priority << endl;
            current = current->next;
        }
        cout << "--------------------------\n" << endl;
    }

    ~PriorityQueue() {
        while (!isEmpty()) {
            removeHighestPriority();
        }
    }
};

int main() {
    PriorityQueue pq;
    pq.insertTask("Finish DSA Assignment", 10);
    pq.insertTask("Buy Groceries", 3);
    pq.insertTask("Fix Waybar Config", 8);
    pq.insertTask("Study Discrete Math", 5);
    pq.displayTasks();
    pq.peekHighestPriority();
    cout << "\nRemoving: " << pq.removeHighestPriority() << endl;
    pq.displayTasks();
    return 0;
}
