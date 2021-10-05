#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

static int rate = 8000;
static const int led = LED_BUILTIN;

void gettingInputFromUser(void * id){
    int temp = 0;
    while(1){
      temp = Serial.read();
      if(temp > 0){
        rate = temp;
        Serial.println(rate);
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
  xTaskCreate(settingLedRate, "Setting the rate for LED", 1024, NULL, 1, NULL);
  xTaskCreate(gettingInputFromUser, "Getting input From User", 1024, NULL, 1, NULL);
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}