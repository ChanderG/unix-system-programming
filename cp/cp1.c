#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/mman.h>

#define COPYMODE 0666

void end_gracefully(char* msg){
  perror(msg);
  exit(1);
}  

void main(int argc, char** argv){
  
  int fd_in, fd_out;
  if((fd_in = open(argv[1], O_RDONLY) == -1)){
    perror("Error opening file: ");
    exit(1);
  }

  if((fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, COPYMODE) == -1)){
    perror("Error opening file: ");
    exit(1);
  }

  size_t filesize;
  if((filesize = lseek(fd_in, 0, SEEK_END) == -1)){
    perror("Error reading file: ");
    exit(1);
  }

  //so unintialized characters are null characters
  char nullbyte;
  lseek(fd_out, filesize-1, SEEK_SET);
  write(fd_out, &nullbyte, 1);


  void *src, *dest;
  if((src =  mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd_in, 0)) == (void*)-1){
    perror("Error mapping file: ");
    exit(1);
  }


  return;
}
