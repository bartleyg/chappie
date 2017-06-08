/* 
  Menu driven control of a sound board over UART.
  Commands for playing by # or by name (full 11-char name)
  Hard reset and List files (when not playing audio)
  Vol + and - (only when not playing audio)
  Pause, unpause, quit playing (when playing audio)
  Current play time, and bytes remaining & total bytes (when playing audio)

  Connect UG to ground to have the sound board boot into UART mode
*/
#include <LiquidCrystal.h>
#include "Adafruit_Soundboard.h"

/*
  Sparkfun Pro Micro 5V pins:
  TXO  -  RX Adafruit Sound Board
  RXI  -  TX Adafruit Sound Board
  2  -  4/SDA Adafruit PWM Servo Shield
  3  -  5/SCL Adafruit PWM Servo Shield
  4  -  Act Adafruit Sound Board
  5  -  brown-black-brown resistor - Mouth LED backlight
  7  -  4 LCD board
  8  -  6 LCD board
  9  -  11 LCD board
  10 -  12 LCD board
  16 -  13 LCD board
  14 -  14 LCD board
  GND - Ground plug
  RAW - 5 V wall wart plug

  LCD Board pins:
  1  -  Ground
  2  -  5 V
  3  -  Potentiometer contrast wiper
  4  -  7 Sparkfun Pro Micro
  5  -  Ground
  6  -  8 Sparkfun Pro Micro
  11 -  9 Sparkfun Pro Micro
  12 -  10 Sparkfun Pro Micro
  13 -  16 Sparkfun Pro Micro
  14 -  14 Sparkfun Pro Micro
  15 -  5 V
  16 -  Ground

  Adafruit 2x2W Amp Sound Board pins:
  Vin -  5 V
  Gnd -  Ground
  TX  -  RXI Sparkfun Pro Micro
  RX  -  TXO Sparkfun Pro Micro
  UG  -  Ground
  Act -  4 Sparkfun Pro Micro
  R+  -  Speaker +
  R-  -  Speaker -
  
  Adafruit 16 x 12-bit PWM Servo Shield pins:
  V+  -  5 V
  GND -  Ground
  5v  -  5 V
  Gnd -  Ground
  4/SDA -  2 Sparkfun Pro Micro
  5/SCL -  3 Sparkfun Pro Micro
  Servo0 - Servo ?
  Servo1 - Servo ?
  Servo2 - Servo ?
  Servo3 - Servo ?
  Servo4 - Servo ?
  Servo5 - Servo ?  
*/
  
// Connect to the RST pin on the Sound Board
//#define SFX_RST 4

// You can also monitor the ACT pin for when audio is playing!
#define SFX_ACT 4

// pass the serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third 
// arg is the reset pin
Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, NULL);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 16, 14);

// make some custom characters:
byte block[8] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
byte diamond[8] = {0x4,0xe,0x1f,0x1f,0x1f,0x1f,0xe,0x4};
/* thin greater than less than for 2 rows */
byte lineCharT1[8] = {0x2,0x4,0x8,0x4,0x2,0x0,0x0,0x0};
byte lineCharT2[8] = {0x8,0x4,0x2,0x4,0x8,0x0,0x0,0x0};
byte lineCharB1[8] = {0x0,0x0,0x0,0x2,0x4,0x8,0x4,0x2};
byte lineCharB2[8] = {0x0,0x0,0x0,0x8,0x4,0x2,0x4,0x8};
/* asterisks for 2 rows */
byte asteriskT[8] = {0x4,0x15,0xe,0x15,0x4,0x0,0x0,0x0};
byte asteriskB[8] = {0x0,0x0,0x0,0x4,0x15,0xe,0x15,0x4};

int n = 0;  // incoming serial playback

// arduino pins 5 and 6 analogwrite are interfered with by delay function
int mouthLEDPin = 5; 


void LCD_setup() {
  // initialize LCD and set up the number of columns and rows: 
  lcd.begin(20, 4);
    // create custom characters
  lcd.createChar(0, asteriskT);  
  lcd.createChar(1, asteriskB);
  lcd.createChar(2, block);
  lcd.createChar(3, diamond);
  lcd.createChar(4, lineCharT1);
  lcd.createChar(5, lineCharT2);
  lcd.createChar(6, lineCharB1);
  lcd.createChar(7, lineCharB2);  
  LCD_clear();
}

