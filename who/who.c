//who program

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>  //for utmp related work
#include<fcntl.h> //for open
#include<time.h>

void main(){
  struct utmp utmp_record; 

  //open the utmp file for reading
  int fd;  //file descriptor
  fd = open(UTMP_FILE, O_RDONLY);
  if(fd == -1){
    perror("Error in opening UTMP_FILE: ");  
    exit(1);
  }

  //until end of file keep reading from the file
  int status;
  int size_utmp_record = sizeof(struct utmp);
  while(1){
    status = read(fd, (void*)(&utmp_record), size_utmp_record);
    if(status == -1){
      perror("Error in reading UTMP_FILE: ");
      exit(1);
    }
    else if(status == 0){
      break;
    }  
    else if(status == size_utmp_record){
      //actual work here
      if(utmp_record.ut_type == USER_PROCESS){
	printf("%s %12s", utmp_record.ut_user, utmp_record.ut_line);
	printf("\t%12.12s\n", ctime(&utmp_record.ut_time) + 4);
      }
    }
  }

  close(fd);

  return;
}
