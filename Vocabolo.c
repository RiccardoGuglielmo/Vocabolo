// Cognome: Guglielmo
// Nome: Riccardo

/* Nota 1: i commenti riguardanti gli algoritmi implementati, sono abbastanza
           lunghi perche' dettagliati e necessari per comprendere il codice
           in poco tempo. Alcuni di questi commenti, pero', sono stati
           sostituiti da commenti brevi che sono semplici "traduzioni in
           italiano", di pezzi di codice che però rendono perfettamente idea
           di quello che fa il codice. Le "traduzioni in italiano" del codice,
           sono delle bravi frasi messe fra virgolette.                     */
/* Nota 2: quando nei commenti scrivo "carattere DEL" o "carattere INVIO" o
           qualcosa del genere, intendo il carattere ottenuto digitando il
           tasto in questione.                                              */
/* Nota 3: nei commenti delle funzioni getNumGiocatori() e setParola(),
           quando parlo di caratteri inseriti o tasti digitati dall'utente
           mi riferisco quelli inseriti/digitati durante l'esecuzione della
           funzione che esse chiamana (la rispettiva funzione definita nel
           progetto). Si capira' il perche' di cio', nella la lettura.
/* Nota 4: nello sviluppo del programma, e' stato previsto ogni tipo di errore
           possibile o malfunzionamento, che potrebbe essere provocato dall'
           utente inserendo, o premendo un tasto non proposto e di conseguenza
           sono stati implementati dei filtri, o comunque dei particolari
           algoritmi, che evitano questi inconvenienti.                     */

//______________________________________________________________________________

// Implementazione delle librerie:
#include <stdio.h>  //per utilizzare le funzioni printf() e scanf();
#include <stdlib.h> //per utilizzare la funzione system();
#include <gotoxy.h> //per utilizzare la funzione gotoxy().

#define MAXSTR 25   /* "Costante" usata per la lunghezza massima
                     * dei vettori di caratteri (delle stringhe). */

//______________________________________________________________________________

// Dichiarazione delle strutture dati:
    typedef struct
    {
        char nome[MAXSTR];    // Per memorizzare il nome di un giocatore;
        char cognome[MAXSTR]; // per memorizzare il cognome di un giocatore;
        char parola[MAXSTR];  // per la parola inserita da un giocatore;
        int punti;        // per memorizzare i punti che totalizza un giocatore;
    }Giocatore;           // Rinominazione della struttura.

//______________________________________________________________________________

// Dichiarazione dei prototipi delle funzioni (definite successivamente):
char menu();
void gestioneScelta(char scelta);
void regole();
void colora();
void vocabolo();
int  getNumGiocatori();
char getNumeroIntero(int i);
void setGiocatori(Giocatore giocatore[], int numGiocatori);
char impostaDifficolta();
void setConsonanti(char consonante[], int nConsPerTurno);
char generaConsonanteCasuale();
int  setParola(char parola[], char consonante[], int nCPT, char *dif);
char getLettera(char consonante[], int nCPT, int controlCons[]);
int  controlTime(char *dif, int timeFinale);
int  calcolaPunti(char parola[], char consonante[], int nCPT);
void vincitore(Giocatore giocatore[], int numGiocatori);
void decoro();

//______________________________________________________________________________

/*
* main()
* funzione principale, che richiama, in una struttura di ripetizione
* pre-condizionale infinita, alcune funzioni dichiarate precedentemente
* come prototipi e successivamente definite.
*
* Valore restituito:
* il valore 0, restituito alla funzione chiamante, ovvero al sistema
* operativo, per indicare che tutte le operazione sono state svolte senza
* errori.
*/
int main()
{
    // Dichiarazione delle variabili:
    /* "scelta", variabile di tipo carattere utilizzata per memorizzare il
     * valore restituito dalla funzione menu(), che rappresenta la
     * scelta fatta ed inserita dall'utente in quella funzione, che verra'
     * poi passata come parametro alla funzione gestioneScelta().         */
    char scelta;
    
    system("color 9");
    
    /* Struttura di ripetizione precondizionale, in questo caso, infinita,
     * utilizzata per far visializzare il menu', della funzione menu(),
     * infinite volte, dopo l'esecuzione di tutte le funzioni chiamate.
     * Di conseguenza la funzione main() non potra' mai essere portata
     * a termine e quindi, non si potra' uscire dal programma, se non
     * con altre funzioni, utilizzate dalle funzioni chiamate...          */
    while(1)
    {
         scelta=menu();
         gestioneScelta(scelta);
	}
    
    return 0;
}

//______________________________________________________________________________

// Implementazione Funzioni Secondarie:

/*
* menu()
* funzione che presenta un menu' di possibili tasti da premere, ognuno
* "associato" ad una possibile attivita' da svolgere col programma.
*
* Valore restituito:
* un carattere, che corrispondera' al tasto digitato dall'utente su tastiera.
*/
char menu()
{
    // Presentazione, su schermo, del menu':
    system("cls");
    printf("\n\n\n\n\n\t\t\t Benvenuto in VOCABOLO!");
    printf("\n\n\n\n\t\t Premere:\n\n\n\t\t - 1, per giocare a VOCABOLO;");
    printf("\n\n\t\t - 2, per conoscere le regole del gioco;");
    printf("\n\n\t\t - 3, per cambiare colore ai caratteri;");
    printf("\n\n\t\t - ESC, per uscire.");
    decoro();
    gotoxy(50,18);
    
    return getch();
}

