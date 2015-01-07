#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>

#define LINELEN 512
#define SCREEN_SIZE 23
#define SPACEBAR 1
#define RETURN 2
#define QUIT 3
#define INVALID 4

//actual function
void do_more_of(FILE* fp);

//get user input
int get_user_intput(FILE *fp);

void get_tty_size(FILE *fp_tty, int *no_rows){
  struct winsize window_arg;
  if(ioctl(fileno(fp_tty), TIOCGWINSZ, &window_arg) == -1)
    exit(1);
  *no_rows = window_arg.ws_row;  
  //*no_cols = window_arg.ws_col;  
  return;
}

int main(int argc, char *argv[]){
  FILE *fp;
  int i = 1;
  if(argc == 1)
    do_more_of( stdin );
  else
    while(i < argc){
      fp = fopen( argv[i], "r");
      if( fp != NULL ){
        do_more_of(fp);
	fclose(fp);
      }	
      else 
        printf("Skipping %s\n", argv[i]);
      i++;
    }
  return 0;
}

void do_more_of(FILE* fp){
  char line[LINELEN];
  int no_of_lines;
  int getmore = 1;
  int reply;
  FILE *fp_tty = fopen("/dev/tty", "r");

  if(fp_tty == NULL) exit(1);

  int ttyrows;
  get_tty_size(fp_tty, &ttyrows);
  no_of_lines = ttyrows;

  while(getmore && fgets(line, LINELEN, fp)){
    if(no_of_lines == 0){
      reply = get_user_intput(fp_tty);
      switch(reply){
        case SPACEBAR: no_of_lines = ttyrows;
	               printf("\033[1A\033[2K\033[1G");
	               break;
	case RETURN: no_of_lines++;
		     printf("\033[1A\033[2K\033[1G");
	             break;
	case QUIT: getmore = 0;
		   printf("\033[1A\033[2K\033[1B\033[7D");
	           break;
	default: break;
      }
    }
    if(fputs(line, stdout) == EOF) exit(1);
    no_of_lines--;
  }
  return;
}

int get_user_intput(FILE *fp){
  int tty_rows;

  get_tty_size(fp, &tty_rows);
  printf("\033[%d;1H", tty_rows);

  int c;
  printf("\033[7m more? \033[m");
  while((c = fgetc(fp)) != EOF) 
    switch(c){
      case ' ' : return SPACEBAR;
      case 'q' : return QUIT;
      case '\n' : return RETURN;
      defualt: return INVALID;
    }
}
