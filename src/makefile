all:
	gcc -g3 -Wall -o main *.c -lncurses

test:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./main > valgrind.out