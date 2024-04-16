/** @file csma.c
 * @brief Main function for CSMA (Carrier Sense Multiple Access)
 *
 *
 * @author Jayden Sahl (jaydensahl)
 * @author Yousaf Nazari (yousafnazari)
 *
 * @bug No known Bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csma_header.h"

//global clock for all nodes
int CLOCK;

/** @brief Write the output link utilization rate
 *          to the output file, "output.txt"
 * 
 * @param link_util Link utilization rate
 * 
 * @return Void.
*/
void output(double link_util){
    FILE *file = fopen("output.txt", "w");
    if (file == NULL){
        printf("Error opening file\n");
        return;
    }
    fprintf(file, "%.2f", link_util);
    fclose(file);   
}
// 
/** @brief Function to read configuration parameters from the input file.
 *
 *  @param filename input file to read from
 *  @param N Number of nodes
 *  @param L length of packet
 *  @param M max retransmission attempts
 *  @param R Random number range
 *  @param T simulation time
 *  @return Void.
 */
void readInput(char *filename, int *N, int *L, int *M, int **R, int *T) {
    // TODO: Implement this function
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file\n");
        return;
    }

    char param;
    int value, i, capacity_R = 2;
    // allocate memory for R based on initial capacity
    *R = malloc(capacity_R * sizeof(int));

    // check for input variable and read the number after it
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
                    //printf("%d\n", value);
                    // check if R needs to reallocated
                    if (i >= capacity_R) {
                        capacity_R++;
                        *R = realloc(*R, capacity_R * sizeof(int));
                    }
                    (*R)[i++] = value;
                };
                //printf("%d\n", i);
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
    // add data into each new node
    for(int i = 0; i < N; i++){
        network->nodes[i] = create_node(i,R[0],M);
    }
}

/** @brief simulate the transmissions on the network for time T
 *         
 *  @param network the network
 *  @param T simulation time
 *  @return Void.
 */
void simulate(Network* network, int T, int* R, int L){
    int channelOccupied = 0; // busy channel flag
    int successful_transmissions = 0; // counter for successful transmissions    
    int transmitting_nodes = 0;
    int tx_done = 0;
    Node* transmitting_node; // identify which node is transmitting
    // simulate in "sync" with clock cycles
    for (CLOCK = 0; CLOCK < T; CLOCK++)
    {
        // to print the table of backoff values
        //printf("clock: %d\n", CLOCK);
        for (int i = 0; i < network->num_nodes; i++){
            // to print the table of backoff values
            //printf("Node %d backoff: %d\n", network->nodes[i]->id,network->nodes[i]->backoff);
        }
        tx_done = 0;

        // iterate over all nodes (in order)
        for (int i = 0; i < network->num_nodes; i++){
            Node* node = network->nodes[i];
                
            // if channel is not occupied and node backoff = 0, begin transmitting
            if (!channelOccupied && node->backoff == 0){
                transmitting_nodes++;
                transmitting_node = node;
                node->tx_start_time = 0;
            }        
        }
        // if only one node is transmitting, increment susccessful transmissions
        if (transmitting_nodes == 1){
            successful_transmissions++;
            channelOccupied = 1;
            transmitting_node->tx_start_time++;
            if (transmitting_node->tx_start_time >= L){           
                transmitting_node->backoff = (transmitting_node->id + CLOCK+1) % transmitting_node->R;
                transmitting_node->tx_start_time=0;
                tx_done = 1;
            }
        }
        // else if more than one node is "transmitting", handle collisions
        else if(transmitting_nodes > 1){
            channelOccupied = 1;
            // handle collision for each node
            for (int i = 0; i < network->num_nodes; i++){
                Node* node = network->nodes[i];
                if(node->backoff == 0){
                    node->collision_count++;
                    // if collision count is less than max, increment R value
                    if (node->collision_count < node->M){
                        node->R = R[node->collision_count]; 
                    }
                    // else reset collision count and R
                    else{
                        node->collision_count = 0;
                        node->R = R[node->collision_count]; 
                    }
                    node->backoff = (node->id + CLOCK+1) % node->R;
                }
            }
            tx_done = 1;
        }
        // if the channel was unoccupied, decrement backoff for all nodes
        for (int i = 0; i < network->num_nodes; i++){
            Node* node = network->nodes[i];
            if(!channelOccupied){
                node->backoff--;
            }
        }
        // after packet transmission is complete, reset flags
        if(tx_done){
            // reset channel occupied flag
            transmitting_nodes = 0;
            channelOccupied = 0;
        }
    }
    double link_util = (double)successful_transmissions / T;
    printf("%.2f", link_util);
    output(link_util);
}

/** @brief main function
 *  reads input file
 *  creates network
 *  creates nodes and assigns values to them
 * 
 * @param input from command line
 * 
 * @return 1
*/
int main(int argc, char** argv) {
    // check command line arguments
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n\n", argv[0]);
        exit(1);
    }

    char* filename = argv[1];

    //CALL CSMA FUNCTIONS HERE
    // Read configuration parameters from input file
    int N, L, M, *R = NULL, T; 
    readInput(filename, &N, &L, &M, &R, &T);
    // Initialize nodes
    Network* network = create_network(N);
    add_nodes(network, N, R, M);
    // Run simulation
    simulate(network, T, R, L);
    // Evaluate network utilization

    return(EXIT_SUCCESS);
}