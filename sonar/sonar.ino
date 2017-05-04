#include <DueTimer.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(26, 28, 29, 30, 31, 32);

int trig = 45;    
int echo = 44;    
float duration, distance;
char buffor[16];

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.clear();

  for (int i = 0; i < 8; i++){
    pinMode(2 + i, OUTPUT);
  }
}

void lightUp(int v){

  for (int i = 0; i < 8; i++){
      digitalWrite(2 + i, 0);
    }

  if (v > 9) {
    v = 9; 
  }

  for (int i = 0; i < v; i++){
      digitalWrite(2 + i, 1);
    }
}

void loop() {

  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW); 

  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
 
  distance = (duration/2) / 29.1 - 0.5;

  Serial.print("Distance (in cm): ");
  Serial.print(distance);
  Serial.print(int(distance));
  Serial.println();

  
  lcd.setCursor(0,0); 
  lcd.print("Distance (in cm): ");
  lcd.setCursor(0,1);
  sprintf(buffor, "%.2f", distance);
  lcd.print(buffor);

  lightUp(int(distance-3));
  
  
  delay(250);
}
