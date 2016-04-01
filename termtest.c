#include "types.h"
#include "user.h"

#define TOTAL_TEST_TRIALS 50

extern int fork_winner(int);

int
main(int argc, char *argv[])
{
    int *i;
    int ret = 0;
    ret=fork();
    if(ret<0){
       printf(1,"fork() failed(%d)\n",ret);
       exit();
     }else if(ret==0){//child
       i=(int *)0xffffffff;
       *i=1;          //should report error
      }else{//parent 
        
        wait();// wait for the death of the first child
        ret=fork();
        if(ret==0){//second child
           asm volatile ("jmp 0xffffffff");
        }else{//the parent
           wait();//wait for the death of the second child
        }
      } 
     return 0;   
}

