#include <Arduino.h>
#include "deauthrey.h"

extern int SCREEN_HEIGHT = 32;

void setup() {
    Serial.begin(115200);
    rey_setup();
}

void loop() {
    rey_loop();
}