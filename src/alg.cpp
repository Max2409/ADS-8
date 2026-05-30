// Copyright 2021 NNTU-CS
#include "bst.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void makeTree(BST<std::string> &tree, const char *filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }
    // последнее слово в файле
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    file.close();
}

void printFreq(BST<std::string> &tree) {
    std::vector<std::pair<std::string, int>> freqList;
    tree.inorder(freqList);

    // сортировка по убыванию частоты
    std::sort(freqList.begin(), freqList.end(),
              [](const auto &lhs, const auto &rhs) {
                  return lhs.second > rhs.second;
              });

    std::ofstream outputFile("result/freq.txt");
    for (const auto &entry : freqList) {
        std::cout << entry.first << " " << entry.second << std::endl;
        if (outputFile) {
            outputFile << entry.first << " " << entry.second << std::endl;
        }
    }
    if (outputFile) {
        outputFile.close();
    }
}
