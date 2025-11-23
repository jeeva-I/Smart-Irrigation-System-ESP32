#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

//PIN DEFINITIONS
#define soil 34        
#define pump 18        
#define pushbutton 4   
#define dhtPin 14     
#define DHTTYPE DHT22
DHT dht(dhtPin, DHTTYPE);

//OLED SETTINGS
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//SYSTEM VARIABLES
int mode = 0;               
int pumpState = 0;          
int moistureThreshold = 2000; 

// Button debounce
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 300; 
int lastButtonState = HIGH; 

//SETUP 
void setup() {
  pinMode(pump, OUTPUT);
  pinMode(pushbutton, INPUT_PULLUP);
  dht.begin();
  Wire.begin(21, 22); 

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Irrigation System");
  display.display();
  delay(1500);
}

//LOOP
void loop() {
  unsigned long currentMillis = millis();
  int buttonState = digitalRead(pushbutton);

  //HANDLE BUTTON FOR MODE TOGGLE
  if (buttonState == LOW && lastButtonState == HIGH && 
      currentMillis - lastButtonTime > debounceDelay) {
      mode = 1 - mode; 
      lastButtonTime = currentMillis;
  }
  lastButtonState = buttonState;

  //READ SOIL MOISTURE
  int moistureValue = analogRead(soil);

  //AUTO MODE
  if (mode == 0) { 
    if (moistureValue < moistureThreshold) {
      pumpState = 1;
    } else {
      pumpState = 0;
    }
  }

  //MANUAL MODE
  else { 
    if (buttonState == LOW && lastButtonState == HIGH &&
        currentMillis - lastButtonTime > debounceDelay) {
      pumpState = 1 - pumpState; // Toggle pump
      lastButtonTime = currentMillis;
    }
  }

  //PUMP OUTPUT
  digitalWrite(pump, pumpState == 1 ? HIGH : LOW);

  //READ TEMPERATURE & HUMIDITY
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  //UPDATE OLED
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("MODE: ");
  display.println(mode == 0 ? "AUTO" : "MANUAL");

  display.print("Moisture: ");
  display.println(moistureValue);

  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Hum: ");
  display.print(humidity);
  display.println(" %");

  display.print("PUMP: ");
  display.println(pumpState == 1 ? "ON" : "OFF");

  display.display();

  delay(500); 
}
