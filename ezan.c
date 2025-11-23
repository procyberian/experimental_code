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