//______________________________________________________________________________

/*
* decoro()
* funzione che stampa su schermo una cornice di asterischi servendosi della
* funzione gotoxy().
*/
void decoro()
{
    // Dichiarazione delle variabili:
    int i;
    
    // Stampa della cornice di asterischi:
    /* Ricordando che lo schermo e' formato da 25 righe (0-24) e 80
     * colonne (0-79) e che la funzione gotoxy() tratta lo schermo
     * come un sistema di assi cartesiani dove l'asse delle ascisse
     * rappresenta le colonne e l'asse delle ordinate, le righe; la
     * stampa della cornice di * avverrà mediante i seguenti passi: 
         
    /*1 Posizionamento in colonna 1, riga 1;
    /*2 Stampa di * ripetututa su tutta la riga 1 (meno l'ultima colonna);
    /*3 Stampa di * sulle colonne 1 e 78, (meno le prime 2 e le ultime 2 righe);
    /*4 Posizionamento in colonna 1, riga 23;
    /*5 Stampa di * ripetututa su tutta la riga 23 (meno l'ultima colonna);
    
    /*1*/ gotoxy(1,1);
    /*2*/ for(i=0;i<78;i++) printf("*"); //Per i che va dalla colonna 0 alla 77;
    /*3*/ for(i=2;i<23;i++)              //Per i che va dalla riga 1 alla 22;
          {
              gotoxy(1,i); printf("*");
              gotoxy(78,i); printf("*");
          }
    /*4*/ gotoxy(1,23);
    /*5*/ for(i=0;i<78;i++) printf("*"); //Per i che va dalla colonna 0 alla 77;
}

//______________________________________________________________________________

/*
* gestioneScelta()
* funzione che si occupa di gestire la scelta effettuata dall'utente
* nell' esecuzione della funzione menu(), che verra' passata a questa
* funzione come parametro.
*
* Parametri in ingresso:
* un carattere, cioe' un tasto digitato dall'utente.
*/
void gestioneScelta(char scelta)
{
    /* La struttura di scelta multipla e' utilizzata per gestire la scelta
     * dell'utente, ricevuta come parametro, ovvero viene verificato se il
     * valore della variabile scelta, sia uguale ad uno dei tasti proposti
     * nel menu' e, se cio' avviene, viene chiamata l'apposita funzione
     * che soddisfera' la scelta effettuata.                                */
    switch(scelta)
    {
        case '1': vocabolo(); break;
        case '2': regole(); break;
        case '3': colora(); break;
        case 27: exit(1);
    }
}

//______________________________________________________________________________

/*
* regole()
* funzione che presenta le regole del gioco VOCABOLO su schermo.
*/
void regole()
{
    // Stampa, su schermo, delle regole del gioco:
    system("cls");
    printf("\n\n\t Il massimo numeri di giocatori consigliati e' 6!");
    printf("\n\n\t Il gioco si divide in 4 turni, differenti solo nel\n\t ");
    printf("numero di consonanti da estrarre.\n\t ");
    printf("In ogni fase, il sistema estrarra' a caso: 4 consonanti nel \n");
    printf("\t primo turno, 5 nel secondo, 6 nel terzo e 7 nel quarto");
    printf(".\n\t Dopo l'estrazione, utilizzando vocali a piacere, \n\t ");
    printf("bisogna formare una parola utilizzando, anche, almeno una \n\t ");
    printf("delle consonanti proposte dal gioco.\n\t ");
    printf("Attenzione pero': \n\t - ogni consonante puo' essere utilizzata");
    printf("una volta sola.\n\t - la parola deve essere scritta completamente");
    printf("in MAIUSCOLO!!!\n\t Dopo l'inserimento della parola di ogni ");
    printf("giocatore, vengono \n\t assegnati tanti punti, ad ognuno di essi,");
    printf(" quante sono le \n\t lettere della parola del giocatore in ");
    printf("questione.\n\t Inoltre, se sono state utilizzate tutte le ");
    printf("consonanti\n\t proposte dal gioco, per la parola, si aggiungera'");
    printf("un bonus,\n\t al punteggio del giocatore che le ha utilizzate, ");
    printf("pari al\n\t numero di quest'ultime.");
    printf("\n\n\t Premi un tasto per leggere la prossima pagina......");
    getch();
    system("cls");
    printf("\n\n\n\n\n\n\t ESEMPIO: consonanti estratte TRGL:\n\t ");
    printf("Se si forma la parola REGOLA si ottengono sei punti, se si\n\t ");
    printf("formano le parole REGALATO, RITAGLIO o TRILOGIA si prendono\n\t ");
    printf("gli otto punti della parola piu' i quattro di bonus per le \n\t ");
    printf("consonanti usate; se poi si compone GELATERIA si totalizzano\n\t ");
    printf("tredici punti.\n\n\t ");
    printf("Alla fine delle 4 fasi del gioco, vincera'/vinceranno il \n\t ");
    printf("giocatore/i che avra'/avranno totalizzato piu' punti.");
    printf("\n\n\n\n\t Premi un tasto per leggere la prossima pagina......");
    getch();
    system("cls");
    printf("\n\n\n\t DIFFICOLTA':");
    printf("\n\n\t FACILE:    non sono presenti limitazioni di tempo per\n\t ");
    printf("           l'inserimento della parolae se non viene");
    printf("\n\t            utilizzata nemmeno una delle consonanti");
    printf("\n\t            proposte, sara' possibile reinserirla.");
    printf("\n\n\t NORMALE:   2 minuti di tempo per inserire la parola!");
    printf("\n\n\t DIFFICILE: 1 minuto di tempo per inserire la parola!");
    printf("\n\n\t ESTREMA:   15 secondi di tempo per inserire la parola!");
    printf("\n\n\n\t Pertanto, nelle ultime 3 difficolta', verranno ");
    printf("assegnati\n\t 0 punti, se la parola inserita' non conterra' ");
    printf("nemmeno una\n\t delle consonanti proposte, o se non verra' ");
    printf("inserito nulla.");
    printf("\n\n\n\t Premere un tasto per tornare al menu'......");
    getch();
}

