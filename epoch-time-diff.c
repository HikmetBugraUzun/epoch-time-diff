#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini tutan struct
struct DateTime {
    int year, month, day, hour, minute, second;
};

// Tarih ve saat bilgisini farkli formatlarda saklamak için union
union EpochConverter {
    struct DateTime dt;
    time_t epoch;
};

// Kullanicidan tarih ve saat bilgisi al
void getDateTime(struct DateTime *dt) {
    printf("Yil, Ay, Gun, Saat, Dakika, Saniye girin: ");
    scanf("%d %d %d %d %d %d", &dt->year, &dt->month, &dt->day, &dt->hour, &dt->minute, &dt->second);
}

// Tarih ve saat bilgisini epoch zamanina çevir
time_t convertToEpoch(struct DateTime dt) {
    struct tm t = {0};
    t.tm_year = dt.year - 1900;
    t.tm_mon = dt.month - 1;
    t.tm_mday = dt.day;
    t.tm_hour = dt.hour;
    t.tm_min = dt.minute;
    t.tm_sec = dt.second;
    return mktime(&t);
}

// Zaman farkini yil, ay, gun, saat, dakika ve saniye olarak hesapla
void convertSecondsToTime(double seconds) {
    int years = seconds / (60 * 60 * 24 * 365);
    seconds -= years * (60 * 60 * 24 * 365);
    int months = seconds / (60 * 60 * 24 * 30);
    seconds -= months * (60 * 60 * 24 * 30);
    int days = seconds / (60 * 60 * 24);
    seconds -= days * (60 * 60 * 24);
    int hours = seconds / (60 * 60);
    seconds -= hours * (60 * 60);
    int minutes = seconds / 60;
    seconds -= minutes * 60;
    
    printf("\nİki tarih arasindaki zaman farki: %d yil, %d ay, %d gun, %d saat, %d dakika, %.0f saniye\n", 
           years, months, days, hours, minutes, seconds);
}

int main() {
    union EpochConverter time1, time2;
    
    printf("Birinci tarihi girin:\n");
    getDateTime(&time1.dt);
    time1.epoch = convertToEpoch(time1.dt);
    printf("Epoch zamani: %ld\n", time1.epoch);
    
    printf("\nİkinci tarihi girin:\n");
    getDateTime(&time2.dt);
    time2.epoch = convertToEpoch(time2.dt);
    printf("Epoch zamani: %ld\n", time2.epoch);
    
    // Zaman farkini hesapla
    double diff = difftime(time2.epoch, time1.epoch);
    convertSecondsToTime(diff);
    
    return 0;
}
