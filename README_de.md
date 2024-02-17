[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TEA5767
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tea5767/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Das TEA5767 ist ein elektronisch abgestimmtes Single-Chip-UKW-Stereoradio für Niederspannungsanwendungen mit vollständig integrierter ZF-Selektivität (Zwischenfrequenz) und Demodulation. Das Radio ist völlig anpassungsfrei und benötigt nur ein Minimum an kleinen und kostengünstigen externen Komponenten. Das Radio kann auf die UKW-Bänder in Europa, den USA und Japan eingestellt werden.

LibDriver TEA5767 ist der voll funktionsfähige Treiber von TEA5767, der von LibDriver gestartet wurde. Er bietet FM-Suche, FM-Wiedergabe und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TEA5767-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TEA5767 IIC.

/test enthält den Testcode des LibDriver TEA5767-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TEA5767-Beispielcode.

/doc enthält das LibDriver TEA5767-Offlinedokument.

/Datenblatt enthält TEA5767-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tea5767/index.html](https://www.libdriver.com/docs/tea5767/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.