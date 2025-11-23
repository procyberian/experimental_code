/**
   MIT License

Copyright (c) 2025 PSD Authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char date[11];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(date, sizeof(date), "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    double lat = 41.0082, lon = 28.9784;
    char url[512];
    snprintf(url, sizeof(url),
        "https://api.aladhan.com/v1/timings/%s?latitude=%.4f&longitude=%.4f&method=13",
        date, lat, lon);

    printf("📅 %s - İstanbul için ezan vakitleri:\n", date);
    printf("───────────────────────────────────────────────────────────────\n");

    // Arapça, İngilizce, Türkçe eşleştirme jq içinde yapılır
    char command[2048];
    snprintf(command, sizeof(command),
        "curl -s \"%s\" | jq -r '.data.timings as $t | ["
        "{a:\"الفجر\", e:\"Fajr\", t:\"İmsak\", v:$t.Fajr},"
        "{a:\"الشروق\", e:\"Sunrise\", t:\"Güneş\", v:$t.Sunrise},"
        "{a:\"الظهر\", e:\"Dhuhr\", t:\"Öğle\", v:$t.Dhuhr},"
        "{a:\"العصر\", e:\"Asr\", t:\"İkindi\", v:$t.Asr},"
        "{a:\"المغرب\", e:\"Maghrib\", t:\"Akşam\", v:$t.Maghrib},"
        "{a:\"العشاء\", e:\"Isha\", t:\"Yatsı\", v:$t.Isha}"
        "][] | \"\\(.a) / \\(.e) / \\(.t): \\(.v)\"'",
        url);

    system(command);
    return 0;
}
