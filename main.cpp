#include <iostream>
#include "BinaryTree.h"

const char *operations[] = {"0. Quit",
                          "1. Add item",
                          "2. Remove item",
                          "3. Search item",
                          "4. Search subtree",
                          "5. Walk the tree and print the items"};

const char *subtree_creation[] = {"0. Done",
                                  "1. Add item"};

template<int N>
int dialog(const char *(&msgs)[N]) {
    int choice;
    for (int i = 0; i < N; ++i)
        cout << msgs[i] << endl;
    cout << "Make your choice: \n";
    cin >> choice;
    return choice;
}

void UI() {
    BinaryTree<int> tree;
    int res = 1;
    while (res != 0) {
        res = dialog(operations);
        switch (res) {
            case 0:
                break;
            case 1: {
                int item;
                cout << "Enter an item to add: ";
                cin >> item;
                tree.Add(item);
                break;
            }
            case 2: {
                int item;
                cout << "Enter an item to remove: ";
                cin >> item;
                tree.Remove(item);
                break;
            }
            case 3: {
                int item;
                cout << "Enter an item to search: ";
                cin >> item;
                cout << tree.Contains(item) << endl;
                break;
            }
            case 4: {
                BinaryTree<int> subtree;
                int res1 = 2;
                while (res1 != 0) {
                    cout << "Create the subtree to be searched" << endl;
                    res1 = dialog(subtree_creation);
                    if (res1 != 0) {
                        int item;
                        cout << "Enter an item to add to the searched subtree: ";
                        cin >> item;
                        subtree.Add(item);
                    }
                }
                cout << tree.Contains(subtree) << endl;
                break;
            }
            case 5: {
                tree.Traversal();
            }
            default:
                break;
        }
    }
}

int main() {
    UI();
    return 0;
}
