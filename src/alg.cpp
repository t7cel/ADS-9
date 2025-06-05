// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <queue>
#include <cmath>
#include  "tree.h"

PMTree::PMTree(const char_vector& input) : root(nullptr) {
    root = buildTree(input);
}

PMTree::~PMTree() {
    deleteTree(root);
}


PMTree::Node* PMTree::buildTree(const char_vector& input) {
    if (input.empty()) {
        return nullptr;
    }

    Node* rootNode = new Node(input[0]);

    if (input.size() > 1) {
        char_vector remainingChars;
        for (size_t i = 1; i < input.size(); ++i) {
            remainingChars.push_back(input[i]);
        }
        std::sort(remainingChars.begin(), remainingChars.end());

        size_t startIndex = 0;
        while (startIndex < remainingChars.size()) {
            char_vector childInput;
            childInput.push_back(remainingChars[startIndex]);
            for (size_t i = 0; i < remainingChars.size(); ++i) {
              if (i != startIndex) {
                childInput.push_back(remainingChars[i]);
              }
            }

            Node* child = buildTree(childInput);
            if(child) {
              rootNode->children.push_back(child);
            }
            startIndex++;
        }
    }

    return rootNode;
}


void PMTree::deleteTree(Node* node) {
    if (node) {
        for (Node* child : node->children) {
            deleteTree(child);
        }
        delete node;
    }
}

std::vector<PMTree::char_vector> PMTree::getAllPerms() {
    std::vector<char_vector> allPerms;
    if (root) {
        getAllPermsRecursive(root, {}, allPerms);
    }
    return allPerms;
}

void PMTree::getAllPermsRecursive(Node* node, char_vector currentPerm, std::vector<char_vector>& allPerms) {
    if (node) {
        currentPerm.push_back(node->data);
        if (node->children.empty()) {
            allPerms.push_back(currentPerm);
        } else {
            for (Node* child : node->children) {
                getAllPermsRecursive(child, currentPerm, allPerms);
            }
        }
    }
}

PMTree::char_vector PMTree::getPerm1(int num) {
    std::vector<char_vector> allPerms = getAllPerms();
    if (num > 0 && num <= allPerms.size()) {
        return allPerms[num - 1];
    }
    return {};
}

int PMTree::calculatePermutationIndex(Node* node) {
    if (!node) return 0;

    int index = 0;
    Node* parent = nullptr;
    std::queue<Node*> q;
    q.push(root);
    bool found = false;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (Node* child : current->children) {
            if (child == node) {
                parent = current;
                found = true;
                break;
            }
            q.push(child);
        }
        if (found) break;
    }

    if (parent) {
        for (size_t i = 0; i < parent->children.size(); ++i) {
            if (parent->children[i] == node) {
                index = i;
                break;
            }
        }
    }
    return index;
}


PMTree::char_vector PMTree::getPerm2(int num) {
    char_vector result;
    if (!root) return result;

    Node* currentNode = root;
    int permNumber = num - 1;
    std::vector<char> path;

    path.push_back(currentNode->data);

    while (!currentNode->children.empty()) {
      int children_count = currentNode->children.size();
      int index = permNumber % children_count;
      permNumber /= children_count;
      currentNode = currentNode->children[index];
      path.push_back(currentNode->data);
    }

    result = path;
    return result;
}
