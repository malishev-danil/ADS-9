// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <memory>  // Добавлено для make_shared
#include "tree.h"

void PMTree::buildPermutationTree(const std::vector<char>& remaining,
                                  std::shared_ptr<PMTreeNode> node) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        std::vector<char> nextRemaining = remaining;
        nextRemaining.erase(nextRemaining.begin() + i);
        auto child = std::make_shared<PMTreeNode>(remaining[i]);
        node->children.push_back(child);
        buildPermutationTree(nextRemaining, child);
    }
}

PMTree::PMTree(const std::vector<char>& symbols) : symbols(symbols) {
    root = std::make_shared<PMTreeNode>('*');
    buildPermutationTree(symbols, root);
}

void collectAllPermutations(std::shared_ptr<PMTreeNode> node,
                           std::vector<char>& path,
                           std::vector<std::vector<char>>& result) {
    path.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(path);
    } else {
        for (auto& child : node->children) {
            collectAllPermutations(child, path, result);
        }
    }

    path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    for (auto& child : tree.root->children) {
        collectAllPermutations(child, path, result);
    }
    return result;
}

int counter = 0;

bool dfsGetNthPerm1(std::shared_ptr<PMTreeNode> node,
                   std::vector<char>& path,
                   std::vector<char>& result,
                   int target) {
    path.push_back(node->value);

    if (node->children.empty()) {
        counter++;
        if (counter == target) {
            result = path;
            path.pop_back();
            return true;
        }
    } else {
        for (auto& child : node->children) {
            if (dfsGetNthPerm1(child, path, result, target)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0)
        throw std::invalid_argument("Number must be positive");

    std::vector<char> result;
    std::vector<char> path;
    counter = 0;

    for (auto& child : tree.root->children) {
        if (dfsGetNthPerm1(child, path, result, num)) {
            return result;
        }
    }

    throw std::out_of_range("Permutation number out of range");
}

int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0)
        throw std::invalid_argument("Number must be positive");

    int n = tree.symbols.size();
    std::vector<char> symbols = tree.symbols;
    std::sort(symbols.begin(), symbols.end());

    std::vector<char> result;
    int index = num - 1;  // индекс начинается с 0

    for (int i = 0; i < n; ++i) {
        int fact = factorial(n - i - 1);
        int selectIndex = index / fact;
        result.push_back(symbols[selectIndex]);
        symbols.erase(symbols.begin() + selectIndex);
        index -= selectIndex * fact;
    }

    return result;
}
