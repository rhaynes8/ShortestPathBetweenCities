#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distance.h"

// Getlines for number

int main()
{
    /* Reading in a text file */
    FILE * distances;
   // FILE * citypairs;
    distances = fopen("ukcities.txt", "r");
    //citypairs = fopen("citypairs.txt", "r");

    int i;
    /* Create a pointer to a new list structure */
    struct List* distancesList = listConstructor();
   /* Creating arrays to store start and end cities */
    char startInput[MAXCITYSTRING], endInput[MAXCITYSTRING];
    /* Variable to store the distances between start and end cities */
    int distanceInput;
    /* Creating an array with all cities (start and end) with no duplicates */
    char citiesArray[80][MAXCITYSTRING];


    i = 0;
    /* Filling the linked lists with values from previous arrays */
    while (fscanf(distances, "%s %s %d", startInput, endInput, &distanceInput) != EOF)
    {
        /* Map makeshift arrays to a new Linked List*/
        listAdd(distancesList, startInput, endInput, distanceInput);
        /* Copy all of the cities over to a different array for later comparison */
        /* Copy over start-end-start-end etc. */
        strcpy(citiesArray[2*i],startInput);
        strcpy(citiesArray[(2*i)+1],endInput);
        i++;
    }

    listDisplay(distancesList);

    /* Declare variable for current amount of cities in the array */
    int noCities = 80;
    int j;
    /* Increment through i, to change comparison between each city */
    for (i = 0; i < 80; i++)
    {
        /* Start increment, j, at i + 1 so that the beginning string doesn't compare to itself */
        for (j = i + 1; j < 80; j++)
        {
            /* If at any point in the increments, the two strings are the same*/
            if (strcmp(citiesArray[i], citiesArray[j]) == 0)
            {
                /* Or if the array is not equal to blank space */
                if (strcmp(citiesArray[i], "") != 0)
                {
                    /* Decrease the number of cities we are working with */
                    noCities--;
                }
                /* Turn duplicate city into empty memory space */
                memset(citiesArray[j], 0, sizeof(citiesArray[j]));
            }
        }
    }
    /* Create new array to store all cities in without duplicates */
    char citiesSansDup[noCities][MAXCITYSTRING];
    int next = 0;
    for (i = 0; i < 80; i++)
    {   /* If one of the original 80 cities and an empty space (which was previously created) */
        /* are not the same */

        if (strcmp(citiesArray[i], "") != 0)
        {
            /* Then equal it to the no duplicates array. This gets rid of the blank spaces created by
            the memset function */
             /* Need next so that it only increments if a new value has been mapped to the array */
            /* Copy the string over */
            strcpy(citiesSansDup[next], citiesArray[i]);
            /* Print the string */
            printf("%s\n", citiesSansDup[next]);
            /* Increment next */

            next = next + 1;

        }
    }
    /* Check how many cities there are with no duplicates */
    printf("\n\n\nnoCities = %d\n\n\n", noCities);

    /* Declare new variables and arrays */
    int searchStart;
    int searchEnd;
    int start[40];
    int end[40];

    /* Find the index each starting city in the original text file compared to its new position
    in the no duplicates array*/
    for (i = 0; i < 40; i++)
    {
        searchStart = listSearchStart(distancesList, citiesSansDup, i);
        start[i] = searchStart;
    }
    /* Find the index each ending city in the original text file compared to its new position
    in the no duplicates array*/
    for (i = 0; i < 40; i++)
    {
        searchEnd = listSearchEnd(distancesList, citiesSansDup, i);
        end[i] = searchEnd;
    }

    printf("\n\n\n\n\n");
    /* define a pointer to a new matrix structure */
    struct Matrix* matrix = MatrixConstructor(distancesList, noCities);
    /* Add to and display the adjacency matrix */
    matrixDisplay(matrix, distancesList, start, end);
    printf("\n\n\n\n\n");
    /* Implement Dijsktra's Algorithm */
    dijsktraAlgorithm(matrix, 0);
    /* Close the file */
    fclose(distances);

    return 0;
}
