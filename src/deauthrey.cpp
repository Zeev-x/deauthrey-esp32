#include "deauth.h"
#include "definitions.h"
#include "lcd_display.h"

bool deauth_mode = false;
int last_btn_state;
unsigned long last_debounce_ms = 0;
const unsigned long debounce_delay = 50;

void btn_control() {
  int btn_state = digitalRead(BTN);

  if (btn_state != last_btn_state) {
    last_debounce_ms = millis();
  }

  if ((millis() - last_debounce_ms) > debounce_delay) {
    static int stable_last = HIGH;
    if (btn_state != stable_last) {
      if (stable_last == HIGH && btn_state == LOW) {
        deauth_mode = !deauth_mode;
        if (deauth_mode) enable_deauth(); else stop_deauth();
      }
      stable_last = btn_state;
    }
  }

  last_btn_state = btn_state;
}

void rey_setup() {
  lcd_init();

  #ifdef LED
  pinMode(LED, OUTPUT);
  #endif

  pinMode(BTN, INPUT_PULLUP);
  last_btn_state = digitalRead(BTN);
}

void rey_loop() {
  btn_control();
  deauth_loop();
}
