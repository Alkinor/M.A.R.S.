CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99
LDFLAGS=
LIBS= -lSDL2main -lSDL2 -lm
EXEC = OCR

all: $(EXEC)

OCR: SDL_content.o binarize.o pixel_access.o matrix_content.o segmentation.o main.o
	$(CC) -o OCR SDL_content.o binarize.o pixel_access.o segmentation.o matrix_content.o main.o $(LDFLAGS) $(LIBS)

SDL_content.o: SDL_content.c
	$(CC) -o SDL_content.o -c SDL_content.c $(CFLAGS) $(LIBS)

pixel_access.o: pixel_access.c
	$(CC) -o pixel_access.o -c pixel_access.c $(CFLAGS) $(LIBS)

matrix_content.o: matrix_content.c
	$(CC) -o matrix_content.o -c matrix_content.c $(CFLAGS) $(LIBS)

binarize.o: binarize.c
	$(CC) -o binarize.o -c binarize.c $(CFLAGS) $(LIBS)

segmentation.o: segmentation.c
	$(CC) -o segmentation.o -c segmentation.c $(CFLAGS) $(LIBS)

main.o: main.c SDL_content.h binarize.h pixel_access.h segmentation.h matrix_content.h
	$(CC) -o main.o -c main.c $(CFLAGS) $(LIBS)

.PHONY: clean clean~ mrproper

clean:
	${RM} *.o

clean~:
	${RM} *.[hc]~

mrproper: cleanrm -rf $(EXEC)
