CC = gcc
CFLAGS = -g -O3 -I../include -I../private
OBJ = insert-sort.o quick-sort.o merge-sort.o
OPT ?= RANDOM
OPT = SEPERATE

all:
	$(CC) $(CFLAGS) -c insert-sort.c
	$(CC) $(CFLAGS) -c quick-sort.c
	$(CC) $(CFLAGS) -c merge-sort.c
	$(CC) $(CFLAGS) -D$(OPT) $(OBJ) timer.c -o timer

plotall: all
	for i in `seq 1 100 3001`; do \
		printf "%d " $$i; \
		./timer $$i all; \
		printf "\n"; \
	done > input.txt
	gnuplot -e "INFILE = 'input.txt'; \
				OUTFILE = 'output.png'; \
				NAME1 = 'insert'; \
				NAME2 = 'quick'; \
				NAME3 = 'merge'" ./drawer.gp

plotiq: all
	for i in `seq 1 100 3001`; do \
		printf "%d " $$i; \
		./timer $$i iq; \
		printf "\n"; \
	done > input.txt
	gnuplot -e "INFILE = 'input.txt'; \
				OUTFILE = 'output.png'; \
				NAME1 = 'insert'; \
				NAME2 = 'quick'" ./drawer.gp

plotim: all
	for i in `seq 1 100 3001`; do \
		printf "%d " $$i; \
		./timer $$i im; \
		printf "\n"; \
	done > input.txt
	gnuplot -e "INFILE = 'input.txt'; \
				OUTFILE = 'output.png'; \
				NAME1 = 'insert'; \
				NAME2 = 'merge'" ./drawer.gp

plotmq: all
	for i in `seq 1 100 3001`; do \
		printf "%d " $$i; \
		./timer $$i mq; \
		printf "\n"; \
	done > input.txt
	gnuplot -e "INFILE = 'input.txt'; \
				OUTFILE = 'output.png'; \
				NAME1 = 'merge'; \
				NAME2 = 'quick'" ./drawer.gp

clean:
	rm *.o *.png *.txt timer
