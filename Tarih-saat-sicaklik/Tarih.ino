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