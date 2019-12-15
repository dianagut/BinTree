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
    int getHeight();
    bool insertNode(NodeData*);
    bool makeEmpty();
    
    // Assignment operators
    BinTree& operator=(const BinTree& p);
private:
    int getHeight(NodeData*, int);
    NodeData *root = NULL;
    int height;
    BinTree* left;
    BinTree* right;
};

#endif /* BinTree_h */
