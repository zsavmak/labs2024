#include <iostream>
#include <string>
#include <iomanip>
//#include <conio.h>

using namespace std;

// Structure to store data in a tree node
struct Leaf {
    string FIO;
    int key;
};

// Structure representing a node in the search tree
struct Tree {
    Tree* left;  // Left child
    Tree* right; // Right child
    Leaf leaf;   // Data stored in the tree node
};

// Structure for queue node, used for breadth-first traversal
struct QueueNode {
    Tree* node;       // Pointer to the tree node
    int level;        // Level of the node in the tree
    QueueNode* next;  // Pointer to the next node in the queue

    QueueNode(Tree* n, int l) : node(n), level(l), next(nullptr) {}
};

// Queue for breadth-first traversal of the tree
struct Queue {
    QueueNode* front;  // Pointer to the first element in the queue
    QueueNode* rear;   // Pointer to the last element in the queue

    Queue() : front(nullptr), rear(nullptr) {}

    // Add an element to the queue
    void push(Tree* node, int level) {
        QueueNode* newNode = new QueueNode(node, level);
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
    }

    // Remove an element from the queue
    void pop() {
        if (front) {
            QueueNode* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    // Check if the queue is empty
    bool empty() {
        return front == nullptr;
    }

    // Get the front element of the queue
    pair<Tree*, int> frontElement() {
        if (front) {
            return { front->node, front->level };
        }
        return { nullptr, -1 };
    }
};

void addLeaf(Tree* root, int key, string FIO);
void findAndView(Tree* root, int key);
Tree* deleteNode(Tree* root, int key);
void viewInOrder(Tree* root, int level);
void viewPreOrder(Tree* root, int level);
void viewPostOrder(Tree* root, int level);
void makeBalancedTree(Tree** root, int start, int end, Leaf arr[]);
void createTree(Tree** root, int n, Leaf arr[]);
void deleteTree(Tree* root);
void quickSort(Leaf[], int, int);
int calculateLeavesPerLevel(Tree* root, int*& leafCountPerLevel);

int main() {
    int n;
    Leaf arr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    // Input data for each tree node
    for (int i = 0; i < n; i++) {
        cout << "Enter FIO: ";
        cin.ignore();
        getline(cin, arr[i].FIO);
        cout << "Enter key: ";
        cin >> arr[i].key;
    }

    // Sort the array of nodes
    quickSort(arr, 0, n - 1);

    // Create a balanced tree from the sorted array
    Tree* tree = nullptr;
    createTree(&tree, n, arr);

    char choice;

    while (true) {
        //system("cls");
        cout << "Menu:\n"
            << "1. Add information to the tree\n"
            << "2. Find an element by key\n"
            << "3. Delete an element by key\n"
            << "4. Print in pre-order\n"
            << "5. Print in post-order\n"
            << "6. Print in order of increasing key\n"
            << "7. Determine the number of leaves at each level\n"
            << "0. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            string FIO;
            int key;
            cout << "Enter FIO: ";
            cin.ignore();
            getline(cin, FIO);
            cout << "Enter key: ";
            cin >> key;
            addLeaf(tree, key, FIO);
            break;
        }
        case '2': {
            int key;
            cout << "Enter key: ";
            cin >> key;
            findAndView(tree, key);
            break;
        }
        case '3': {
            int key;
            cout << "Enter key: ";
            cin >> key;
            tree = deleteNode(tree, key);
            break;
        }
        case '4':
            viewPreOrder(tree, 0);
            //_getch();
            break;
        case '5':
            viewPostOrder(tree, 0);
            //_getch();
            break;
        case '6':
            viewInOrder(tree, 0);
            //_getch();
            break;
        case '7': {
            int* leafCountPerLevel;
            int levels = calculateLeavesPerLevel(tree, leafCountPerLevel);
            for (int k = 0; k <= levels; k++)
                cout << "Level: " << k << " Number of leaves: " << leafCountPerLevel[k] << endl;
            delete[] leafCountPerLevel;
            //_getch();
            break;
        }
        case '0':
            deleteTree(tree);
            return 0;
        }
    }
}

