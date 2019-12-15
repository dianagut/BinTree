//
//  main.cpp
//  BinTree
//
//  Created by Diana Gutierrez on 12/14/19.
//  Copyright © 2019 Diana Gutierrez. All rights reserved.
//

#include "BinTree.h"

BinTree::BinTree() {
    root = NULL;
    left = NULL;
    right = NULL;
}

BinTree::~BinTree() {
    makeEmpty();
}

bool BinTree::makeEmpty()
{
    if (root) {
        if (left)
            left->makeEmpty();
        if (right)
            right->makeEmpty();
        delete root;
    }
    return true;
}

int BinTree::getHeight()
{
    if (!root) {
        return 0;
    }
    int hl = 0;
    int hr = 0;
    int h = 1;
    if (left) {
        hl = left->getHeight();
    }
    if (right) {
        hr = right->getHeight();
    }
    int max = (hl > hr) ? hl : hr;
    h += max;
    return h;
}

bool BinTree::insertNode(NodeData *node)
{
    if (!node)
        return false;

    if (!root) {
        root = node;
        return true;
    }
    
    if (node < root) {
        if (!left) {
            left = new BinTree();
        }
        return left->insertNode(node);
    } else {
        if (!right) {
            right = new BinTree();
        }
        return right->insertNode(node);
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const BinTree& p)
{
    if (p.root) {
        if (p.left) {
            os << p.left;
        }
        os << " " << p.root << " ";
        if (p.right) {
            os << p.right;
        }
    }
    
    return os;
}
