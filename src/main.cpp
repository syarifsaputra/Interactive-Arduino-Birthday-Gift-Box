#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUZZER 8
#define BUTTON 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784

String lirikBawah = "HBD Bub,semoga sehat selalu, i loved you, miss you ";
int posisiScroll = 0;

void scrollBarisBawah() {
  String tampil = lirikBawah.substring(posisiScroll, posisiScroll + 16);
  if (tampil.length() < 16) {
    tampil += lirikBawah.substring(0, 16 - tampil.length());
  }
  lcd.setCursor(0, 1);
  lcd.print(tampil);
  posisiScroll++;
  if (posisiScroll >= (int)lirikBawah.length()) posisiScroll = 0;
}

void mainkanNada(int nada, int durasi) {
  tone(BUZZER, nada);
  scrollBarisBawah();
  delay(durasi);
  noTone(BUZZER);
  delay(50);
}

void happyBirthday() {
  mainkanNada(G4, 250); mainkanNada(G4, 250); mainkanNada(A4, 500);
  mainkanNada(G4, 500); mainkanNada(C5, 500); mainkanNada(B4, 750);
  delay(200);
  mainkanNada(G4, 250); mainkanNada(G4, 250); mainkanNada(A4, 500);
  mainkanNada(G4, 500); mainkanNada(D5, 500); mainkanNada(C5, 750);
  delay(200);
  mainkanNada(G4, 250); mainkanNada(G4, 250); mainkanNada(G5, 500);
  mainkanNada(E5, 500); mainkanNada(C5, 500); mainkanNada(B4, 500); mainkanNada(A4, 750);
  delay(200);
  mainkanNada(F5, 250); mainkanNada(F5, 250); mainkanNada(E5, 500);
  mainkanNada(C5, 500); mainkanNada(D5, 500); mainkanNada(C5, 1000);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Tekan tombolnya");
  lcd.setCursor(0, 1);
  lcd.print("ya cantik");

  Serial.println("=== SETUP SELESAI, MENUNGGU TOMBOL ===");
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    delay(20);
    if (digitalRead(BUTTON) == LOW) {

      Serial.println(">>> TOMBOL DITEKAN - MULAI SIKLUS BARU <<<");

      posisiScroll = 0;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HBD Shayla Luna");

      happyBirthday();

      Serial.print("Lagu selesai. posisiScroll saat ini = ");
      Serial.println(posisiScroll);

      int posisiAkhir = lirikBawah.length() - 16;  // titik dimana jendela 16-karakter pas di ujung kalimat, tanpa nyerempet ke awal
      if (posisiAkhir < 0) posisiAkhir = 0;

      int langkahTersisa = posisiAkhir - posisiScroll;
      if (langkahTersisa < 0) langkahTersisa = 0;

      Serial.print("Sisa langkah scroll yang akan dijalankan = ");
      Serial.println(langkahTersisa);

      for (int i = 0; i < langkahTersisa; i++) {
        scrollBarisBawah();
        delay(300);
      }

      Serial.println("Scroll sisa selesai. Kembali ke layar awal.");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tekan tombolnya");
      lcd.setCursor(0, 1);
      lcd.print("ya cantik");

      Serial.println("--- Menunggu tombol dilepas ---");
      while (digitalRead(BUTTON) == LOW) {
        delay(10);
      }
      Serial.println("=== Tombol sudah dilepas. Siap untuk siklus berikutnya ===");

      delay(100);
    }
  }
}
