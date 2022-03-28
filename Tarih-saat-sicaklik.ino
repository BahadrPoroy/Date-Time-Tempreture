#include <virtuabotixRTC.h>
#include <dht11.h>
#include <U8glib.h>

#define DHT11PIN 2
virtuabotixRTC myRTC(6, 7, 8);
int dly = 5000;
dht11 DHT;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

void sayfaTarih(){
  myRTC.updateTime(); 
  u8g.setPrintPos(20, 20); 
  if(myRTC.dayofweek==1){
    u8g.print("Pazartesi");
  }
  else if(myRTC.dayofweek==2){
    u8g.print("Sali");
  }
  else if(myRTC.dayofweek==3){
    u8g.print("Carsamba");
  }
  else if(myRTC.dayofweek==4){
    u8g.print("Persembe");
  }
  else if(myRTC.dayofweek==5){
    u8g.print("Cuma");
  }
  else if(myRTC.dayofweek==6){
    u8g.print("Cumartesi");
  }
  else{
    u8g.print("Pazar");
  }
  u8g.setPrintPos(10, 40); 
  if(myRTC.dayofmonth>0 && myRTC.dayofmonth<=9){
    u8g.print("0");
  }
  u8g.print(myRTC.dayofmonth);
  u8g.print("/");
  if(myRTC.month>0 && myRTC.month<=9){
    u8g.print("0");
  }
  u8g.print(myRTC.month);
  u8g.print("/");
  u8g.print(myRTC.year);
  u8g.setPrintPos(10, 60);
  if(myRTC.hours>=0 && myRTC.hours<=9){
    u8g.print("0");
  } 
  u8g.print(myRTC.hours);
  u8g.print(":");
  if(myRTC.minutes>=0 && myRTC.minutes<=9){
    u8g.print("0");
  } 
  u8g.print(myRTC.minutes);
}
void sayfaHava(){
  int chk = DHT.read(DHT11PIN);
  u8g.setPrintPos(10, 20); 
  u8g.print("SICAKLIK: ");
  u8g.print(DHT.temperature);
  u8g.print(" C");
  u8g.setPrintPos(10, 40); 
  u8g.print("NEM: %");
  u8g.print(DHT.humidity);
}
const int sayfaSayisi = 2;
int p;
void (*sayfalar[sayfaSayisi])() = { sayfaTarih, sayfaHava};
int sure [sayfaSayisi] = { 2500, 2500};

void setup() {
  Serial.begin(9600);
  int chk = DHT.read(DHT11PIN);
  u8g.setFont(u8g_font_unifont);
  p = 0;
}


void loop() {
u8g.firstPage();
  do {  
    (*sayfalar[p])();
  } while( u8g.nextPage() );
  delay(sure[p]);
  p = p+1;
  if (p == sayfaSayisi)
    p=0;
}
