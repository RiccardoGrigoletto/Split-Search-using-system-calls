#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define SIGKILL 9


typedef int bool;
#define TRUE 1
#define FALSE 0


//viene eseguito se c'è errore da riga di comando
void commanderror() {
    printf("Errore da riga di comando\n");
    exit(0);
}

int main(int argc, char** argv)
{

    //opzione -m
    int nValoriDaRestituire=INT_MAX;

    //j contatore di argomenti da linea di comando
    int j=1;

    char *fileInput = NULL;
    char *fileOutput= NULL;
    char *valoreDaCercare=NULL;
    bool mostraAzioni=FALSE;

    //inizializzazione argomenti da linea di comando
    //v_i_o, m, a sono funzioni della libreria markup.c
    while(j<argc)
    {
        if(strcmp(argv[j],"-v")==0)
        {
            if(v_i('v',j,&valoreDaCercare,argv,argc)==FALSE)
            {
                commanderror();
            }
        }
        if(strcmp(argv[j],"-i")==0)
        {
            if(v_i('i',j,&fileInput,argv,argc)==FALSE)
            {
                commanderror();
            }

        }
        if(strcmp(argv[j],"-o")==0)
        {
            if(o('o',j,&fileOutput,argv,argc)==FALSE)
            {
                commanderror();
            }

        }

        if(strcmp(argv[j],"-m")==0)
        {
            if (m(j,&nValoriDaRestituire,argv,argc)==FALSE)
            {
                commanderror();
            }
        }

        if(strcmp(argv[j],"-a")==0)
        {
            if (a(&mostraAzioni)==FALSE)
            {
                commanderror();
            }
        }
        j++;
    }

    //check_obb_marks() è una funzioone della libreria markup.c
    //se i marcatori obbligatori non sono presenti check_obb_marks ritorn FALSE
    if(check_obb_marks()==FALSE)
    {
        printf("\nErrore nella richiesta! Mancano dei dati essenziali per l'esecuzione del programma!\n\n");
        exit(1);
    }

    //open del file di input
    int fd;
    if ((fd=open(fileInput, O_RDONLY))==-1)
    {
        perror("fileInput");
        exit(2);
    }
    //il file di input diventa lo stdin
    dup2(fd,0);

    //getrows(int) conta le righe del file in fd
    int rows=getrows(fileInput);

    //! dichiarazione array, il numero di caratteri per riga è massimo 100
    char data[rows][100];

    //inizializzazioe array
    int counter=0;
    while(scanf("%s",data[counter])!=EOF)
    {
        counter++;
    }
    close(fd);

    int fda;
    if((fda=open("fa.txt", O_CREAT | O_RDWR))==-1) {
        printf("errore creazione file di supporto\n");
        exit(0);
    }

    //apertura file output
    int fdo;
    if((fdo = open(fileOutput, O_WRONLY | O_TRUNC))==-1)
    {
        //se il marcatore -o è presente ma il file indicato non esiste viene creato un file
        //con nome output.txt
        if (get_o()==TRUE) {
            fdo=open("output.txt", O_CREAT | O_WRONLY | O_TRUNC );
            chmod("output.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        }
        //se -o non è presente
        else {
            printf("file di output selezionato non esistente, risultato su stdin\n");
            fdo=-1;
        }
    }
    //il file output indicato esiste ed è stato aperto in output
    else
    {
        chmod(fileOutput,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    }

    //indici per albero
    int inizio=0,fine=rows;
    //profondità albero
    int deep=0;
    //controllore while
    int flag=1;

    int pid1=0;


    //ciclo albero
    while(flag)
    {

        pid1=fork();
        deep++;

        //opzione -m
        setgid(0);

        //errore nella fork, ricerca diretta tramite funzione search
        if (pid1<0)
        {
            //lettura file appoggio
            	//opzione -a
            if (mostraAzioni==TRUE) {
                printf("fork exception, ricerca diretta senza annotazioni\n");
                usleep(500000);
            }
            char buf[sizeof(int)];
            lseek(fda,0,SEEK_SET);
            int n = read(fda,buf,sizeof(int));

            //ricerca diretta
            search(data,rows,valoreDaCercare,inizio,nValoriDaRestituire,fdo,atoi(buf));

            flag=0;
        }

        //figlio (ramo sinistro)
        if (pid1==0)
        {
            fine=((inizio+fine)/2);

            //opzione -a
            if (mostraAzioni==TRUE) {
                usleep(500000);
                printf("figlio: %d , %d. deep:%d\n", inizio+1, fine+1, deep);
            }

        }
        //padre (ramo destro)
        else if(pid1>0)
        {
            //in attesa che il figlio finisca
            wait();

            inizio=((inizio+fine)/2)+1;

            //opzione -a
            if (mostraAzioni==TRUE) {
                usleep(500000);
                printf("padre: %d , %d. deep:%d\n",inizio+1,fine+1,deep);
            }
        }

        //ramo foglia
        if (inizio>=fine) {

            //stop fork
            flag=0;

            //match (inizio)-esimo elemento e stringa da cercare
            if(strcmp(data[inizio],valoreDaCercare)==0)
            {
                //opzione -a
                if (mostraAzioni==TRUE) {
                    usleep(500000);
                    printf("valore trovato in posizione: ");
                    //stampa riga di match
                    printf("%d\n",inizio+1);
                }

                //opzione -o
                if (fdo>=0) {
                    char* array = malloc(sizeof(int));
                    lseek(fdo,0,SEEK_END);
                    int n = sprintf(array,"%d\n",inizio+1);
                    write(fdo,array,n);
                }
                else {
                    //stampa riga di match
                    printf("%d\n",inizio+1);
                }

                //lettura file appoggio
                char buf[sizeof(int)];
                lseek(fda,0,SEEK_SET);
                int n = read(fda,buf,sizeof(int));

                //incremento numero valori trovati
                int val = atoi(buf)+1;

                //opzione -m
                if (val>=nValoriDaRestituire) {
                    killpg(0,SIGKILL);
                    exit(1);
                }

                //scrittura file appoggio
                char buf2[sizeof(int)];
                sprintf(buf2,"%d",val);
                lseek(fda,0,SEEK_SET);
                write(fda,buf2,sizeof(buf2));

            }

            //se siamo nell'ultima riga e non sono stati trovati output
            //stampiamo/scriviamo 0
            else if(inizio>=rows) {
                char buf[sizeof(int)];
                lseek(fda,0,SEEK_SET);
                int n = read(fda,buf,sizeof(int));
                if (atoi(buf)<=0) {
                    if (fdo>=0) {
                        char* array = malloc(sizeof(int));
                        int n = sprintf(array,"0");
                        write(fdo,array,n);
                    }
                    else {
                        if (mostraAzioni==TRUE) {
                            usleep(500000);
                            printf("nessun valore trovato\n");
                        }
                        else {
                            printf("0\n");
                        }
                    }
                }

            }
        }

    }

    //rimuovi file appoggio
    remove("fa.txt");

    //chiudo file descriptor
    close(fda);
    close(fdo);
    return 0;
}
