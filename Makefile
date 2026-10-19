# =========================
# Variáveis Globais
# =========================CC = gcc

CFLAGS = -Wall -Iinclude
PICFLAGS = -fPIC
LIBFLAG = -Llib -lgraph

OBJ = build/core.o \
      build/edges.o \
      build/traversal.o \
      build/properties.o

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
LIB_STATIC = lib/libgraph.a
$(LIB_STATIC): $(OBJ)
	ar rcs $(LIB_STATIC) $(OBJ)


# =========================
# Biblioteca dinâmica
# =========================
LIB_SHARED = lib/libgraph.so
$(LIB_SHARED): $(OBJ)
	$(CC) -shared -o $(LIB_SHARED) $(LIBFLAG) $(OBJ)


# =========================
# Aplicação cliente
# =========================
APP = bin/graph_app
$(APP): app/main.c
	$(CC) $(CFLAGS) app/main.c  -o $(APP)


# =========================
# Executar aplicação
# =========================
run: $(APP)
	LD_LIBRARY_PATH=lib ./$(APP)


# =========================
# Testes
# =========================
TEST_SHARED = bin/graph_test_shared
TEST_STATIC = bin/graph_test_static

$(TEST_SHARED): tests/graph_test.c $(LIB_SHARED)
	$(CC) $(CFLAGS) tests/graph_test.c $(LIBFLAG) -o $(TEST_SHARED)

$(TEST_STATIC): tests/graph_test.c $(LIB_STATIC)
	$(CC) $(CFLAGS) tests/graph_test.c $(LIB_STATIC) -o $(TEST_STATIC)

test: $(TEST_SHARED) $(TEST_STATIC)
	@echo "===== Testando com biblioteca dinâmica (.so) ====="
	LD_LIBRARY_PATH=lib ./$(TEST_SHARED)
	@echo
	@echo "===== Testando com biblioteca estática (.a) ====="
	./$(TEST_STATIC)
	@echo

# =========================
# Limpeza
# =========================
clean:
	rm -rf build/* bin/* lib/*


# =========================
# Instalação
# =========================
PREFIX?=$(HOME)/.local

install: all
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	cp -r lib/* $(PREFIX)/lib/
	cp -r include/* $(PREFIX)/include/

.PHONY: all clean run test install