#include <Servo.h>
#include <LiquidCrystal.h>
#define Joy_X A4
#define Joy_Y A5
#define BUTTON 2

int pot_change = A0;
int pot_pin_bottom = A1;
int pot_pin_joint1 = A2;
int pot_pin_joint2 = A3;

int value_change;
int value_bottom;
int value_joint1;
int value_joint2;
int Joy_Val = 0;

Servo servo_bottom;
Servo servo_joint1;
Servo servo_joint2;

LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup() {
  servo_bottom.attach(3);
  servo_joint1.attach(4);
  servo_joint2.attach(5);
  pinMode(BUTTON, INPUT_PULLUP);
  lcd.begin(16,2);
}

void loop() {
  int pot_inputs[4];
  pot_inputs[0] = analogRead(pot_change);
  pot_inputs[1] = analogRead(pot_pin_bottom);
  pot_inputs[2] = analogRead(pot_pin_joint1);
  pot_inputs[3] = analogRead(pot_pin_joint2);

  if(pot_inputs[0] > 511) {
  lcd.setCursor(0, 0);
  lcd.print("Mode:");
  lcd.setCursor(0, 1);
  lcd.print("Robot Arm");
    
  value_bottom = map(pot_inputs[1], 110, 800, 180 , 0);
  value_joint1 = map(pot_inputs[2], 1023, 600, 30, 160);
  value_joint2 = map(pot_inputs[3], 170, 880, 180, 0);

  servo_bottom.write(value_bottom);
  servo_joint1.write(value_joint1);
  servo_joint2.write(value_joint2);
  delay(5);
  
  } 
  else {
      lcd.setCursor(0, 0);
      lcd.print("Mode:");
      lcd.setCursor(0, 1);
      lcd.print("Joystick ");
      
      if (digitalRead(BUTTON) == LOW) {
      Joy_Val = analogRead(Joy_Y);
      Joy_Val = map(Joy_Val, 0, 1023, 0, 180);
      servo_joint2.write(Joy_Val);
      }
      else{
        Joy_Val = analogRead(Joy_X);
        Joy_Val = map(Joy_Val, 0, 1023, 180, 0);
        servo_bottom.write(Joy_Val);
        Joy_Val = analogRead(Joy_Y);
        Joy_Val = map(Joy_Val, 0, 1023, 0, 180);
        servo_joint1.write(Joy_Val);
        delay(15);
        }
      }

}
