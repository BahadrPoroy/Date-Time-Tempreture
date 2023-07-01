#include <Test.h>
#include <virtuabotixRTC.h>
#include <dht11.h>
#include <U8glib.h>
#include <EEPROM.h>

// I/O pin and device setups

#define DHT11PIN 2
virtuabotixRTC myRTC(6, 7, 8);
dht11 DHT;
#define u8g_logo_width 90
#define u8g_logo_height 20

const unsigned char u8g_logo_bits[] U8G_PROGMEM = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0xC0, 0xC3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0xC0, 0xC3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0xC0, 0xC3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0xC0, 0xC3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
  0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 
};

int maxAddr = 288; //maxAddr Calculation: 24 hours x 60 minutes / recording frequency (In this example my frequency is 5 minutes)
int p, addr = 0;
int sec = 50, mnt = 28, clk = 15, dayofweek = 6, dd = 24, mm = 6, yyyy = 2023; //Date and time variables
float ort_sck;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

// Date page

void sayfaTarih() {
  myRTC.updateTime();
  u8g.drawFrame(2,1,126,63);
  u8g.setPrintPos(10, 60);

  //Names of days printer

  if (myRTC.dayofweek == 1) {
    u8g.print("Pazartesi");
  } else if (myRTC.dayofweek == 2) {
    u8g.print("Sali");
  } else if (myRTC.dayofweek == 3) {
    u8g.print("Carsamba");
  } else if (myRTC.dayofweek == 4) {
    u8g.print("Persembe");
  } else if (myRTC.dayofweek == 5) {
    u8g.print("Cuma");
  } else if (myRTC.dayofweek == 6) {
    u8g.print("Cumartesi");
  } else {
    u8g.print("Pazar");
  }

  //Day of month printer

  u8g.setPrintPos(10, 40);
  if (myRTC.dayofmonth > 0 && myRTC.dayofmonth <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.dayofmonth);
  u8g.print("/");
  if (myRTC.month > 0 && myRTC.month <= 9) {
    u8g.print("0");
  }

  //Month printer

  u8g.print(myRTC.month);
  u8g.print("/");
  u8g.print(myRTC.year);
  
  //Clock Printer

  u8g.setPrintPos(10, 20);
  if (myRTC.hours >= 0 && myRTC.hours <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.hours);
  u8g.print(":");
  if (myRTC.minutes >= 0 && myRTC.minutes <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.minutes);

  //Weather page

}
void sayfaHava() {
  u8g.drawFrame(2,1,126,63);
  int chk = DHT.read(DHT11PIN);
  u8g.setPrintPos(10, 20);
  u8g.print("SICAKLIK: ");
  u8g.print(DHT.temperature);
  u8g.print("C");
  u8g.setPrintPos(10, 40);
  u8g.print("24H ORT: ");
  u8g.print(ort_sck);
  u8g.setPrintPos(10, 60);
  u8g.print("NEM: %");
  u8g.print(DHT.humidity);
}

void sayfaMarka() {
u8g.drawFrame(2,1,126,63);
u8g.drawXBMP(19, 22, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
}

//Page's settings

const int sayfaSayisi = 3;
void (*sayfalar[sayfaSayisi])() = {sayfaMarka, sayfaHava, sayfaTarih};

void setup() {
  //myRTC.setDS1302Time(sec, mnt, clk, dayofweek, dd, mm, yyyy); //Just set the time by running it on the first installation, then comment line and upload again
  myRTC.updateTime();
  // TIMER 1 for interrupt frequency 0.40000512006553685 Hz:
  cli();       // stop interrupts
  TCCR1A = 0;  // set entire TCCR1A register to 0
  TCCR1B = 0;  // same for TCCR1B
  TCNT1 = 0;   // initialize counter value to 0
  // set compare match register for 0.40000512006553685 Hz increments
  OCR1A = 31249;  // = 16000000 / (1024 * 0.40000512006553685) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();  // allow interrupts
  Serial.begin(9600);
  int chk = DHT.read(DHT11PIN);
  u8g.setFont(u8g_font_unifont);
  p = 0;
  for (int i = 0; i < maxAddr; i++) {
    ort_sck = (float)(ort_sck + EEPROM.read(i)) / 2.0;
  }
}

ISR(TIMER1_COMPA_vect) {
  //interrupt commands for TIMER 1 here
  u8g.firstPage();
  do {
    (*sayfalar[p])();
  } while (u8g.nextPage());
  p = (p + 1) % sayfaSayisi;
}

bool writed = false;

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
}