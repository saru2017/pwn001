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

まずは何も考えずにコンパイルしてみた。

```bash-session
$ gcc overflow01.c -o overflow01
overflow01.c: In function ‘saru’:
overflow01.c:9:3: warning: implicit declaration of function ‘gets’; did you mean ‘fgets’? [-Wimplicit-function-declaration]
   gets(buf);
   ^~~~
   fgets
/tmp/ccrGzHYJ.o: In function `saru':
overflow01.c:(.text+0x2b): warning: the `gets' function is dangerous and should not be used.
$
```

gets危険だから使うなというwarningは出るけど一応コンパイルはできる。
サーバとして起動してみてtelnetで長い文字列を送り付けてみた。

```bash-sessoin
$ telnet localhost 28080
Trying ::1...
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*** stack smashing detected ***: <unknown> terminated
Connection closed by foreign host.
$
```

するとstack smashing protection (SSP)のせいで落ちる。
SSPはcanaryを使ってスタックの書き換えを検知するやつらしい。
変数の順番も入れ替わるのか？

SSPを無効にするために-fno-stack-protectorオプションをつけてみた。

```bash-session
saru@lucifen:~/pwn001$ gcc overflow01.c -fno-stack-protector -o overflow01
overflow01.c: In function ‘saru’:
overflow01.c:9:3: warning: implicit declaration of function ‘gets’; did you mean ‘fgets’? [-Wimplicit-function-declaration]
   gets(buf);
   ^~~~
   fgets
/tmp/cc7I14bT.o: In function `saru':
overflow01.c:(.text+0x1c): warning: the `gets' function is dangerous and should not be used.
saru@lucifen:~/pwn001$
```

そしてtelnetで攻撃。

```bash-session
saru@lucifen:~/pwn001$ telnet localhost 28080
Trying ::1...
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
buf[] = aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
The secret is d6161
Connection closed by foreign host.
saru@lucifen:~/pwn001$
```

無事にsecretを書き換えられたっぽい。

-fno-stack-protectorオプションを付けたときとつけなかったときのsecretとbufのアドレスが気になるのでチェックしてみた。

まずはSSPありバージョン

```bash-session
saru@lucifen:~/pwn001$ ./overflow01
buf address = f77afc20
secret address = f77afc1c
aaa
buf[] = aaa
The secret is 0
saru@lucifen:~/pwn001$
```

次にSSPなしバージョン

```bash-session
saru@lucifen:~/pwn001$ ./overflow01
buf address = 4c09df90
secret address = 4c09df8c
aaa
buf[] = aaa
The secret is 0
saru@lucifen:~/pwn001$
```

かわらない？
ということはSSPありでも書き換えられる？

0xf77afc20 - 0xf77afc1c = 4

0x4c09df90 - 0x4c09df8c = 4

なんかprintfでアドレス出力しているせいで配置が変わっているみたい．．．

## exploit codeを書いてみる

良く分からないのでとりあえずprintfでsecretの書き換えが成功している状態のものをexploit codeで書き換えるのを試してみることにする。




# 参考サイト

[PWN入門](https://gist.github.com/matsubara0507/72dc50c89200a09f7c61)

