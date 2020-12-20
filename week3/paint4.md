# ソフトウェアII 第3週 課題

#### 発展課題について

今回の発展課題では、長方形と円の塗りつぶし機能、色を変える機能、そして表示モードを変える機能を搭載しました。

### 長方形と円の塗りつぶし機能

授業内で作成した`rect`という機能をベースに、`crect`という関数を作りました。引数の指定方法は`rect`と同じですが、`crect`を使うと中が塗りつぶされます。

```
* > crect x0 y0 width height
```

同様に、`ccircle`という関数も作りました。

```
* > ccircle x0 y0 r
```

関数冒頭の`c`はcolorのcです。

### 色を変える機能

表示の色を変える機能を付けました。色の変更も`commands`として保存されているため、ストロークごとの色が記憶されており、`undo`や`save`などにも対応しています。

色を変更するには、`chcol`を使います。

```
* > chcol [色識別用の文字]
```

なお、使える色は以下です。

```
b: 黒
l: 青
r: 赤
g: 緑
y: 黄
w: 白
```

### 表示モードを変える機能

terminalでは文字色だけでなく背景色を変えることもできるので、bitmap風の画像を作成したい場合の`fillmode`というオプションを追加しました。shellで`fillmode`を最後につけると塗りつぶされた表示になります。以下は例です。

##### 通常モード

````
$ ./paint 80 40 doraemon.txt
````

<img src="/Users/masayukifujita/Desktop/Screen Shot 2020-12-11 at 15.14.06.png" alt="Screen Shot 2020-12-11 at 15.14.06" style="zoom:25%;" />

##### 塗りつぶしモード

````
$ ./paint 80 40 doraemon.txt fillmode
````

<img src="/Users/masayukifujita/Desktop/Screen Shot 2020-12-11 at 15.13.56.png" alt="Screen Shot 2020-12-11 at 15.13.56" style="zoom:25%;" />

ドラえもんのデータは`doraemon.txt`に入っています。

ダークモードで表示するとドラえもんもダークサイドへ行ってしまうので注意してください。