#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
// Set DHT pin:
#define DHTPIN 8
// Set DHT type, uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
   dht.begin();
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  // Print a message on both lines of the LCD.
  //lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  //lcd.print("Temperature: ");
  byte celc[8] = {
    0b01000,
    0b10100,
    0b01000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
    };
    byte Check[8] = {
    0b00000,
    0b00001,
    0b00011,
    0b10110,
    0b11100,
    0b01000,
    0b00000,
    0b00000
    };

    byte Bell[8] = {
    0b00100,
    0b01110,
    0b01110,
    0b01110,
    0b11111,
    0b00000,
    0b00100,
    0b00000
    };

    lcd.createChar(0, celc);
    lcd.createChar(1, Check);
    lcd.createChar(2, Bell);
    

}

void loop() {
    // Wait a few seconds between measurements:
    delay(2000);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read the humidity in %:
    int h = dht.readHumidity();
    // Read the temperature as Celsius:
    int t = dht.readTemperature();
    // Read the temperature as Fahrenheit:
    float f = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again):
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    // Compute heat index in Fahrenheit (default):
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius:
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Temperature: ");

    lcd.setCursor(0,0);   
    lcd.print("Temp:");
    lcd.print(t);
    
    lcd.write(0);
    lcd.print("C");

    for (int i=0; i<1;i++){
      lcd.scrollDisplayLeft();
      lcd.print(" Wet:");
      lcd.print(h);
      lcd.print("%");
      delay(1500);
    }

    for (int i=0; i<1;i++){
      lcd.scrollDisplayRight();
      delay(1500);
    }
    

    int sensorValue = analogRead(A1);
    
    lcd.setCursor(1,1);
    lcd.print("Air:");
    if (sensorValue<60)
      {
        lcd.print("Good");
        lcd.write(1);
      }
    else {
      lcd.print("Danger ");
      lcd.write(2);
    }
      

    
 

;}