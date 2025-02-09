void sayfaTarih() {
  u8g.setFont(u8g_font_fur17);
  myRTC.updateTime();

  // Gün adı yazdırma (switch yerine dizi erişimi kullanıldı)
  byte spacing = (128 - u8g.getStrPixelWidth(day[myRTC.dayofweek - 1])) / 2;
  u8g.setPrintPos(spacing, 54);
  u8g.print(day[myRTC.dayofweek - 1]);

  // Tarih yazdırma (Gereksiz `if` kaldırıldı)
  char tarih[11];
  sprintf(tarih, "%02d/%02d/%04d", myRTC.dayofmonth, myRTC.month, myRTC.year);
  spacing = (128 - u8g.getStrPixelWidth(tarih)) / 2;
  u8g.setPrintPos(spacing, 34);
  u8g.print(tarih);
}
