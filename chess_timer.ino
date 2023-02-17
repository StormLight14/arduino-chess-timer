#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int TimeWM = 10;
int TimeWS = 0;
int TimeBM = 10;
int TimeBS = 0;
int IncrementBlack = 1;
int IncrementWhite = 1;

bool WhiteCanIncrement = true;
bool BlackCanIncrement = false;
String InputMode = "BUTTONS";
String CurrentTurn = "WHITE";
int SwitchPinValue = 0;
int WhiteButtonPinValue = 0;
int BlackButtonPinValue = 0;
int SetupPinValue = 0;
const int SwitchPin = 8;
const int BlackButtonPin = 6;
const int WhiteButtonPin = 7;
const int SetupPin = 13;


void setup() {
  pinMode(SwitchPin, INPUT);
  pinMode(BlackButtonPin, INPUT);
  pinMode(WhiteButtonPin, INPUT);
  pinMode(SetupPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  print_lcd();
  
  if (InputMode == "SWITCH") {
    SwitchPinValue = digitalRead(SwitchPin);
    if (SwitchPinValue == LOW) {
      if (TimeWS <= 0)
      {
        TimeWM -= 1;
        TimeWS = 59;
      }
      else
      { 
        TimeWS -= 1;
      }
      
    if (SwitchPinValue == HIGH)
    {
      if (TimeBS <= 0)
      {
        TimeBM -= 1;
        TimeBS = 59;
      }
      else
      { 
        TimeBS -= 1;
        }
      }
    }
  }
  
  if (InputMode == "BUTTONS") {
    WhiteButtonPinValue = digitalRead(WhiteButtonPin);
    BlackButtonPinValue = digitalRead(BlackButtonPin);
    
      if (WhiteButtonPinValue == HIGH) {
        CurrentTurn = "BLACK";
      }
      if (BlackButtonPinValue == HIGH) {
        CurrentTurn = "WHITE";
      }

      if (CurrentTurn == "WHITE") {
        if (TimeWS <= 0)
          {
            TimeWM -= 1;
            TimeWS = 59;
          }
        else
        { 
          TimeWS -= 1;
        }
      }

      else if (CurrentTurn == "BLACK") {
        if (TimeBS <= 0)
          {
            TimeBM -= 1;
            TimeBS = 59;
          }
        else
        { 
          TimeBS -= 1;
        }
      }
      /*
      if (SetupPinValue == HIGH) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("SETUP MODE");
        delay(1000);
        lcd.clear();
        lcd.print("HOLD4,5M");
        delay(4000);
        if (SetupPinValue == HIGH) {
          TimeWS = 0;
          TimeWM = 5;
          TimeBS = 0;
          TimeBM = 5;
        }
      }
        
      else {
        lcd.clear();
      }
      */
    }
  
  delay(1000);
}

void print_lcd() {
  lcd.setCursor(0, 0);
  lcd.print("W");
  lcd.print(" ");
  lcd.print(TimeWM);
  lcd.print(":");
  lcd.print(TimeWS);
  lcd.setCursor(0, 1);
  lcd.print("B");
  lcd.print(" ");
  lcd.print(TimeBM);
  lcd.print(":");
  lcd.print(TimeBS);
}
  