//______________________________________________________________________________

/*
* colora()
* funzione che permette all'utente di cambiare colore ai caratteri.
*/
void colora()
{
    // Dichiarazione delle variabili:
    char s[7]="color ";  /* Stringa (vettore di caratteri), da passare come
                          * parametro alla funzione system(), per colorare i
                          * i caratteri dello schermo.                      */
    
    // Colorazione dello sfondo e dei caratteri:
    /* La struttura di ripetizione post-condizionale e' utilizzata per
     * ripetere l'esecuzione del blocco di istruzioni finche' l'utente
     * non digita INVIO.                                                    */
    do
    {
        system("cls");
        printf("\n\n\t Per colorare i caratteri premi:");
        printf("\n\n\n\t\t1 = blu scuro;\n\t\t2 = verde;");
        printf("\n\t\t3 = verde acqua;\n\t\t4 = bordeaux;\n\t\t5 = viola;");
        printf("\n\t\t6 = verde oliva;\n\t\t7 = grigio chiaro;");
        printf("\n\t\t8 = grigio;\n\t\t9 = blu;\n\t\tA = verde limone;");
        printf("\n\t\tB = azzurro;\n\t\tC = rosso;\n\t\tD = fucsia;");
        printf("\n\t\tE = giallo;\n\t\tF = bianco.");
        printf("\n\n\n\t Premere: - INVIO, per tornare al menu',");
        printf("\n\t          - ESC, per uscire......");
        
        /* Inserimento del tasto digitato nella settima variabile di tipo
         * carattere, del vettore s (esempio: si ottiene s="color 8",
         * nel caso in cui l'utente abbia digitato 8):                      */
        s[6]=getch();
        
        if(s[6]==27) exit(1);  // Se l'utente digita 0, si esce dal programma.
        
        /* Controllo sul tasto digitato, per verificare che sia uno dei
         * tasti proposti, per poi passare la stringa s, come parametro,
         * alla funzione system(), nel caso risulti vero il controllo, per
         * cambiare il colore ai caratteri dello schermo (in base alla
         * scelta fatta dall'utente):                                       */
        if((s[6]>='1'&&s[6]<='9')||(s[6]>='A'&&s[6]<='F')
           ||(s[6]>='a'&&s[6]<='f')) system(s);
           
    }while(s[6]!=13);
}

//______________________________________________________________________________

