// Copyright 2022 NNTU-CS

#include "tree.h"

#include <vector>
#include <iostream>
#include <chrono>

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::vector<std::vector<char>> perms = getAllPerms(tree);
    std::cout << "All permutations:\n";
    for (const auto& p : perms) {
        for (char c : p) {
            std::cout << c;
        }
        std::cout << "\n";
    }

    std::cout << "\nTesting getPerm1:\n";
    for (int i = 1; i <= perms.size(); ++i) {
        std::vector<char> p = getPerm1(tree, i);
        for (char c : p) {
            std::cout << c;
        }
        std::cout << "\n";
    }

    std::cout << "\nTesting getPerm2:\n";
    for (int i = 1; i <= perms.size(); ++i) {
        std::vector<char> p = getPerm2(tree, i);
        for (char c : p) {
            std::cout << c;
        }
        std::cout << "\n";
    }

    std::cout << "\nTime comparison test:\n";

    PMTree bigTree({'1','2','3','4','5','6','7','8'});

    auto start = std::chrono::high_resolution_clock::now();
    getPerm1(bigTree, 20000);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm1 time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    getPerm2(bigTree, 20000);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm2 time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}
