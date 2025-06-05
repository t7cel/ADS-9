// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>
#include <iostream>

class PMTree {
public:
    using char_vector = std::vector<char>;
    using tree_node = struct Node;

    struct Node {
        char data;
        std::vector<Node*> children;
        Node(char val) : data(val) {}
    };

    PMTree(const char_vector& input);
    ~PMTree();

    std::vector<char_vector> getAllPerms();
    char_vector getPerm1(int num);
    char_vector getPerm2(int num); 

private:
    Node* root;

    Node* buildTree(const char_vector& input);
    void getAllPermsRecursive(Node* node, char_vector currentPerm, std::vector<char_vector>& allPerms);
    void deleteTree(Node* node);

    Node* navigateToNode(int permNumber);
    int calculatePermutationIndex(Node* node);
};
#endif  // INCLUDE_TREE_H_
