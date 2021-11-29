#include <string>
#pragma once
using namespace std;

//Classe che implementa le caratteristiche del Nodo
struct Node
{
	int data; //campo chiave
	Node *parent; //campo puntatore all'elemento padre
	Node *left; //campo puntatore all'elemento figlio sinistro
	Node *right; //campo puntatore all'elemento figlio destro
	char color; //campo colore: 'r'=Red, 'b'=black
	Node(){;}
};
typedef Node *NodePtr; //definizione del nuovo tipo di dato derivato dalla classe Node

//Classe implementa le caratteristiche della struttura dati Red_Black_Tree
class RBTree
{
    private:
        NodePtr root;   //Campo radice
        NodePtr TNULL;  //Nodo sentinella nullo

        void preOrderHelper(NodePtr node);      //visita preorder
        void inOrderHelper(NodePtr node);       //visita inorder
        void postOrderHelper(NodePtr node);     //visita postorder
        NodePtr searchTreeHelper(NodePtr node,int key);     //ricerca di una chiave nella struttira
        void fixDelete(NodePtr x);              //fixup dopo l'operazione di delete
        void rbTransplant(NodePtr u,NodePtr v);             //transplant per Albero Red_Black
        void deleteNodeHelper(NodePtr node,int key);        //cancellazione
        void fixInsert(NodePtr k);              //fixup dopo l'operazione di inserimento
        void printHelper(NodePtr root,string indent,bool last);     //stampa dell'intera struttura
    public:
        RBTree();       //costruttore per inizializzazione
        void preorder();
        void inorder();
        void postorder();
        NodePtr searchTree(int k);
        NodePtr minimum(NodePtr node);      //ricerca del minimo
        NodePtr maximum(NodePtr node);      //ricerca del massimo
        NodePtr successor(NodePtr x);       //ricerca del successore
        NodePtr predecessor(NodePtr x);     //ricerca del predecessore
        void leftRotate(NodePtr x);         //rotazione verso sinistra
        void rightRotate(NodePtr x);        //rotazione verso destra
        void insert(int key);               //inserimento di un nuovo nodo
        NodePtr getRoot();                  //procedura che restituisce la radice della struttura
        void deleteNode(int data);          //cancellazione
        void prettyPrint();                 //stampa
};
