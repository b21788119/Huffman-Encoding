#include "HuffmanConversionSystem.h"
#include <fstream>
#include <stdexcept>
#include "Character.h"
#include "CharacterNode.h"
#include <sstream>
#include <cctype>
#include <iostream>
int count = 5;  // We will use this variable to increase our whitespaces
void HuffmanConversionSystem::createTreeVisualization(CharacterNode *_root,int spaceCount)
{
    if (_root == nullptr){  // This is our base case
        return;
    }  
    spaceCount += count;  // In every recursive call,the space amount that we use increased by 10;
    createTreeVisualization(_root->rigthChild, spaceCount); // Right childs of our nodes will be printed first.
    treeRepresentation+="\n";  // After rigth child representation we use \n to go to the next line.
    for (int i = count; i < spaceCount; i++)
    {   
        if(i== spaceCount-5){
            treeRepresentation+= "---"; // From now on,add this string and break.
            break;
        }
        else{
            treeRepresentation+= " "; // Before i== space count-5,adds whitespaces
        }
    }
    if(_root->isLeaf){ // When we reach a leaf node
        treeRepresentation+= "Leaf";
        treeRepresentation+= _root->nodeCharacter.getRepresentation();
        treeRepresentation+= "\n";  // I used new line here to prevent confusion.
    }
    else{
        treeRepresentation+="#"+std::to_string(_root->key)+"\n"; // If our current node is not a leaf node,just adds # and its representation.
    }  
    createTreeVisualization(_root->leftChild, spaceCount); // Finally,same operations for left childs.
}
void HuffmanConversionSystem::getCodeFromTree(char character){
     std::ifstream treeFile("MyTree.txt");
     std::string treeLine;
     if(treeFile.is_open()){
        while(treeFile.good()){
            getline(treeFile,treeLine);
        }
    }
    else
    {
        try
        {
            throw std::string("Error");
        }
        catch (std::string e){
            std::cout << "Please provide a tree first" << std::endl;
            return;
        }
    }
    std::vector<std::string> allINodes;
    std::stringstream s_stream(treeLine); //create string stream from the strisng
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        allINodes.push_back(substr);
   }
   std::vector<CharacterNode*> nodes;  //Firstly,I'm creating our nodes.This vector will include node pointers comes from inputFile.
   for(size_t j=0;j<allINodes.size();j++)
    {
       char _representation = allINodes.at(j).at(0); // Index 0 of each vector object is representation.
       std::string _frequency = allINodes.at(j).substr(1,allINodes.at(j).length()-1); //Index 1 to end represents frequency.
       int frequency ;
       CharacterNode *newNode;
       std::istringstream(_frequency) >> frequency;  // This line converts our string to int.
       if(_representation != '#'){ // We have used this representation for empty nodes .If representation does not equal to #,that means we are creating a leaf node.
           Character newCharacter(_representation,frequency);
           newNode = new CharacterNode();
           newNode->isLeaf = true;
           newNode->isEmpty = false;
           newNode->key = frequency;
           newNode->nodeCharacter = newCharacter;
           newNode->leftChild = nullptr;
           newNode->rigthChild = nullptr;
           newNode->parent = nullptr;
           nodes.push_back(newNode); // Pushing all nodes to our vector which was created before the loop
       }
       else
        { // That means we are creating an empty node.
            newNode = new CharacterNode();
            newNode->isLeaf = false; 
            newNode->isEmpty = true;
            newNode->key = frequency;
            newNode->leftChild = nullptr;
            newNode->rigthChild = nullptr;
            newNode->parent = nullptr;
            nodes.push_back(newNode);  // Pushing all nodes to our vector which was created before the loop
       }
   }
 
   root = constructTree(nodes,0);
   CharacterNode *temp = root;
   std::vector<std::string> codes;
   encode(temp,codes,0);
   getCodeFromNodes(character);
}
void HuffmanConversionSystem::controlAndConvert(std::string &line){
    for(size_t i=0;i<line.length();i++){
        if(line.at(i) >=65 || line.at(i) <= 90){
            line.at(i) = line.at(i)+32;
        }
    }
    for(size_t j=0;j<line.length();j++){
        if(line.at(j) == 32){
            line.at(j) = 95;
        }
    }
}
CharacterNode *HuffmanConversionSystem::constructTree(std::vector<CharacterNode*> nodes,size_t index){
    CharacterNode *_root = nodes.at(index);
    size_t rigthIndex;
    if(_root->isLeaf){
        _root->leftChild = nullptr;
        _root->rigthChild = nullptr;
        return _root;
    }
    _root->leftChild = constructTree(nodes,index+1);
    for(size_t i=index+2;i<nodes.size();i++){
        if(nodes.at(i)->key >= _root->leftChild->key ){
            rigthIndex = i;
            break;
        }
    }
    _root->rigthChild =constructTree(nodes,rigthIndex);
    return _root;
}
void HuffmanConversionSystem::traverseAndCopy(CharacterNode *_root){
    //This function has written to perform preOrder traversal
    //root-leftChild-rightChild.
    if(_root){
        //For every root,treeCommands will be updated.
        //
        treeCommands+= _root->nodeCharacter.getRepresentation()+std::to_string(_root->key)+",";
        traverseAndCopy(_root->leftChild);
        traverseAndCopy(_root->rigthChild);
    }
    else
    {
        return; //Base Case 
    }
}
void HuffmanConversionSystem::sort(std::vector<Character> &characters){
    // This function uses selection sort algorithm to sort our vector.
    std::vector <Character> tempVector;  // Temporary vector to push our characters in a sorted way.
    for(size_t i=0;i<characters.size();i++){
        size_t minIndex = i;
        for(size_t j=i+1;j<characters.size();j++){
            if(characters.at(minIndex).getFrequency() > characters.at(j).getFrequency()){
                minIndex = j;
           }
        }
        tempVector.push_back(characters.at(minIndex));
    }
    //Copying characters to our main argument vector.
    characters = tempVector;
}
void HuffmanConversionSystem::getCodeFromNodes(char character)
{
    char temp;
    if(character >= 65 && character <= 90){
        temp = character+32;
    }
    else {
        temp = character;
    }
    // This function can only work when our input is -i inputFile.txt -encode -s character
    std::string code = "";
    for(size_t i=0;i<encodedCharacters.size();i++)  // Looping through our encodedCharacters to find a match
    {
        if(encodedCharacters.at(i).encodedCharacter.getRepresentation() == temp){
            code = encodedCharacters.at(i).code; //If a node which has the same representation exists in the encodedCharacters,we take its code.   
            break;
        }
    }
    std::cout<< "Huffman Encoding of "<< character << ":" << code << std::endl; // prints the code to the console.
}
void HuffmanConversionSystem::createBinaryTree(){
    for(size_t i=0;i<providedCharacters.size();i++){
        CharacterNode *node = new CharacterNode();
        node->isEmpty = false;  // Nodes which include characters will never be empty.
        node->isLeaf = true;   // All nodes of characters will be a leaf node.
        node->nodeCharacter = providedCharacters.at(i);
        node->key = providedCharacters.at(i).getFrequency();
        node->leftChild = nullptr;
        node->rigthChild = nullptr;
        node->parent = nullptr;
        pq.push(node);
    }
    if(pq.size() < 2 ){
        try{
            throw std::string("Error");
        }
        catch(std::string e){
            std::cout << "Please provide more characters.Tree could not be created!"<< std::endl;
        }
    }
    else{
        while(true){
            if(pq.size() == 1){  // That means our subtrees are created and our root is ready to assign.
                break;
            }
            CharacterNode *minFrequencyNode1;
            minFrequencyNode1 = pq.top(); //Node which has the least frequency.
            pq.pop();
            CharacterNode *minFrequencyNode2;
            minFrequencyNode2 = pq.top();// Second node that has the least frequency.
            pq.pop();
            CharacterNode *emptyNode = new CharacterNode();
            emptyNode->leftChild = minFrequencyNode1;
            emptyNode->rigthChild = minFrequencyNode2;
            emptyNode->key = emptyNode->leftChild->key + emptyNode->rigthChild->key;
            emptyNode->isEmpty = true;  // always empty
            emptyNode->isLeaf = false;
            emptyNode->leftChild->parent = emptyNode;
            emptyNode->rigthChild->parent = emptyNode;
            emptyNode->parent = nullptr;
            pq.push(emptyNode);
        }
        CharacterNode *rootNode;
        rootNode = pq.top();
        root = rootNode; // Our tree has created.
        pq.pop();
    }
}
HuffmanConversionSystem::HuffmanConversionSystem()
{
    root = nullptr;
}
void HuffmanConversionSystem::Encoder(std::string inputFile)
{   
    std::ifstream myFile(inputFile); // I'm reading the character line that will be encoded here.
    std::string line;               // This algorithm works with  one line inputs.If you test with multiple line files,it will crash.
    if(myFile.is_open()){   
        getline(myFile,line);
        myFile.close(); 
    }
    else {
        std::cout << "Unable To Open File" << std::endl;  // If file can not be opened or found.
    }
    controlAndConvert(line); // This function controls our line to find uppercase characters and whitespaces.
    std::vector<Character> unsortedCharacters;  //This vector will include all distint characters which comes from input file.
    size_t index = 0; //Our while loop will start looping on our line using this variable.
    while(index < line.length())
    {  // Looping on the each character of line.
        if(index == 0){  // If we are at the beginning of the line.
            char _representation = line.at(0); 
            int count = 1; // First occurence of a specific character.
            for(size_t j=1;j<line.size();j++){  // Looping after next index to find frequency.
                if(line.at(j) == _representation){
                    count++; //If we have more than one of the same character,count will be increased.
                }
            }
            Character newCharacter(_representation,count); // Character object is created here.
            unsortedCharacters.push_back(newCharacter); // Adding created character to our vector.
            index++; // 1
        }
        else
        { 
            char _representation = line.at(index);
            int count = 1;
            bool existance = false;
            //If we pushed a character with same representation,no need to push it again.
            for(size_t i=0;i<unsortedCharacters.size();i++){
                if(unsortedCharacters.at(i).getRepresentation() == _representation){
                    existance = true;
                    break;
                }
            }
            if(existance){ // We won't push the same character again.            
                index++;
                continue;  // Skip all operations and turn back to the beginning of the loop.
            }
            else
            {  // If we did not push it to our vector,we will calculate its frequency,create it and push it.
                for(size_t j=index+1;j<line.length();j++){
                    if(line.at(j) == _representation){
                        count++;
                    }
                }
                Character newCharacter(_representation,count);
                unsortedCharacters.push_back(newCharacter);
                index++;
            }
        }
    }
    providedCharacters = unsortedCharacters; // All character objects are ready and assigned to our system's variable.
    createBinaryTree(); // Our binary tree will be created by using provided characters.
    std::vector<std::string> codes ; // We need an empty vector to use in our next function calls.
    CharacterNode *temp = root; // We need a temporary variable which is equal to our tree's root to use in our function calls.
    encode(temp,codes,0);  // Our characters will be encoded after this call is executed.
    createEncodingOutput(line); //Our result will be printed to the screen after this function is executed.
    //We will save our tree by using preorder traversal.After next line is executed,string representation of our tree will be ready.
    traverseAndCopy(temp);  
    saveTree(temp);  // Creates an output file that represents our tree.(MyTree.txt)
}  
void HuffmanConversionSystem::encode(CharacterNode *_root,std::vector<std::string> codes,size_t index){
    // This function uses recursion to calculate encodings of all leaaf nodes in our system.
    // After this function is executed,all leaf nodes and their encodings will be stored in encodedCharacters.
    // We will be able to reach encoding of  a specific character by using encodedCharacters.
    if(_root->leftChild)
    {
        // All left childs mean 0;
        codes.insert(codes.begin()+index,"0");  // If our root has a left child,we will insert a 0 to the specified index.
        encode(_root->leftChild,codes,index+1);  //Until we reach a leaf node,we will increase our index by 1  and call our function again.
    }
    if(_root->rigthChild){
        // All right childs mean 1
        codes.insert(codes.begin()+index,"1");  // If our root has a right child,we will insert a 1 to the specified index.
        encode(_root->rigthChild,codes,index+1);  //Until we reach a leaf node,we will increase our index by 1 and call our function again.
    }
    if(_root->isLeaf)
    {
        // When we reach a leaf node,we will save character inside it and its encoding info.
        EncodingNode encodedNode;  // Creating an empty EncodingNode
        encodedNode.encodedCharacter = _root->nodeCharacter; // This line assigns our leaf node's character to our encodedNode's encoded character.
        std::string encoding = ""; // We will store encoding information in this variable.
        for(size_t i=0;i<index;i++)  
        {   
            //This loop itetates through our vector until i reaches index.
            encoding+= codes.at(i); //Update our encoding by the element which is at the index i.
        }
        encodedNode.code = encoding; // Finally,this line assigns our encoding variable to the code of encodedNode.Our encodedNode is ready.
        encodedCharacters.push_back(encodedNode); // When our encodedNode is ready,this line pushes it to the encodedCharacters.
        //encodedCharacters is our attribute which was defined in .h file.
    }
}
void HuffmanConversionSystem::createEncodingOutput(std::string fullLine)
{
    std::string data ="";  //We will store our all encodings in this variable.
    for(size_t i=0;i<fullLine.length();i++) // This loop iterates through all characters in line.
    {   
        char representation = fullLine.at(i); //This line stores character at index i.
        for(size_t j=0;j<encodedCharacters.size();j++){ //This loop iterates through our encodedCharacters for every character comes from outer loop.
            if(encodedCharacters.at(j).encodedCharacter.getRepresentation() == representation){
                data+= encodedCharacters.at(j).code; // After a match found,this line updates our encoding line.
                break;
            }
        }
    }
    std::cout << data << std::endl; // After all operations are done,this line prints our encoding to the console.
    std::ofstream encodingOutput("Encoding.txt"); // This line creates a new file named Encoding.txt
    encodingOutput << data;  // Writes our encodings to our newFile.
    encodingOutput.close(); 
}

