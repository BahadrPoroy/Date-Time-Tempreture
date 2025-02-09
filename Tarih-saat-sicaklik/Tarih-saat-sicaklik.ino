#include <Test.h>
#include <virtuabotixRTC.h>
#include <dht11.h>
#include <U8glib.h>
#include <EEPROM.h>

// I/O pin and device setups

#define DHT11PIN 2
#define btSet 3
#define btOk 4
virtuabotixRTC myRTC(6, 7, 8);
dht11 DHT;

#define pageCount 3                                                              //number of pages variable

int maxAddr = 288;  //maxAddr Calculation: 24 hours x 60 minutes / recording frequency (In this example my frequency is 5 minutes)
int p, addr = 0;
int nowMillis = 0, lastMillis = 0, nowMillisAyar = 0, lastMillisAyar = 0;       //time control variables

float ort_sck;

byte spacing;
char* day[] = { "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar" };

byte is_changed = 0;  //0: hours, 1: minutes, 2: dayofweek, 3: dayofmonth, 4: month, 5: year

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

//Page's settings

void setup() {
  pinMode(btSet, INPUT);
  pinMode(btOk, INPUT);
  myRTC.updateTime();
  int chk = DHT.read(DHT11PIN);
  u8g.begin();
  u8g.setFont(u8g_font_fur14);
  p = 0;
  for (int i = 0; i < maxAddr; i++) {
    ort_sck = (float)(ort_sck + EEPROM.read(i)) / 2.0;
  }
  nowMillis = millis();
  while ((lastMillis - nowMillis) < 3000) {
    u8g.firstPage();
    do {
      sayfaMarka();
    } while (u8g.nextPage());
    lastMillis = millis();
  }
}

bool writed = false;
bool setting = false;

void ayar() {
  setting = true;
  
  void (*ayarFonksiyon[])() = {saatAyar, dakikaAyar, gunAyar, ay_gunuAyar, ayAyar, yilAyar};

  if (is_changed >= 0 && is_changed <= 5) {
    u8g.firstPage();
    do {
      ayarFonksiyon[is_changed]();
    } while (u8g.nextPage());
  } else if (is_changed == 6) {
    is_changed = 0;
    setting = false;
  }
}

void pageChange() {
  lastMillis = millis();
  void (*sayfa[])() = {sayfaHava, sayfaTarih, sayfaSaat}; // Fonksiyon işaretçileri dizisi
    u8g.firstPage();
    do {
      sayfa[p]();
    } while (u8g.nextPage());
}


void ortaliMetin(const char* metin, int ekranGenislik, int ekranYukseklik) {
  int textWidth = u8g.getStrPixelWidth(metin);                  // Metin genişliği
  int textHeight = u8g.getFontAscent() - u8g.getFontDescent();  // Metin yüksekliği

  int x = (ekranGenislik - textWidth) / 2;    // Yatay ortalama
  int y = (ekranYukseklik + textHeight) / 2;  // Dikey ortalama

  u8g.setPrintPos(x, y);
  u8g.print(metin);
}


void loop() {
  myRTC.updateTime();
  int chk = DHT.read(DHT11PIN);
  if (SaatTest(myRTC.minutes) && !writed) {
    addr = (addr + 1) % maxAddr;
    EEPROM.update(addr, DHT.temperature);
    writed = true;
    ort_sck = 0;
    for (int i = 0; i < maxAddr; i++) {
      ort_sck = (float)(ort_sck + EEPROM.read(i)) / 2.0;
    }
  } else if (!SaatTest(myRTC.minutes)) {
    writed = false;
  }
  nowMillis = millis();
  if ((nowMillis - lastMillis >= 2500) && !setting) {
    p = (p + 1) % pageCount;
    pageChange();
  }
  if (digitalRead(btSet) || digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    ayar();
  }
}