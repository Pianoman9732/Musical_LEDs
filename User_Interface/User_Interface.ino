
#include <Adafruit_NeoPixel.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_RGB + NEO_KHZ800);

  //initiate variables
  
  int Potentiometer = 0;
  int Lednumber = 1;
  int Red = 0;
  int Green = 0;
  int Blue = 0;
  int Time = 1000;
  //Time is in milliseconds
  int Ledmode = 1;
  
  int Rightarrow = 0;
  int Leftarrow = 0;
  int Select = 0;

  //Pin List
  //Digital: 2-5, 10-12 Reserved for LCD Display | 6 Reserved for LED Strip Output/Input | 7-9 Reserved for button input to change LED display mode
  //Analog: 1 Reserved for Potentiometer control input in method Solidcolor
  

void setup(){

  //serial test
  Serial.begin(9600);  
  
  //initiate and clear strip color values  
  
  strip.begin();
  strip.setBrightness(64);
  strip.show();
  
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Select Mode");
  
}

void loop() { //investigate changing the delay:

  //serial print section
  Serial.println(Rightarrow);
  Serial.println(Leftarrow);
  
  Leftarrow = 0;
  Rightarrow = 0;
  Select = 0;
  
  
  Rightarrow = digitalRead(7);  
  Leftarrow = digitalRead(9);
  //cannot delay and display at the same time; change to millis() call
  delay(1000);
  
  if(Rightarrow == 1){
    Ledmode = Ledmode + 1;
    Display();
  }
  else if(Leftarrow == 1){
    Ledmode = Ledmode - 1;
    Display();
  }
  else if(Select == 1){
    Display();
  
  }
  
  

}

void Display(){  //delay needs to be change
  
  //Mode 1: Solid Color Display
  if((Ledmode == 1 || Ledmode == 5) && Select == 0){
    Ledmode = 1;
    lcd.clear();
    lcd.print("Solid Color");
  }
  else if((Ledmode == 1 || Ledmode == 5) && Select == 1){
    lcd.clear();
    lcd.print("Solid Color");
    Select = 0;
    Solidcolor();
  }
  //Mode 2: Change Color Display
  else if(Ledmode == 2 && Select == 0){
   lcd.clear();
    lcd.print("Change Color");
  }
  else if(Ledmode == 2 && Select == 1){
    lcd.clear();
    lcd.print("Change Color");
    Select = 0;
    Changecolor();
  }
  //Mode 3: Disco Display
  else if(Ledmode == 3 && Select == 0){
    lcd.clear(); 
    lcd.print("Disco");
  }
  else if(Ledmode == 3 && Select == 1){
    lcd.clear(); 
    lcd.print("Disco");
     Select = 0;
     Disco();
  }
  //Mode 4: Music Display
  else if((Ledmode == 4 || Ledmode == 0) && Select == 0){
    lcd.clear();
    lcd.print("Music");
  }
  else if((Ledmode == 4 || Ledmode == 0) && Select == 1){
    Ledmode = 4;
    lcd.clear();
    lcd.print("Music");
    Select = 0;
    Music();
  }  
  //cannot have LEDs display and have the delay: change call to millis()
  delay(500);
  
}


void Solidcolor() {
  
  while(Select == 0){
  
  Select = digitalRead(8);
  
  Potentiometer = analogRead(A0);   // read the potentiometer value at the input pin

  if (Potentiometer < 341)  // Lowest third of the potentiometer's range (0-340)
  {                  
    Potentiometer = (Potentiometer * 3) / 4; // Normalize to 0-255

    Red = 256 - Potentiometer;  // Red from full to off
    Green = Potentiometer;        // Green from off to full
    Blue = 0;             // Blue off
  }
  else if (Potentiometer < 682) // Middle third of potentiometer's range (341-681)
  {
    Potentiometer = ( (Potentiometer-341) * 3) / 4; // Normalize to 0-255

    Red = 0;            // Red off
    Green = 256 - Potentiometer; // Green from full to off
    Blue = Potentiometer;       // Blue from off to full
  }
  else  // Upper third of potentiometer"s range (682-1023)
  {
    Potentiometer = ( (Potentiometer-683) * 3) / 4; // Normalize to 0-255

    Red = Potentiometer;       // Red from off to full
    Green = 0;            // Green off
    Blue = 256 - Potentiometer; // Blue from full to off
  }
  
  strip.Color(Red, Green, Blue);
  }  
  
}


void Changecolor() {
  
  int Redlimit = 0;
  int Greenlimit = 0;
  int Bluelimit = 0;
    
  Red = 0;
  Green = 0;
  Blue = 0;
  Lednumber = 0;
  
  strip.show();
  
  while(Select == 0){
    
  Select = digitalRead(8);
  
  strip.setPixelColor(Lednumber, Red, Green, Blue);
    if(Redlimit == 0){red++;}
  

  }
  
}

void Disco() {
  
}

void Music() {
  
}
