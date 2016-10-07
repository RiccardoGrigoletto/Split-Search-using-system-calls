Progetto Sisitemi Operativi 2016

Il progetto è composto da un makefile, il comando help mostra a
video tutte le funzionalità del make, del programma e i marcatori disponibili.
Inoltre sono presenti altre 3 cartelle: assets che contiene i file per i
test di input, build contiene l'eseguibile e la cartella src i file sorgenti del programma
compreso di librerie e  main.c.
(librerie a scopo didattico di supporto per rendere il codice all'interno del main più mantenibile e leggibile)
Il main.c è il file che contiene la funzione main.
Nella parte iniziale del programma si risolve il problema della rilevazione di
eventuali errori dei marcatori e vengono definite le funzionalità decise dall'utente.
Una volta fatto questo, vengono prelevati i dati dal file di input (si noti che il file di input non può contenere più di 100 caratteri per riga)
e in base al risultato del marcatore -o si definisce l'output.
Una volta prelevati tutti i dati dal file di input,vengono salvati in una matrice (righe*100) e
si passa alla splitsearch. Facendo delle fork e 2 indici viene composto
l'albero dei  processi. Raggiunte le foglie dell'albero si controlla se la riga i-esima è uguale alla stringa che stiamo cercando (Il programma può essere
utilizzato per cercare qualsiasi tipo di dato basta ricordare che la ricerca è effettuata con stringhe, ad esempio 3.0 e 3 non risulteranno uguali)
il programma si preoccupa di processare il risultato nell'output definito dall'utente.
Una volta terminata la splitsearch, i file di output e di appoggio vengono chiusi così come i file descriptor e il programma termina.

Migliorie:
gestire gli argomenti con marcatori evitando di usare la posizione
come filtro, gestire dati numerici non interi, gestire dati di tipo stringa,
mostrare il processo delle azioni, gestire impossibilità di creare nuovi processi
e gestire il limite di risultati fermando tutti gli altri processi.

Autori:
Roberti Marco N°173834, Grigoletto Riccardo N°174168,Gilberti Nicola N°170676
