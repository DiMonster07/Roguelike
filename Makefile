CC = g++

SOURCES = main.cpp map.cpp units.cpp gamemanager.cpp
EXECUTABLE = main
OBJECTS = $(SOURCES: .cpp = .o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lpanel -lncurses
del:
	rm -f &(EXECUTABLE) *.o 