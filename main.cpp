#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "HuffmanConversionSystem.h"
using namespace std;
int main(int argc, char* argv[]){
    string controlInput = argv[1];   // We will choose our system acoording to the commands.
    if(controlInput.compare("-i") == 0)
    {   // name -i input.txt -encode // name -i input.txt -decode // name -i input.txt -encode -s character
        string inputFile = argv[2];
        if(argc == 4)  // name -i input.txt -encode // name -i input.txt -decode
        {   
            string operation = argv[3]; // -encode or -decode
            if(operation.compare("-encode") == 0){
                HuffmanConversionSystem huffmanSystem;  // This line creates our conversion system.
                huffmanSystem.Encoder(inputFile); // This line calls our encoder.
            }
            else if(operation.compare("-decode") == 0){
                HuffmanConversionSystem huffmanSystem;
                huffmanSystem.Decoder(inputFile);
            }
        }
        else if(argc == 6 ) { // name -i input.txt -encode -s character
             HuffmanConversionSystem huffmanSystem;
             huffmanSystem.Encoder(inputFile);
             string _character = argv[5];
             char character = _character.at(0);
             huffmanSystem.getCodeFromNodes(character);
        }
    }
    else if(controlInput.compare("-s") == 0)
    {   //  name -s character
        HuffmanConversionSystem huffmanSystem;
        string _character = argv[2];
        char character = _character.at(0);
        huffmanSystem.getCodeFromTree(character);
    }
    else if(controlInput.compare("-l") == 0){
        HuffmanConversionSystem huffmanSystem;
        huffmanSystem.listTree();
    }
    return 0;
    }

