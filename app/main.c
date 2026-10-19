/**
 * @file main.c
 * @brief Exemplo de uso da biblioteca: 3 problemas de grafos resolvidos direto no main.
 *
 *   Problema 1 - Is it a tree?      -> módulo properties
 *   Problema 2 - Tree Diameter      -> módulo traversal
 *   Problema 3 - Graph and String   -> módulos core e edges
 *
 * Em cada um: o enunciado, como ele vira um grafo (modelagem) e a solução.
 * Os exemplos são pequenos de propósito (a matriz de adjacência não comporta
 * as entradas gigantes dos juízes online).
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(void){

    /* ====================================================================
     * PROBLEMA 1 - Is it a tree?
     *
     * Enunciado (reconstruído pelo título; troque pelo texto original):
     *   Dado um grafo não direcionado, diga se ele é uma árvore
     *   (conexo e sem ciclos). Saída: YES ou NO.
     *
     * Modelagem: cada vértice é um vértice; cada aresta "u v" vira
     *   graph_add_edge(g, u, v, 1).
     * Solução: graph_is_tree já faz exatamente essa verificação.
     * ==================================================================== */
    printf("=== Problema 1: Is it a tree? ===\n");

    Graph *g = graph_create(4);
    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 1, 2, 1);
    graph_add_edge(g, 2, 3, 1);
    printf("caminho 0-1-2-3:      %s\n", graph_is_tree(g) ? "YES" : "NO");   // esperado: YES

    graph_add_edge(g, 3, 0, 1);                                              // fecha um ciclo
    printf("com a aresta 3-0:     %s\n", graph_is_tree(g) ? "YES" : "NO");   // esperado: NO

    graph_remove_edge(g, 3, 0);                                              // desfaz
    printf("sem a aresta 3-0:     %s\n", graph_is_tree(g) ? "YES" : "NO");   // esperado: YES
    graph_destroy(g);


    /* ====================================================================
     * PROBLEMA 2 - Tree Diameter
     *
     * Enunciado (resumido; confira com o original):
     *   Dada uma árvore com N nós, o diâmetro é a maior distância (em
     *   arestas) entre dois nós. Determine o diâmetro.
     *
     * Modelagem: os nós 1..N viram os vértices 0..N-1; cada aresta "a b"
     *   vira graph_add_edge(g, a-1, b-1, 1).
     * Solução (duas buscas em largura):
     *   1) a partir do vértice 0, acha-se o mais distante (a);
     *   2) a partir de a, a maior distância encontrada é o diâmetro.
     * ==================================================================== */
    printf("\n=== Problema 2: Tree Diameter ===\n");

    // árvore do exemplo: 1-2, 1-3, 3-4, 3-5   (nos vértices: 0-1, 0-2, 2-3, 2-4)
    g = graph_create(5);
    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 2, 3, 1);
    graph_add_edge(g, 2, 4, 1);

    int *d = graph_distance_length_all(g, 0);          // distâncias a partir do 0
    if(d == NULL) return 1;
    unsigned int a = 0;
    for(unsigned int v = 1; v < graph_get_vertices(g); v++){
        if(d[v] > d[a]) a = v;                          // o mais distante do 0
    }
    free(d);

    d = graph_distance_length_all(g, a);               // distâncias a partir de a
    if(d == NULL) return 1;
    int diametro = 0;
    for(unsigned int v = 0; v < graph_get_vertices(g); v++){
        if(d[v] > diametro) diametro = d[v];
    }
    free(d);

    printf("diametro: %d\n", diametro);                 // esperado: 3
    graph_destroy(g);


    /* ====================================================================
     * PROBLEMA 3 - Graph and String
     *
     * Enunciado (resumido; confira com o original):
     *   Dado um grafo simples com N vértices, decida se existe uma string s
     *   de N letras ('a', 'b' ou 'c') tal que, para todo par i != j, há
     *   aresta entre i e j se e somente se s[i] e s[j] são iguais ou
     *   vizinhas no alfabeto (a-b e b-c são; a e c NÃO). Saída: "Yes" e
     *   uma string válida, ou "No".
     *
     * Modelagem: vértice i = posição i da string; aresta = par de posições
     *   "compatíveis". graph_get_weight(g,i,j) != 0 significa "há aresta".
     * Solução:
     *   1) vértice com grau N-1 (graph_degree) pode ser 'b';
     *   2) o primeiro restante vira 'a'; os outros viram 'a' se forem
     *      vizinhos dele e 'c' se não forem;
     *   3) conferir todos os pares: há aresta se e somente se as letras
     *      são iguais ou uma delas é 'b'.
     * ==================================================================== */
    printf("\n=== Problema 3: Graph and String ===\n");

    // vértice 0 ligado a todos; pares 1-2 e 3-4 ligados entre si
    g = graph_create(5);
    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 0, 3, 1);
    graph_add_edge(g, 0, 4, 1);
    graph_add_edge(g, 1, 2, 1);
    graph_add_edge(g, 3, 4, 1);

    unsigned int n = graph_get_vertices(g);
    char s[6];                                          // n letras + '\0'
    for(unsigned int i = 0; i < n; i++) s[i] = '?';
    s[n] = '\0';

    for(unsigned int v = 0; v < n; v++){                // 1) grau N-1 -> 'b'
        if(graph_degree(g, v) == (int)(n - 1)) s[v] = 'b';
    }

    unsigned int base = n;                              // 2) primeiro restante -> 'a'
    for(unsigned int v = 0; v < n; v++){
        if(s[v] == '?'){ base = v; break; }
    }
    if(base < n){
        s[base] = 'a';
        for(unsigned int w = base + 1; w < n; w++){
            if(s[w] == '?') s[w] = (graph_get_weight(g, base, w) != 0) ? 'a' : 'c';
        }
    }

    int valida = 1;                                     // 3) conferir todos os pares
    for(unsigned int i = 0; i < n; i++){
        for(unsigned int j = i + 1; j < n; j++){
            int tem_aresta = (graph_get_weight(g, i, j) != 0);
            int deveria    = (s[i] == s[j]) || s[i] == 'b' || s[j] == 'b';
            if(tem_aresta != deveria) valida = 0;
        }
    }

    if(valida) printf("Yes %s\n", s);                   // esperado: Yes baacc
    else       printf("No\n");
    graph_destroy(g);

    return 0;
}
