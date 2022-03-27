#include "DHT.h" // include the library
#define Type DHT11 //constant type
#include "LiquidCrystal.h"
#include "IRremote.h"

//for temp
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
LiquidCrystal lcd(rs,en,  d4,d5,d6,d7);
int sensePIN=2;
DHT HT(sensePIN, Type);
float humidity;
float tempF;
int delayTime = 1000;

bool kill = false;

//for clock
int hour = 12;
int minute;
int second;
int times;

//for remote
const int PIN = 4;
IRrecv irrecv(PIN);
decode_results results;

//for buzzer
int buzzPin = 5;
int hReader;

void setup() {
  Serial.begin(9600);
  HT.begin();
  delay(500);
  lcd.begin(16,2);
  irrecv.enableIRIn();
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  humidity = HT.readHumidity(true);
  if (humidity > 85) { 
    digitalWrite(buzzPin, HIGH); // buzz when humidity reaches 85
  }
  
  tempF = HT.readTemperature(true);

  if(irrecv.decode(&results)) {
  Serial.println(results.value, HEX); //prints the HEX numbers for each buttom clicked on remote on the Serial Monitor
    delay(500);
    irrecv.resume();
    /* for hours */
    if(results.value==0xFF30CF) { // hex number for number 1 on remote, add one hour when clicked
      hour=hour+1;
    }
    if(results.value==0xFF10EF) { // hex number for number 4 on remote, minus one hour when clicked. (for mistakes :))
      hour=hour-1;
    }
    if(results.value==0xFF42BD) { // hex number for number 7 on remote, take the hours back to 12. (for mistakes :))
      hour = 12;
    }
    /* for minutes*/
    if(results.value==0xFF18E7) { // hex number for number 2 on remote, add one minute when clicked
      minute=minute+1;
    }
    if(results.value==0xFF38C7) { // hex number for number 5 on remote, subtract one minute when clicked (for mistakes :))
      minute=minute-1;
    }
    if(results.value==0xFF4AB5) { // hex number for number 8 on remote, take the minutes back to 0 (for mistakes :))
      minute=0;
    }

    /* for seconds */
    if(results.value==0xFF7A85) { // hex number for number 3 on remote, reset to 0 seconds when clicked
      second=0;
    }
    if(results.value==0xFFA25D) { // if reset
      kill = false;  // if power is pressed reset
      int hour = 12;
      int minute = 0;
      int second = 0;
      int times = 0;

      // print the time and temp 
      lcd.print("TIME: ");
      lcd.print(hour);
      lcd.print(":");
      lcd.print(minute);
      lcd.print(":");
      lcd.print(second);
      lcd.setCursor(0,1);
      lcd.print("T=");
      lcd.print(tempF);
      lcd.print("F,");
      lcd.print("H=");
      lcd.print(humidity);
      delay(1000);
    }
  }

  lcd.setCursor(0,0); //first row

  //print the clock
  lcd.print("TIME: ");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  lcd.setCursor(0,1);
  lcd.print("T=");
  lcd.print(tempF);
  lcd.print("F,");
  lcd.print("H=");
  lcd.print(humidity);
  delay(500);

  
  if(!kill){
    second++;
    delay(1000);
    lcd.clear();
    //set time
    if(hour==24) {
      hour = 0;
    }
    if(minute==59) {
      minute=0;
      hour=hour+1;
    }
    if(second==59) {
      second=0;
      minute=minute+1;
    }
      humidity > 85 ? kill = true : kill = false;
    }

}
