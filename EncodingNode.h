#ifndef ENCODINGNODE_H
#define ENCODINGNODE_H
#include "Character.h"
#include <string>
// After our tree is created an all characters are encoded,they will be stored inside this node.
struct EncodingNode
{
    Character encodedCharacter; // Character representation
    std::string code; // string form of the encoding code.
};
#endif // ENCODING NODE