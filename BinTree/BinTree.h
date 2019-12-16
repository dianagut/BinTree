//
//  BinTree.h
//  BinTree
//
//  Created by Francisco Sanchez on 12/14/19.
//  Copyright © 2019 Francisco Sanchez. All rights reserved.
//

#pragma once
#ifndef BinTree_h
#define BinTree_h

#include "nodedata.hpp"
#include <iostream>
#include <string>

class BinTree {
    friend std::ostream& operator<<(std::ostream& output, const BinTree& p);
public:
    BinTree();
    ~BinTree();
    BinTree(const BinTree& bt);
    
    int getHeight() const;
    int getHeight (const NodeData &) const;
    bool insert(const NodeData *);
    bool makeEmpty();
    void bsTreeToArray(NodeData* []);
    void arrayToBSTree(NodeData* []);
    bool retrieve(const NodeData &, NodeData* &);
    void displaySideways();
    
    // Assignment operators
    BinTree& operator=(const BinTree& p);
    bool operator==(const BinTree& p);
    bool operator!=(const BinTree& p);

private:
    int getHeight(NodeData*, int);
    int bsTreeToArray(NodeData* [], int index);
    void arrayToBSTree(NodeData* [] , int, int);
    NodeData *root = NULL;
    BinTree* left = NULL;
    BinTree* right = NULL;
};

#endif /* BinTree_h */
