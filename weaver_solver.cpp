#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void solve(std::vector<std::string>& words, std::map<std::string, int>& words_id, 
        std::string word1, std::string word2) {

    int n = words.size();
    std::vector<std::vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < words[i].length(); j++) {
            for (char k = 'a'; k <= 'z'; k++) {
                std::string new_word = words[i];
                new_word[j] = k;
                if (new_word != words[i] && words_id.find(new_word) != words_id.end()) {
                    graph[i].push_back(words_id[new_word]);
                }
            }
        }
    }

    std::vector<int> prev_word(n, -1);
    std::queue<int> Q;

    int id1 = words_id[word1];
    int id2 = words_id[word2];

    prev_word[id1] = id1;
    Q.push(id1);

    while (!Q.empty()) {
        int i = Q.front();
        Q.pop();
        if (i == id2) break;
        for (int j : graph[i]) {
            if (prev_word[j] == -1) {
                prev_word[j] = i;
                Q.push(j);
            }
        }
    }

    std::vector<std::string> solution;
    int a = id2;
    int b = prev_word[a];
    while (a != b) {
        solution.push_back(words[a]);
        a = b;
        b = prev_word[a];
    }
    std::reverse(solution.begin(), solution.end());
    for (auto s : solution) std::cout << s << '\n';
}

int main(int argc, char** argv) {
    std::ifstream file_words("4_letter_words.txt");
    if (!file_words.is_open()) {
        std::cerr << "couldn't open file\n";
        return 1;
    }

    std::vector<std::string> words;
    std::string word;
    while (file_words >> word) words.push_back(word);

    std::map<std::string, int> words_id;
    for (int i = 0; i < words.size(); i++) words_id[words[i]] = i;

    if (argc < 3) {
        std::cerr << "usage: weaver_solver word1 word2\n";
        return 1;
    }
    std::string word1 = argv[1];
    std::string word2 = argv[2];
    if (word1.length() != 4 || word2.length() != 4) {
        std::cerr << "words must be 4 letter long\n";
        return 1;
    }
    if (words_id.find(word1) == words_id.end()) {
        std::cerr << "first word does not exist\n";
        return 1;
    }
    if (words_id.find(word2) == words_id.end()) {
        std::cerr << "second word does not exist\n";
        return 1;
    }
    if (word1 == word2) {
        std::cerr << "words must be different\n";
        return 1;
    }
    
    solve(words, words_id, word1, word2);

    return 0;
}
