// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTreeNode {
 public:
    char value;
    std::vector<std::shared_ptr<PMTreeNode>> children;

    PMTreeNode(char val) : value(val) {}
};

class PMTree {
 private:
    std::shared_ptr<PMTreeNode> root;
    std::vector<char> symbols;

    void buildPermutationTree(const std::vector<char>& remaining, std::shared_ptr<PMTreeNode> node);

 public:
    PMTree(const std::vector<char>& symbols);
    std::shared_ptr<PMTreeNode> getRoot() const { return root; }
    const std::vector<char>& getSymbols() const { return symbols; }

    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
};

#endif  // INCLUDE_TREE_H_
