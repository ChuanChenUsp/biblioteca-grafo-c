
# Biblioteca de Grafos em C

Trabalho Prático 2 da disciplina **MAC0216 – Técnicas de Programação I**.

O projeto implementa uma biblioteca modular em C para criação, manipulação,
percurso e análise de grafos não direcionados e ponderados.

A biblioteca foi dividida em quatro módulos funcionais:

- `core`: criação e gerenciamento do grafo;
- `edges`: manipulação de arestas;
- `traversal`: alcançabilidade, componentes e distâncias;
- `properties`: análise de propriedades do grafo.

O projeto também contém uma aplicação cliente, testes automatizados,
biblioteca estática (`.a`) e biblioteca dinâmica (`.so`).

---

## 0. Responsabilidade principal de cada integrante

- Chuan Xi Chen: integrante responsável pelo módulo `core` e `edges`
- Luiz Miguel: integrante responsável pelo módulo `traversal`
- Arthur Campos: integrante responsável pelo módulo `properties`

---

## 1. Pré-requisitos

Para compilar e executar o projeto, são necessárias as seguintes ferramentas:

- ambiente LINUX.
- GCC;
- GNU Make;
- `ar`.

É possível verificar se as principais ferramentas estão instaladas com:

```bash
gcc --version
make --version
ar --version
```

---

## 2. Estrutura do projeto

O projeto está organizado da seguinte forma:

```text
.
├── app/
│   └── main.c
│
├── include/
│   ├── core.h
│   ├── edges.h
│   ├── graph.h
│   ├── properties.h
│   └── traversal.h
│
├── src/
│   ├── core.c
│   ├── edges.c
│   ├── properties.c
│   └── traversal.c
│
├── tests/
│   └── graph_test.c
│
├── build/
│   └── arquivos objeto (.o)
│
├── lib/
│   ├── libgraph.a
│   └── libgraph.so
│
├── bin/
│   ├── graph_shared
│   ├── graph_static
│   ├── graph_test_shared
│   └── graph_test_static
│
├── Makefile
└── README.md
```

Os diretórios possuem as seguintes responsabilidades:

- `include/`: arquivos de interface pública da biblioteca;
- `src/`: implementação dos módulos;
- `app/`: aplicação cliente que demonstra o uso da biblioteca;
- `tests/`: testes automatizados;
- `build/`: arquivos objeto gerados durante a compilação;
- `lib/`: bibliotecas estática e dinâmica;
- `bin/`: executáveis da aplicação cliente e dos testes.

A biblioteca está dividida em quatro módulos principais, como explicado no começo deste documento.

O arquivo `graph.h` funciona como interface geral da biblioteca e inclui as interfaces dos quatro módulos.

---

## 3. Compilação

Para compilar todo o projeto, execute na raiz do repositório:

```bash
make
```

ou:

```bash
make all
```

O alvo `all` gera as bibliotecas:

```text
lib/libgraph.a
lib/libgraph.so
```

e as duas versões da aplicação cliente:

```text
bin/graph_shared
bin/graph_static
```

A mesma aplicação cliente é compilada utilizando as duas formas de linkagem:

```text
app/main.c + libgraph.so -> bin/graph_shared
app/main.c + libgraph.a  -> bin/graph_static
```

A compilação utiliza dependências entre os arquivos fonte e os arquivos objeto, permitindo compilação incremental.

---

## 4. Alvos do Makefile

### `make all`

Compila os módulos da biblioteca, gera as bibliotecas estática e dinâmica e gera as aplicações cliente.


### `make clean`

Remove os arquivos gerados durante a compilação. Mais especificamente, todos arquivos do diretórios ` build/`, `bin/`e `lib/`.


### `make run`

Executa a aplicação cliente. Por padrão, executa aplicação cliente de versão dinâmica.


### `make run-shared`

Executa a aplicação cliente ligada à biblioteca dinâmica `libgraph.so`.


### `make run-static`

Executa a aplicação cliente ligada à biblioteca estática `libgraph.a`.


### `make test`

Compila e executa automaticamente os testes da biblioteca.
Os testes são executados utilizando tanto a biblioteca dinâmica quanto a biblioteca estática.

### `make install`

Instala as bibliotecas e os arquivos de interface em um prefixo configurável.

Também é possível definir outro prefixo:

```bash
make install PREFIX=$HOME/.loc
```

---

## 5. Execução

A aplicação cliente está localizada em:

```text
app/main.c
```

Ela utiliza exclusivamente a API pública definida nos arquivos `.h` da biblioteca.

A aplicação cliente exemplifica o uso de biblioteca em 3 probelmas de grafo: 
 *   Problema 1 - Is it a tree?      -> módulo properties
 *   Problema 2 - Tree Diameter      -> módulo traversal
 *   Problema 3 - Graph and String   -> módulos core e edges

### Execução com biblioteca dinâmica

Para executar a versão ligada a `libgraph.so`:

```bash
make run-shared
```

### Execução com biblioteca estática

Para executar a versão ligada a `libgraph.a`:

```bash
make run-static
```

Na versão estática, o código necessário da biblioteca é incorporado ao executável durante a etapa de linkagem.


---

## 6. Testes

Os testes estão implementados em:

```text
tests/graph_test.c
```

Para executar todos os testes:

```bash
make test
```

O mesmo código de teste é utilizado para testar as duas versões da biblioteca:

```text
tests/graph_test.c
        |
        +-- libgraph.so --> bin/graph_test_shared
        |
        +-- libgraph.a  --> bin/graph_test_static
```

Os testes utilizam `assert` para verificar os resultados das funções públicas. Todas as funções públicas foram testadas.

Se uma condição verificada por `assert` não for satisfeita, o programa de testes termina indicando falha.

---

## 7. Instalação

O alvo `install` instala:

- as bibliotecas `libgraph.a` e `libgraph.so`;
- os arquivos públicos de interface `.h`.

Por padrão:

```bash
make install
```

utiliza o prefixo definido pelo projeto.

A instalação pode ser realizada em outro local através da variável `PREFIX`.

Exemplo:

```bash
make install PREFIX=$HOME/.loc
```

Nesse caso, a estrutura instalada será semelhante a:

```text
$HOME/.loc/
├── include/
│   ├── core.h
│   ├── edges.h
│   ├── graph.h
│   ├── properties.h
│   └── traversal.h
│
└── lib/
    ├── libgraph.a
    └── libgraph.so
```

O uso de um diretório dentro de `$HOME` permite instalar a biblioteca sem privilégios administrativos.

Após a instalação, um programa externo pode utilizar a biblioteca incluindo:

```c
#include "graph.h"
```

Por exemplo, considerando uma instalação em `$HOME/.loc`:

```bash
gcc programa.c \
    -I$HOME/.loc/include \
    -L$HOME/.loc/lib \
    -lgraph \
    -o programa
```

Caso seja utilizada a biblioteca dinâmica, pode ser necessário executar:

```bash
LD_LIBRARY_PATH=$HOME/.loc/lib ./programa
```
