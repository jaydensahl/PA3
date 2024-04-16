/** @file csma_header.h
 * @brief Structure for nodes, network, and initalization functions.
 * 
 *
 *
 * @author Jayden Sahl (jaydensahl)
 * @author Yousaf Nazari (yousafnazari)
 *
 * @bug No known Bugs.
 *
 *
 */


#ifndef PACKET_STRUCT
#define PACKET_STRUCT

#include <stdint.h>
#include <stdlib.h> 

/** @brief Structure definition for single node
 *
 * @param id Node identifier
 * @param R Random number range
 * @param M Maximum retransmission attempts
 * @param collision_count Total number of collisions
 * @param backoff  backoff value
 */
typedef struct Node {
    char id;
    int R;
    int M;
    int collision_count;
    int backoff;
    int tx_start_time;
} Node;

/** @brief Structure definition for single node
 *
 * @param id Node identifier
 * @param R Random number range
 * @param M Maximum retransmission attempts
 */
Node* create_node(int id, int R_min, int M) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->id = id;
    node->R = R_min;
    node->M = M;
    node->collision_count = 0;
    node->backoff = id;
    return node;
}

/** @brief Structure definition for single node
 *
 * @param nodes list of all nodes in network
 * @param num_nodes total number of nodes in network 
 */
typedef struct Network {
    Node** nodes; // array of Node pointers
    int num_nodes; // total number of nodes
} Network;

/** @brief initialize nodes
 * 
 * @param N number of nodes to create
 * @return network
*/
Network* create_network(int N){
    Network* network = (Network*) malloc(sizeof(Network));
    network->nodes = (Node**) malloc(N*sizeof(Node*));
    network->num_nodes = N;
    return network;
}

// Function prototypes
void output(double link_util);
void readInput(char *filename, int *N, int *L, int *M, int **R, int *T);
void add_nodes(Network* network, int N, int* R, int M);
void simulate(Network* network, int T, int* R, int L);
Network* create_network(int num_nodes);
Node* create_node(int id, int R, int M);
void test_readInput();

#endif