#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saru(){
  char buf[16];
  int secret = 0;


  gets(buf);

  if (secret == 0xaabbccdd){
    puts("flag is ...");
  }else{
    printf("buf[] = %s\n", buf);
    printf("The secret is %x\n", secret);
  }
}

int main(int argc, char **argv){
  saru();

  return 0;
}

