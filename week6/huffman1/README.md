```shell
$ make
$ bin/huffman1 news.txt
```

で`news.txt.dat`というファイルが生成されます。ハフマン符号を用いてバイナリデータとして圧縮したものです。変換表もファイル内に組み込まれています。ファイルサイズもきちんと小さくなっているようです。

```shell
$ gcc decode.c -o decoder
$ ./decoder news.txt.dat
```

で、ターミナルに解答したファイルが読み込まれます。実装が大変でしたがちゃんとできたので達成感があります。