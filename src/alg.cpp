// Copyright 2022 NNTU-CS
#include <algorithm>
#include <iostream>
#include <cmath>
#include  "tree.h"
#include <functional>
#include <vector>

PMTree::~PMTree() {
    for (PMTree* child : children) {
        delete child;
    }
}

PMTree::PMTree(std::vector<char> input) : value('\0'), children({}) {
    if (input.empty()) return;

    for (size_t i = 0; i < input.size(); ++i) {
        std::vector<char> next_input;
        for (size_t j = 0; j < input.size(); ++j) {
            if (i != j) {
                next_input.push_back(input[j]);
            }
        }
        PMTree* child = new PMTree(next_input);
        child->value = input[i];
        children.push_back(child);
    }
}


std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> permutations;

    std::function<void(PMTree*, std::vector<char>)> traverse =
        [&](PMTree* node, std::vector<char> current_permutation) {
        if (node->children.empty()) {
            permutations.push_back(current_permutation);
            return;
        }

        for (PMTree* child : node->children) {
            std::vector<char> next_permutation = current_permutation;
            next_permutation.push_back(child->value);
            traverse(child, next_permutation);
        }
    };

    traverse(&tree, {});
    return permutations;
}



std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> all_perms = getAllPerms(tree);
    if (num <= 0 || num > all_perms.size()) {
        return {};
    }
    return all_perms[num - 1];
}



std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> permutation;
    std::vector<char> available_chars;
    std::function<bool(PMTree*, int, std::vector<char>&)> find_permutation =
        [&](PMTree* node, int k, std::vector<char>& current_permutation) -> bool {
        if (node->children.empty()) {
            if (k == 1) {
                return true;
            }
            return false;
        }

        int count = 0;
        for (PMTree* child : node->children) {
            std::function<int(PMTree*)> count_permutations = 
                [&](PMTree* subtree) -> int {
                if (subtree->children.empty()) {
                    return 1;
                }
                int total = 0;
                for (PMTree* subchild : subtree->children) {
                    total += count_permutations(subchild);
                }
                return total;
            };

            int num_perms_under_child = count_permutations(child);


            if (k <= num_perms_under_child) {
                current_permutation.push_back(child->value);
                if (find_permutation(child, k, current_permutation)) {
                    return true;
                }
                return false;

            }
            k -= num_perms_under_child;
        }

        return false;
    };

    if (!find_permutation(&tree, num, permutation)) {
        return {};
    }

    return permutation;
}
