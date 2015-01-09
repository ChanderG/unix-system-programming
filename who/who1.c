//who program ver 2

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>  //for utmp related work
#include<time.h>

void main(){
  struct utmp* utmp_record; 

  setutent();

  while(1){
    utmp_record = getutent_r();

    if(utmp_record == NULL){
      break;
    }
    else 
      //actual work here
      if(utmp_record->ut_type == USER_PROCESS){
	printf("%s %12s", utmp_record->ut_user, utmp_record->ut_line);
	printf("\t%12.12s\n", ctime(&utmp_record->ut_time) + 4);
      }
    }

  endutent();
  return;
}
