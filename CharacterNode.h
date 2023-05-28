#ifndef CHARACTERNODE_H
#define CHARACTERNODE_H
#include "Character.h"
struct CharacterNode
{
    int key; // Represents our frequency
    Character nodeCharacter;
    bool isLeaf;
    bool isEmpty;   // Nodes that has no specific character will be empty.
    // All nodes will have 3 pointers .
    CharacterNode *parent;
    CharacterNode *leftChild;
    CharacterNode *rigthChild;
};
#endif // CHARACTERNODE_H