void HuffmanConversionSystem::saveTree(CharacterNode *_root){
    // I will use postorder traversal to save my tree in a text file.
    std::ofstream output("MyTree.txt");  // This line creates a new file named MyTree.txt.We will use this file while decoding.
    //treeCommands is an attribute of our system.It was initialized in our .h file and updated in the function traverseAndCopy()
    treeCommands = treeCommands.substr(0,treeCommands.length()-1); // To avoid comma at the last index of our variable.
    output << treeCommands; // This line writes treeCommands to the destination file.
    output.close();
}

void HuffmanConversionSystem::Decoder(std::string inputFile)
{
    //Input file will include our encodings.
    std::string line;  // Our encoding
    std::string treeLine;  // Our data which comes from MyTree.txt
    std::ifstream myFile(inputFile);
    if(myFile.is_open())
    {
        getline(myFile,line);  // Gets the line of our encoding file.
    }
    else
    {
        std::cout << "Unable to open file!" << std::endl;
    }
    std::ifstream treeFile("MyTree.txt");  // Saved by using preorder traversal.
    if(treeFile.is_open()){
        getline(treeFile,treeLine); // Gets the line of our tree file.
    }
    else
    {
        try
        {
            throw std::string("Error");
        }
        catch (std::string e){
            std::cout << "Please provide a tree data !" << std::endl;
            return;
        }
    }
    std::vector<std::string> allINodes;
    std::stringstream s_stream(treeLine); //create string stream from the strisng
    while(s_stream.good()) 
    {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        allINodes.push_back(substr);
   }
   std::vector<CharacterNode*> nodes;  //Firstly,I'm creating our nodes.This vector will include node pointers comes from inputFile.
   for(size_t j=0;j<allINodes.size();j++)
    {
       char _representation = allINodes.at(j).at(0); // Index 0 of each vector object is representation.
       std::string _frequency = allINodes.at(j).substr(1,allINodes.at(j).length()-1); //Index 1 to end represents frequency.
       int frequency ;
       CharacterNode *newNode;
       std::istringstream(_frequency) >> frequency;  // This line converts our string to int.
       if(_representation != '#'){ // We have used this representation for empty nodes .If representation does not equal to #,that means we are creating a leaf node.
           Character newCharacter(_representation,frequency);
           newNode = new CharacterNode();
           newNode->isLeaf = true;
           newNode->isEmpty = false;
           newNode->key = frequency;
           newNode->nodeCharacter = newCharacter;
           newNode->leftChild = nullptr;
           newNode->rigthChild = nullptr;
           newNode->parent = nullptr;
           nodes.push_back(newNode); // Pushing all nodes to our vector which was created before the loop
       }
       else
        { // That means we are creating an empty node.
            newNode = new CharacterNode();
            newNode->isLeaf = false; 
            newNode->isEmpty = true;
            newNode->key = frequency;
            newNode->leftChild = nullptr;
            newNode->rigthChild = nullptr;
            newNode->parent = nullptr;
            nodes.push_back(newNode);  // Pushing all nodes to our vector which was created before the loop
       }
   }
   root = constructTree(nodes,0); // This function call will create our tree again.
   decode(line); // Calling decode function and send it the line that written at 348
}

