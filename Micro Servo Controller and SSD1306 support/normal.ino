#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo myservo;

//GPIO definition
const int decreaseSpeedPin = 3;
const int increaseSpeedPin = 4;

//button states
int increaseButtonState = 0;
int decreaseButtonState = 0; 

//Screen definitions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 //sharing Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Motor rotation limits and values
const int minimumRotationSpeedLimit = 60;
const int maximumRotationSpeedLimit = 120;
const int stopRotation = 88;
int currentRotationSpeed = 88;
  
void setup() {
  Serial.begin(9600);

  //init display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("Screen allocation failed");
  }

  display.clearDisplay();
  display.display();
  
  //init servo
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
  myservo.write(stopRotation); //set to zero

  //init input pins
  pinMode(increaseSpeedPin, INPUT);
  pinMode(decreaseSpeedPin, INPUT);
}

void loop() {
  increaseButtonState = digitalRead(increaseSpeedPin);
  decreaseButtonState = digitalRead(decreaseSpeedPin);

  if (increaseButtonState == HIGH && decreaseButtonState == HIGH) {
    return; // if both are pressed, don't do anything.
  }
  
  if (increaseButtonState == HIGH) {
    if (currentRotationSpeed >= maximumRotationSpeedLimit) {
      Serial.println("maximum CW rotation speed reached");
      currentRotationSpeed = maximumRotationSpeedLimit;
      return;
    }

    Serial.println(currentRotationSpeed);
    
    currentRotationSpeed += 1;
    myservo.write(currentRotationSpeed);
  }

  if (decreaseButtonState == HIGH) {
    Serial.println("Pressed reduce speed");

    if (currentRotationSpeed <= minimumRotationSpeedLimit) {
      Serial.println("maximum CCW rotation speed reached");
      currentRotationSpeed = minimumRotationSpeedLimit;
      return;
    }
    
    currentRotationSpeed -= 1;
    myservo.write(currentRotationSpeed);
  }

  double percentageValue = calculatePercentage(currentRotationSpeed);

  drawProgressBar(percentageValue);

  delay(100);
} 

double calculatePercentage(int currentValue) {
  double percentage = ((currentValue - minimumRotationSpeedLimit) * 100) / (maximumRotationSpeedLimit - minimumRotationSpeedLimit);
  return percentage;
}

void drawProgressBar(int percentageValue)
{
  int width = 128;
  int height = 25;

  percentageValue = percentageValue > 100 ? 100 : percentageValue;
  percentageValue = percentageValue < 0 ? 0 : percentageValue;
  
  float bar = ((float)(width - 4) / 100) * percentageValue; 

  display.clearDisplay();
  display.drawRect(0, 0, width, height, WHITE);
  display.fillRect(2, 2, bar, height - 4, WHITE);

  printProgressLabels();
  
  display.display();  
}

void printProgressLabels() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.println("CW");

  display.setCursor(58, 30);
  display.println("0");

  display.setCursor(114, 30);
  display.println("CCW");
}
