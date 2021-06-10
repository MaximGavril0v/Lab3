#include "gtest/gtest.h"
#include "../BinaryTree.h"

int mapper(int a) {
    return -a;
}

bool where_test(int a) {
    return a % 2 == 0;
}

int reducer(int a, int b) {
    return a + b;
}

TEST(BinaryTree, Add) {
    BinaryTree<int> tree;
    tree.Add(3);
    ASSERT_EQ(3, tree.GetRoot()->GetItem());
    EXPECT_ANY_THROW(tree.Add(3));
    tree.Add(4);
    tree.Add(5);
    ASSERT_EQ(4, tree.GetRoot()->GetItem());
    ASSERT_EQ(3, tree.GetRoot()->GetLeft()->GetItem());
    ASSERT_EQ(5, tree.GetRoot()->GetRight()->GetItem());
}

TEST(BinaryTree, Remove) {
    int arr[] = {4, 3, 5, 6};
    auto *sequence = new ListSequence<int>(arr, 4);
    BinaryTree<int> tree(sequence);
    tree.Remove(3);
    ASSERT_EQ(5, tree.GetRoot()->GetItem());
    EXPECT_ANY_THROW(tree.Remove(1));
}

TEST(BinaryTree, Contains) {
    int arr[] = {4, 3, 5, 6};
    auto *sequence = new ListSequence<int>(arr, 4);
    BinaryTree<int> tree(sequence);
    ASSERT_TRUE(tree.Contains(4));
    tree.Remove(4);
    ASSERT_FALSE(tree.Contains(4));
}

TEST(BinaryTree, ContainsSubtree) {
    int arr[] = {4, 3, 5, 6};
    auto *sequence = new ListSequence<int>(arr, 4);
    BinaryTree<int> tree(sequence);

    int arr1[] = {4, 5};
    auto *sequence1 = new ListSequence<int>(arr1, 2);
    BinaryTree<int> tree1(sequence1);

    ASSERT_TRUE(tree.Contains(tree1));

    tree1.Add(6);
    ASSERT_FALSE(tree.Contains(tree1));
}

TEST(BinaryTree, Map) {
    int arr[] = {4, 3, 5};
    auto *sequence = new ListSequence<int>(arr, 3);
    BinaryTree<int> tree(sequence);
    BinaryTree<int> mapped_tree = tree.Map(mapper);
    ASSERT_EQ(-4, mapped_tree.GetRoot()->GetItem());
}

TEST(BinaryTree, Where) {
    int arr[] = {4, 3, 5};
    auto *sequence = new ListSequence<int>(arr, 3);
    BinaryTree<int> tree(sequence);
    BinaryTree<int> filtered_tree = tree.Where(where_test);
    ASSERT_EQ(0, filtered_tree.GetHeight());
}

TEST(BinaryTree, Reduce) {
    int arr[] = {1, 2, 3};
    auto *sequence = new ListSequence<int>(arr, 3);
    BinaryTree<int> tree(sequence);
    ASSERT_EQ(10, tree.Reduce(reducer, 4));
}

