/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define SERVOHALF (SERVOMAX-SERVOMIN)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

// convert from degrees to pulse length
uint16_t degrees2Pulse(uint16_t degrees) {
  return map(degrees, 0, 180, SERVOMIN, SERVOMAX);
}

/* moveEars moves the pair of robot ears which contain a jointed servo pair.
 *  1st argument is pitch (up/down) ear movement servo pulse
 *  2nd argument is roll (rotate/swivel) ear movment servo pulse
 * right and left ears do same thing for now. */
void moveEars(uint16_t pitchPulseLen, uint16_t rollPulseLen) {
    // left ear
    pwm.setPWM(5, 0, pitchPulseLen);  // up/down ear movement is pitch
    pwm.setPWM(4, 0, rollPulseLen);  // rotate/swivel ear movement is roll
    // right ear
    pwm.setPWM(7, 0, pitchPulseLen);
    pwm.setPWM(6, 0, rollPulseLen);  
}

/* this very much depends on how the servos are mounted and arms are mounted */
void upEars() {
  // left ear
  pwm.setPWM(5, 0, SERVOMAX);  // up/down ear movement is pitch
  pwm.setPWM(4, 0, SERVOMIN);  // rotate/swivel ear movement is roll
  // right ear 
  pwm.setPWM(7, 0, SERVOMIN);  // opposite of left ear due to symmetry
  pwm.setPWM(6, 0, SERVOMIN);  
}

/* this very much depends on how the servos are mounted and arms are mounted */
void downEars() {
  // left ear
  pwm.setPWM(5, 0, SERVOMIN);  // up/down ear movement is pitch
  pwm.setPWM(4, 0, SERVOMAX);  // rotate/swivel ear movement is roll
  // right ear 
  pwm.setPWM(7, 0, SERVOMAX);  // opposite of left ear due to symmetry
  pwm.setPWM(6, 0, SERVOMAX);  
}

void loop() {
  Serial.println("up ears");
  upEars();
  delay(2000);
  Serial.println("down ears");
  downEars();
  delay(2000); 
 
 /* 
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
    pwm.setPWM(5, 0, pulselen);
    pwm.setPWM(6, 0, pulselen);
    pwm.setPWM(7, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen);
    pwm.setPWM(1, 0, pulselen);
    pwm.setPWM(2, 0, pulselen);
    pwm.setPWM(3, 0, pulselen);
    pwm.setPWM(4, 0, pulselen);
    pwm.setPWM(5, 0, pulselen);
    pwm.setPWM(6, 0, pulselen);
    pwm.setPWM(7, 0, pulselen);
  }
  delay(500);
*/
}
