#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_stack(void* p, int span)
{
    unsigned long int i = (unsigned long int) p - span;
    printf("0x%08x\n", p);
    for(i = p - span; i < p + span; i += 4){
	unsigned int val0, val1, val2, val3;
	char *c = (char*) i;
        val0 = (unsigned char) *(c + 0);
        val1 = (unsigned char) *(c + 1);
        val2 = (unsigned char) *(c + 2);
        val3 = (unsigned char) *(c + 3);
        printf("0x%016x: %02x %02x %02x %02x\n", i, val0, val1, val2, val3);
    }
}

void saru(){
  char buf[16];
  int secret = 1;


  gets(buf);

  if (secret == 0xaabbccdd){
    puts("flag is ...");
  }else{
    printf("buf[] = %s\n", buf);
    printf("The secret is %x\n", secret);
  }
//  printf("secret address = %0x\n", &secret);
//  printf("buf address = %0x\n", buf);
  dump_stack(&secret, 32);
}

int main(int argc, char **argv){
  saru();

  return 0;
}

