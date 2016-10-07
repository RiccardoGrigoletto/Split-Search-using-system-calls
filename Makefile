#variabili
CC = gcc
CFLAGS = -o
NAME = splitsearch.out
#default
default: help
#regole
help:
	@echo "1- Opzioni disponibili per il comando make: "
	@echo "      1.1- compile : permette la sola compilazione dei sorgenti e crea il file eseguibile nella cartella apposita "
	@echo "      1.2- clean : ripulisce la gerarchia delle cartelle da vari file di supporto ed eseguibili precedentemente creati ed elimina anche tutti i possibili file .txt che si trovano nelle cartelle build e src "
	@echo "      1.3- build : richiama le opzioni 1.2 e 1.1 in questo preciso ordine "
	@echo "      1.4- test : richiama l'opzione 1.3 ed esegue l'eseguibile con i file di supporto che abbiamo nella cartella apposita stampando a video i risultati specificando per ogni case test il suo risultato"
	@echo "      1.5- help : opzione di default, stampa le opzioni disponibili per il comando make e le opzioni disponibili per l'eseguibile "
	@echo "2- Opzioni per L'eseguibile: "
	@echo "      2.1- Marcatori: "
	@echo "              2.1.1. -i per identificare file per input dati "
	@echo "              2.1.2. -v per identificare il dato da cercare "
	@echo "              2.1.3. -o per identificare un file di output su cui avverra la stampa dei soli risultati "
	@echo "              2.1.4. -a per chiedere al programma di mostrare a video i processi in esecuzione e i dati che stanno elaborando "
	@echo "              2.1.5. -m per limitare gli output ad un valore e stoppare tutti gli altri processi "
	@echo "      2.2- Precisazioni: "
	@echo "              2.2.1. sono obbligatori il file di input ed il valore da cercare, si causa altrimenti lo stop del programma "
	@echo "              2.2.2. in caso di utilizzo del marcatore -o scorretto si possono avere uno o piu' casi di terminazione o continuazione del programma con precisazioni durante l'esecuzione di questo "

compile:
	@cd build;\
	$(CC) $(CFLAGS) $(NAME) ../src/main.c ../src/lib/search.c ../src/lib/getrows.c ../src/lib/markup.c

clean:
	@rm -f *.o *~ *.out;\
	rm -f src/*.o src/*~ src/*.out src/*.txt;\
	rm -f build/*.o build/*~ build/*.out build/*.txt;\
	rm -f src/lib/*.o src/lib/*~ src/lib/*.out

build: clean compile

#aggiungere file da annettere che sono in assets
test: build
	@echo "case test 1 -> (7,19,22,27)";
	./build/$(NAME) -i assets/test1.txt -v 6
	@echo "case test 2 -> (22,40,42)";
	./build/$(NAME) -i assets/test2.txt -v dell
	@echo "case test 3 -> (21,44,67,90,113,136)";
	./build/$(NAME) -i assets/test3.txt -v 12.0
	@echo "case test 4 -> (61,62)";
	./build/$(NAME) -i assets/test4.txt -v ciao
	@echo "case test 5 -> (0)";
	./build/$(NAME) -i assets/test5.txt -v 1
	@echo "case test 6 -> (21,44,67)";
	./build/$(NAME) -i assets/test6.txt -v 12.0 -m 3

