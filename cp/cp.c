#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void main(int argc, char** argv){
  if(argc == 1) return;

  int fd = open(argv[1], O_RDONLY);  
  if (fd == -1){
    perror("Unable to open file: ");
    exit(1);
  }

  int fd_out = creat(argv[2],COPYMODE); 
  int status;
  char buffer[BUFFERSIZE];
  while(1){
    status = read(fd, buffer, BUFFERSIZE);
    if(status < 0){
      perror("Error copying file");
      exit(1);
    }
    else if(status == 0){
      break;
    }
    else{
      if(status != write(fd_out, buffer, status)){
        perror("Error writing file");
	exit(1);
      }
    }
  }

  close(fd);  
  close(fd_out);  
  return;
}
