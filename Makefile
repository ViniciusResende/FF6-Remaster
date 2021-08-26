LIBS=`pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5` -lm

INCLUDES=-I/usr/include/allegro5/

all: FF6 

FF6: FF6.o
	gcc -o FF6 FF6.o $(LIBS)

FF6.o: FF6.c
	gcc  -c FF6.c $(LIBS)


clean:
	rm -f FF6.o
	rm -f FF6
