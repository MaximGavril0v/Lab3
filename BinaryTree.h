#ifndef LAB3_BINARYTREE_H
#define LAB3_BINARYTREE_H

#include <iostream>
#include <cstring>
#include "ArraySequence.h"
#include "ListSequence.h"

using namespace std;

template <class T>
class BinaryTree {
private:
    class Node;
    Node *root;

    class Node {
    private:
        T data;
        Node *right;
        Node *left;

    public:
        Node(T data, Node *left = nullptr, Node *right = nullptr) {
            this->data = data;
            this->right = right;
            this->left = left;
        }

        Node *GetRight() {
            return right;
        }

        Node *GetLeft() {
            return left;
        }

        void SetRight(Node *node) {
            this->right = node;
        }

        void SetLeft(Node *node) {
            this->left = node;
        }

        T &GetItem() {
            return data;
        }
    };

public:
    BinaryTree() {
        root = nullptr;
    }

    explicit BinaryTree(Node *node) {
        root = node;
    }

    explicit BinaryTree(Sequence<T> *items) : BinaryTree(){
        for (int i = 0; i < items->GetLength(); i++)
            Add(items->operator[](i));
    }

    Node *GetRoot() {
        return root;
    }

    void Add(T item) {
        if (root) {
            if (item > root->GetItem()) {
                if (root->GetRight()) {
                    BinaryTree<T> sub_tree(root->GetRight());
                    sub_tree.Add(item);
                } else {
                    Node *new_node = new Node(item);
                    root->SetRight(new_node);
                }
            } else if (item < root->GetItem()) {
                if (root->GetLeft()) {
                    BinaryTree<T> sub_tree(root->GetLeft());
                    sub_tree.Add(item);
                } else {
                    Node *new_node = new Node(item);
                    root->SetLeft(new_node);
                }
            }
            else throw invalid_argument("BST cannot have two equal values");
        }
        else
            root = new Node(item);
        Balance();
    }

    void Remove(T item) {
        if (root) {
            if (item > root->GetItem()) {
                if (root->GetRight()) {
                    BinaryTree<T> sub_tree(root->GetRight());
                    sub_tree.Remove(item);
                    root->SetRight(sub_tree.root);
                } else
                    throw invalid_argument("item does not exist");
            } else if (item < root->GetItem()) {
                if (root->GetLeft()) {
                    BinaryTree<T> sub_tree(root->GetLeft());
                    sub_tree.Remove(item);
                    root->SetLeft(sub_tree.root);
                } else
                    throw invalid_argument("item does not exist");
            } else {
                if (root->GetLeft() && root->GetRight()) {
                    Node *current = root->GetLeft();
                    while (current->GetRight())
                        current = current->GetRight();
                    root->GetItem() = current->GetItem();
                    BinaryTree<T> sub_tree(root->GetLeft());
                    sub_tree.Remove(current->GetItem());
                    root->SetLeft(sub_tree.root);
                } else if (root->GetLeft()) {
                    Node *temp = root;
                    root = root->GetLeft();
                    delete temp;
                } else if (root->GetRight()) {
                    Node *temp = root;
                    root = root->GetRight();
                    delete temp;
                } else {
                    delete root;
                    root = nullptr;
                }
            }
            Balance();
        } else throw out_of_range("BST is empty");
    }

    bool Contains(T item) {
        if (item > root->GetItem()) {
            if (root->GetRight()) {
                BinaryTree<T> sub_tree(root->GetRight());
                sub_tree.Contains(item);
            } else
                return false;
        }
        else if (item < root->GetItem()) {
            if (root->GetLeft()) {
                BinaryTree<T> sub_tree(root->GetLeft());
                sub_tree.Contains(item);
            } else
                return false;
        }
        else return true;
    }

    int GetHeight() {
        if (root) {
            if (root->GetRight() || root->GetLeft()) {
                BinaryTree<T> left_sub_tree(root->GetLeft());
                BinaryTree<T> right_sub_tree2(root->GetRight());
                return max(left_sub_tree.GetHeight(), right_sub_tree2.GetHeight()) + 1;
            }
            else return 0;
        }
        else return -1;
    }

    BinaryTree<T> GetSubtree(Node *node) {
        BinaryTree<T> res(node);
        return res;
    }

