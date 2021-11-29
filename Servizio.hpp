#include <string>

using namespace std;
class Servizio          //definizione della classe Servizio che implementa la traccia del problema
{
    public:
        int selezionaTree();    //seleziona quale albero utilizzare per effettuare le operazioni
        string get_RBTfile();   //seleziona il file di input dei vari insiemi numerici
        int caricarbt(string rbt_file);     //visualizza a video gli insiemi numerici del file dato in input
        void visualizza_header(string FileName);            //visualizza a video l'intestazione dell'output
        int unionerbt();            //implementazione dell'operazione di union
        int intersezionerbt();      //implemnetazione dell'operazione di intersezione
        int differenzarbt();        //implementazione dell'operazione di differenza
};
