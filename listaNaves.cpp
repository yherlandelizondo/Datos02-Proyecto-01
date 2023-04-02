#include <iostream>
#include <stdio.h>
#include "nodoNaves.cpp"

using namespace std;

//EN la clase nodo se necesita un identificador para cada nodo

class listaNaves{

    nodoNaves* head;
    public:
        listaNaves(){
            head=NULL;
        }

        void insert(int data){
            nodoNaves* newNode = new nodoNaves(data);
            newNode->next = head;
            head = newNode;
        }

        nodoNaves* removeAux(nodoNaves* node){
            nodoNaves* temp = head;
            delete node;
            while (temp != NULL){
                
                if(temp->getData() == node->getData()){
                    head = head -> next;
                    return temp;
                }
                else if (temp->next->getData() == node->getData()){
                    temp->next = temp->next->next;
                    return temp;
                }
                else{
                    temp = temp->next;
                }
            }
            return 0;
        }

        int remove(int value){
            nodoNaves* temp=head;
            while (temp != NULL){
                if(temp->getData() == value){
                    removeAux(temp);
                    return 0;
                }
                else{
                    temp = temp->next;
                }
            }
            return 0;
        }

        int prinList(){
            nodoNaves* temp1=head;
            if(head == NULL){
                cout<<"lista vacía"<<"\n";
            }
            else{
                while (temp1 != NULL){
                    cout<<temp1->getData()<<"->";
                    temp1 = temp1->next;
                }
            }
            return 0;
        }

        nodoNaves* getHead(){
            return head;
        }

        void setHead(nodoNaves* data){
            head = data;
        }
};