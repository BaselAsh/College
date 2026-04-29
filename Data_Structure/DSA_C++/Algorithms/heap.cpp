#include <algorithm> // Includes algorithms like swap() to exchange two values
#include <climits> // Provides constants like INT_MIN (the smallest possible integer)
#include <iostream> // Includes the standard input/output stream library

using namespace std; // Allows using classes/functions from the standard
                     // namespace without 'std::' prefix

class MinHeap {
  private:
    int *heap;    // A pointer used to create a dynamic array that stores heap
                  // elements
    int capacity; // The maximum number of elements the heap can hold
    int size;     // The current number of elements actually present in the heap

    /**
     * heapifyUp (Bubble Up):
     * Used after insertion to restore the heap property.
     * If a child is smaller than its parent, they swap places until the
     * property is fixed.
     */
    void heapifyUp(int i) {
        // While we aren't at the root AND the parent's value is greater than
        // the current node
        while (i != 0 && heap[get_parent(i)] > heap[i]) {
            swap(
                heap[i],
                heap[get_parent(i)]); // Exchange the values of child and parent
            i = get_parent(i); // Move the index 'i' up to the parent's position
                               // to continue checking
        }
    }

    /**
     * heapifyDown (Sift Down):
     * Used after delete_min to restore the heap property.
     * The root is compared with its children and swapped with the smallest
     * child.
     */
    void heapifyDown(int i) {
        int left = get_l_ch(i);  // Calculate the index of the left child
        int right = get_r_ch(i); // Calculate the index of the right child
        int smallest = i; // Assume the current node 'i' is the smallest for now

        // If the left child exists and is smaller than the current smallest
        // node
        if (left < size && heap[left] < heap[smallest])
            smallest = left; // Update smallest to be the left child's index

        // If the right child exists and is smaller than the current smallest
        // node
        if (right < size && heap[right] < heap[smallest])
            smallest = right; // Update smallest to be the right child's index

        // If the smallest value is no longer at index 'i', we must swap
        if (smallest != i) {
            swap(heap[i], heap[smallest]); // Move the smallest child to the
                                           // parent position
            heapifyDown(smallest); // Recursively call heapifyDown on the new
                                   // child position
        }
    }

  public:
    /**
     * Constructor: Initializes the heap with a specific capacity.
     */
    MinHeap(int cap) {
        size = 0;            // Start with an empty heap
        capacity = cap;      // Store the maximum allowed capacity
        heap = new int[cap]; // Dynamically allocate memory for the array on the
                             // heap (RAM)
    }

    /**
     * get_parent: Returns the index of the parent node.
     * Formula: (i - 1) / 2
     */
    int get_parent(int i) { return (i - 1) / 2; }

    /**
     * get_l_ch: Returns the index of the left child.
     * Formula: (2 * i) + 1
     */
    int get_l_ch(int i) { return (2 * i + 1); }

    /**
     * get_r_ch: Returns the index of the right child.
     * Formula: (2 * i) + 2
     */
    int get_r_ch(int i) { return (2 * i + 2); }

    /**
     * insert: Adds a new value to the heap.
     */
    void insert(int key) {
        if (size == capacity)
            return; // Basic error handling: don't insert if the array is full

        size++; // Increase the count of elements
        int i =
            size - 1;  // Find the index of the very last position in the array
        heap[i] = key; // Place the new value at that last position

        heapifyUp(i); // "Bubble" the value up until it's in the correct sorted
                      // position
    }

    /**
     * delete_min: Removes and returns the smallest element (the root).
     */
    int delete_min() {
        if (size <= 0)
            return INT_MAX; // Return a huge value if the heap is empty
        if (size == 1) {    // If only one element exists, just remove it
            size--;
            return heap[0];
        }

        int root = heap[0]; // Save the root value to return it later
        heap[0] = heap[size -
                       1]; // Take the very last element and move it to the root
        size--;            // Decrease the size of the heap
        heapifyDown(
            0); // Push the new root down to its proper place to restore order

        return root; // Return the original smallest value
    }

    /**
     * modify_by_index: Changes the value at a specific position.
     */
    void modify_by_index(int i, int new_val) {
        if (i >= size)
            return; // Don't modify if the index is out of bounds

        int old_val = heap[i]; // Keep track of the old value
        heap[i] = new_val;     // Apply the new value to the index

        // If the new value is smaller than the old one, it needs to move UP
        if (new_val < old_val) {
            heapifyUp(i);
        }
        // If the new value is larger than the old one, it needs to move DOWN
        else {
            heapifyDown(i);
        }
    }

    /**
     * delete_key: Deletes a specific value without using INT_MIN.
     */
    void delete_key(int key) {
        int index = -1; // 1. Start by searching for the key's index

        // 2. Locate the key in the array (Linear Search)
        for (int i = 0; i < size; i++) {
            if (heap[i] == key) {
                index = i;
                break;
            }
        }

        // 3. If the key was found, perform the swap-and-fix logic
        if (index != -1) {
            // 4. Optimization: If it's the last element, just decrease size
            if (index == size - 1) {
                size--;
                return;
            }

            // 5. Replace the target node with the very last node in the heap
            heap[index] = heap[size - 1];

            // 6. Decrease size so the old last element is "gone"
            size--;

            // 7. The node we just moved might be larger than its children...
            heapifyDown(index);

            // 8. ...OR it might be smaller than its parent.
            // We call both to ensure the Min-Heap property is restored
            // perfectly.
            heapifyUp(index);
        }
    }

    /**
     * printHeap: Utility to see the array representation of the tree.
     */
    void printHeap() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main() {
    MinHeap h(10); // Create a heap object that can hold 10 integers
    h.insert(3);   // Insert 3
    h.insert(2);   // Insert 2 (will bubble up above 3)
    h.insert(15);  // Insert 15
    h.insert(5);   // Insert 5
    h.insert(4);   // Insert 4
    h.insert(45);  // Insert 45

    cout << "Initial Min Heap Array: ";
    h.printHeap(); // Output the array state

    cout << "Extracting Min (Root): " << h.delete_min() << endl;
    h.printHeap(); // Output state after root removal

    return 0; // Standard exit for C++ programs
}