// Quick sort algorithm to sort an array of Leaf elements by key
void quickSort(Leaf arr[], int left, int right) {
    if (left >= right) return;

    int i = left, j = right;
    int pivot = arr[(left + right) / 2].key;

    // Divide and conquer pattern for quick sort
    while (i <= j) {
        while (arr[i].key < pivot) i++;
        while (arr[j].key > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

Tree* deleteNode(Tree* root, int key) {
    Tree* del = root;
    Tree* prevDel = nullptr;
    Tree* replacement;
    Tree* prevReplacement;

    // Find the node to delete
    while (del != nullptr && del->leaf.key != key) {
        prevDel = del;
        if (key < del->leaf.key)
            del = del->left;
        else
            del = del->right;
    }

    if (del == nullptr) {
        cout << "Key not found!" << endl;
        //_getch();
        return root;
    }

    // Find a replacement for the node to delete
    if (del->right == nullptr) {
        replacement = del->left;
    }
    else if (del->left == nullptr) {
        replacement = del->right;
    }
    else {
        prevReplacement = del;
        replacement = del->left;
        while (replacement->right != nullptr) {
            prevReplacement = replacement;
            replacement = replacement->right;
        }
        if (prevReplacement != del) {
            replacement->right = del->right;
            prevReplacement->right = replacement->left;
            replacement->left = prevReplacement;
        }
        else {
            replacement->right = del->right;
        }
    }

    if (del == root) root = replacement;
    else if (del->leaf.key < prevDel->leaf.key)
        prevDel->left = replacement;
    else
        prevDel->right = replacement;

    delete del;
    return root;
}

void deleteTree(Tree* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void findAndView(Tree* root, int key) {
    if (root != nullptr) {
        if (root->leaf.key == key) {
            cout << "Element is found!\n" << root->leaf.FIO << endl;
            //_getch();
            return;
        }
        findAndView(root->left, key);
        findAndView(root->right, key);
    }
}

void addLeaf(Tree* root, int key, string FIO) {
    Tree* prev = nullptr;
    Tree* current = root;
    bool isUnique = true;

    while (current && isUnique) {
        prev = current;
        if (key == current->leaf.key) {
            isUnique = false;
            cout << "Key must be unique!\n";
            //_getch();
            break;
        }
        if (key < current->leaf.key)
            current = current->left;
        else
            current = current->right;
    }

    if (isUnique) {
        Tree* newNode = new Tree;
        newNode->leaf = { FIO, key };
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (key < prev->leaf.key)
            prev->left = newNode;
        else
            prev->right = newNode;
    }
}

int calculateLeavesPerLevel(Tree* root, int*& leafCountPerLevel) {
    if (!root) {
        leafCountPerLevel = nullptr;
        return 0;
    }

    // Initialize queue for level-order traversal
    Queue q;
    q.push(root, 0);

    int* leaves = new int[1000]();
    int maxLevel = 1;
    while (!q.empty()) {
        Tree* currentNode = q.front->node;
        int currentLevel = q.front->level;
        q.pop();
        leaves[currentLevel]++;
        maxLevel = max(maxLevel, currentLevel);
        // Enqueue children with incremented level
        if (currentNode->left) q.push(currentNode->left, currentLevel + 1);
        if (currentNode->right) q.push(currentNode->right, currentLevel + 1);
    }

    // Allocate and copy the final results to the output parameter
    leafCountPerLevel = new int[maxLevel + 1]();
    for (int i = 0; i <= maxLevel; ++i) {
        leafCountPerLevel[i] = leaves[i];
    }

    delete[] leaves; // Clean up temporary storage
    return maxLevel;
}


// Recursive function to print the tree in in-order traversal
void viewInOrder(Tree* root, int level) {
    if (root) {
        viewInOrder(root->left, level + 1);
        cout << setw(level * 4) << root->leaf.key << endl;
        viewInOrder(root->right, level + 1);
    }
}

// Recursive function to print the tree in pre-order traversal
void viewPreOrder(Tree* root, int level) {
    if (root) {
        cout << setw(level * 4) << root->leaf.key << endl;
        viewPreOrder(root->left, level + 1);
        viewPreOrder(root->right, level + 1);
    }
}

// Recursive function to print the tree in post-order traversal
void viewPostOrder(Tree* root, int level) {
    if (root) {
        viewPostOrder(root->left, level + 1);
        viewPostOrder(root->right, level + 1);
        cout << setw(level * 4) << root->leaf.key << endl;
    }
}

// Recursive function to create a balanced binary search tree
void makeBalancedTree(Tree** root, int start, int end, Leaf arr[]) {
    if (start > end) return;

    int mid = (start + end) / 2;
    *root = new Tree;
    (*root)->leaf = arr[mid];
    (*root)->left = nullptr;
    (*root)->right = nullptr;

    makeBalancedTree(&(*root)->left, start, mid - 1, arr);
    makeBalancedTree(&(*root)->right, mid + 1, end, arr);
}

// Function to create a tree from an array
void createTree(Tree** root, int n, Leaf arr[]) {
    makeBalancedTree(root, 0, n - 1, arr);
}
