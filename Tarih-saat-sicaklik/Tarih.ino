void sayfaTarih() {
  u8g.setFont(u8g_font_fur14);
  myRTC.updateTime();
  u8g.drawFrame(0, 0, 128, 64);

  //Names of days printer

  switch (myRTC.dayofweek) {
    case (1):
      spacing = (128 - u8g.getStrPixelWidth(day[0])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[0]);
      break;
    case (2):
      spacing = (128 - u8g.getStrPixelWidth(day[1])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[1]);
      break;
    case (3):
      spacing = (128 - u8g.getStrPixelWidth(day[2])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[2]);
      break;
    case (4):
      spacing = (128 - u8g.getStrPixelWidth(day[3])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[3]);
      break;
    case (5):
      spacing = (128 - u8g.getStrPixelWidth(day[4])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[4]);
      break;
    case (6):
      spacing = (128 - u8g.getStrPixelWidth(day[5])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[5]);
      break;
    default:
      spacing = (128 - u8g.getStrPixelWidth(day[6])) / 2;
      u8g.setPrintPos(spacing, 60);
      u8g.print(day[6]);
      break;
  }
  //Day of month printer
  spacing = (128 - u8g.getStrPixelWidth("11/11/2024")) / 2;
  u8g.setPrintPos(spacing, 40);
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
  spacing = (128 - u8g.getStrPixelWidth("23:59")) / 2;
  u8g.setPrintPos(spacing, 20);
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