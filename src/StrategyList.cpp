#include<iostream>
#include<stdio.h>
#include <cstdlib>
#include "StrategyNode.cpp"
using namespace std;

class StrategyList{
    
    StrategyNode* head;

    private:
        string sprinterPath = "./data/sprinter.xml";
        string deceleratorPath = "./data/decelerator.xml";
        string cowboyPath = "./data/cowboy.xml";
        string atomicCowboyPath = "./data/atomicCowboy.xml";
        bool status = false;

        int getIdToModify(){
            return rand()%2;
        }

    public:
        //! constructor method
        StrategyList(){
            head = NULL;
            
        }
        //!insert two nodes to the list, the ID for those nodes it's random
        void initialize(){
            for(int i = 0; i < 2; i++){

                int randomID = rand()%4;

                if(randomID == 0){
                    cout << "entro 1\n";
                    insert(i,randomID, sprinterPath);
                }else if(randomID == 1){
                    cout << "entro 2\n";
                    insert(i, randomID, deceleratorPath);
                }else if(randomID = 2){
                    cout << "entro 3\n";
                    insert(i, randomID, cowboyPath);
                }else{
                    cout << "entro 4\n";
                    insert(i, randomID, atomicCowboyPath);
                } 
            }
        }
        //! method to insert a node at the beginnig of the list
        void insert(int nodeID, int strategyID, string path){
            StrategyNode* newNode = new StrategyNode(nodeID, strategyID, path);
            newNode -> setNext(head);
            head = newNode;
        }  
        //! method used to return the head of the list
        StrategyNode* getHead(){
            return head;
        }
        //!function to check if some strategy it's loaded on memory
        bool checkStrategyStatus(int ID){
            StrategyNode* temp = head;

            while (temp != NULL){ 
                if(temp->getStrategyID() == ID){
                    status = true;
                    return status;
                }  
                temp = temp -> getNext();
            }
            return status;
        }

        void loadMemory(int ID){
            StrategyNode* temp = head;

            while (temp != NULL){ 
                if(temp -> getNodeID() == getIdToModify()){
                    if(ID == 0){
                        temp -> setPath(sprinterPath);
                        temp -> setStrategyID(ID);
                    }
                    if(ID == 1){
                        temp -> setPath(deceleratorPath);
                        temp -> setStrategyID(ID);
                    }
                    if(ID == 2){
                        temp -> setPath(cowboyPath);
                        temp -> setStrategyID(ID);
                    }
                    else{
                        temp -> setPath(atomicCowboyPath);
                        temp -> setStrategyID(ID);
                    }
                }  
                temp = temp -> getNext();
            }
        }
};