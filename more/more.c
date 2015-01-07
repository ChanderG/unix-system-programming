#include<stdio.h>

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
  int no_of_lines = SCREEN_SIZE;
  int getmore = 1;
  int reply;
  FILE *fp_tty = fopen("/dev/tty", "r");

  if(fp_tty == NULL) exit(1);

  while(getmore && fgets(line, LINELEN, fp)){
    if(no_of_lines == 0){
      reply = get_user_intput(fp_tty);
      switch(reply){
        case SPACEBAR: no_of_lines = SCREEN_SIZE;
	               break;
	case RETURN: no_of_lines++;
	             break;
	case QUIT: getmore = 0;
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
