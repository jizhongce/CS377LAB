CC = gcc
CFLAG = -std=c99

part1: part1.c
		$(CC) $(CFLAG) part1.c -o part1

part2: part2.c
		$(CC) part2.c -o part2

part3: part3.c
		$(CC) part3.c -o part3
