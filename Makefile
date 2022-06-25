OBJ=ui.o gui.o game.o objects.o human.o AI.o main.o gui_game.o gui_menu.o
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
PROG=sfml-app
CXX=g++

all: $(OBJ)
	@ $(CXX) $(OBJ) -o $(PROG) $(LIBS)

#all: $(PROG)
#
#$(PROG):$(OBJ)
#	g++ $(OBJ) -o $(PROG) $(LIBS)

#main.o: main.cpp
#	g++ -c main.cpp
#
#AI.o: AI.cpp
#	g++ -c AI.cpp
#
#human.o: human.cpp
#	g++ -c human.cpp
#
#objects.o: objects.cpp
#	g++ -c objects.cpp
#
#game.o: game.cpp
#	g++ -c game.cpp
#
#gui.o: gui.cpp gui_game.cpp gui_menu.cpp
#	g++ -c gui.cpp gui_game.cpp gui_menu.cpp
#
#gui_game.o: gui_game.cpp
#
#
#ui.o: ui.cpp
#	g++ -c ui.cpp

.cpp.o:
	@ $(CXX) -c $*.cpp

clean:
	rm *.o $(OBJ) $(PROG)