# Jiashu Yang jyang166
# Katelyn Surrao ksurrao1
# Ai Omae aomae1
# Midterm Project - Solution Makefile

CC=gcc
CFLAGS= -g -std=c99 -pedantic -Wall -Wextra

project: project.o ppm_io.o img_processing.o
	$(CC) -o project project.o ppm_io.o img_processing.o
project.o: project.c ppm_io.h img_processing.h
	$(CC) $(CFLAGS) -c project.c
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c
img_processing.o: img_processing.c img_processing.h ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c img_processing.c 
clean:
	rm -f *.o project