/*
* vocabolo()
* funzione che permette di giocare al gioco VOCABOLO.
*
* Variabili locali di questa funzione:
* 1- un vettore di caratteri per memorizzare le consonanti estratte
*    casualmente;
* 1- 2 variabili di tipo carattere, la prima, per memorizzare il
*    carattere restituito della funzione che si occupa di far
*    inserire all'utente la difficolta' del gioco e restituirla
*    alla funzione chiamante; la seconda serve per creare una copia
*    della precedente variabile, perche' essa verra' passata per
*    indirizzo, a funzioni che ne modificheranno il valore nel caso
*    l'utente violi il tempo concesso dalla modalita' scelta e di
*    conseguenza occorrera' ripristinarne il "vero" valore, mediante
*    questa variabile di copia;
* 3- 2 variabili di tipo intero, utilizzabili come contatori per dei
*    cicli e come indici di vettori;
* 4- una variabile di tipo intero per memorizzare il numero di
*    consonanti per turno;
* 5- una variabile di tipo intero per memorizzare il numero di
*    giocatori (inizializzata con l'apposita funzione);
* 6- un vettore di strutture, per memorizzare i dati di ogni
*    giocatore.
*/
void vocabolo()
{
    // Dichiarazione delle variabili:                                                     */
    /*1*/ char consonante[7];
    /*2*/ char dif, difTemp;
    /*3*/ int i, j;
    /*4*/ int nCPT;
    /*5*/ int numGiocatori=getNumGiocatori();
    /*6*/ Giocatore giocatore[numGiocatori];
    
    // Inserimento del Nome e del Cognome di ogni giocatore:
    setGiocatori(giocatore, numGiocatori);
    
    // Scelta della difficolta:
    dif=impostaDifficolta();
    difTemp=dif;  // copia di dif...
    
    // Esecuzione del gioco:
    /* Il prossimo ciclo utilizzato, serve per ripetere il suo blocco di
     * istruzioni 4 volte (per le 4 fasi del gioco). quindi la condizione
     * sara': "per nCPT che va da 4 a 7" perche' 4 sono le consonanti della
     * prima fase del gioco e 7, le consonanti dell'ultima fase).           */
    for(nCPT=4; nCPT<=7; nCPT++)
    {
        // Estrazione delle nCPT consonanti:
        setConsonanti(consonante, nCPT);
        
        for(i=0; i<numGiocatori; i++) // "Per ogni giocatore":
        {
            // Giocata del giocatore di turno:
            /* Il prossimo ciclo utilizzato non ripete il suo blocco di
             * istruzioni, solo se il giocatore di turno ha inserito una
             * parola che rientra nel regolamento del gioco.                */
            do{
            system("cls");
            printf("\n\n\t Premere ESC in qualsiasi momento per uscire...");
            printf("\n\n\t ATTENZIONE! Ricordiamo che sono ritenute valide ");
            printf("solo\n\t parole scritte completamente in MAIUSCOLO e che ");
            printf("sia-\n\t no formate da vocali e consonanti proposte (non ");
            printf("rip-\n\t etute)! Pertanto, non potranno essere immessi ");
            printf("carat-\n\t teri fuori dal regolamento!!!");
            printf("\n\n\t Turno %d: lettere estratte: ", nCPT-3);
               // Stampa delle consonanti estratte:
               for(j=0; j<nCPT; j++) printf("%c ", consonante[j]);
            printf("\n\n\n\n\t Tocca al giocatore ");
            printf("%d, %s %s:", i+1, giocatore[i].nome, giocatore[i].cognome);
            printf("\n\n\t inserire la parola: ");
            
            // Inserimento e controllo della parola inserita:
            }while(setParola(giocatore[i].parola, consonante, nCPT, &dif));
            
            // Calcolo e dichiarazione del punteggio del giocatore di turno:
            // "Se l'utente ha violato il tempo concesso dalla difficolta'":
            if(dif=='0')
            {
                printf("\n\n\t Il tempo concesso dalla difficolta' scelta, e'");
                printf(" stato superato");
                dif=difTemp;  // Per recuperare il "vero" valore di dif.
            }
            else  // "..altrimenti":
            {
                giocatore[i].punti+=
                calcolaPunti(giocatore[i].parola, consonante, nCPT);
            }
            printf("\n\n\t Punteggio totalizzato = %d", giocatore[i].punti);
            printf("\n\n\t Premere un tasto per continuare......");
            getch();
        }
    }
    
    // Controllo e dichiarazione del/dei giocatore/i vincente/i:
    vincitore(giocatore, numGiocatori);
    printf("\n\n\n\n\n\t Premere un tasto per tornare al menu'......");
    getch();
}

//______________________________________________________________________________

/*
* getNumGiocatori()
* funzione che restituisce il numero di giocatori, alla funzione chiamante,
* numero che viene letto non servendosi di un semplice scanf(), ma attraverso
* un particolare algoritmo che gestisce, in un ciclo, la restituzione di un
* carattere che puo' solo essere o un numero, o DEL, oppure '/0'. L'effetto
* finale sara' una scanf(), che ignora l'inserimento di caratteri non numero,
* non DEL, non ESC, non INVIO, tranne se questo, viene digitato senza aver
* inserito alcuna cifra del numero di giocatori, e anche tutti i caratteri
* numero, se inseriti dopo la seconda cifra (il numero di giocatori non puo'
* quindi essere superiore a 99).
*
* Valore restituito:
* un intero, cioe' il numero di giocatori.
*/
int getNumGiocatori()
{
    // Dichiarazione delle variabili:
    char c[2];  /* Vettore di caratteri, per memorizzare le i caratteri
                 * restituiti dalla funzione getNumeroIntero().             */
    int i=0;    // Indice per il vettore di caratteri;
    int flag;   // Flag, per far continuare o terminare il ciclo utilizzato.
    
    // Acquisizione del numero di giocatori:
    system("cls");
    printf("\n\n\n\t Premere ESC in qualsiasi momento per uscire...");
    printf("\n\n\n\n\t Inserire il numero di giocatori (max consigliati 6): ");
    do
    {
        /* Restituzione, in c[i], di un carattere, che puo' solo essere
         * o un numero, o DEL, oppure '/0':                                 */
        c[i]=getNumeroIntero(i);
        
        // "Se c[i] e' uguale al carattere DEL":
        if(c[i]==8)
        {
            i-=2;  // Per "annullare" l'ultimo ciclo.
            
            /* "Se e' c'è almeno uno cifra da cancellare, allora
             *  viene simulata la pressione del tasto DEL":                 */
            if(i>=-1) printf("\b \b");
        }
        
        /* "Se l'utente ha digitato INVIO senza inserire nemmeno una cifra del
         *  numero di giocatori, allora bisogna annullare l'ultimo ciclo":  */
        if(c[i]=='\0'&&i==0) i-=2;
        
        i++;
        
        /* Se uno dei due if precedenti e' risultato vero, arrivati a
         * questo punto i potrebbe essere minore di 0 e se lo e', lo
         * si riporta a 0:                                                  */
        if(i<=0) i=0;
        
        /* Il ciclo ripete il suo blocco di istruzioni, se l'ultimo
         * carattere inserito non e' INVIO, cioe' se c[i-1]!='\0,           */
    }while(c[i-1]!='\0');
    
    /* Restituzione alla funzione chiamante, del numero di giocatori,
     * se questo e' di una sola cifra:                                      */
    if(i<=2) return c[0]-48;
    
    // Restituzione alla funzione chiamante, del numero di giocatori:
    return (c[0]-48)*10+(c[1]-48);
}

