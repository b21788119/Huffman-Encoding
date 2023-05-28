#ifndef FREQUENCYCOMPARE_H
#define FREQUENCYCOMPARE_H
#include "CharacterNode.h"

struct FrequencyCompare{
    bool operator()(const CharacterNode *node1,const CharacterNode  *node2){
        return (node1->key >  node2->key);
    }
};

#endif // FREQUENCYCOMPARE_H