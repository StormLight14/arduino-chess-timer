#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int TimeWM = 10;
int TimeWS = 0;
int TimeBM = 10;
int TimeBS = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
//dont change StartTime variables
int StartTimeWM = TimeWM;
int StartTimeWS = TimeWS;
int StartTimeBM = TimeBM;
int StartTimeBS = TimeBS;
int IncrementBlack = 1;
int IncrementWhite = 1;
bool WhiteCanIncrement = true;
bool BlackCanIncrement = false;

String InputMode = "BUTTONS";
String CurrentTurn = "WHITE";
String CurrentMode = "PLAY";
String Winner = "None";

int SwitchPinValue = 0;
int WhiteButtonPinValue = 0;
int BlackButtonPinValue = 0;
int SetupPinValue = 0;

const int SetupPin = 8;
const int SwitchPin = 9;
const int BlackButtonPin = 10;
const int WhiteButtonPin = 11;

bool has_printed_end = false;


void setup() {
  pinMode(SwitchPin, INPUT);
  pinMode(BlackButtonPin, INPUT);
  pinMode(WhiteButtonPin, INPUT);
  pinMode(SetupPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  startMillis = millis();
  /*
  TimeWM *= 1000;
  TimeWS *= 1000;
  TimeBM *= 1000;
  TimeBS *= 1000;
  */
}

void loop() {
  print_lcd();
  
  if (CurrentMode == "PLAY") {
    play_mode();
  } else if (CurrentMode == "END") {
    end_mode();
  }

  WhiteButtonPinValue = digitalRead(WhiteButtonPin);
  BlackButtonPinValue = digitalRead(BlackButtonPin);
}

void play_mode() {
  currentMillis = millis();
  if (InputMode == "SWITCH") {
    SwitchPinValue = digitalRead(SwitchPin);
    //WHITE
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

      if (TimeWS <=0  && TimeWM <= 0) {
          CurrentMode = "END";
          Winner = "Black";          
      }
      
    //BLACK
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

      if (TimeBS <=0  && TimeBM <= 0) {
          CurrentMode = "END";
          Winner = "White";
        }

      }
    }
  }

  if (InputMode == "BUTTONS") {
    
      if (WhiteButtonPinValue == HIGH) {
        CurrentTurn = "BLACK";
      }
      if (BlackButtonPinValue == HIGH) {
        CurrentTurn = "WHITE";
      }

      if (CurrentTurn == "WHITE") {
        if (currentMillis - startMillis >= period){
        if (TimeWS <= 0)
          {
            TimeWM -= 1;
            TimeWS = 59;
            startMillis = currentMillis;
          }
        else
        { 
          TimeWS -= 1;
          startMillis = currentMillis;
        }
        }
        if (TimeWS <=0  && TimeWM <= 0) {
          CurrentMode = "END";
          Winner = "Black";          
        }
      }
      else if (CurrentTurn == "BLACK") {
        if (currentMillis - startMillis >= period){
        if (TimeBS <= 0)
          {
            TimeBM -= 1;
            TimeBS = 59;
            startMillis = currentMillis;
          }
        else
        { 
          TimeBS -= 1;
          startMillis = currentMillis;
        }

        if (TimeBS <=0  && TimeBM <= 0) {
          CurrentMode = "END";
          Winner = "White";
        }
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
}

void end_mode() {
  if (WhiteButtonPinValue == HIGH || BlackButtonPinValue == HIGH) {
    CurrentMode = "PLAY";
    TimeWM = StartTimeWM;
    TimeWS = StartTimeWS;
    TimeBM = StartTimeBM;
    TimeBS = StartTimeBS;    
  }
}

void print_lcd() {
  if (CurrentMode == "PLAY") {
    lcd.clear();
    String WSPrint = String(TimeWS);
    String BSPrint = String(TimeBS);
    
    switch (TimeWS) {
      case 0:
        WSPrint = "00";
        break;
      case 1:
        WSPrint = "01";
        break;
      case 2:
        WSPrint = "02";
        break;
      case 3:
        WSPrint = "03";
        break;
      case 4:
        WSPrint = "04";
        break;
      case 5:
        WSPrint = "05";
        break;
      case 6:
        WSPrint = "06";
        break;
      case 7:
        WSPrint = "07";
        break;
      case 8:
        WSPrint = "08";
        break;
      case 9:
        WSPrint = "09";
        break;
    }

    switch (TimeBS) {
      case 0:
        BSPrint = "00";
        break;
      case 1:
        BSPrint = "01";
        break;
      case 2:
        BSPrint = "02";
        break;
      case 3:
        BSPrint = "03";
        break;
      case 4:
        BSPrint = "04";
        break;
      case 5:
        BSPrint = "05";
        break;
      case 6:
        BSPrint = "06";
        break;
      case 7:
        BSPrint = "07";
        break;
      case 8:
        BSPrint = "08";
        break;
      case 9:
        BSPrint = "09";
        break;
    }
    lcd.setCursor(0, 0);
    lcd.print("W ");
    lcd.print(TimeWM);
    lcd.print(":");
    lcd.print(WSPrint);
    lcd.setCursor(0, 1);
    lcd.print("B ");
    lcd.print(TimeBM);
    lcd.print(":");
    lcd.print(BSPrint);
    delay(100);
  }
  else if (CurrentMode == "END") {
    if (has_printed_end == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(Winner);
      lcd.print(" ");
      lcd.print("won");
      lcd.setCursor(0, 1);
      lcd.print("on time.");

      has_printed_end = true;
    }
    
    if (WhiteButtonPinValue == HIGH or BlackButtonPinValue == HIGH) {
      CurrentMode == "PLAY";     
    }
  }
}