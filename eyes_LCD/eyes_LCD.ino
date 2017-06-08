// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 16, 14);

// make some custom characters:
byte block[8] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
byte diamond[8] = {0x4,0xe,0x1f,0x1f,0x1f,0x1f,0xe,0x4};
byte diamondCir[8] = {0xe,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0xe};
byte diamondRight[8] = {0x6,0xf,0x1f,0x1f,0x1f,0x1f,0x1e,0xc};
byte diamondLeft[8] = {0xc,0x1e,0x1f,0x1f,0x1f,0x1f,0xf,0x6};
/*byte lineCharA[8] = {0x3,0x6,0xc,0x18,0xc,0x6,0x3,0x1};
byte lineCharB[8] = {0x18,0xc,0x6,0x3,0x6,0xc,0x18,0x10};
*/
/* thicker
byte lineCharT1[8] = {0x3,0x6,0xc,0x6,0x3,0x0,0x0,0x0};
byte lineCharT2[8] = {0x18,0xc,0x6,0xc,0x18,0x0,0x0,0x0};
byte lineCharB1[8] = {0x0,0x0,0x0,0x3,0x6,0xc,0x6,0x3};
byte lineCharB2[8] = {0x0,0x0,0x0,0x18,0xc,0x6,0xc,0x18};
*/

/* thin greater than less than for 2 rows */
byte lineCharT1[8] = {0x2,0x4,0x8,0x4,0x2,0x0,0x0,0x0};
byte lineCharT2[8] = {0x8,0x4,0x2,0x4,0x8,0x0,0x0,0x0};
byte lineCharB1[8] = {0x0,0x0,0x0,0x2,0x4,0x8,0x4,0x2};
byte lineCharB2[8] = {0x0,0x0,0x0,0x8,0x4,0x2,0x4,0x8};

/* asterisks for 2 rows */
byte asteriskT[8] = {0x4,0x15,0xe,0x15,0x4,0x0,0x0,0x0};
byte asteriskB[8] = {0x0,0x0,0x0,0x4,0x15,0xe,0x15,0x4};


void setup() {
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
  lcd.setCursor(0, 1);

/* thin greater than less than for 2 rows */
/*lcd.setCursor(1,1);
  for(int i=0; i < 9; i++) {
    lcd.write(4); lcd.write(5);  
  }
  lcd.setCursor(1,2);
  for(int i=0; i < 9; i++) {
    lcd.write(6); lcd.write(7);  
  }
/*

/* asterisks for 2 rows */
/*lcd.setCursor(1,1);
  for(int i=0; i < 18; i++) {
    lcd.write(byte(0));  
  }
  lcd.setCursor(1,2);
  for(int i=0; i < 18; i++) {
    lcd.write(1);  
  }
*/

/* block eyes */
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

void loop() {
/* flash solid */
/*
  lcd.setCursor(0, 0);  
  for(int i=0; i<80; i++)
    lcd.write(2);  
  delay(400);
  for(int i=0; i<80; i++)
    lcd.print(" ");  
  delay(400);
*/


  while(1){}
}
