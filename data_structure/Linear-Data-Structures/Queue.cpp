#include <iostream>
using namespace std;

class Queue {
  private:
    int *arr;
    size_t front;
    size_t rear;
    size_t size;

  public:
    Queue(size_t s) : size(s), front(0), rear(0) { arr = new int[s]; }
    ~Queue() { delete[] arr; }

    void enqueue(int value) {
        arr[rear] = value;
        rear++;
    }
    int dequeue() {
        if (isEmpty()) {
            return -1;
        }
        return arr[front++];
    }
    int peek() { return arr[front]; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return rear == size - 1; }
    void display() {
        cout << "[";
        for (size_t i = front; i < rear; i++) {
            cout << arr[i];
            if (i < rear - 1) {
                cout << ", ";
            }
        }
        cout << "]\n";
    }
};

int main() {
    Queue q(5);
    q.enqueue(5);
    q.display();
    q.enqueue(4);
    q.display();
    q.enqueue(88);
    q.display();
    q.enqueue(69);
    q.display();
    q.dequeue();
    q.display();
    return 0;
}
