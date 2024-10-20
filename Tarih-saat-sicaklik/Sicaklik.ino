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