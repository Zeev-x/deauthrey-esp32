#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "lcd_display.h"
#include "definitions.h"

#define SCREEN_WIDTH 128
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 32
#endif
#define OLED_RESET    -1  // Tidak digunakan di I2C

// Gunakan alamat I2C OLED Anda (biasanya 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void centeredText(const String& text, int y, uint8_t textSize = 1) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(textSize);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  display.setCursor(x, y);
  display.print(text);
}

void typewriterText(const String& text, int y, uint8_t textSize = 1, int delayPerChar = 50) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(textSize);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;

  display.setCursor(x, y);
  for (int i = 0; i < text.length(); i++) {
    display.print(text[i]);
    display.display(); // tampilkan setiap karakter
    delay(delayPerChar);
  }
}

void lcd_conf() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void lcd_init_128x32() {
    lcd_conf();
    display.clearDisplay();
    typewriterText("Reyette-Projects", 14, 1, 100);
    delay(100);
    display.clearDisplay();
    typewriterText("ESP-32", 14, 2, 200);
    delay(100);
    display.clearDisplay();
    typewriterText("Deauthrey v1.0", 14, 1, 100);
    display.display();
}

void lcd_init_128x64() {
    lcd_conf();
    typewriterText("Reyette-Projects", 5, 1, 150);
    delay(200);
    typewriterText("ESP-32", 25, 2, 500);
    delay(200);
    typewriterText("Deauthrey v1.0", 50, 1, 150);
    display.display();
}

void lcd_init() {
  if(SCREEN_HEIGHT == 32) {
    lcd_init_128x32();
  } else if(SCREEN_HEIGHT == 64) {
    lcd_init_128x64();
  }
}

void lcd_show_status(const char* message) {
    display.clearDisplay();
    display.fillRect(0, 16, SCREEN_WIDTH, 16, SSD1306_BLACK); // Bersihkan area status
    display.setCursor(0, 16);
    if(SCREEN_HEIGHT == 32) {
      centeredText("Deauth mode:", 0, 1);
      centeredText(message, 16, 2);
    } else if(SCREEN_HEIGHT == 64) {
      centeredText("Deauth mode:", 5, 1);
      centeredText(message, 25, 2);
      centeredText("Reyette Projects", 50, 1);
    }
    display.display();
}







