#define MAX_COORDINATE 6
#define NUM_VERTICES 54

typedef struct _vertex *Vertex;

Vertex*** makeVertexMap(void);

int getID(Vertex vertex);
int getContents(Vertex vertex);
int changeContents(Vertex vertex, int newElement);
void freeMap(Vertex*** map);

int sizeOfVertex(void);
