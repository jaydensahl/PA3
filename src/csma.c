/** @file csma.c
 * @brief Insert Brief here. 
 * 
 * Main function for CSMA
 *
 *
 * @author Jayden Sahl (jaydensahl)
 * @author Yousaf Nazari (yousafnazari)
 *
 * @bug No known Bugs.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csma_header.h"

//global clock for all nodes
int CLOCK;

// 
/** @brief Function to read configuration parameters from the input file.
 *
 *  
 *
 *  @param filename input file to read from
 *  @param N Number of nodes
 *  @param L length of packet
 *  @param M max retransmission attempts
 *  @param R Random number range
 *  @param T simulation time
 *  @return Void.
 */
void readInput(char *filename, int *N, int *L, int *M, int *R, int *T) {
    // TODO: Implement this function
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file\n");
        return;
    }

    char param;
    int value, i;

    while(fscanf(file," %c", &param) != EOF){
        switch(param){
            case 'N':
                fscanf(file, "%d", N);
                //printf("%d",N);
                break;
            case 'L':
                fscanf(file, "%d", L);
                break;
            case 'M':
                fscanf(file, "%d", M);
                break;
            case 'R':
                i = 0;
                while(fscanf(file, "%d", &value) == 1){
                    R[i++] = value;
                };
                break;
            case 'T':
                fscanf(file, "%d", T);
                break;
            default:
                printf("Unknown character %c\n",param);
                break;
        }
    }
    fclose(file);
}

/** @brief Add nodes to the network and assign values to them.
 *         
 *
 *
 *  @param network network structure
 *  @param N Number of nodes
 *  @param R random number range
 *  @param M max retransmission attempts
 *  @return Void.
 */
void add_nodes(Network* network, int N, int* R, int M){
    // 
    for(int i = 1; i <= N; i++){
        network->nodes[i] = create_node(i,R[0],M);
    }
}

/** @brief simulate the transmissions on the network for time T
 *         
 *  @param network the network
 *  @param T simulation time
 *  @return Void.
 */
void simulate(Network* network,int T){
    for (CLOCK = 0; CLOCK < T; CLOCK++)
    {
        //printf("%d \n",CLOCK);
    }
    
}

int main(int argc, char** argv) {
    // check command line arguments
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n\n", argv[0]);
        exit(1);
    }

    char* filename = argv[1];
    int length_R = 6; // this should not be a hardcoded value, needs to change

    //CALL CSMA FUNCTIONS HERE
    // Read configuration parameters from input file
    int N, L, M, R[length_R], T; 
    readInput(filename, &N, &L, &M, R, &T);
    // Initialize nodes
    Network* network = create_network(N);
    add_nodes(network, N, R, M);
    // Run simulation
    simulate(network,T);
    // Evaluate network utilization

    return(EXIT_SUCCESS);
}