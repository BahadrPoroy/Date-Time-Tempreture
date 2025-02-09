void bekle(int sure) {
  lastMillisAyar = millis();
  nowMillisAyar = millis();
  while ((nowMillisAyar - lastMillisAyar) < sure) {
    nowMillisAyar = millis();
  }
}

void zamanAyarla(int saat, int dakika, int saniye, int gun, int ay, int yil) {
  myRTC.setDS1302Time(saniye, dakika, saat, gun, myRTC.dayofmonth, ay, yil);
}

void saatAyar() {
  u8g.setFont(u8g_font_fur14);
  myRTC.updateTime();

  char saat[6];
  sprintf(saat, "%02d:  ", myRTC.hours);
  ortaliMetin(saat, 128, 64);
  if (digitalRead(btSet)) {
    zamanAyarla((myRTC.hours + 1) % 24, myRTC.minutes, myRTC.seconds, myRTC.dayofweek, myRTC.month, myRTC.year);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 1;
    ayar();
  }
}

void dakikaAyar() {
  myRTC.updateTime();

  char dakika[6];
  sprintf(dakika, "  :%02d", myRTC.minutes);
  ortaliMetin(dakika, 128, 64);

  if (digitalRead(btSet)) {
    zamanAyarla(myRTC.hours, (myRTC.minutes + 1) % 60, myRTC.seconds, myRTC.dayofweek, myRTC.month, myRTC.year);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 2;
    ayar();
  }
}

void gunAyar() {
  myRTC.updateTime();

  spacing = (128 - u8g.getStrPixelWidth(day[myRTC.dayofweek - 1])) / 2;
  u8g.setPrintPos(spacing, 25);
  u8g.print(day[myRTC.dayofweek - 1]);

  if (digitalRead(btSet)) {
    zamanAyarla(myRTC.hours, myRTC.minutes, myRTC.seconds, (myRTC.dayofweek + 1) % 7, myRTC.month, myRTC.year);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 3;
    ayar();
  }
}

void ay_gunuAyar() {
  myRTC.updateTime();

  char tarih[11];
  sprintf(tarih, "%02d/  /    ", myRTC.dayofmonth);
  ortaliMetin(tarih, 128, 64);

  if (digitalRead(btSet)) {
    int yeniGun = (myRTC.dayofmonth + 1) % 31;
    if (yeniGun == 0) yeniGun = 31;
    zamanAyarla(myRTC.hours, myRTC.minutes, myRTC.seconds, myRTC.dayofweek, myRTC.month, myRTC.year);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 4;
    ayar();
  }
}

void ayAyar() {
  myRTC.updateTime();

  char tarih[11];
  sprintf(tarih, "  /%02d/    ", myRTC.month);
  ortaliMetin(tarih, 128, 64);

  if (digitalRead(btSet)) {
    int yeniAy = (myRTC.month + 1) % 12;
    if (yeniAy == 0) yeniAy = 12;
    zamanAyarla(myRTC.hours, myRTC.minutes, myRTC.seconds, myRTC.dayofweek, yeniAy, myRTC.year);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 5;
    ayar();
  }
}

void yilAyar() {
  myRTC.updateTime();

  char tarih[11];
  sprintf(tarih, "  /  /%d", myRTC.year);
  ortaliMetin(tarih, 128, 64);

  if (digitalRead(btSet)) {
    zamanAyarla(myRTC.hours, myRTC.minutes, myRTC.seconds, myRTC.dayofweek, myRTC.month, myRTC.year + 1);
    bekle(200);
  } else if (digitalRead(btOk)) {
    bekle(200);
    is_changed = 6;
    setting = false;
    ayar();
  }
}
