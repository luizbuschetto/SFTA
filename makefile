CC = g++

all: all_files

all_files: main.cpp otsurec.cpp sfta.cpp findBorders.cpp
	$(CC) `pkg-config --cflags opencv` main.cpp otsurec.cpp sfta.cpp findBorders.cpp -o sfta `pkg-config --libs opencv`

clean:
	rm -f sfta
