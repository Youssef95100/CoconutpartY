CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = main.o terrain.o crabe.o sauvgarde.o

exec: $(OBJ)
	$(CC) $(CFLAGS) -o exec $(OBJ)

main.o: main.c sauvegarde.h
	$(CC) $(CFLAGS) -c main.c

terrain.o: terrain.c terrain.h
	$(CC) $(CFLAGS) -c terrain.c

crabe.o: crabe.c crabe.h
	$(CC) $(CFLAGS) -c crabe.c

sauvgarde.o: sauvgarde.c sauvegarde.h
	$(CC) $(CFLAGS) -c sauvgarde.c

clean:
	rm -f *.o exec

