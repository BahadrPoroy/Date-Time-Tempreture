void sayfaHava() {
  u8g.setFont(u8g_font_fur11);

  DHT.read(DHT11PIN); // Gerekli, ancak chk değişkeni gereksiz
  
  byte sicaklik = DHT.temperature;
  byte nem = DHT.humidity;

  byte spacing = (128 - 90) / 2; // "SICAKLIK: XXC" yaklaşık 90 px genişlikte
  u8g.setPrintPos(spacing, 20);
  u8g.print("SICAKLIK: ");
  u8g.print(sicaklik);
  u8g.print("C");

  spacing = (128 - 100) / 2; // "24H ORT: XX.XXC" yaklaşık 100 px genişlikte
  u8g.setPrintPos(spacing, 40);
  u8g.print("24H ORT: ");
  u8g.print(ort_sck, 1);  // Ondalık hassasiyetini 1 basamağa düşürdük

  spacing = (128 - 80) / 2; // "NEM: %XX" yaklaşık 80 px genişlikte
  u8g.setPrintPos(spacing, 60);
  u8g.print("NEM: %");
  u8g.print(nem);
}
