target main:
	gcc $(shell pkg-config --cflags gtk4) -o Rezeptapp main.c $(shell mysql_config --libs) $(shell pkg-config --libs gtk4);