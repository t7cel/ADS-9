// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "tree.h"

void print_vector(const std::vector<char>& vec) {
    for (char c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}


int main() {
  std::cout << "Примеры использования:" << std::endl;
    PMTree::char_vector input = {'1', '2', '3'};
    PMTree tree(input);

    std::cout << "Все перестановки:" << std::endl;
    std::vector<PMTree::char_vector> allPerms = tree.getAllPerms();
    for (const auto& perm : allPerms) {
        print_vector(perm);
    }

    std::cout << "Перестановка №1 (getPerm1): ";
    print_vector(tree.getPerm1(1));
    std::cout << "Перестановка №4 (getPerm1): ";
    print_vector(tree.getPerm1(4));

    std::cout << "Перестановка №1 (getPerm2): ";
    print_vector(tree.getPerm2(1));
    std::cout << "Перестановка №4 (getPerm2): ";
    print_vector(tree.getPerm2(4));
  
  return 0;
}
