#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(Edge *edges, int size) {
    for (int i = 0; i < size; i++) {
        int src = edges[i].src, dest = edges[i].dest;
        if (nodes.count(src) == 0) {
            nodes[src] = new SingleLinkedList<int>();
        }
        nodes[src]->add(dest);
        if (nodes.count(dest) == 0) {
            nodes[dest] = new SingleLinkedList<int>();
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete (*it).second;
    }
}

void DirectedGraph::printGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        printf("node(%d) has edges: ", (*it).first);
        for (auto itl = (*it).second->begin(); itl != (*it).second->end(); itl++) {
            printf("%d ", (*itl));
        }
        printf("\n");
    }
}

void DirectedGraph::topologySort(int node, LinkedStack<int> &Stack, set<int> &set2) {
    if (set2.find(node) != set2.end())
    {
        return;
    }
    for (int neighbourNode : *nodes[node]) {
        topologySort(neighbourNode, Stack, set2);
    }
    set2.insert(node);
    Stack.push(node);
}

vector<int> *DirectedGraph::topologySort() {

    LinkedStack<int> sortStack;
    set<int> set2;

    for (auto const&[node,next] : nodes) {
        if (set2.find(node) == set2.end()) {
            topologySort(node, sortStack, set2);
        }
    }

    auto *ptr = new vector<int>();
    while (!sortStack.isEmpty()) { 
        ptr->push_back(sortStack.peek());
        sortStack.pop();
    }
    return ptr;
}
//get idea from flowing:
//iq.opengenus.org/topological-sorting-dfs/
//https://www.geeksforgeeks.org/topological-sorting/