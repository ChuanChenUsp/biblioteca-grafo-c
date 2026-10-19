# =========================
# Variáveis Globais
# =========================
CFLAGS = -Wall -Iinclude
PICFLAGS = -fPIC
SHAREFLAG = -Llib -lgraph

OBJ = build/core.o \
      build/edges.o \
      build/traversal.o \
      build/properties.o

LIB_STATIC = lib/libgraph.a
LIB_SHARED = lib/libgraph.so
APP_SHARED = bin/graph_shared
APP_STATIC = bin/graph_static
APP_SRC = app/main.c
# =========================
# Alvo principal
# =========================
all: $(LIB_STATIC) $(LIB_SHARED) $(APP_SHARED) $(APP_STATIC)

# =========================
# Receitas
# =========================
build/core.o: src/core.c include/core.h
	gcc $(CFLAGS) $(PICFLAGS) -c src/core.c -o build/core.o

build/edges.o: src/edges.c include/edges.h include/core.h
	gcc $(CFLAGS) $(PICFLAGS) -c src/edges.c -o build/edges.o

build/traversal.o: src/traversal.c include/traversal.h include/core.h
	gcc $(CFLAGS) $(PICFLAGS) -c src/traversal.c -o build/traversal.o

build/properties.o: src/properties.c include/properties.h include/core.h
	gcc $(CFLAGS) $(PICFLAGS) -c src/properties.c -o build/properties.o


# =========================
# Biblioteca estática
# =========================

$(LIB_STATIC): $(OBJ)
	ar rcs $(LIB_STATIC) $(OBJ)


# =========================
# Biblioteca dinâmica
# =========================
$(LIB_SHARED): $(OBJ)
	gcc -shared -o $(LIB_SHARED) $(SHAREFLAG) $(OBJ)


# =========================
# Aplicação cliente
# =========================
$(APP_SHARED): $(APP_SRC) $(LIB_SHARED)
	gcc $(CFLAGS) $(APP_SRC) $(SHAREFLAG) -o $(APP_SHARED)

$(APP_STATIC): $(APP_SRC) $(LIB_STATIC)
	gcc $(CFLAGS) $(APP_SRC) $(LIB_STATIC) -o $(APP_STATIC)

# =========================
# Executar aplicação
# =========================
run: run-shared

run-shared: $(APP_SHARED)
	LD_LIBRARY_PATH=lib ./$(APP_SHARED)

run-static: $(APP_STATIC)
	./$(APP_STATIC)


# =========================
# Testes
# =========================
TEST_SHARED = bin/graph_test_shared
TEST_STATIC = bin/graph_test_static

$(TEST_SHARED): tests/graph_test.c $(LIB_SHARED)
	gcc $(CFLAGS) tests/graph_test.c $(SHAREFLAG) -o $(TEST_SHARED)

$(TEST_STATIC): tests/graph_test.c $(LIB_STATIC)
	gcc $(CFLAGS) tests/graph_test.c $(LIB_STATIC) -o $(TEST_STATIC)

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

.PHONY: all clean run run-shared run-static test install