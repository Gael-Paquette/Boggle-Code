CC=gcc
CFLAGS=-ansi -pedantic -Wall -g
LDFLAGS=-lncurses -lm
SRC=./src/
INC=-I./include
OBJ=Main.o Lettre.o Mot.o Jeu.o Graphique.o

boggle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: $(SRC)%.c
	$(CC) $(INC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o 

mrproper: clean
	rm -f boggle