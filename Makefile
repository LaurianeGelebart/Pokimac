default : main

CC=g++
OFLAGS= $(CCFLAGS) -MMD
SRC = main.cpp Accueil.cpp affichageTerrain.cpp afficheASCII.cpp combat.cpp Defaite.cpp deplacement.cpp menuDebut.cpp Victoire.cpp

main : $(SRC:%.cpp=%.o)
	$(CC) $^ -o $@

main.o : main.cpp
	$(CC) $(OFLAGS) -c $<

%.o : %.cpp %.h
	$(CC) $(OFLAGS) -c $<

clean :
	del *.o
	del *.d

-include $(SRC:%.cpp=%.d)
