#define SHM_KEY 1234
#define SHM_SIZE 1024
#define SHM_MODE (SHM_R | SHM_W | IPC_CREAT)
#define MAX_BUF 5
#define NLOOPS 10

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
