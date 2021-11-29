#include "Red-Black-Tree.hpp"
#include <iostream>
#include <string>
using namespace std;

RBTree::RBTree()            //implementazione metodo costruttore della classe RBTree
{
    TNULL=new Node;
    TNULL->color='b';
    TNULL->left=nullptr;
    TNULL->right=nullptr;
    root=TNULL;
}

void RBTree::preOrderHelper(NodePtr node)           //operazione di visita preorder
{
    if(node!=TNULL)
    {
        cout<<node->data<<" ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RBTree::inOrderHelper(NodePtr node)            //operazione di visita inorder
{
    if(node!=TNULL)
    {
        inOrderHelper(node->left);
        cout<<node->data<<" ";
        inOrderHelper(node->right);
    }
}

void RBTree::postOrderHelper(NodePtr node)          //operazione di visita postorder
{
    if(node!=TNULL)
    {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout<<node->data<<" ";
    }
}

NodePtr RBTree::searchTreeHelper(NodePtr node,int key)      //operazione di ricerca di una chiave nella struttura
{
    if(node==TNULL || key==node->data)
        return node;
    if(key<node->data)
        return searchTreeHelper(node->left,key);
    else if(key>node->data)
        return searchTreeHelper(node->right,key);
    return TNULL;
}

void RBTree::fixDelete(NodePtr x)                       //operazione di fixup dopo la cancellazione
{
    NodePtr s;
    while(x!=root && x->color=='b')
    {
        if(x==x->parent->left)      //x è figlio sx
        {
            s=x->parent->right;
            if(s->color=='r')       //caso 1: zio di x rosso
            {
                s->color='b';
                x->parent->color='r';
                leftRotate(x->parent);
                s=x->parent->right;
            }
            if(s->left->color=='b' && s->right->color=='b')     //caso 2: zio di x ed entrambi i suoi figli neri
            {
                s->color = 'r';
                x = x->parent;
            }
            else
                {
					if(s->right->color=='b')            //caso 3: zio di x nero con figlio sx rosso e il dx nero
					{
                        s->left->color='b';
						s->color=1;
						rightRotate(s);
						s = x->parent->right;
					}
					s->color=x->parent->color;          //caso 4: zio di x nero con figlio dx rosso
					x->parent->color='b';
					s->right->color='b';
					leftRotate(x->parent);
					x=root;
				}
			}
			else            //ripetizione dei casi sopra elencati con x figlio destro
                {
                    s=x->parent->left;
                    if(s->color=='r')
                        {
                            s->color='b';
                            x->parent->color='r';
                            rightRotate(x->parent);
                            s=x->parent->left;
                        }
                    if(s->right->color=='b' && s->right->color=='b')
                        {
                            s->color='r';
                            x=x->parent;
                        }
                    else
                        {
                            if(s->left->color=='b')
                                {
                                    s->right->color='b';
                                    s->color='r';
                                    leftRotate(s);
                                    s=x->parent->left;
                                }
                            s->color=x->parent->color;
                            x->parent->color='b';
                            s->left->color='b';
                            rightRotate(x->parent);
                            x=root;
                    }
                }
		}
		x->color='b';
}

void RBTree::rbTransplant(NodePtr u,NodePtr v)          //transplant per una struttura Red_Black_Tree
{
    if (u->parent==nullptr)
        root=v;
    else if(u==u->parent->left)
			u->parent->left=v;
        else
			u->parent->right=v;
    v->parent=u->parent;
}

void RBTree::deleteNodeHelper(NodePtr node,int key)         //operazione di cancellazione di un nodo dalla struttura
{
    NodePtr x,y;
    NodePtr z=searchTree(key);  //ricerca del nodo con chiave key da dover cancellare
    if(z==TNULL)                //se il nodo non c'è nella struttura non si può effettuare la cancellazione
        {
			cout<<"Impossibile trovare la chiave desiderata!"<<endl;
			return;
		}
    y=z;                        //inizio della cancellazione
    char y_original_color=y->color;
    if(z->left==TNULL)
        {
			x=z->right;
			rbTransplant(z,z->right);
		}
    else if(z->right==TNULL)
        {
			x=z->left;
			rbTransplant(z,z->left);
		}
        else
            {
                y=minimum(z->right);
                y_original_color=y->color;
                x=y->right;
                if(y->parent==z)
                    x->parent=y;
                else
                    {
                        rbTransplant(y,y->right);
                        y->right=z->right;
                        y->right->parent=y;
                    }
                rbTransplant(z,y);
                y->left=z->left;
                y->left->parent=y;
                y->color=z->color;
            }
		delete z;
    if(y_original_color=='b')
        fixDelete(x);
}

void RBTree::fixInsert(NodePtr k)                                //operazione di fixup dopo l'operazione di insert
{
    NodePtr u;
    while(k!=root && k->parent->color=='r')
        {
			if(k->parent==k->parent->parent->right)
                {
                    u=k->parent->parent->left;                  //zio di x figlio destro
                    if(u->color=='r')                           //caso 1: zio di x rosso
                        {
                            u->color='b';
                            k->parent->color='b';
                            k->parent->parent->color = 'r';
                            k=k->parent->parent;
                        }
                    else                                        //caso 2: zio di x nero e x figlio sinistro
                        {
                            if(k==k->parent->left)
                                {
                                    k=k->parent;
                                    rightRotate(k);
                                }
                            k->parent->color='b';               //caso 3: zio di x nero e x figlio destro
                            k->parent->parent->color='r';
                            leftRotate(k->parent->parent);
                        }
                }
            else                                                //ripetizione dei casi sopra elencati con zio di x figlio sinistro
                {
                    u=k->parent->parent->right;
                    if(u->color=='r')
                        {
                            u->color='b';
                            k->parent->color='b';
                            k->parent->parent->color='r';
                            k=k->parent->parent;
                        }
                    else
                        {
                            if(k==k->parent->right)
                            {
                                k=k->parent;
                                leftRotate(k);
                            }
                            k->parent->color = 'b';
                            k->parent->parent->color = 'r';
                            rightRotate(k->parent->parent);
                        }
                }
		}
    root->color='b';
}

void RBTree::printHelper(NodePtr root,string spazio,bool last)      //stampa dell'intera struttura
{
    if (root!=TNULL)
        {
            cout<<spazio;
            if(last)
                {
                    cout<<"R----";
                    spazio += "     ";
                }
		   else
                {
                    cout<<"L----";
                    spazio += "|    ";
                }
           string sColor = root->color=='r'?"RED":"BLACK";
		   cout<<root->data<<"("<<sColor<<")"<<endl;
		   printHelper(root->left,spazio,false);
		   printHelper(root->right,spazio,true);
		}
}


void RBTree::preorder()
{
    preOrderHelper(this->root);
}

void RBTree::inorder()
{
    inOrderHelper(this->root);
}

void RBTree::postorder()
{
    postOrderHelper(this->root);
}


NodePtr RBTree::searchTree(int k)
{
    return searchTreeHelper(this->root,k);
}

NodePtr RBTree::minimum(NodePtr node)       //ricerca della chiave minima
{
    while(node->left!=TNULL)
        {
            node=node->left;
        }
    return node;
}

NodePtr RBTree::maximum(NodePtr node)       //ricerca della chiave massima
{
    while (node->right!=TNULL)
        {
            node=node->right;
        }
    return node;
}

NodePtr RBTree::successor(NodePtr x)        //ricerca del successore di un nodo dato in input
{
    if(x->right!=TNULL)
        return minimum(x->right);
    NodePtr y=x->parent;
    while(y!=TNULL && x==y->right)
        {
            x=y;
            y=y->parent;
        }
    return y;
}

NodePtr RBTree::predecessor(NodePtr x)      //ricerca del predecessore di un nodo dato in input
{
    if(x->left!=TNULL)
        return maximum(x->left);
    NodePtr y=x->parent;
    while(y!=TNULL && x==y->left)
        {
            x=y;
            y=y->parent;
        }
    return y;
}


void RBTree::leftRotate(NodePtr x)          //rotazione verso sinistra
{
    NodePtr y=x->right;
    x->right=y->left;
    if(y->left!=TNULL)
        y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==nullptr)
        this->root=y;
    else if(x==x->parent->left)
            x->parent->left = y;
        else
			x->parent->right=y;
    y->left=x;
    x->parent=y;
}

void RBTree::rightRotate(NodePtr x)         //rotazione verso destra
{
    NodePtr y=x->left;
    x->left=y->right;
    if(y->right!=TNULL)
        y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==nullptr)
        this->root=y;
    else if(x==x->parent->right)
            x->parent->right=y;
         else
			x->parent->left=y;
    y->right=x;
    x->parent=y;
}

void RBTree::insert(int key)            //operazione di inserimento
{
    NodePtr node=new Node;              //creazione del nuovo nodo
    node->parent=nullptr;
    node->data=key;
    node->left=TNULL;
    node->right=TNULL;
    node->color='r';
    NodePtr y=nullptr;
    NodePtr x=this->root;
    while(x!=TNULL)
        {
            y=x;
			if(node->data<x->data)
				x=x->left;
			else
				x=x->right;
        }
    node->parent=y;
    if(y==nullptr)
        root=node;
    else if(node->data<y->data)
			y->left=node;
		 else
			y->right=node;
    if(node->parent==nullptr)
        {
			node->color='b';
			return;
		}
    fixInsert(node);
}

NodePtr RBTree::getRoot()               //procedura che restituisce la radice della struttura
{
    return this->root;
}

void RBTree::deleteNode(int data)
{
    deleteNodeHelper(this->root, data);
}

void RBTree::prettyPrint()
{
    if(root)
        printHelper(this->root,"",true);
};
