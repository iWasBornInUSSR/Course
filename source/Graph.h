//
// Created by peeknick on 08.11.18.
//

#ifndef COURSEWORK_GRAPH_H
#define COURSEWORK_GRAPH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

enum {
    ALPHABET = 26, BEG = 'a', END = 'z'
};

using namespace std;

class Graph {
public:
    explicit Graph();

    explicit Graph(unsigned short);

    void printMatrix();

    void cycle_search_with_DFS(unsigned short);

    void findCycle();

    // block operator =
    Graph operator=(const Graph &) const;

    Graph operator=(Graph &&) const;

    //fictitious destructor
    ~Graph() = default;


private:
    //const unsigned short N; // number of vertex
    int numberOfCycles = 0;
    vector<vector<char>> matrix; // adjacency matrix
    vector<unsigned short> colors;
};

void Graph::printMatrix() {
    char a = BEG;
    for (auto &k : matrix) {
        a++;
        if (!k.empty()) {
            cout << a << ": ";
            for (auto c : k)
                cout << c << " ";

            cout << endl;
        }
    }
}

void Graph::cycle_search_with_DFS(unsigned short vertex) {
    if (matrix.at(vertex).empty()) {
        colors.at(vertex) = 2;
        return;
    }
    colors.at(vertex) = 1;
    for (char j : matrix.at(vertex)) {
        auto buf = (unsigned short) (j - BEG);
        if (colors.at(buf) == 0)
            cycle_search_with_DFS(buf);
        if (colors.at(buf) == 1) {
            numberOfCycles++;
        }
        colors.at(vertex) = 2;
    }
}

Graph::Graph(unsigned short size) : colors(ALPHABET, 0) { //size must be <= ALPHABET
    matrix.resize(ALPHABET);
    for (int i = 0; i < size; ++i) {
        for (char j = BEG; j < END + 1; ++j) {
            if (rand() % 4 == 1) matrix.at(i).push_back(j);
        }
    }
}

Graph::Graph() : colors(ALPHABET, 0) { //
    matrix.resize(ALPHABET);
    ifstream myfile("../in.txt");
    string buffer;
    if (myfile.is_open()) {
        for (int i = 0; getline(myfile, buffer) && i < ALPHABET; i++) {
            string subBuffer = buffer.substr(buffer.find(':') + 1, buffer.size() - buffer.find(':')); //string parsing
            for (auto c : subBuffer) if (isalpha(c)) matrix.at((unsigned) buffer.at(0) - BEG).push_back(c);
        }
    }
}

void Graph::findCycle() {    //vectors in obj must be init

    for (unsigned short i = 0; i < colors.size(); ++i)
        if (!colors.at(i)) { cycle_search_with_DFS(i); }
    if (!numberOfCycles) { cout << "This graph is acyclic" << endl; }
    else { cout << "Graph has " << numberOfCycles << " cycles"; }
}

#endif //COURSEWORK_GRAPH_H