    bool Contains(BinaryTree<T> &subtree) {
        if (!subtree.root) {
            return true;
        }
        if (subtree.root->GetItem() > root->GetItem()) {
            if (root->GetRight()) {
                BinaryTree<T> right_subtree(root->GetRight());
                right_subtree.Contains(subtree);
            }
            else return false;
        }
        else if (subtree.root->GetItem() < root->GetItem()) {
            if (root->GetLeft()) {
                BinaryTree<T> left_subtree(root->GetLeft());
                left_subtree.Contains(subtree);
            }
            else return false;
        }
        else {
            if ((subtree.root->GetRight() && !(root->GetRight())) || (subtree.root->GetLeft() && !(root->GetLeft())))
                return false;
            else if (!subtree.root->GetLeft() && !subtree.root->GetRight())
                return subtree.root->GetItem() == root->GetItem();
            else {
                BinaryTree<T> this_right_subtree(root->GetRight());
                BinaryTree<T> other_right_subtree(subtree.root->GetRight());
                BinaryTree<T> this_left_subtree(root->GetLeft());
                BinaryTree<T> other_left_subtree(subtree.root->GetLeft());
                return this_right_subtree.Contains(other_right_subtree) && this_left_subtree.Contains(other_left_subtree);
            }
        }
    }

    ListSequence<T>* toSequence() {
        if (!root) {
            auto *res = new ListSequence<T>();
            return res;
        }
        if (root->GetLeft() || root->GetRight()) {
            BinaryTree<T> right_subtree(root->GetRight());
            BinaryTree<T> left_subtree(root->GetLeft());
            ListSequence<T> *temp = left_subtree.toSequence();
            temp->Append(root->GetItem());
            ListSequence<T> *res = temp->Concat(right_subtree.toSequence());
            return res;
        }
        else {
            auto *res = new ListSequence<T>();
            res->Append(root->GetItem());
            return res;
        }
    }

    BinaryTree<T> Map(T (*f)(T)) {
        ListSequence<T> *sequence = toSequence();
        ListSequence<T> *mapped_sequence = sequence->Map(f);
        BinaryTree<T> res = BinaryTree(mapped_sequence);
        return res;
    }

    BinaryTree<T> Where(bool (*f)(T)) {
        ListSequence<T> *sequence = toSequence();
        ListSequence<T> *new_sequence = sequence->Where(f);
        BinaryTree<T> res = BinaryTree(new_sequence);
        return res;
    }

    T Reduce(T (*f)(T, T), const T c) {
        ListSequence<T> *sequence = toSequence();
        return sequence->Reduce(f, c);
    }

    void Traversal() {
        ListSequence<T> *sequence = toSequence();
        for (int i = 0; i < sequence->GetLength(); i++)
            cout << sequence->operator[](i) << " ";
        cout << endl;
    }


protected:

    int GetHeight(const Node *node) {
        if (node->data > root->GetItem()) {
            BinaryTree<T> sub_tree(root->GetRight());
            return sub_tree.GetHeight(node) + 1;
        }
        else if (node->data < root->GetItem()) {
            BinaryTree<T> sub_tree(root->GetLeft());
            return sub_tree.GetHeight(node) + 1;
        }
        else return 0;
    }


    void Balance() {
        if (root) {
            BinaryTree<T> left_sub_tree(root->GetLeft());
            BinaryTree<T> right_sub_tree(root->GetRight());
            while (right_sub_tree.GetHeight() - left_sub_tree.GetHeight() > 1) {
                Node *temp = root->GetRight();
                root->SetRight(temp->GetLeft());
                temp->SetLeft(root);
                root = temp;
                left_sub_tree = BinaryTree<T>(root->GetLeft());
                right_sub_tree = BinaryTree<T>(root->GetRight());
            }
            while (left_sub_tree.GetHeight() - right_sub_tree.GetHeight() > 1) {
                Node *temp = root->GetLeft();
                root->SetLeft(temp->GetRight());
                temp->SetRight(root);
                root = temp;
                left_sub_tree = BinaryTree<T>(root->GetLeft());
                right_sub_tree = BinaryTree<T>(root->GetRight());
            }
        }
    }

};


#endif //LAB3_BINARYTREE_H
