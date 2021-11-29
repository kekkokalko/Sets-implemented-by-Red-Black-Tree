#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Servizio.hpp"
#include "Red-Black-Tree.hpp"
using namespace std;

extern vector<vector<int>> node;
extern vector<int> n_node;

//procedura che permette la selezione degli alberi per poi effettuare le varie operazioni
int Servizio::selezionaTree()
{
    int i;
    cin>>i;
    return i;
}

//procedura che acquisisce il nome del file contenente i valori degli insiemi numerici
string Servizio::get_RBTfile()
{
    string s;
    cout<<"Digitare il nome del file di input ";
    cin>>s;
    s="./Data/"+s+".txt";                                       //percorso del file che contiene i valori degli insiemi
    return s;
}


/*si carica il file con i valori degli insiemi; i dati vengono inseriti nel vettore node mentre il numero totale dei nodi
di ogni insieme viene inserito nel vettore n_node. In input si ha il file che contiene i valori degli insiemi;
in output si restituisce un intero che indicherà se il caricamento è andato a buon fine o no.*/
int Servizio::caricarbt(string rbt_file)
{
    int i=0;                                                    //tale variabile indica quanti insiemi è composto il file di input
    int j;
    int i_node;
    int n;                                                      //tale variabile indica la quantità di numeri di cui è composto un insieme
    string line;
    ifstream readFile(rbt_file);
    if(readFile.fail())                                         //controllo apertura del file
        {
            cout<<"File non trovato"<<endl;
            return 0;                                           //caricamento fallito
        }
    cout<<"Il file selezionato e' composto dai seguenti insiemi:";
    while(!readFile.eof())                                      //finchè non si sono esaminati tutti gli elementi del file
        {
            n_node.push_back(0);                                //inizializzazione della cella i del vettore n_node
            n=0;
            getline(readFile,line);                             //lettura di una riga intera del file
            stringstream stream(line);                          //definizione di uno stream associato alla stringa line che contiene una riga del file di input
            if(line.length()>0)				                    //strategia per saltare le linee vuote
                {
                    vector<int> node_temp;
                    while(stream>>i_node)                       //lettura di un numero alla volta
                        {
                            node_temp.push_back(i_node);        //i-esimo insieme ha come n-esimo valore il numero i_node e lo si salva nel vettore temporaneo node_temp
                            n_node.at(i)++;                     //aggiorno il numero di nodi dell'insieme i-esimo nel vettore apposito
                            n++;
                        }
                    node.push_back(node_temp);                  //inserimento degli elementi appena salvati nel vettore temporaneo nel vettore di vettori node
                    cout<<endl;
                    cout<<endl<<"Insieme n."<<i+1<<" "<<"avente "<<n_node[i]<<" elementi:"<<endl;
                    for(j=0;j<n;j++)
                        {
                            cout<< node[i][j]<<' ';             //stampa del contenuto del file di input
                        }
                    i++;
                }
        }
    cout<<endl<<endl<<endl;
    readFile.close();
    return 1;                                                   //caricamento avvenuto con successo
}

/*visualizzazione del file di intestazione*/
void Servizio::visualizza_header(string FileName)
{
    string line;
    ifstream HeaderFile;
    HeaderFile.open(FileName);
    if (!HeaderFile)
        cout<< "Errore di apertura del file di intestazione: "<< "Intestazione";
    while(getline(HeaderFile,line))
        cout<<line<<endl;
}

