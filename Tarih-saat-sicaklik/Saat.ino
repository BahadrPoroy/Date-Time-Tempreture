void sayfaSaat() {
  u8g.setFont(u8g_font_fur30n);
  myRTC.updateTime();
  // Saat yazdırma
  
  char saat[6];
  sprintf(saat, "%02d:%02d", myRTC.hours, myRTC.minutes);
  ortaliMetin(saat, 128, 64);
  /*spacing = (128 - u8g.getStrPixelWidth(saat)) / 2;
  u8g.setPrintPos(spacing, 60);
  u8g.print(saat);*/

}

