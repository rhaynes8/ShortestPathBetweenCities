#define MAXCITYSTRING 20
#define V 20
struct Node;
struct Graph;
struct List;
struct Matrix;
struct Node* NodeConstructor(char* start, char* end, int distance);
struct List* listConstructor();
struct Graph* GraphConstructor(int Size);
void NodeDestructor(struct Node* node);
void listDestructor(struct List* linkedList);
int listSize (struct List* linkedList);
int listIsEmpty (struct List* list);
int listAdd(struct List* list, char* start, char* end, int distance);
void listDisplay(struct List* list);
int addEdge(struct Graph* graph, struct Node* node);
void displayGraph(struct Graph * graph);
int listSearchStart(struct List* list, char entity[][MAXCITYSTRING], int index);
int listSearchEnd(struct List* list, char entity[][MAXCITYSTRING], int index);
char deblank(char* input);
void matrixDisplay(struct Matrix* matrix, struct List* list, int* start, int* end);
struct Matrix* MatrixConstructor(struct List* list, int Size);
int listRead(struct List* list, int index);
struct ListNode* listGetNode(struct List* list, int index);
void graph(struct List* list, int size);
void dijsktraAlgorithm(struct Matrix* matrix, int src);
