#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
    char representation;
    int frequency;
public:
    Character();
    Character(char _representation,int _frequency);
    Character(const Character &source); // Copy constructor
    void setRepresentation(char _representation);
    char getRepresentation(){return representation;}
    void setFrequency(int _frequency);
    int getFrequency(){return frequency;}
    ~Character();

};

#endif // CHARACTER_H
