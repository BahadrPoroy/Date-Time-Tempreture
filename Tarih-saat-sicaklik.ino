#include <Test.h>
#include <virtuabotixRTC.h>
#include <dht11.h>
#include <U8glib.h>
#include <EEPROM.h>


// I/O pin and device setups

#define DHT11PIN 2
virtuabotixRTC myRTC(6, 7, 8);
dht11 DHT;

int p, addr = 0;
float ort_sck;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);


// Date page

void sayfaTarih() {
  myRTC.updateTime();
  u8g.setPrintPos(10, 20);


  //Names of days printer

  if (myRTC.dayofweek == 1) {
    u8g.print("Pazartesi");
  }
  else if (myRTC.dayofweek == 2) {
    u8g.print("Sali");
  }
  else if (myRTC.dayofweek == 3) {
    u8g.print("Carsamba");
  }
  else if (myRTC.dayofweek == 4) {
    u8g.print("Persembe");
  }
  else if (myRTC.dayofweek == 5) {
    u8g.print("Cuma");
  }
  else if (myRTC.dayofweek == 6) {
    u8g.print("Cumartesi");
  }
  else {
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
  u8g.setPrintPos(10, 60);


  //Clock Printer

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
  int chk = DHT.read(DHT11PIN);
  u8g.setPrintPos(10, 20);
  u8g.print("SICAKLIK: ");
  u8g.print(DHT.temperature);
  u8g.print("C");
  u8g.setPrintPos(10, 40);
  u8g.print("NEM: %");
  u8g.print(DHT.humidity);
  u8g.setPrintPos(10, 60);
  u8g.print("24H ORT: ");
  u8g.print(ort_sck);
}


//Page's settings

const int sayfaSayisi = 2;
void (*sayfalar[sayfaSayisi])() = {sayfaHava, sayfaTarih};

void setup() {
  myRTC.updateTime();
  // TIMER 1 for interrupt frequency 0.40000512006553685 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 0.40000512006553685 Hz increments
  OCR1A = 31249; // = 16000000 / (1024 * 0.40000512006553685) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts

  Serial.begin(9600);
  int chk = DHT.read(DHT11PIN);
  u8g.setFont(u8g_font_unifont);
  p = 0;
  ort_sck = EEPROM.read(24);
}

ISR(TIMER1_COMPA_vect) {
  //interrupt commands for TIMER 1 here
  u8g.firstPage();
  do {
    (*sayfalar[p])();
  } while ( u8g.nextPage() );
  p = (p + 1) % sayfaSayisi;
}

bool writed = false;

void loop() {
  myRTC.updateTime();
  int chk = DHT.read(DHT11PIN);
  if (SaatTest(myRTC.minutes, myRTC.seconds) && !writed) {
    addr = (addr + 1) % 24;
    EEPROM.write(addr, (float)DHT.temperature);
    writed = true;
    ort_sck = 0;
    for (int i = 0; i < 24; i++) {
      ort_sck = (float)(ort_sck + EEPROM.read(i)) / 2.0;
    }
    EEPROM.write(24, ort_sck);
  }
  else if (!SaatTest(myRTC.minutes, myRTC.seconds)) {
    writed = false;
  }
}
