#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h> 
/**
 * Date: October 4, 2021
 * Author: Liya Norng
 * 
 * Using mega 2560 board using freertos create two thread to toggle the built in LED on and off. 
 *  
 */

// Pins
static const int led_pin = LED_BUILTIN;

// Our task: blink an LED
void task1(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    Serial.println("Task 1 : Turn if off");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    Serial.println("Task 1 : Turn if on");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task2(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    Serial.println("Task2 : Turn if off");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    Serial.println("Task2 : Turn if on");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {

  // Configure pin
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  xTaskCreate(task1,   // Function to be called
   "Task1",  //Name of the task to be called
   1024, // Stack size 
   NULL, // Parameter to pass to function 
   1,  // Task priority (0 to configMAX_PRIORITIES - 1) 
   NULL // Task handle
   );
  xTaskCreate(task2, "Task2", 1024, NULL, 1, NULL);
}

void loop() {
  // Do nothing
  
  // setup() and loop() run in their own task with priority 1 
}