//______________________________________________________________________________

/*
* getNumeroIntero()
* funzione che legge un carattere inserito da tastiera ed utilizza un
* algoritmo che permette di "ignorare" l'inserimento di un carattere
* non numero, non DEL, non INVIO e non ESC. Se quindi il carattere
* inserito e' un numero, viene stampato sullo schermo e restituito alla
* funzione chiamante, se e' INVIO, viene restituito '\0', se e' DEL,
* viene direttamente resituito, se e' ESC, si esce dal programma.
* Nota: viene ignorato anche 0 se inserito come prima cifra.
*
* Parametri in ingresso:
* - un intero che sara' uguale all' indice del vettore di caratteri nel
*   quale verra' restituito il valore di ritorno di questa funzione.
*
* Valore restituito:
* un carattere, che potra' essere o un numero compreso fra 0 e 9 (inclusi),
* o il BACKSPACE, oppure '\0'.
*/
char getNumeroIntero(int i)
{
    // Dichiarazione delle variabili:
    char c;  // Per memorizzare un carattere digitato dall'utente, da tastiera.

    /* L'algoritmo consinte in un struttura di ripetizione post-condizionale
     * che ripete il suo blocco di istruzioni finche' l'utente non preme
     * INVIO. Nel blocco di istruzioni possiamo distingure 4 fasi:
     * 1- chiamata della funzione getch() con restituzione di parametro in c;
     * 2- struttura alternativa che verifica se il carattere inserito e' ESC
     *    e se il controllo risulta vero, si esce dal programma con exit(1);
     * 3- struttura alternativa che controlla se i<2, cioe' controlla l'indice
     *    del ciclo in cui e' stata chiamata questa funzione, perche' se e'
     *    maggiore o uguale a 2, vuol dire che l'utente ha inserito un numero
     *    di due cifre ma non ha ancora premuto INVIO, quindi bisognera'
     *    ignorare l'ulteriore inserimento di numeri e quindi non eseguire le
     *    prossime sottofasi:
     *    3.1- con una struttura alternativa si verifica se il carattere
     *         inserito e' compreso fra 0 e 9 (cioe' se e' un numero).
     *         Se si, si procede con le prossime 2 sottofasi:
     *         3.1.1- con una struttura alternativa si verifica se il carattere
     *                inserito e' 0 e che i==0, cioe' se l'utente ha inserito 0
     *                come prima cifra. Se il controllo risulta vero, basta
     *                ignorare questo ultimo inserimento tramite continue;
     *         3.1.2- si stampa il numero inserito e lo si restituisce alla
     *                funzione chiamante;
     * 4- struttura alternativa che verifica se il carattere inserito dall'
     *    utente e' DEL. Se il controllo risulta vero, lo si restituisce
     *    alla funzione chiamante.
     * Se la struttura di ripetizione, viene terminata, significa che l'utente
     * ha digitato INVIO. Quindi si restituire '\0'.                        */
    do
    {
        //Fase 1:
        c=getch();
        
        //Fase 2:
        if(c==27) exit(1);
        
        //Fase 3:
        if(i<2)
        {
            //Fase 3.1:
            if(c>='0'&&c<='9')
            {
                //Fase 3.1.1:
                if(c=='0'&&i==0) continue;
                //Fase 3.1.2:
                printf("%c", c);
                return c;
            }
        }
        //Fase 4:
        if(c==8) return c;
        
    }while(c!=13);
    
    return '\0';
}

//______________________________________________________________________________

/*
* setGiocatori()
* funzione che si occupa di gestire l'inserimento del nome e del cognome di
* ogni giocatore e di inizializzare a 0 i suoi punti.
*
* Parametri in ingresso:
* - un vettore di strutture (piu' precisamente, il riferimento, ovvero il
*   puntatore, alla prima struttura del vettore);
* - un intero che sara' uguale al numero di consonanti estratte in un turno.
*/
void setGiocatori(Giocatore giocatore[], int numGiocatori)
{
    // Dichiarazione delle variabili:
    int i;  // Come contatore per ciclo for e come indice per il vettore.
    
    // Inserimento del Nome e del Cognome di ogni giocatore:
    for(i=0;i<numGiocatori;i++)    // "Per ogni giocatore":
    {
        system("cls");
        printf("\n\n\n\t Inserire 0 in qualsiasi momento per uscire..... ");
        printf("\n\n\n\n\n\t Giocatore %d:\n\n\n\t Inserisci il Nome: ", i+1);
        scanf("%s", giocatore[i].nome);
        if(giocatore[i].nome[0]=='0') exit(1);
        printf("\n\n\t Inserisci il Cognome: ");
        scanf("%s", giocatore[i].cognome);
        if(giocatore[i].cognome[0]=='0') exit(1);
        giocatore[i].punti=0;  // Inizializzazione dei punti del giocatore.
    }
}

//______________________________________________________________________________

