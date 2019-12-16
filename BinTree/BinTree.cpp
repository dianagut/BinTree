//
//  main.cpp
//  BinTree
//
//  Created by Diana Gutierrez on 12/14/19.
//  Copyright © 2019 Diana Gutierrez. All rights reserved.
//

#include "BinTree.h"
#include <memory>

BinTree::BinTree() {
    root = NULL;
    left = NULL;
    right = NULL;
}

BinTree::~BinTree() {
    makeEmpty();
}

BinTree::BinTree(const BinTree& bt)
{
    if (root != bt.root) {
        makeEmpty();
        root = new NodeData(*bt.root);
        if (bt.left) {
            left = new BinTree(*bt.left);
        }
        if (bt.right) {
            right = new BinTree(*bt.right);
        }
    }
}

BinTree& BinTree::operator=(const BinTree& rhs)
{
    // if we are doing BT=BT then don't remove the original
    if (this != &rhs)
    {
        // make sure there is some data to copy
        if (rhs.root != NULL) {
            root = new NodeData(*rhs.root);
            if (rhs.left) {
                left = new BinTree(*rhs.left);
            }
            if (rhs.right) {
                right = new BinTree(*rhs.right);
            }
        }
    }
    return *this;
}

bool BinTree::operator==(const BinTree& p)
{
    if (std::addressof(*this) == std::addressof(p))
        return true;
    if ((*root) == (*p.root)) {
        bool answer = true;
        if (left && p.left) {
            answer &= (*left) == (*p.left);
        }
        if (!answer) return answer;
        if (right && p.right) {
            answer &= (*right) == (*p.right);
        }
        return answer;
    }
    return false;
}

bool BinTree::operator!=(const BinTree& p)
{
    return false;
}

bool BinTree::makeEmpty()
{
    if (root) {
        if (left) {
            left->makeEmpty();
            left = NULL;
        }
        if (right) {
            right->makeEmpty();
            right = NULL;
        }
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

bool BinTree::insert(const NodeData *node)
{
    if (!node)
        return false;

    if (!root) {
        root = new NodeData(*node);
        return true;
    }
    
    NodeData *p;
    if( retrieve(*node, p)) {
        return false;
    }
    
    if ((*root) > (*node) ) {
        if (!left) {
            left = new BinTree();
        }
        return left->insert(node);
    } else {
        if (!right) {
            right = new BinTree();
        }
        return right->insert(node);
    }
    return false;
}

void BinTree::bsTreeToArray(NodeData* array[])
{
    bsTreeToArray(array, 0);
    makeEmpty();
}

int BinTree::bsTreeToArray(NodeData* array[], int index)
{
    if (root) {
        if (left) {
            index = left->bsTreeToArray(array, index);
        }
        array[index] = root;
        root = NULL;
        index++;
        if (right) {
            index = right->bsTreeToArray(array, index);
        }
    }
    return index;
}

void BinTree::arrayToBSTree(NodeData* array[])
{
    int sz = 0;
    while (array[sz] ) { sz++; }
    arrayToBSTree(array, 0, sz);
}

void BinTree::arrayToBSTree(NodeData* array[] , int low, int high)
{
    makeEmpty();
    int middle = (low+high) / 2;
    root = array[middle];
    array[middle] = NULL;
    if (low < middle) {
        left = new BinTree();
        left->arrayToBSTree(array, low, middle -1 );
    }
    if ((high - 1) > middle) {
        right = new BinTree();
        right->arrayToBSTree(array, middle + 1, high);
    }
}

bool BinTree::retrieve(const NodeData &elem, NodeData* &answer)
{
    if (root) {
        if (*root == elem) {
            answer = root;
            return true;
        }
        if (*root > elem && left) {
            return left->retrieve(elem, answer);
        }
        if (*root < elem && right) {
            return right->retrieve(elem, answer);
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const BinTree& p)
{
    if (p.root) {
        if (p.left) {
            os << *p.left;
        }
        os << " " << *p.root << " ";
        if (p.right) {
            os << *p.right;
        }
    }
    
    return os;
}

void BinTree::displaySideways()
{
    
}

int BinTree::getHeight (const NodeData &) const
{
    return 0;
}
