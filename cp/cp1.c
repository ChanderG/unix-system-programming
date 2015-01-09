#include<stdio.h>
#include<stdlib.h>

#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>

#define COPYMODE 0666

void end_gracefully(char* msg){
  perror(msg);
  exit(1);
}  

void main(int argc, char** argv){
  
  int fd_in, fd_out;
  if((fd_in = open(argv[1], O_RDONLY)) == -1)
    end_gracefully("Error opening file: ");

  if((fd_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, COPYMODE)) == -1)
    end_gracefully("Error opening file: ");

  size_t filesize;
  if((filesize = lseek(fd_in, 0, SEEK_END)) == -1)
    end_gracefully("Error reading file: ");

  //so unintialized characters are null characters
  char nullbyte;
  lseek(fd_out, filesize-1, SEEK_SET);
  write(fd_out, &nullbyte, 1);


  void *src, *dest;
  if((src =  mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd_in, 0)) == (void*)-1)
    end_gracefully("Error mapping file: ");

  if((dest =  mmap(NULL, filesize, PROT_WRITE, MAP_SHARED, fd_out, 0)) == (void*)-1)
    end_gracefully("Error mapping file: ");

  memcpy(dest, src, filesize);

  munmap(src, filesize);
  munmap(dest, filesize);

  close(fd_in);
  close(fd_out);

  return;
}