/*
* impostaDifficolta()
* funzione che propone all'utente, a video, 4 differenti difficolta' di
* gioco, "abbinate" ad un tasto richiesto da primere. Una volta che
* utente avrà inserito uno dei tasti proposti, viene restituito il
* corrispondente carattere alla funzione chiamante.
* (Questa funzione permette anche di uscire dal programma premendo ESC).
*
* Valore restituito:
* un carattere, che potra' essere 1, 2, 3 o 4, a seconda della difficolta'
* scelta dall'utente.
*/
char impostaDifficolta()
{
    // Dichiarazione delle variabili:
    char dif; // Per memorizzare il carattere di un tasto digitato dall'utente.
    
    // Scelta della difficolta:
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\t\t Inserire la difficolta' di gioco, premendo:");
        printf("\n\n\n\n\t\t - 1, per giocare in modalita' FACILE;");
        printf("\n\n\t\t - 2, per giocare in modalita' NORMALE;");
        printf("\n\n\t\t - 3, per giocare in modalita' DIFFICILE;");
        printf("\n\n\t\t - 4, per giocare in modalita' ESTREMA;");
        printf("\n\n\t\t - ESC, per uscire;");
        dif=getch();
    }while((dif<'1'&&dif!=27)||dif>'4');   /*"Ripeti se l'utente ha inserito
                                            * un valore non proposto".      */
    if(dif==27) exit(1);  // Si esce dal programma se l'utente ha digitato ESC.
    
    return dif;
}

//______________________________________________________________________________

/*
* setConsonanti()
* funzione che si occupa delle estrazioni delle consonanti di un turno.
*
* Parametri in ingresso:
* - un vettore di caratteri (piu' precisamente, il riferimento, ovvero il
*   puntatore, al primo carattere del vettore);
* - un intero che sara' uguale al numero di consonanti da estrarre in un turno.
*/
void setConsonanti(char consonante[], int nCPT)
{
    // Dichiarazione delle variabili:
    int i, j;       // Come contatori per cicli e come indici di vettori.
    
    // Estrazione delle nCPT consonanti diverse fra loro:
    for(i=0; i<nCPT; i++)
    {
        consonante[i]=generaConsonanteCasuale();
        for(j=0; j<i; j++)
        {
            /* Se la consonante e stata gia' estratta i--, per
             *  "annullare" l'ultima ripetizione del ciclo.     */
            if(consonante[i]==consonante[j])
            {
                i--;
                break;
            }    
        }
    }
}

//______________________________________________________________________________

/*
* generaConsonanteCasuale()
* funzione che genera una consonante maiuscola in modo casuale e la
* restituisce alla funzione chiamante.
*
* Valore restituito:
* un carattere, cioe' la consonante generata casualmente.
*/
char generaConsonanteCasuale()
{
    // Dichiarazione delle variabili:
    char c;    // Per memorizzare la consonante maiuscola, generata casualmente.
    int flag=1;// Flag utilizzato per far continuare o terminare il ciclo while.
    
    // Generazione consonante maiuscola casuale:
        while(flag)
        {
            // Generazione di una lettera maiuscola casuale:
            c=66+(rand()+time(NULL))%25;
            
            /* Istruzioni per far ripetere la generazione della lettera
             * maiuscola, finche' non viene estratta una consonante
             * maiuscola diversa da J, K, W, X e Y:                         */
             flag=0;
             switch(c)
             {
                 case 'E': flag=1; break;
                 case 'I': flag=1; break;
                 case 'O': flag=1; break;
                 case 'U': flag=1; break;
                 case 'J': flag=1; break;
                 case 'K': flag=1; break;
                 case 'W': flag=1; break;
                 case 'X': flag=1; break;
                 case 'Y': flag=1; break;
             }
        }
    
    return c;
}

//______________________________________________________________________________

