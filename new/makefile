CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
LIBS=-lMLV
CFLAGS= -Wall -std=c17 -pedantic -g -g3

EXEC=minesweeper

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

# On récupère tous les fichiers sources .c, et on leurs préfixe
# le chemin de build, et suffixe en .o :
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
#$(info $(OBJS))

all: $(EXEC)

# Assemblage de l'exécutable final
$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Dépendances
main.o: main.c game.h graph.h init.h interaction.h struct.h tool.h
game.o: struct.h game.h
graph.o: struct.h graph.h
init.o: struct.h init.h tool.h
interaction.o: struct.h interaction.h
tool.o: struct.h tool.h

# Création des fichiers objets à partir des fichiers sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)

# CC=gcc
# CFLAGS=-Wall -std=c17 -pedantic
# OBJ=main.o game.o graph.o init.o interaction.o
# LDLIBS=-lMLV
# EXEC=minesweeper

# build/%(EXEC): $(OBJ)
# 	$(CC) $^ -o $@ $(LDLIBS)

# main.o: main.c include/game.h include/graph.h include/init.h include/interaction.h include/struct.h
# game.o: include/struct.h include/game.h
# graph.o: include/struct.h include/graph.h
# init.o: include/struct.h include/init.h
# interaction.o: include/struct.h include/interaction.h

# build/%.o: src/%.c main.c
# 	@mkdir --parents build
# 	$(CC) -I include $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f *.o

# mrproper: clean
# 	rm -f $(EXEC)