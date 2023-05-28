#ifndef HUFFMANCONVERSIONSYSTEM_H
#define HUFFMANCONVERSIONSYSTEM_H
#include <vector> 
#include <string>
#include "CharacterNode.h"
#include "EncodingNode.h"
#include "FrequencyCompare.h"
#include <queue>

// All operations and creations of our Huffman Binary Tree was defined in this class.
class HuffmanConversionSystem
{
private : 
    std::vector<Character> providedCharacters;   // This vector includes all Character objects provided by our input File; 
    std::priority_queue<CharacterNode*,std::vector<CharacterNode*>,FrequencyCompare> pq;  // I used priority queue to sort our nodes.
    std::vector<EncodingNode> encodedCharacters;  // Includes all encoded characters.
    std::string treeRepresentation=""; // This variable will include visual representation of our binary tree.(Lists Tree)
    std::string treeCommands = "" ;  //This variable will be used to create our tree again while decoding.
    CharacterNode *root;  // root of our huffman binary tree
public:
    HuffmanConversionSystem();
    void Encoder(std::string inputFile);  // We will use this constructor while encoding.
    void Decoder(std::string inputFile);  // This constructor will be used while decoding.
    void sort(std::vector<Character> &characters);  // Sorts all character objects by their frequency.
    void createBinaryTree();  // Creates our Huffman Binary Tree when command is encode.
    void encode(CharacterNode *_root,std::vector<std::string> codes,size_t index); // Encodes all characters of Huffman Tree.
    void decode(std::string line);
    void listTree(); // This function will visualize our binary tree.
    void returnHuffmanEncoding(char character);  // Returns Huffman encoding of a specific character.
    void createEncodingOutput(std::string fullLine);  //Displays encoding
    void saveTree(CharacterNode *_root); // This function will create an output file whic includes commands to recreate our tree.
    void createTreeVisualization(CharacterNode *_root,int spaceCount); // Cooperates with listTree();
    void traverseAndCopy(CharacterNode *_root);
    void controlAndConvert(std::string &line); // Converts uppercases and whitespaces.
    void getCodeFromNodes(char character);
    void getCodeFromTree(char character);
    CharacterNode *constructTree(std::vector <CharacterNode*> nodes,size_t index);
    ~HuffmanConversionSystem();
};

#endif // HUFFMANCONVERSIONSYSTEM_H
