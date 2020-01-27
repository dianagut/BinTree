//
//  main.cpp
//  BinTree
//
//  Created by Diana Gutierrez on 12/14/19.
//  Copyright © 2019 Diana Gutierrez. All rights reserved.
//

#include "BinTree.h"

using namespace std;

BinTree::BinTree()
{
    root = NULL;
}

BinTree::~BinTree()
{
    makeEmpty();
}

BinTree::BinTree(const BinTree& rhs)
{
    if (root != rhs.root) {
        root = new Node(rhs.root->data);
    }
}

BinTree::Node* BinTree::copy(const Node* rhsNode)
{
    if (rhsNode == NULL) {
        return NULL;
    }
    Node* node = new Node(rhsNode->data);
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
    return equalHelper(root, p.root);
}

bool BinTree::equalHelper(Node* lNode, Node* rNode)
{
    if ( !lNode && !rNode) {
        // both sides null they will be considered equal
        return true;
    }
    if ( !lNode || !rNode ) {
        // one side empty, one with data, is considered not equal
        return false;
    }
    if ((*lNode->data) == (*rNode->data)) {
        bool answer = true;
        if (lNode->left && rNode->left) {
            answer &= equalHelper(lNode->left, rNode->right);
        }
        if (!answer) return false;
        if (lNode->right && rNode->right) {
            answer &= equalHelper(lNode->right, rNode->right);
        }
        return answer;
    }
    return false;
}


bool BinTree::operator!=(const BinTree& p)
{
    return !equalHelper(root, p.root);
}

bool BinTree::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
    return true;
}

bool BinTree::makeEmpty(Node* node)
{
    if (node) {
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return true;
}

bool BinTree::insert(const NodeData *node)
{
    if (!node)
        return false;

    if (!root) {
        root = new Node(node);
        return true;
    }
    
    if ((*root->data) == (*node)) {
        // ignore duplicates
        return false;
    }
    
    return insertHelper(root, node);
}

bool BinTree::insertHelper(Node* root, const NodeData *node)
{
    if ((*root->data) > (*node)) {
        if (!root->left) {
            root->left = new Node(node);
            return true;
        }
        return insertHelper(root->left, node);
    } else {
        if (!root->right) {
            root->right = new Node(node);
            return true;
        }
        return insertHelper(root->right, node);
    }
    return false;
}

void BinTree::bsTreeToArray(NodeData* array[])
{
    bsTreeToArray(array, 0);
}

int BinTree::bsTreeToArray(NodeData* array[], int index)
{
    if (root) {
        bsTreeToArrayHelper(root, array, 0);
        root = NULL;
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
    root = new Node();
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
        return retrieveHelper(root, elem, answer);
    }
    return false;
}

bool BinTree::retrieveHelper(Node* node, const NodeData &elem, NodeData* &answer)
{
    if (*node->data == elem) {
        answer = node->data;
        return true;
    }
    if (*node->data > elem && node->left) {
        return retrieveHelper(node->left, elem, answer);
    }
    if (*node->data < elem && node->right) {
        return retrieveHelper(node->right, elem, answer);
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const BinTree& p)
{
    return p.nodeOutput(os, p.root);
}

std::ostream& BinTree::nodeOutput(std::ostream& os, const Node* node) const
{
    if (node && node->data) {
        if (node->left) {
            nodeOutput(os, node->left);
        }
        os << " " << node->data << " ";
        if (node->right) {
            nodeOutput(os, node->right);
        }
    }
    return os;
}
void BinTree::displaySideways()
{
    cout << endl;
    displaySideways(root, "");
}

void BinTree::displaySideways(Node* root, string buff)
{
    size_t offset = 1;
    if (root) {
        offset += root->data->getData().length();
    }
    string spacer = string(offset + buff.length(), ' ');
    if (root->right) {
        displaySideways(root->right, spacer);
    }
    if (root) {
        if (root->right) {
            cout << string(spacer.length() - 1, ' ') << '/' << endl;
        }
        cout << buff;
        cout << *root->data << endl;
        if (root->left) {
            cout << string(spacer.length() - 1, ' ') << '\\' << endl;
        }
    }
    if (root->left) {
        displaySideways(root->left, spacer);
    }
}

int BinTree::getHeight(const NodeData &target) const
{
    if (root) {
        return getHeightHelper(root, target);
    }
    return 0;
}

int BinTree::getHeightHelper(const Node* node, const NodeData &target) const
{
    if(node != NULL) {
        if (*node->data == target) {
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

int BinTree::calcHeight(const BinTree::Node* node) const
{
    int lh = 0, rh = 0;
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
