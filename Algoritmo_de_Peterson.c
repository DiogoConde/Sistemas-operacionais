#include <stdio.h>
#include <pthread.h>
void* processo(void *s);
int flag[2];
int turno,count=0,mode=0;
const int MAX = 1e9;
int main(){
 
  printf("\nAlgoritmo de Peterson\n");
  pthread_t p1,p2,p3,p4;
  printf("\nPrimeiro sem Lock\n");
  pthread_create(&p1, NULL, processo, (void*)0);
  pthread_create(&p2, NULL, processo, (void*)1);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("Contagem real: %d | Contagem esperada: %d\n",count, MAX*2);
  printf("\n\nAgora com Lock\n");
  count = 0;
  mode = 1;
  void lock_init();
  pthread_create(&p3, NULL, processo, (void*)0);
  pthread_create(&p4, NULL, processo, (void*)1);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  printf("Contagem real: %d | Contagem esperada: %d\n",count, MAX*2);
return 0;
}
void lock_init(){
  flag[0] = flag[1] = 0;
  turno = 0;
}
void lock(int atual){
  flag[atual] = 1;
  turno = 1-atual;
  while (flag[1-atual]==1 && turno==1-atual) ;
}
void unlock(int atual){
  flag[atual] = 0;
}
void* processo(void *s){
  int i = 0;
  int atual = (int *)s;
  printf("Processo : %d\n", atual);
  if(mode == 1){
      lock(atual);}
  for (i=0; i<MAX; i++){
      count++;}
  if(mode == 1){
      unlock(atual);}
}
