#include "Character.h"

Character::Character()
{
    frequency = 0;
    representation = '#' ;
}
Character::Character(char _representation,int _frequency){
    representation = _representation;
    frequency = _frequency;
}
Character::Character(const Character &source){
    representation = source.representation;
    frequency = source.frequency;
}
void Character::setRepresentation(char _representation){
    representation = _representation;
}
void Character::setFrequency(int _frequency){
    frequency = _frequency;
}
Character::~Character()
{
    // Nothing
}

