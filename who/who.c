//who program

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>  //for utmp related work
#include<fcntl.h> //for open

void main(){
   
  //open the utmp file for reading
  int fd;  //file descriptor
  fd = open(UTMP_FILE, O_RDONLY);
  if(fd == -1){
    perror("Error in opening UTMP_FILE: ");  
    exit(1);
  }

  //until end of file keep reading from the file

  return;
}