/*
* setParola()
* funzione che si occupa di far inserire una parola, nel modo previsto
* dal regolamento e dalla difficolta' del gioco (i caratteri non ammessi
* non potranno essere inseriti, le consonanti proposte non potranno essere
* ripetute e deve essere rispettato il tempo previsto dalla difficolta'
* di gioco scelta per non ricevere 0 punti).
*
* Parametri in ingresso:
* - due vettori di caratteri (piu' precisamente, i riferimenti, ovvero i
*   puntatori, ai primi caratteri dei vettori);
* - un vettore di interi (piu' precisamente, il riferimento, ovvero il
*   puntatore, al primo intero del vettore);
* - un intero che sara' uguale al numero di consonanti estratte in un turno;
* - una variabile puntatore di tipo char, che punta alla "vera" variabile,
*   dichiarata, nella funzione vocabolo.
*
* Valore restituito:
* - 0, se l'utente ha inserito la parola nel modo previsto dal regolamento del
*      gioco, oppure se ha oltrepassato il limite di tempo, oppure se non ha
*      utilizzato nemmeno una delle consonanti proposte (in difficolta' non
*      facile);
* - 1, se non ha utilizzato nemmeno una delle consonanti proposte
*      (in modalita' facile), per far ripetere l'inserimento.
*/
int setParola(char parola[], char consonante[], int nCPT, char *dif)
{
    // Dichiarazione delle variabili:
    int i=0, j;  // Come contatori e come indici di vettori.
    int flag=0;  // Flag utilizzato come predicato di struttura alternativa.
    int controlCons[nCPT];
    for(j=0; j<nCPT; j++) controlCons[j]=0;  // Inizializzazione...
    /* controlCons e' un vettore di nCPT interi (uno per ogni consonante),
     * che serve per tenere conto di quante volte e' stata inserita una
     * consonante proposta, nella parola.                                   */
    int tempoIniziale=time(NULL), tempoImpiegato;
    /* ...per memorizzare rispettivamente il tempo (in secondi) di
     * inizio inserimento parola, ed il tempo impiegato per inserirla.      */
    

    // Inserimento e controllo della parola inserita:
    do
    {
        /* Restituzione, in parola[i], di un carattere, che puo' solo
         * essere: o una vocala, o una consonante non ancora inserita,
         * o DEL, oppure '/0':                                              */
        parola[i]=getLettera(consonante,nCPT,controlCons);
        
        // "Se parola[i] e' uguale al carattere DEL":
        if(parola[i]==8)
        {
            /* Per ogni consonante estratta, controllo se il carattere che
             * l'utente vuole cancellare, e' appunto una consonante, e se
             * lo e', decremento il corrispettivo contatore della consonante
             * e se in questo modo e sceso sotto lo 0, lo riporto a 0:      */
            for(j=0; j<nCPT; j++)
            {
                if(parola[i-1]==consonante[j])
                {
                    controlCons[j]--;
                    if(controlCons[j]<0) controlCons[j]=0;
                }
            }
            i-=2;  // Per "annullare" l'ultimo ciclo.
            
            /* "Se e' c'è almeno uno cifra da cancellare, allora
             *  viene simulata la pressione del tasto DEL":                 */
            if(i>=-1) printf("\b \b");
        }
        
        i++;
        
        /* Se il precedente if e' risultato vero, i potrebbe essere
         * minore di 0 e se lo e', lo si riporta a 0:                       */
        if(i<=0) i=0;
        
        /* Il ciclo ripete il suo blocco di istruzioni, se l'ultimo
         * carattere inserito non e' INVIO, cioe' se c[i-1]!='\0,           */
    }while(parola[i-1]!='\0');
    
    // "Se l'utente ha scelto di giocare in una modalita non facile":
    if(*dif>'1')
    {
        // Calcolo del tempo impegato per l'inserimento della parola:
        tempoImpiegato=time(NULL)-tempoIniziale;
        // Controllo del tempo impiegato:
        // "Se l'utente ha impegato piu' tempo del concesso":
        if(controlTime(dif, tempoImpiegato)) return 0;
    }
    
    // "Per ogni carattere del vettore parola":
    for(i=0; i<strlen(parola); i++)
    {
        // "Per ogni consonante estratta in una fase del gioco":
        for(j=0; j<nCPT; j++)
        {
            // "Se il carattere del vettore parola e' una consonante estratta":
            if(parola[i]==consonante[j])
            {
                flag=1;            // per il prossimo if...
                j=nCPT;            // break;
                i=strlen(parola);  // break sul primo ciclo for.
            }    
        }
    }
    // ..."Se la parola non contiene nemmeno una delle consonanti estratte":
    if(!flag)
    {
        printf("\n\n\t Non hai utillizzato nemmeno una delle consenanti");
        printf("\n\t proposte!!!");
        if(*dif=='1')  // Per la difficolta' facile:
        {
            printf("\n\n\t Premere un tasto per reinserire la parola...");
            getch();
            return 1;
        }
        // Per le altre difficolta':
        else return 0;
    }
    
    return 0;
}

//______________________________________________________________________________

