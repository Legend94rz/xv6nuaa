#include "types.h"
#include "stat.h"
#include "user.h"

//you need to implement these system calls first
extern int alloc_sem(int);
extern int wait_sem(int);
extern int signal_sem(int);
extern int dealloc_sem(int);

void compute(int sem){//wait on a semaphore, print something, and then signal the semaphore
int pid=getpid(),i=0;
sleep(3);
if((wait_sem(sem))<0){
  printf(1,"wait error, pid=%d, sem=%d\n",pid,sem);
  return;
}
printf(1,"pid: %d in\n ",pid);
for(i=0;i<20;i++){
  printf(1,"-%d-",pid);
  sleep(3);
}
printf(1,"\npid=%d leaving\n\n",pid,sem);
if(signal_sem(sem)<0){
  printf(1,"signal error, pid=%d, sem=%d\n",pid,sem);
  return;
}
}

int
main(int argc, char *argv[])
{
 //create 3 semaphores with different initial values
 int s[3],i,j;
 for(i=0;i<3;i++){
   if((s[i]=alloc_sem(i+1))<0){
     printf(1,"error creating semaphore, please debug\n");
     return -1;
   }
 } 
 printf(1,"created semaphores with indices %d %d %d \n",s[0],s[1],s[2]);


for(i=0;i<3;i++){//test the semaphores one by one
   printf(1,"testing semaphore %d with initial value %d\n",s[i],i+1);
   for(j=0;j<5;j++){//create 5 children
     if(fork()==0){//children
       compute(s[i]);
     return 0;
     }
   }
  for(j=0;j<5;j++) wait();//wait for five children to die
}
 
printf(1,"normal test done\n");
printf(1,"testing dealloc_sem\n");
if(fork()==0){
     printf(1,"pid=%d is going to wait on sem %d three times\n",getpid(),s[0]);
     if(wait_sem(s[0])<=0){printf(1,"first wait fail\n");return 0;}
     printf(1,"pid=%d wait on sem %d: first success\n",getpid(),s[0]);

     if((wait_sem(s[0]))<=0){printf(1,"second wait fail\n");return 0;}
     printf(1,"pid=%d wait on sem %d: second success (should not be here)\n",getpid(),s[0]);

     if((wait_sem(s[0]))<=0){printf(1,"third wait fail (should not be here)\n");return 0;}
     printf(1,"pid=%d wait on sem %d: third success (absolutely not be here)\n",getpid(),s[0]);
     return 0;
}
sleep(100);
dealloc_sem(s[0]);
dealloc_sem(s[1]);
dealloc_sem(s[2]);
wait();
printf(1,"parent leaving \n");
return 0;
 
}
