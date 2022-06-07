#define SHM_KEY 1234
#define SHM_SIZE
#define SHM_MODE
#define MAX_BUF
#define NLOOPS

typedef struct
{
	int data;
}ItemType;

typedef struct
{
	ItemType buf[MAX_BUF];
	int in;
	int out;
	int counter;
} BoundedBufferType;