/*
* getLettera()
* La parola inserita dal giocatore, non viene letta tramite scanf(), ma
* carattere dopo carattere, attraverso questa funzione, che ignorera' i
* caratteri non lettera e le consonanti gia' inserite una volta.
* Inoltre, come nella scanf(), sara' possibile utilizzare il tasto DEL
* e, l'inserimento parola, viene terminato premendo INVIO.
* Nota: sara' possibile uscire dal programma in qualsiasi momento,
* premendo ESC.
*
* Parametri in ingresso:
* - un vettore di caratteri (piu' precisamente, il riferimento, ovvero il
*   puntatore, al primo carattere del vettore);
* - un intero che sara' uguale al numero di consonanti estratte in un turno;
* - un vettore di interi (piu' precisamente, il riferimento, ovvero il
*   puntatore, al primo intero del vettore);
*
* Valore restituito:
* un carattere inserito dall'utente oppure '\0', se l'utente digita INVIO.
*/
char getLettera(char consonante[], int nCPT, int controlCons[])
{
    // Dichiarazione delle variabili:
    int i;   // Come contatatore e come indici di vettore.
    char c;  // Per memorizzare un carattere inserito dall'utente.
    
    // Inserimento e controllo del carattere:
    do  //"Esegui...":
    {
        c=getch();
        if(c==27) exit(1); //"Se e' stato digitato ESC, uscita dal programma".
        /* "Se il carattere inserito e' una vocale, stampala
         *  e restituiscila alla funzione chiamante":         */
        if(c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
        {
            printf("%c", c);
            return c;
        }
        // "Per ogni consonante estratta":
        for(i=0; i<nCPT; i++)
        {
            /* "Se il carattere inserito e' uguale ad una consonante estratta,
             *  allora stampala, incrementa controlCons[i] e restituiscila
             *  alla funzione chiamante":                                   */
            if((c==consonante[i])&&(controlCons[i]<1))
            {
                printf("%c", c);
                controlCons[i]++;
                return c;
            }
        }
        //"Se e' stato digitato DEL, si restituisce c alla funzione chiamante":
        if(c==8) return c;
    }while(c!=13);  //"... e ripeti finche' l'utente non preme INVIO".
    
    /* Se si e' usciti dal precedente ciclo, sara' perche' l'utente avra'
     * digitato INVIO. Quindi si restituisce '\0' alla funzione chiamante:  */
    return '\0';
}

//______________________________________________________________________________

/*
* controlTime()
* funzione che controlla il tempo impegato dall'utente ad inserire la parola,
* e restituisce il valore descritto successivamente.
*
* Parametri in ingresso:
* - una variabile puntatore di tipo char, che punta alla "vera" variabile,
*   dichiarata, nella funzione vocabolo;
* - una variabile di tipo intero, cioè il tempo impegato dall'utente
*   (in secondi), ad inserire la parola.
*
* Valore restituito:
* un intero, 1 se l'utente ha inserito la parola nel tempo concesso, 0 se no.
*/
int controlTime(char *dif, int tempoImpiegato)
{
    switch(*dif)
    {
        case '2':
            if(tempoImpiegato>120)
            {
                *dif='0'; /* Serve per non far calcolare il punteggio della
                           * parola nella funzione vocabolo(), ed assegnare
                           * 0 punti.                                       */
                return 1;
            }
        case '3':
            if(tempoImpiegato>60)
            {
                *dif='0';
                return 1;
            }
        case '4':
            if(tempoImpiegato>15)
            {
                *dif='0';
                return 1;
            }
    }
    
    return 0;
}

//______________________________________________________________________________

/*
* calcolaPunti()
* questa funzione calcola i punti totalizzati da un giocatore, in un turno.
*
* Parametri in ingresso:
* - due vettori di caratteri (piu' precisamente, i riferimenti, ovvero i
*   puntatori, ai primi caratteri dei vettori);
* - un intero che sara' uguale al numero di consonanti estratte in un turno.
*/
int calcolaPunti(char parola[], char consonante[], int nCPT)
{
    // Dichiarazione delle variabili:
    int i, j;  // Come contatori e come indici di vettori.
    int p=0;   // Per memorizzare i punti totalizzati dall'utente.
    
    // Calcolo del punteggio del giocatore:
    for(i=0; i<strlen(parola); i++)  //"Per ogni carattere del vettore parola":
    {
        // Verifico se quel carattere e' una consonante estratta...
        for(j=0; j<nCPT; j++)
        {
            if(parola[i]==consonante[j]) p++; //...se si, incremento p di 1.
        }
    }
    if(p>0) //"Se e' stata trovata almeno una consonante estratta nella parola":
    {
        if(p==nCPT)  //"Se sono state utilizzate tutte le consonanti estratte":
        {
            /* si aggiunge il bonus di punti uguale al numero di consonanti,
             * cioe' p = numero di consonanti + lunghezza della parola :    */
            p=nCPT+strlen(parola);
        }
        else p=strlen(parola);  // altrimenti p = lunghezza della parola.
    }
    
    return p;
}

//______________________________________________________________________________

/*
* vincitore()
* funzione che si occupa della ricerca e della dichiarazione del vincitore.
*
* Parametri in ingresso:
* - un vettore di strutture (piu' precisamente, il riferimento, ovvero il
*   puntatore, alla prima struttura del vettore);
* - un intero che sara' uguale al numero di giocatori.
*/
void vincitore(Giocatore giocatore[], int numGiocatori)
{
    // Dichiarazione delle variabili:
    int i;    // Come contatore per i cicli for e come indice di vettore;
    int p;    // Per memorizzare un punteggio di un giocatore;
    int c=0;  // Per contare i giocatori con il punteggio piu' alto.
    
    // Controllo e dichiarazione del/dei giocatore/i vincente/i:
    /* Fasi dell'algoritmo:
     * 1- Si "pulisce" lo schermo e si stampa "Il vincitore e':";
     * 2- Si crea una copia del punteggio del primo giocatore (il primo
     *    elemento del vettore di struct), e la si confronta con i punteggi
     *    di tutti gli altri giocatori, per trovare il punteggio piu' alto,
     *    da memorizzare nella variabile p.
     * 3- Si controlla, in un ciclo, quale è il giocatore con il punteggio
     *    piu' alto (ce ne puo' essere piu' di uno), e ad ogni controllo che
     *    risulta positivo, si incrementa di 1 la variabile c, e si stampa su
     *    schermo il suo nome ed il suo cognome. Successivamente, sempre nel
     *    ciclo, si controlla se c e' uguale a 2, cioe' se ci sono piu'
     *    giocatori vincenti e se ci sono, si  "pulisce" ancora lo schermo,
     *    si stampa "I vincitori sono:", poi si incrementa c e si fa
     *    ricominciare il ciclo dall'inizio da i=0 (ponendo i uguale a -1)  */
    // Fase 1:
    system("cls");
    printf("\n\n\n\n\t Il vincitore e':\n\n\n");
    // Fase 2:
    p=giocatore[0].punti;
    for(i=1; i<numGiocatori; i++)  // "Per ogni giocatore eccetto il primo":
    {
        if(p<giocatore[i].punti)
        {
            p=giocatore[i].punti;
        }    
    }
    // Fase 3:
    for(i=0; i<numGiocatori; i++)  // "Per ogni giocatore":
    {
        if(p==giocatore[i].punti)
        {
            c++;
            printf("\n\n\t\t%s %s!!!", giocatore[i].nome, giocatore[i].cognome);
        }
        if(c==2)
        {
            system("cls");
            printf("\n\n\n\n\t I vincitori sono:\n\n\n");
            c++;
            i=-1;
        }
    }
}

