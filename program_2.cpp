
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>          
#include <unistd.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdlib.h>
//#include<vector>
//#include<algorithm>
#define STORAGE_SIZE 10000

int main(int argc, char *argv[])
{
	int res;
	int fd;
  int mem;
	pid_t pid;
	void *addr;

	pid = getpid();

	


   fd = open("./data", O_RDWR , 0600);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}

	// map shared memory to process address space
	addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);

	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}
	  // get shared memory file descriptor 
      mem = shm_open("./data_1", O_RDWR|O_EXCL, S_IRUSR | S_IWUSR);
      int sm_id;
sm_id = shmget(9000,  sizeof(mem), IPC_CREAT | IPC_EXCL | 0666);
if(sm_id>0){
    perror("Shared memory has not been created yet");
    exit(1);
}else{
    sm_id = shmget(9000, sizeof(mem), IPC_CREAT | 0666);
         printf(" created shared memory\n");
}
	// place addr into memory
	memcpy(&mem, addr, sizeof(addr));

	printf("PID %d: Read from shared memory: \"%d\"\n", pid,mem );
//	creating a new file
  int file_descriptor = open("./data_2", O_RDWR | O_CREAT , 0600);
  int *address = mmap(NULL, sizeof(file_descriptor), PROT_READ, MAP_SHARED, file_descriptor, 0);
  int *c=address;
  	memcpy(&c, addr, sizeof(addr));
  
//	
}
