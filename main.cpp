#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Servizio.hpp"

using namespace std;

char HeaderFile[]="./Data/Intestazione.txt";            //percorso file di intestazione
vector<vector<int>> node;                               //vettore globale che contiene i valori degli insiemi di input
vector<int> n_node;                                     //vettore che contiene le dimensioni dei vari insiemi di input

int main(int argc, char** argv)
{
	int i_switch;               //azione scelta da effettuare
	int i_exit;                 //variabile per rimanere o uscire dal programma
	int rbt_loaded=0;           //variabile che indica lo stato dell'apertura del file
	string rbt_file;            //nome del file test
	Servizio servizio;
    servizio.visualizza_header(HeaderFile);     //visualizzazione dell'intestazione
	while(rbt_loaded==0)
        {
           rbt_file=servizio.get_RBTfile();
           cout<<endl;
           rbt_loaded=servizio.caricarbt(rbt_file);
        }
    cout<<endl<<"---------------Implementazione--------------------"<<endl;
	while(i_exit!=4)
        {
            cout<<"Digitare:"<<endl;
            cout<<"1 per eseguire l'operazione di union"<<endl;
            cout<<"2 per eseguire l'operazione di intersezione"<<endl;
            cout<<"3 per eseguire l'operazione di differenza"<<endl;
            cout<<"4 per uscire e terminare il programma"<<endl;
            cin>>i_switch;
            cout<<" "<<endl;
            switch(i_switch)
                {
                    case 1:
                        {
                            cout<<"E' stata scelta l'operazione di union"<<endl;
                            servizio.unionerbt();
                            break;
                        }
                    case 2:
                        {
                            cout<<"E' stata scelta l'operazione di intersezione"<<endl;
                            servizio.intersezionerbt();
                            break;
                        }
                    case 3:
                        {
                            cout<<"E' stata scelta l'operazione di differenza"<<endl;
                            servizio.differenzarbt();
                            break;
                        }
                    case 4:
                        {
                            cout<<"Uscita dal programma"<<endl;
                            i_exit=4;
                            break;
                        }
                    default:
                        {
                            cout<<"Caso sconosciuto!"<<endl;
                            break;
                        }
                }
        }
	return 0;
}
