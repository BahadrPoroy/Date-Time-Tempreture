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


int maxAddr = 288;  //maxAddr Calculation: 24 hours x 60 minutes / recording frequency (In this example my frequency is 5 minutes)
int p, addr = 0;
int sec = 00, mnt = 28, clk = 15, dayofweek = 6, dd = 24, mm = 6, yyyy = 2023;  //Date and time variables
int nowMillis = 0, lastMillis = 0, nowMillisAyar = 0, lastMillisAyar = 0;       //time control variables
int pageCount = 2;                                                              //number of pages variable
float ort_sck;

int spacing;
char *day[] = { "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar" };

int is_changed = 0;  //0: hours, 1: minutes, 2: dayofweek, 3: dayofmonth, 4: month, 5: year

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

//Page's settings

void setup() {
  //myRTC.setDS1302Time(sec, mnt, clk, dayofweek, dd, mm, yyyy);  //Just set the time by running it on the first installation, then comment line and upload again
  pinMode(btSet, INPUT);
  pinMode(btOk, INPUT);
  myRTC.updateTime();
  Serial.begin(9600);
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
  switch (is_changed) {
    case (0):
      u8g.firstPage();
      do {
        saatAyar();
      } while (u8g.nextPage());

      break;
    case (1):
      u8g.firstPage();
      do {
        dakikaAyar();
      } while (u8g.nextPage());
      break;
    case (2):
      u8g.firstPage();
      do {
        gunAyar();
      } while (u8g.nextPage());
      break;
    case (3):
      u8g.firstPage();
      do {
        ay_gunuAyar();
      } while (u8g.nextPage());
      break;
    case (4):
      u8g.firstPage();
      do {
        ayAyar();
      } while (u8g.nextPage());
      break;
    case (5):
      u8g.firstPage();
      do {
        yilAyar();
      } while (u8g.nextPage());
      break;
    case (6):
      is_changed = 0;
      setting = false;
      break;
  }
}

void pageChange() {
  lastMillis = millis();
  switch (p) {
    case (0):
      u8g.firstPage();
      do {
        sayfaHava();
      } while (u8g.nextPage());
      break;
    case (1):
      u8g.firstPage();
      do {
        sayfaTarih();
      } while (u8g.nextPage());
      break;
  }
}

void loop() {
  myRTC.updateTime();
  Serial.println(myRTC.seconds);
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