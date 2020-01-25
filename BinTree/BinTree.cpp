//
//  main.cpp
//  BinTree
//
//  Created by Diana Gutierrez on 12/14/19.
//  Copyright © 2019 Diana Gutierrez. All rights reserved.
//

#include "BinTree.h"

using namespace std;

BinTree::BinTree() {
    root = NULL;
}


BinTree::BinTree(const BinTree& rhs)
{
    if (root != rhs.root) {
        root = new Node();
        root = copy(rhs.root);
    }
}

BinTree::Node* BinTree::copy(const Node* rhsNode)
{
    if (rhsNode == NULL) {
        return NULL;
    }
    Node* node = new Node();
    node->data = new NodeData(*rhsNode->data);
    node->left = node->right = NULL;
    if (rhsNode->left) {
        node->left = copy(rhsNode->left);
    }
    if (rhsNode->right) {
        node->right = copy(rhsNode->right);
    }
    return node;
}

BinTree& BinTree::operator=(const BinTree& rhs)
{
    // if we are doing BT=BT then don't remove the original
    if (this != &rhs)
    {
        // make sure there is some data to copy
        if (rhs.root != NULL) {
            if (root != NULL) {
                makeEmpty(root);
            }
            root = copy(rhs.root);
        }
    }
    return *this;
}

bool BinTree::operator==(const BinTree& p)
{
    if (this == &p)
        return true;
    if ((*root->data) == (*p.root->data)) {
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

bool BinTree::equalHelper(Node* lNode, Node* rNode)
{
    
}


bool BinTree::operator!=(const BinTree& p)
{
    return false;
}

bool BinTree::makeEmpty(Node* node)
{
    if (node != NULL) {
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return true;
}

int BinTree::getHeight() const
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
    
    if ((*root) == (*node)) {
        // ignore duplicates
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
    makeEmpty(root);
}

int BinTree::bsTreeToArray(NodeData* array[], int index)
{
    if (root) {
        bsTreeToArrayHelper(root, array, 0);
    }
    return index;
}

int BinTree::bsTreeToArrayHelper(BinTree::Node* node, NodeData* array[], int index)
{
    if (node) {
        if (node->left) {
            index = bsTreeToArrayHelper(node->left, array, index);
        }
        array[index] = node->data;
        index++;
        if (node->right) {
            index = bsTreeToArrayHelper(node->right, array, index);
        }
        delete node;
    }
    return index;
}

void BinTree::arrayToBSTree(NodeData* array[])
{
    makeEmpty();
    int sz = 0;
    while (array[sz] ) { sz++; }
    arrayToBSTreeHelper(root, array, 0, sz);
}

void BinTree::arrayToBSTreeHelper(Node* node, NodeData* array[], int low, int high)
{
    int middle = (low+high) / 2;
    node->data = array[middle];
    array[middle] = NULL;
    if (low < middle) {
        node->left = new Node();
        arrayToBSTreeHelper(node->left, array, low, middle - 1);
    }
    if ((high -1) > middle) {
        node->right = new Node();
        arrayToBSTreeHelper(node->right, array, middle + 1, high);
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
    cout << endl;
    displaySideways("");
}

void BinTree::displaySideways(string buff)
{
    size_t offset = 1;
    if (root) {
        offset += root->getDate().length();
    }
    string spacer = string(offset + buff.length(), ' ');
    if (right) {
        right->displaySideways(spacer);
    }
    if (root) {
        if (right) {
            cout << string(spacer.length() - 1, ' ') << '/' << endl;
        }
        cout << buff;
        cout << *root << endl;
        if (left) {
            cout << string(spacer.length() - 1, ' ') << '\\' << endl;
        }
    }
    if (left) {
        left->displaySideways(spacer);
    }
}

int BinTree::getHeight(const NodeData &node) const
{
    if (root!=NULL) {
        return getHeightHelper(root, target);
    }
    return 0;
}

int BinTree::getHeightHelper(BinTree::Node* node, const NodeData &target)
{
    if(node != NULL) {
        if (node->data == target) {
            return 1 + calcHeight(node);
        }
        int lh = 0, rh = 0;
        if (node->left) {
            lh = getHeightHelper(node->left, target);
            if (lh > 0) {
                return lh;
            }
        }
        if (node->right) {
            rh = getHeightHelper(node->right, target);
            if (rh > 0) {
                return rh;
            }
        }
    }
    return 0;
}

int BinTree::calcHeight(BinTree::Node* node)
{
    int lh = rh = 0;
    if (node->left) {
        lh = 1 + calcHeight(node->left);
    }
    if (node->right) {
        rh = 1 + calcHeight(node->right);
    }
    if (lh > rh ) {
        return lh;
    }
    return rh;
}
