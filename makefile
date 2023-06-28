VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

all: clean valgrind-ejemplo valgrind-chanutron valgrind-alumno

valgrind-chanutron: pruebas_chanutron
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron

pruebas_chanutron: src/*.o pruebas_chanutron.o
	$(CC) $(CFLAGS) src/*.o pruebas_chanutron.o -o pruebas_chanutron


valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.o pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.o pruebas_alumno.c -o pruebas_alumno

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

ejemplo: src/*.o ejemplo.c
	$(CC) $(CFLAGS) src/*.o ejemplo.c -o ejemplo

clean:
	rm -f pruebas_chanutron pruebas_chanutron ejemplo
