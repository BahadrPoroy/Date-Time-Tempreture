void sayfaHava() {
  u8g.setFont(u8g_font_fur11);
  u8g.drawFrame(0, 0, 128, 64);
  spacing = (128 - u8g.getStrPixelWidth("SICAKLIK: 23C")) / 2;
  int chk = DHT.read(DHT11PIN);
  u8g.setPrintPos(spacing, 20);
  u8g.print("SICAKLIK: ");
  u8g.print(DHT.temperature);
  u8g.print("C");
  spacing = (128 - u8g.getStrPixelWidth("24H ORT: 23.00C")) / 2;
  u8g.setPrintPos(spacing, 40);
  u8g.print("24H ORT: ");
  u8g.print(ort_sck);
  u8g.print("C");
  spacing = (128 - u8g.getStrPixelWidth("NEM: %50")) / 2;
  u8g.setPrintPos(spacing, 60);
  u8g.print("NEM: %");
  u8g.print(DHT.humidity);
}