

void saatAyar() {
  u8g.setFont(u8g_font_fur14);
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("23:59")) / 2;
  u8g.setPrintPos(spacing, 25);
  if (myRTC.hours >= 0 && myRTC.hours <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.hours);
  u8g.print(":  ");
  if (digitalRead(btSet)) {
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, ((myRTC.hours + 1) % 24), myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 1;
    ayar();
  }
}


void dakikaAyar() {
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("23:59")) / 2;
  u8g.setPrintPos(spacing, 25);
  u8g.print("  :");
  if (myRTC.minutes >= 0 && myRTC.minutes <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.minutes);
  if (digitalRead(btSet)) {
    myRTC.setDS1302Time(myRTC.seconds, ((myRTC.minutes + 1) % 60), myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 2;
    ayar();
  }
}

void gunAyar() {
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  switch (myRTC.dayofweek) {
    case (1):
      spacing = (128 - u8g.getStrPixelWidth(day[0])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[0]);
      break;
    case (2):
      spacing = (128 - u8g.getStrPixelWidth(day[1])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[1]);
      break;
    case (3):
      spacing = (128 - u8g.getStrPixelWidth(day[2])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[2]);
      break;
    case (4):
      spacing = (128 - u8g.getStrPixelWidth(day[3])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[3]);
      break;
    case (5):
      spacing = (128 - u8g.getStrPixelWidth(day[4])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[4]);
      break;
    case (6):
      spacing = (128 - u8g.getStrPixelWidth(day[5])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[5]);
      break;
    default:
      spacing = (128 - u8g.getStrPixelWidth(day[6])) / 2;
      u8g.setPrintPos(spacing, 25);
      u8g.print(day[6]);
      break;
  }
  if (digitalRead(btSet)) {
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, ((myRTC.dayofweek + 1) % 7), myRTC.dayofmonth, myRTC.month, myRTC.year);
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 3;
    ayar();
  }
}

void ay_gunuAyar() {
  int day;
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("11/11/2024")) / 2;
  u8g.setPrintPos(spacing, 25);
  if (myRTC.dayofmonth > 0 && myRTC.dayofmonth <= 9) {
    u8g.print("0");
  }
  u8g.print(myRTC.dayofmonth);
  u8g.print("/");

  //Month printer

  u8g.print("  /    ");

  if (digitalRead(btSet)) {
    day = (myRTC.dayofmonth + 1) % 31;
    if (day == 0) {
      day = 31;
    }
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, day, myRTC.month, myRTC.year);
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 4;
    ayar();
  }
}

void ayAyar() {
  int ay;
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("11/11/2024")) / 2;
  u8g.setPrintPos(spacing, 25);
  u8g.print("  /");
  if (myRTC.month > 0 && myRTC.month <= 9) {
    u8g.print("0");
  }

  //Month printer

  u8g.print(myRTC.month);
  u8g.print("/    ");

  if (digitalRead(btSet)) {
    ay = (myRTC.month + 1) % 12;
    if (ay == 0) {
      ay = 12;
    }
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, ay, myRTC.year);
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 5;
    ayar();
  }
}

void yilAyar() {
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("11/11/2024")) / 2;
  u8g.setPrintPos(spacing, 25);

  u8g.print("  /  /");

  //Month printer

  u8g.print(myRTC.year);

  if (digitalRead(btSet)) {
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, (myRTC.year + 1));
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
  } else if (digitalRead(btOk)) {
    lastMillisAyar = millis();
    nowMillisAyar = millis();
    while ((nowMillisAyar - lastMillisAyar) < 200) {
      nowMillisAyar = millis();
    }
    is_changed = 6;
    setting = false;
    ayar();
  }
}