# ソートアルゴリズム可視化ツール (バブルソート)

このプロジェクトは、C 言語と SDL2 ライブラリを使用して、バブルソートアルゴリズムの動作を視覚的に表示するツールです。配列の要素が棒グラフとして描画され、ソートの過程で要素が比較・交換される様子がアニメーションとして表示されます。
現在はバブルソートのみの実装ですが、以降ヒープソートやクイックソート等も追加し、UI/UX も改善する予定です。

## 機能

-  配列の要素を棒グラフとして表示
-  バブルソートアルゴリズムのステップごとの可視化
-  比較中の要素を赤色でハイライト表示
-  ソートの進行状況をアニメーションで確認

## 動作環境

-  **OS**: macOS, Linux, Windows (SDL2 がサポートされている環境)
-  **コンパイラ**: GCC (または Clang など)
-  **ライブラリ**: SDL2

## 必要なもの

プログラムを実行するには、[SDL2 ライブラリ](https://www.google.com/search?q=https://www.libsdl.org/download-2.0.php) がシステムにインストールされている必要があります。

### SDL2 のインストール例

-  **macOS (Homebrew を使用)**:

   ```bash
   brew install sdl2
   ```

-  **Ubuntu / Debian**:

   ```bash
   sudo apt-get install libsdl2-dev
   ```

-  **Windows**:
   SDL の公式サイトから開発ライブラリをダウンロードし、ご使用のコンパイラ（MinGW, Visual Studio など）に合わせて設定してください。

## ビルドと実行

1. **ソースコードの保存**:
   提供された C 言語のコードを `main.c` という名前で保存します。

2. **コンパイル**:
   ターミナルを開き、`main.c` があるディレクトリに移動して、以下のコマンドでコンパイルします。

   -  **macOS / Linux**:

      ```bash
      gcc main.c -o sorting_visualizer `sdl2-config --cflags --libs`
      ```

      (`sdl2-config` は SDL2 のコンパイル・リンクに必要なフラグを自動で出力します。)

   -  **Windows (MinGW-w64 を使用する場合の例)**:

      ```bash
      gcc main.c -o sorting_visualizer -lmingw32 -lSDL2main -lSDL2
      ```

      (SDL2 のヘッダファイルとライブラリファイルへのパスを適切に設定している必要があります。)

3. **実行**:
   コンパイルが成功すると、`sorting_visualizer` (Windows では `sorting_visualizer.exe`) という実行可能ファイルが生成されます。これを実行します。

   ```bash
   ./sorting_visualizer
   ```

   (Windows では `sorting_visualizer.exe` または単に `sorting_visualizer`)

   プログラムが起動すると、バブルソートの可視化ウィンドウが表示され、ソートのプロセスがアニメーションで表示されます。ウィンドウを閉じるとプログラムは終了します。
