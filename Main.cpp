#include <iostream>
#include <stdio.h>
#include "Initializer.cpp"
#include "SpaceshipNode.cpp"

using namespace std;

int main(){
    SpaceshipNode* node = new SpaceshipNode(1);
    node->randomColor();
    return 0;
}