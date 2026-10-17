CC = gcc

CFLAGS = -Wall -Iinclude
PICFLAGS = -fPIC

SRC = src/core.c \
      src/edges.c \
      src/traversal.c \
      src/properties.c

OBJ = build/core.o \
      build/edges.o \
      build/traversal.o \
      build/properties.o

LIB_STATIC = lib/libgraph.a
LIB_SHARED = lib/libgraph.so

APP = bin/graph_app
TEST = bin/graph_test


# =========================
# Alvo principal
# =========================

all: $(LIB_STATIC) $(LIB_SHARED) $(APP)

# =========================
# Receitas
# =========================
build/core.o: src/core.c include/core.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/core.c -o build/core.o

build/edges.o: src/edges.c include/edges.h include/core.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/edges.c -o build/edges.o

build/traversal.o: src/traversal.c include/traversal.h include/core.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/traversal.c -o build/traversal.o

build/properties.o: src/properties.c include/properties.h include/core.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c src/properties.c -o build/properties.o


# =========================
# Biblioteca estática
# =========================

$(LIB_STATIC): $(OBJ)
	ar rcs $(LIB_STATIC) $(OBJ)


# =========================
# Biblioteca dinâmica
# =========================

$(LIB_SHARED): $(OBJ)
	$(CC) -shared -o $(LIB_SHARED) $(OBJ)


# =========================
# Aplicação cliente
# =========================

$(APP): app/main.c
	$(CC) $(CFLAGS) app/main.c -Llib -lgraph -o $(APP)


# =========================
# Executar aplicação
# =========================

run: $(APP)
	LD_LIBRARY_PATH=lib ./$(APP)


# =========================
# Testes
# =========================

$(TEST): tests/graph_test.c
	$(CC) $(CFLAGS) tests/graph_test.c -Llib -lgraph -o $(TEST)

test: $(TEST)
	LD_LIBRARY_PATH=lib ./$(TEST)

# =========================
# Limpeza
# =========================

clean:
	rm -rf build/* bin/* lib/*


.PHONY: all clean run test install