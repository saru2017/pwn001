# 概要

自分でPWNをいろいろ試す用のコード

# pwn_server.py

接続が来たら標準入出力を持つプログラムにプロセスを受け渡すプログラム。

# 最も単純なPWN

```c:overflow01.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saru(){
  char buf[16];
  int secret = 0;

  gets(buf);

  if (secret == 0xaabbccdd){
    puts("flag is OSAKA_UNIV_CTF");
  }else{
    printf("buf[] = %s\n", buf);
    printf("The secret is %x\n", secret);
  }
}

int main(int argc, char **argv){
  saru();

  return 0;
}
```

bufでオーバーフローを起こさせてsecretを書き換えてflagを出力させる。

まずは何も考えずにコンパイルして文字列をぶち込んでみる。




# 参考サイト

[PWN入門](https://gist.github.com/matsubara0507/72dc50c89200a09f7c61)

