#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "distance.h"

struct Node
{
    int distance;
    char startCity[MAXCITYSTRING];
    char endCity[MAXCITYSTRING];
    struct Node* next;
    struct Node* prev;
    //struct Adjacent* adj; // Pointer to Adjacent node
};

struct Node* NodeConstructor(char* start, char* end, int distance)
{
    /* strcpy() function */
    struct Node* newNode;
    newNode = malloc(sizeof(struct Node));
    strcpy(newNode->startCity, start);
    strcpy(newNode->endCity, end);
    newNode->distance = distance;
    newNode->next = NULL;
    newNode->prev = NULL;
    //newNode->adj = NULL;
    return newNode;
}

void NodeDestructor(struct Node* node)
{
    free(node);
}

struct List
{
    int size;
    struct Node* graphNext;
    struct Node* graphPrev;
    struct Node* head;
    struct Node* tail;
   // struct Node** adjLists;
};

struct List* listConstructor()
{
    struct List* newLinkedList;
    newLinkedList = malloc(sizeof(struct List) );
    newLinkedList->size = 0;
    newLinkedList->graphNext = NULL;
    newLinkedList->graphPrev = NULL;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;
    return newLinkedList;
}

/* Works */
void listDestructor(struct List* linkedList)
{
    struct Node* currentRecord;
    struct Node* nextRecord = linkedList->head;

    while(nextRecord != NULL)
    {
        currentRecord = nextRecord;
        nextRecord = currentRecord->next;
        NodeDestructor(currentRecord);
    }

    free(linkedList);
}
/* Works */
int listSize (struct List* linkedList)
{
    printf("%d\n\n", linkedList->size);
    return linkedList->size;
}

int listSearchStart(struct List* list, char entity[][MAXCITYSTRING], int index)
{
    struct Node* node = list->head;
    /* Define a node and equate it to the first node in the list */
    int i;

    // As long as we have an element to test
    for(i = 0; i < index; i++)
    {
        /* Check the next node during the next iteration of the loop */
        node = node->next;
    }
    for (i = 0; i <= 21; i++)
    {
        if(strcmp(node->startCity, entity[i]) == 0)
        {
            return i;
        }
    }
    return 0;
}

int listSearchEnd(struct List* list, char entity[][MAXCITYSTRING], int index)
{
    struct Node* node = list->head;
    /* Define a node and equate it to the first node in the list */
    int i;
    // Index from 0-40 to traverse the linked list
    // As long as we have an element to test
    for(i = 0; i < index; i++)
    {
        /* Check the next node during the next iteration of the loop */
        node = node->next;
    }
    for (i = 0; i <= 21; i++)
    {
        if(strcmp(node->endCity, entity[i]) == 0)
        {
            return i;
        }
    }
    return 0;
}

/* Works */
int listIsEmpty (struct List* list)
{
    // Return 1 if the list is empty
    if ( list->head == NULL )
    {
        return 1;
    }
    // Return 0 if list is not empty
    return 0;
}
/* Works */
int listAdd(struct List* list, char* start, char* end, int distance)
{

    struct Node* newNode = NodeConstructor(start, end, distance);
    newNode->prev = list->tail;
    newNode->next = NULL;

    if ( list->head == NULL )
    {
        list->head = newNode;
    }

    newNode->prev = list->tail;

    list->tail = newNode;

    if (list->head != list->tail)

    {
        newNode->prev->next = newNode;
    }

    list->size++;

    return 1;
}

/* Works */

void listDisplay(struct List* list)
{

    struct Node* currentNode = list->head;

    while (currentNode != NULL)
    {
        printf("%s %s %d\n", currentNode->startCity, currentNode->endCity, currentNode->distance);
        currentNode = currentNode->next;
    }
    printf("\n\n");
}

struct Matrix
{
    int row;
    int column;
    int** data;
};

struct Matrix* MatrixConstructor(struct List* list, int Size)
{
    int i;

    struct Matrix* newMatrix;
    newMatrix = malloc(sizeof(struct Matrix));
    newMatrix->row = Size;
    newMatrix->column = Size;
    int** data = malloc(sizeof(int**) * Size);

    for(i = 0; i < Size; i++)
    {
        data[i] = calloc(Size, sizeof(double*));
    }

    newMatrix->data = data;
    return newMatrix;
}


void matrixDisplay(struct Matrix* matrix, struct List* list, int* start, int* end)
{
    struct Node* node = list->head;
    int i, j;

    for (i = 0; i < 1; i++)
    {
        /* Loop alone creates one row with all correct distances */
        for (j = 0; j < 40; j++)
        {
            matrix->data[start[j]][end[j]] = node->distance;
            /* node = node->next outside of j for loop prints whole matrix */
            node = node->next;
        }

    }
    printf("Adjacency Matrix:\n");
    for (i = 0; i < matrix->row; i++)
    {

        printf("\n");

        for (j = 0; j < matrix->column; j++)
        {

            printf("%d  ", matrix->data[i][j] + matrix->data[j][i]);

        }
        //node = node->next;
    }
}

int minDistance(int dist[], int sptSet[])
{
    int min = INT_MAX, min_index;

    int v;
    for (v = 0; v < V; v++)
    {
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void printResult(int dist[], int n)
{
    int i;
    for (i = 0; i < V; i++)
    {
        printf("Vertex: %d   Distance From Source: %d\n", i, dist[i]);
    }
}

void dijsktraAlgorithm(struct Matrix* matrix, int source)
{
    /* V is #defined as 20 */

    /* Output array to hold the shortest distance from source to i */
    int dist[V];
    /* sptSet = 1 if vertex i is included in shortest path tree*/
    int sptSet[V];
    int i, v;

    /* Initialise all distances as infinite and stpSet as false */
    for (i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        dist[i] = sptSet[i] = 0;
    }

    /* Distance from source vertex is always 0 */
    dist[source] = 0;
    /* Find shortest path for all vertices */
    for (i = 0; i < V-1; i++)
    {
        /* Pick the minimum distance vertex from the set of vertices not
        yet processed. u is always equal to source in first iteration. */
        int u = minDistance(dist, sptSet);
        /* Set the picked vertex to 1 */
        sptSet[u] = 1;
        /* Update distance value of the adjacent vertices of picked vertex  */
        for (v = 0; v < V; v++)
        {
            /* Update dist[v] only if is not in sptSet, there is an edge from
            u to v, and total weight of path from src to  v through u is
            smaller than current value of dist[v] */
            if (sptSet[v] == 0 && matrix[u][v] && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + matrix[u][v];
            }

        }
    }
    /* Print out the results */
    printResult(dist, V);
}