void HuffmanConversionSystem::listTree(){
    std::ifstream myFile("MyTree.txt");
    std::string treeLine;
    if(myFile.is_open()){
        getline(myFile,treeLine);
    }
    else{
        std::cout << "No tree!" << std::endl;
        return;
    }
    std::vector<std::string> allINodes;
    std::stringstream s_stream(treeLine); //create string stream from the strisng
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        allINodes.push_back(substr);
   }
   std::vector<CharacterNode*> nodes;  //Firstly,I'm creating our nodes.This vector will include node pointers comes from inputFile.
   for(size_t j=0;j<allINodes.size();j++)
    {
       char _representation = allINodes.at(j).at(0); // Index 0 of each vector object is representation.
       std::string _frequency = allINodes.at(j).substr(1,allINodes.at(j).length()-1); //Index 1 to end represents frequency.
       int frequency ;
       CharacterNode *newNode;
       std::istringstream(_frequency) >> frequency;  // This line converts our string to int.
       if(_representation != '#'){ // We have used this representation for empty nodes .If representation does not equal to #,that means we are creating a leaf node.
           Character newCharacter(_representation,frequency);
           newNode = new CharacterNode();
           newNode->isLeaf = true;
           newNode->isEmpty = false;
           newNode->key = frequency;
           newNode->nodeCharacter = newCharacter;
           newNode->leftChild = nullptr;
           newNode->rigthChild = nullptr;
           newNode->parent = nullptr;
           nodes.push_back(newNode); // Pushing all nodes to our vector which was created before the loop
       }
       else
        { // That means we are creating an empty node.
            newNode = new CharacterNode();
            newNode->isLeaf = false; 
            newNode->isEmpty = true;
            newNode->key = frequency;
            newNode->leftChild = nullptr;
            newNode->rigthChild = nullptr;
            newNode->parent = nullptr;
            nodes.push_back(newNode);  // Pushing all nodes to our vector which was created before the loop
       }
   }
 
   root = constructTree(nodes,0);
   CharacterNode *temp = root;
   createTreeVisualization(root,10);
   std::cout << treeRepresentation << std::endl;
}
void HuffmanConversionSystem::decode(std::string line){
    std::string decoding = "";  // We will store decoding inside this variable
    size_t index = 0;  // Starting point
    while(index < line.length())
    {
        CharacterNode *temp = root; // For each character in the line we will iterate again.
        while(!temp->isLeaf){  // Loop continues until we reach a leaf node
            if(line.at(index) == '0'){
                temp = temp->leftChild; // 0 means go to the leftChild
                index++;
            }
            else if(line.at(index) == '1'){
                temp = temp->rigthChild; // 1 means go to the rightChild.
                index++;
            }
        }
        decoding+= temp->nodeCharacter.getRepresentation(); //When we reach our leaf node,update decoding by our nodes representation.
    }
    
    std::cout << decoding << std::endl; // prints all characters to the console.
}
HuffmanConversionSystem::~HuffmanConversionSystem()
{
    delete root;
}

