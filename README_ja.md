[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TEA5767

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tea5767/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TEA5767 は、完全に統合された中間周波数 (IF) 選択性と復調機能を備えた、低電圧アプリケーション向けの電子的に調整されたシングルチップ FM ステレオ ラジオです。 ラジオは完全に調整不要で、最小限の小型で低コストの外付け部品のみが必要です。 ラジオは、ヨーロッパ、米国、および日本の FM バンドにチューニングできます。

LibDriver TEA5767 は、LibDriver によって起動される TEA5767 のフル機能ドライバーです。FM 検索、FM 再生、およびその他の機能を提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TEA5767のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TEA5767用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TEA5767ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TEA5767プログラミング例が含まれています。

/ docディレクトリには、LibDriver TEA5767オフラインドキュメントが含まれています。

/ datasheetディレクトリには、TEA5767データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_tea5767_basic.h"

uint8_t res;
float mhz;

/* init */
res = tea5767_basic_init();
if (res != 0)
{
    return 1;
}

...

/* search up */
res = tea5767_basic_search_up()；
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

res = tea5767_basic_get_frequency(&mhz);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}
tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);

...

/* search down */
res = tea5767_basic_search_down()；
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

res = tea5767_basic_get_frequency(&mhz);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}
tea5767_interface_debug_print("tea5767: frequency is %0.2fMHz.\n", mhz);

...

/* enable mute */
res = tea5767_basic_set_mute(TEA5767_BOOL_TRUE);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* disable mute */
res = tea5767_basic_set_mute(TEA5767_BOOL_FALSE);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* set the frequency */
res = tea5767_basic_set_frequency(88.67f);
if (res != 0)
{
    (void)tea5767_basic_deinit();
    
    return 1;
}

...

/* deinit */
(void)tea5767_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/tea5767/index.html](https://www.libdriver.com/docs/tea5767/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。