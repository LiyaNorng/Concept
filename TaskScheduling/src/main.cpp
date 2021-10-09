#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <stdlib.h>

static int rate = 1000;
static const int led = LED_BUILTIN;
static const uint8_t buf_len = 20;

void readSerial(void *parameters) {

  char c;
  char buf[buf_len];
  uint8_t idx = 0;

  // Clear whole buffer
  memset(buf, 0, buf_len);

  // Loop forever
  while (1) {

    // Read characters from serial
    if (Serial.available() > 0) {
      c = Serial.read();

      // Update delay variable and reset buffer if we get a newline character
      if (c == '\n') {
        rate = atoi(buf);
        Serial.print("Updated LED delay to: ");
        Serial.println(rate);
        memset(buf, 0, buf_len);
        idx = 0;
      } else {
        
        // Only append if index is not over message limit
        if (idx < buf_len - 1) {
          buf[idx] = c;
          idx++;
        }
      }
    }
  }
}

void settingLedRate(void * id){

    while(1){
      digitalWrite(led, LOW);
      Serial.println("Led turn OFF");
      vTaskDelay(rate/portTICK_PERIOD_MS);
      digitalWrite(led, HIGH);
      Serial.println("Led turn ON");
      vTaskDelay(rate/portTICK_PERIOD_MS);

    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  delay(3000);
  Serial.println("Multi-task LED Demo");
  Serial.println("Enter a number in milliseconds to change the LED delay.");
  Serial.flush();

  xTaskCreate(settingLedRate, "Setting the rate for LED", 1024, NULL, 1, NULL);
  xTaskCreate(readSerial, "Getting input From User", 1024, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}