/* block eyes */
void LCD_blockEyes() {
  LCD_clear(); 
  lcd.setCursor(2, 1);  // row 1
  lcd.write(3); lcd.write(3); lcd.write(3);
  lcd.print("          ");
  lcd.write(3); lcd.write(3); lcd.write(3);
  lcd.setCursor(2, 2);  // row 2
  lcd.write(3); lcd.write(3); lcd.write(3);
  lcd.print("          ");
  lcd.write(3); lcd.write(3); lcd.write(3);
  lcd.setCursor(2, 3);  // row 3
  lcd.write(3); lcd.write(3); lcd.write(3);
  lcd.print("          ");
  lcd.write(3); lcd.write(3); lcd.write(3);
}

/* make every character all solid */
void LCD_allSolid() {
  lcd.setCursor(0,0);
  for(int i=0; i<80; i++)
    lcd.write(2);
}

/* clear every character */
void LCD_clear() {
  lcd.setCursor(0,0);
  for(int i=0; i<80; i++)
    lcd.print(" ");  
}

/* flash solid */
void LCD_flashSolid() {
  LCD_allSolid();
  delay(200);
  LCD_clear(); 
  delay(200);
  LCD_allSolid();
}

/* asterisks for 2 rows */
void LCD_2rowAsterisks() {
  LCD_clear();
  lcd.setCursor(1,1);
  for(int i=0; i < 18; i++) {
    lcd.write(byte(0));  
  }
  lcd.setCursor(1,2);
  for(int i=0; i < 18; i++) {
    lcd.write(1);  
  }
}

/* thin greater than less than for 2 rows */
void LCD_2rowLessThanGreaterThan() {
  LCD_clear(); 
  lcd.setCursor(1,1);
  for(int i=0; i < 9; i++) {
    lcd.write(4); lcd.write(5);  
  }
  lcd.setCursor(1,2);
  for(int i=0; i < 9; i++) {
    lcd.write(6); lcd.write(7);  
  }
}

void Sound_setup() {
  Serial1.begin(9600);  // adafruit soundboard hardware serial
/*  if (!sfx.reset()) {
    Serial.println("Not found");
    while (1);
  }
  Serial.println("SFX board found");
*/
}

void Mouth_setup() {
  pinMode(mouthLEDPin, OUTPUT);  // white LED mouth
  pinMode(SFX_ACT, INPUT);  // sense Sound Board ACT pin low when playing audio
}

void Mouth_LEDflash() {
  if(digitalRead(SFX_ACT)) {  // if ACT pin hasn't gone low, wait for it to
    while(digitalRead(SFX_ACT));
  }
  while(!digitalRead(SFX_ACT)) {  // flash mouth LED when speaking
    digitalWrite(mouthLEDPin, HIGH);
    delay(20);
    digitalWrite(mouthLEDPin, LOW);
    delay(20);
  }
}

void setup() {
  Serial.begin(115200);
  
  LCD_setup();
  Sound_setup();
  Mouth_setup();
  
  while(!Serial);  // wait for the serial port to be opened
}


/* MAIN LOOP */
void loop() {
  flushInput();
  
  Serial.print("Enter command> ");
  uint8_t cmd = readnumber();
  flushInput();
  
  switch (cmd) {
    case 0: {
      LCD_2rowAsterisks();
      Serial.println("\nDrop your weapons you're under arrest.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }    
    case 1: {
      LCD_2rowLessThanGreaterThan();
      Serial.println("\nNo.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }
    case 2: {
      LCD_2rowLessThanGreaterThan();
      Serial.println("\nI'm being cool.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }
    case 3: {
      LCD_blockEyes();
      Serial.println("\nI don't want to die. I want to live.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }    
    case 4: {
      LCD_allSolid();
      Serial.println("\nI am consciousness.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }
    case 5: {
      Serial.println("\nI am alive.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();  // this could be a problem
      LCD_flashSolid();  // put this here because audio can play while LCD catches up
      break;
    }
    case 6: {
      LCD_blockEyes();
      Serial.println("\nI am Chappie.");
      if (! sfx.playTrack(cmd) ) {
        Serial.println("Failed to play track?");
      }
      Mouth_LEDflash();
      break;
    }
  }
}


void flushInput() {
  // Read all available serial input to flush pending data.
  uint16_t timeoutloop = 0;
  while (timeoutloop++ < 40) {
    while(Serial1.available()) {
      Serial1.read();
      timeoutloop = 0;  // If char was received reset the timer
    }
    delay(1);
  }
}

char readBlocking() {
  while (!Serial.available());
  return Serial.read();
}

uint16_t readnumber() {
  uint16_t x = 0;
  char c;
  while (! isdigit(c = readBlocking())) {
    Serial.print(c);
  }
  Serial.print(c);
  x = c - '0';
  /*while (isdigit(c = readBlocking())) {
    Serial.print(c);
    x *= 10;
    x += c - '0';
  }*/
  return x;
}


