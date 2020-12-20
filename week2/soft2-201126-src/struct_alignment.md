#課題1
`struct_alignment.c`を実行すると以下のようになった。
````
tag(char):	0x7ffee0d32840			1 -> 4
id(int):	0x7ffee0d32844			4
name(char):	0x7ffee0d32848			100
age(int):	0x7ffee0d328ac			4
height(double):	0x7ffee0d328b0		8
weight(double):	0x7ffee0d328b8		8
size:	128

tag(char):	0x7ffee0d328c0			1 -> 4
id(int):	0x7ffee0d328c4			4
name(char):	0x7ffee0d328c8			100
age(int):	0x7ffee0d3292c			4
height(double):	0x7ffee0d32930		8
weight(double):	0x7ffee0d32938		8
size:	128

id(int):	0x7ffee0d32940			4
name(char):	0x7ffee0d32944　			100
age:(double)	0x7ffee0d329a8		8
height(double):	0x7ffee0d329b0		8
weight(double):	0x7ffee0d329b8		8
tag(char):	0x7ffee0d329c0			1 -> 8
size:	136

id(int):	0x7ffee0d329c8			4
name(char):	0x7ffee0d329cc			100
age(int):	0x7ffee0d32a30			4 -> 8
height(double):	0x7ffee0d32a38		8
weight(double):	0x7ffee0d32a40		8
size:	128

id(int):	0x7ffee0d32a48			4
name(char):	0x7ffee0d32a4c			100
age(int):	0x7ffee0d32ab0			4 -> 8
height(double):	0x7ffee0d32ab8		8
weight(double):	0x7ffee0d32ac0		8
size:	128
````
右の数字は、型のバイト数を表している。パディングは、そこまでのメンバ変数の合計が、そのメンバ変数の型のバイト数の倍数になるように調節されていることがわかる。また、それぞれの構造体の最初の値が8の倍数となるように、それぞれの構造体の合計バイト数が8の倍数となるように調整されていることもわかる。