/*Procedura che implementa l'operazione di union sugli insiemi selezionati*/
int Servizio::unionerbt()
{
	RBTree rbt[2];			                                    //Array di tipo RBTree contenente le 2 strutture su cui si deve effettuare l'unione
    RBTree RBTreeUnion;		                                    //Albero Red_Black di unione
	int j;                                                      //indice di scorrimento
    int nUnion=0;                                               //numero di elementi dell'albero di unione
	int a;                                                      //variabile che definisce il primo insieme
	int b;                                                      //variabile che definisce il secondo insieme
	NodePtr nodePtr;
	cout<<"Digitare 1 per selezionare il primo insieme, 2 per selezionare il secondo insieme, 3 per selezionare il terzo insieme ecc."<<endl;
	cout<<"Seleziona il numero del primo insieme:";
	a=selezionaTree();
	cout<<"Seleziona il numero del secondo insieme:";
	b=selezionaTree();
	//primo albero
	for(j=0;j<n_node.at(a-1);j++)
    {
        rbt[0].insert(node[a-1][j]);                            //costruzione del primo albero formato dagli elementi del primo insieme selezionato
        RBTreeUnion.insert(node[a-1][j]);
        nUnion++;
	}
	cout<<endl;
    cout<<"Albero Red-Black "<<a<<" composto da "<<n_node.at(a-1)<<" nodi"<<endl;
    //stampa del primo albero
	rbt[0].prettyPrint();
	cout<<endl<<"Visita inorder del primo albero:"<<endl;
	rbt[0].inorder();
	//secondo albero
	for(j=0;j<n_node.at(b-1);j++)
    {
        rbt[1].insert(node[b-1][j]);                            //costruzione del secondo albero atraverso gli elementi del secondo insieme
        nodePtr=rbt[0].searchTree(node[b-1][j]);                //ricerca nel primo albero degli elmenti del secondo albero per poter creare l'albero unione
        if(nodePtr->data!=node[b-1][j])
        {
            RBTreeUnion.insert(node[b-1][j]);                   //gli elementi distinti vengono inseriti nel terzo albero,cioè l'albero di unione
            nUnion++;
        }
	}
	cout<<endl;
    //stampa del secondo albero
    cout<<"Albero Red-Black "<<b<<" composto da "<<n_node.at(b-1)<<" nodi"<<endl;
	rbt[1].prettyPrint();
	cout<<endl<<"Visita inorder del secondo albero:"<<endl;
	rbt[1].inorder();
    //stampa dell'albero unione
    cout<<endl;
	cout<<endl<<"ALbero Red-Black di unione dell'insieme "<<a<<" e dell'insiene "<<b<<" composto da "<<nUnion<<" elementi"<<endl;
    RBTreeUnion.prettyPrint();
    cout<<endl<<"Visita inorder dell'albero di unione:"<<endl;
    RBTreeUnion.inorder();
    cout<<endl;
    return 1;
}

//Procedura che implementa l'operazione di intersezione e ne visulizza il risultato
int Servizio::intersezionerbt()
{
    RBTree rbt[2];				                                //Array di tipo RBTree contenente le 2 strutture su cui si deve effettuare l'intersezione
    RBTree RBTreeIntersec;		                                //Albero Red_Black di intersezione
    int j;
    int nIntersec=0;                                            //numero di elementi dell'albero di intersezione
    int a;
    int b;
    int c;                                                      //indica l'indice della dimensione più piccola tra i due insiemi selezionati nel vettore n_node
    int d;                                                      //indica l'indice dell'isnieme che ha la dimensione più grande nell'array rbt
    NodePtr nodePtr;
    cout<<"Digitare 1 per selezionare il primo insieme, 2 per selezionare il secondo insieme, 3 per selezionare il terzo insieme ecc."<<endl;
	cout<<"Seleziona il numero del primo insieme:";
	a=selezionaTree();
	cout<<"Seleziona il numero del secondo insieme:";
	b=selezionaTree();
    for(j=0;j<n_node.at(a-1);j++)                               //costruzione del primo albero
            rbt[0].insert(node[a-1][j]);
    cout<<endl;
    cout<<"Albero Red-Black "<<a<<" composto da "<<n_node.at(a-1)<<" nodi"<<endl;
    //stampa del primo albero
    rbt[0].prettyPrint();
    cout<<"Visita inorder del primo albero:"<<endl;
    rbt[0].inorder();
    for(j=0;j<n_node.at(b-1);j++)                               //costruzione del secondo albero
        rbt[1].insert(node[b-1][j]);
    cout<<endl;
    //stampa del secondo albero
    cout<<"Albero Red-Black "<<b<<" composto da "<<n_node.at(b-1)<<" nodi"<<endl;
    rbt[1].prettyPrint();
    cout<<"Visita inorder del secondo albero:"<<endl;
    rbt[1].inorder();
    if(n_node.at(a-1)>n_node.at(b-1))                          //ricerca della dimensione più piccola tra i due insiemi
        {
            c=b;
            d=0;
        }
    else
        {
            c=a;
            d=1;
        }
    for(j=0;j<n_node.at(c-1);j++)                              //costruzione dell'albero intersezione
        {
            nodePtr=rbt[d].searchTree(node[c-1][j]);           //si ricerca l'elemento dell'isnieme con dimensione più piccola in quello con dimensione più grande
            if(nodePtr->data==node[c-1][j])                    //gli elementi in comune tra i due insiemi vengono inseriti nel insieme intersezione
                {
                    RBTreeIntersec.insert(node[c-1][j]);
                    nIntersec++;
                }
        }
    //stampa dell'albero intersezione
    cout<<endl;
    cout<<"ALbero Red-Black di intersezione composto da "<<nIntersec<<" elementi"<<endl;
    RBTreeIntersec.prettyPrint();
    cout<<"Visita inorder dell'albero di intersezione:"<<endl;
    RBTreeIntersec.inorder();
    cout<<endl;
    return 1;
}

