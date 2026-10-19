/**
 * @file graph_test.c
 * @brief Teste de todas as funções públicas da biblioteca através de assert.
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"

int main(void){

    printf("================================\n");
    printf("1. Criar um grafo g com 6 vértices\n");
    // printf("================================\n");
    Graph *g;
    g = graph_create(6);

    assert(g != NULL);
    printf("Quantidade de vértices: %d\n", graph_get_vertices(g));
    assert(graph_get_vertices(g) == 6);

    assert(graph_add_edge(g, 0, 1, 4));
    assert(graph_add_edge(g, 0, 2, 2));
    assert(graph_add_edge(g, 1, 3, 5));
    assert(graph_add_edge(g, 2, 4, 1));
    assert(graph_add_edge(g, 4, 5, 3));
    // assert(graph_add_edge(g, 4, 6, 3)); //Deu Assertion failed.


    printf("================================\n");
    printf("2. Testar o módulo Edges\n");
    // printf("================================\n");

    printf("Peso de (0, 1): %d\n", graph_get_weight(g, 0, 1));
    assert(graph_get_weight(g, 0, 1) == 4);

    printf("Peso de (2, 4): %d\n", graph_get_weight(g, 2, 4));
    assert(graph_get_weight(g, 2, 4) == 1);

    printf("Peso de (1, 5): %d\n", graph_get_weight(g, 1, 5));
    assert(graph_get_weight(g, 1, 5) == 0);

    printf("Grau de 0: %d\n", graph_degree(g, 0));
    assert(graph_degree(g, 0) == 2);

    printf("Grau de 3: %d\n", graph_degree(g, 3));
    assert(graph_degree(g, 3) == 1);

    printf("Grau de 4: %d\n", graph_degree(g, 4));
    assert(graph_degree(g, 4) == 2);

    int *qtd_edges = malloc(sizeof *qtd_edges);
    assert(qtd_edges != NULL);

    Edge *edges;
    edges = graph_get_edges(g, qtd_edges);

    printf("Quantidade de aresta: %d\n", *qtd_edges);
    assert(*qtd_edges == 5);

    for(int i = 0; i < *qtd_edges; i++){
        printf("Aresta %d: (%u, %u, %u)\n", i, edges[i].u, edges[i].v, edges[i].w);
        assert(graph_get_weight(g, edges[i].u, edges[i].v) == (int)edges[i].w);
    }


    printf("================================\n");
    printf("3. Testar Traversal\n");
    // printf("================================\n");

    printf("0 alcança 5? %d\n", graph_is_reachable(g, 0, 5));
    assert(graph_is_reachable(g, 0, 5) == true);

    printf("3 alcança 5? %d\n", graph_is_reachable(g, 3, 5));
    assert(graph_is_reachable(g, 3, 5) == true);

    printf("Tamanho de componente de 0: %d\n", graph_component_size(g, 0));
    assert(graph_component_size(g, 0) == 6);

    printf("Tamanho de componente de 5: %d\n", graph_component_size(g, 5));
    assert(graph_component_size(g, 5) == 6);

    printf("Distância em número de arestas de 3 até 5: %d\n", graph_distance_length(g, 3, 5));
    assert(graph_distance_length(g, 3, 5) == 5);

    int *dist = malloc(sizeof *dist);
    dist = graph_distance_weight_all(g, 3);
    for(int i = 0; i < 6; i++){
        printf("Distância ponderada de 3 até %d: %d\n", i, dist[i]);
        assert(dist[i] == graph_distance_weight(g, i, 3));
    }

    dist = graph_distance_length_all(g, 3);
    for(int i = 0; i < 6; i++){
        printf("Distância em número de arestas de 3 até %d: %d\n", i, dist[i]);
        assert(dist[i] == graph_distance_length(g, i, 3));
    }

    free(dist);


    printf("================================\n");
    printf("4. Testar Properties no grafo inicial\n");
    // printf("================================\n");

    printf("Conectado? %d\n", graph_is_connected(g));
    assert(graph_is_connected(g) == true);

    printf("Possui ciclo? %d\n", graph_has_cycle(g));
    assert(graph_has_cycle(g) == false);

    printf("Árvore? %d\n", graph_is_tree(g));
    assert(graph_is_tree(g) == true);

    printf("Floresta? %d\n", graph_is_forest(g));
    assert(graph_is_forest(g) == true);

    printf("Bipartido? %d\n", graph_is_bipartite(g));
    assert(graph_is_bipartite(g) == true);


    printf("================================\n");
    printf("5. Criar um ciclo\n");
    // printf("================================\n");  

    assert(graph_add_edge(g, 1, 2, 1));

    printf("Conectado? %d\n", graph_is_connected(g));
    assert(graph_is_connected(g) == true);

    printf("Possui ciclo? %d\n", graph_has_cycle(g));
    assert(graph_has_cycle(g) == true);

    printf("Árvore? %d\n", graph_is_tree(g));
    assert(graph_is_tree(g) == false);

    printf("Floresta? %d\n", graph_is_forest(g));
    assert(graph_is_forest(g) == false);

    printf("Bipartido? %d\n", graph_is_bipartite(g));
    assert(graph_is_bipartite(g) == false);

    printf("Grau de 1: %d\n", graph_degree(g, 1));
    assert(graph_degree(g, 1) == 3);

    printf("Grau de 2: %d\n", graph_degree(g, 2));
    assert(graph_degree(g, 2) == 3);


    free(edges);

    edges = graph_get_edges(g, qtd_edges);

    printf("Quantidade de aresta: %d\n", *qtd_edges);
    assert(*qtd_edges == 6);


    printf("================================\n");
    printf("6. Testar remoção de arestas\n");
    // printf("================================\n");

    assert(graph_remove_edge(g, 2, 4));

    printf("0 alcança 5? %d\n", graph_is_reachable(g, 0, 5));
    assert(graph_is_reachable(g, 0, 5) == false);

    printf("Tamanho de componente de 0: %d\n", graph_component_size(g, 0));
    assert(graph_component_size(g, 0) == 4);

    printf("Tamanho de componente de 5: %d\n", graph_component_size(g, 5));
    assert(graph_component_size(g, 5) == 2);

    printf("Conectado? %d\n", graph_is_connected(g));
    assert(graph_is_connected(g) == false);

    printf("Distância em número de arestas de 3 até 5: %d\n", graph_distance_length(g, 3, 5));
    assert(graph_distance_length(g, 3, 5) == -1);

    printf("Possui ciclo? %d\n", graph_has_cycle(g));
    assert(graph_has_cycle(g) == true);

    printf("Árvore? %d\n", graph_is_tree(g));
    assert(graph_is_tree(g) == false);

    printf("Floresta? %d\n", graph_is_forest(g));
    assert(graph_is_forest(g) == false);


    assert(graph_remove_edge(g, 1, 2)); // Remove a aresta que estava formando o ciclo

    printf("Conectado? %d\n", graph_is_connected(g));
    assert(graph_is_connected(g) == false);

    printf("Possui ciclo? %d\n", graph_has_cycle(g));
    assert(graph_has_cycle(g) == false);

    printf("Árvore? %d\n", graph_is_tree(g));
    assert(graph_is_tree(g) == false);

    printf("Floresta? %d\n", graph_is_forest(g));
    assert(graph_is_forest(g) == true);

    printf("Bipartido? %d\n", graph_is_bipartite(g));
    assert(graph_is_bipartite(g) == true);


    printf("================================\n");
    printf("7. Testes de entradas inválidas\n");
    // printf("================================\n");

    printf("Grau de 6: %d\n", graph_degree(g, 6));
    assert(graph_degree(g, 6) == -1);

    printf("Distância em número de arestas de 0 até 6: %d\n", graph_distance_length(g, 0, 6));
    assert(graph_distance_length(g, 0, 6) == -1);

    printf("Distância ponderada de 0 até 6: %d\n", graph_distance_weight(g, 0, 6));
    assert(graph_distance_weight(g, 0, 6) == -1);

    printf("0 alcança 6? %d\n", graph_is_reachable(g, 0, 6));
    assert(graph_is_reachable(g, 0, 6) == false);

    printf("Tamanho de componente de 6: %d\n", graph_component_size(g, 6));
    assert(graph_component_size(g, 6) == 0);

    free(edges);
    free(qtd_edges);
    graph_destroy(g);

    printf("================================\n");
    
    printf("8. Testar overflow em graph_distance_weight\n");

    g = graph_create(3);
   
    assert(graph_add_edge(g, 0, 1, 1500000000));
    assert(graph_add_edge(g, 1, 2, 1000000000));

    int distancia = graph_distance_weight(g, 0, 2);

    printf("Distância com possível overflow: %d\n", distancia);

    graph_destroy(g);
    return 0;
}
    
