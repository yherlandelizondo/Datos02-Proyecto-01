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
        int lastStrategyUsed = 5; 

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
                if (randomID == lastStrategyUsed){
                    randomID = rand()%4;
                    i--;
                }else{
                    if(randomID == 0){
                        cout << "entro 1\n";
                        insert(i,randomID, sprinterPath);
                        lastStrategyUsed = randomID;

                    }else if(randomID == 1){
                        cout << "entro 2\n";
                        insert(i, randomID, deceleratorPath);
                        lastStrategyUsed = randomID;

                    }else if(randomID == 2){
                        cout << "entro 3\n";
                        insert(i, randomID, cowboyPath);
                        lastStrategyUsed = randomID;

                    }else if(randomID == 3){
                        cout << "entro 4\n";
                        insert(i, randomID, atomicCowboyPath);
                        lastStrategyUsed = randomID;
                    } 
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
            status = false;
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
        //!function used to return the path of an specific strategy
        string getStrategyPath(int ID){
            StrategyNode* temp = head;

            while (temp != NULL){ 
                if(temp->getStrategyID() == ID){
                    return temp -> getPath();
                }  
                temp = temp -> getNext();
            }
            return temp->getPath();
        }

        void removeFromMemory(int ID){
            StrategyNode* temp = head;
            int randomID = rand()%4;

            while (temp != NULL){ 
                if(randomID != ID){
                    if(temp -> getStrategyID() == ID){
                        if(randomID == 0){
                            temp -> setStrategyID(randomID);
                            temp -> setPath(sprinterPath);

                        }else if(randomID == 1){
                            temp -> setStrategyID(randomID);
                            temp -> setPath(deceleratorPath);
                            
                        }else if(randomID == 2){
                            temp -> setStrategyID(randomID);
                            temp -> setPath(cowboyPath);

                        }else if(randomID == 3){
                            temp -> setStrategyID(randomID);
                            temp -> setPath(atomicCowboyPath);
                        }
                    }  
                    temp = temp -> getNext();
                }else{
                    randomID = rand()%4;
                }
            }
        }

        void loadOnMemory(int ID){
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