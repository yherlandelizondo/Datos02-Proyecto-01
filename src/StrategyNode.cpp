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
        //!constructor method
        StrategyNode(){
            nodeID = 0;
            next = NULL;
        }
        //!constructor method
        StrategyNode(int identifier, int strategyIdentifier, string StrategyPhat){
            this -> nodeID = identifier;
            this -> next = NULL;
            this -> path = StrategyPhat;
            this -> strategyID = strategyIdentifier;
        }
        //!method used to set the node id
        void setNodeID(int identifier){
            this -> nodeID = identifier;
        }
        //!method used to get the node id
        int getNodeID(){
            return nodeID;
        }
        //!method used to get the strategy id
        int getStrategyID(){
            return strategyID;
        }
        //!method used to set the strategy id
        void setStrategyID(int strategyIdentifier){
            this -> strategyID =  strategyIdentifier;
        }
        //!method used to set the next node
        void setNext(StrategyNode* ptr){
            this -> next = ptr;
        }   
        //!method used to seth the xml path
        void setPath(string StrategyPath){
            this -> path = StrategyPath;
        }
        //!method used to get the xml path
        string getPath(){
            return path;
        }
        //!method used to get the next node
        StrategyNode* getNext(){
            return next;
        }
};