//Procedura che effettua l'operazione di differenza tra i due insiemi selezionati e ne visualizza il risultato
int Servizio::differenzarbt()
{   //stesse variabili e strutture utilizzate nelle procedure precedenti
    RBTree rbt[2];
    RBTree RBTreeDifference;		                                        //Albero di differenza
    int j;
    int nDifference=0;                                                      //numero di elementi dell'albero di differenza
    int a;
    int b;
    NodePtr nodePtr;
    cout<<"Digitare 1 per selezionare il primo insieme, 2 per selezionare il secondo insieme, 3 per selezionare il terzo insieme ecc."<<endl;
	cout<<"Seleziona il numero del primo insieme:";
	a=selezionaTree();
	cout<<"Seleziona il numero del secondo insieme:";
	b=selezionaTree();
    for(j=0;j<n_node.at(b-1);j++)                                           //costruzione del primo albero contenente gli elementi del secondo insieme
        rbt[0].insert(node[b-1][j]);
    cout<<endl;
    //stampa del primo labero
    cout<<"Albero Red-Black "<<a<<" composto da "<<n_node.at(a-1)<<" nodi"<<endl;
    rbt[0].prettyPrint();
    cout<<"Visita inorder del primo albero:"<<endl;
    rbt[0].inorder();

    for(j=0;j<n_node.at(a-1);j++)                                          //costruzione del secondo albero contenente gli elementi del primo insieme
        {
            rbt[1].insert(node[a-1][j]);
            nodePtr=rbt[0].searchTree(node[a-1][j]);                       //ricerca degli elementi del primo insieme nel secondo insieme
            if(nodePtr->data!=node[a-1][j])
                {
                    RBTreeDifference.insert(node[a-1][j]);                 //gli elementi del primo insieme che non si trovano nel secondo insieme vengono aggiunti all'insieme differenza
                    nDifference++;
                }
        }
    cout<<endl;
    cout<<"Albero Red-Black "<<b<<" composto da "<<n_node[b-1]<<" nodi"<<endl;
    //stampa del secondo albero
    rbt[1].prettyPrint();
    cout<<"Visita inorder del secondo albero:"<<endl;
    rbt[1].inorder();
    //stampa albero di differenza
    cout<<endl;
    cout<<"Albero Red-Black di differenza composto da "<<nDifference<< " elementi"<<endl;
    RBTreeDifference.prettyPrint();
    cout<<"Visita inorder dell'albero di differenza:"<<endl;
    RBTreeDifference.inorder();
    cout<<endl;
    return 1;
}
