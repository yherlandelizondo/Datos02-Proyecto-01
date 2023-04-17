#include <iostream>
#include <stdio.h>

using namespace std;

class StrategyNode{

    private:
        int nodeID;
        int strategyID;
        StrategyNode* next;
        string path;

    public:
        StrategyNode(){
            nodeID = 0;
            next = NULL;
        }

        StrategyNode(int identifier, int strategyIdentifier, string StrategyPhat){
            this -> nodeID = identifier;
            this -> next = NULL;
            this -> path = StrategyPhat;
            this -> strategyID = strategyIdentifier;
        }

        void setNodeID(int identifier){
            this -> nodeID = identifier;
        }

        int getNodeID(){
            return nodeID;
        }

        int getStrategyID(){
            return strategyID;
        }

        void setStrategyID(int strategyIdentifier){
            this -> strategyID =  strategyIdentifier;
        }

        void setNext(StrategyNode* ptr){
            this -> next = ptr;
        }   

        void setPath(string StrategyPath){
            this -> path = StrategyPath;
        }

        string getPath(){
            return path;
        }

        StrategyNode* getNext(){
            return next;
        }
};