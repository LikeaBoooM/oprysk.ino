#include <Servo.h>

#include <Arduino.h>
#include <TM1637Display.h>

#include <EEPROM.h>

//POCZATEK WYSWIETLACZ
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
const uint8_t SEG_LOAD[] = {
  SEG_D | SEG_E | SEG_F,           // L
  SEG_C | SEG_D | SEG_E | SEG_G,   // O
  SEG_A | SEG_B | SEG_C | SEG_G | SEG_E | SEG_F,   // A
  SEG_E | SEG_B | SEG_C | SEG_D | SEG_G           // D
  };
//KONIEC WYSWIETLACZ
int czas,w;
int krok=0;
int startmilis,stopmilis;
int first=0;
void setup() {
  pinMode(10, OUTPUT); //Przekaznik 1
  pinMode(11, OUTPUT); //PRzekaznik 2
  pinMode(8, INPUT_PULLUP); //Pzycisk dol
  pinMode(7, INPUT_PULLUP); //Przycisk gora
  pinMode(4, INPUT_PULLUP); //Wrzutnik
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  ladowanie();
  czas=EEPROM.read(0);
  if (digitalRead(7) == LOW) {do{mignij(czas,1,100);}while (digitalRead(7)== LOW);programuj();}
  display.showNumberDec(czas, false);
  digitalWrite(11, LOW);delay(180000);digitalWrite(11, HIGH);delay(500);
}
 
void loop()
{   
    if (digitalRead(4) == LOW) {
      startmilis=millis();
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);  w=czas*1000;  do{stopmilis=millis();first=1;}while(((stopmilis-w)<startmilis));
      }else{
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    if (first==1){
      delay(200);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    first=0;
      }
      }
}

void ladowanie(){
  for(int i=0; i<4 ; i++){
  display.setBrightness(1);
  display.setSegments(SEG_LOAD);
  delay(1000);
  display.setBrightness(1, false);
  display.setSegments(SEG_LOAD);
  delay(500);
  }
  display.setBrightness(1, true);
}
void programuj(){
  bool wyjscie=false;
  do{
  mignij(czas,1,400);  
  if((digitalRead(7)==LOW)&&(digitalRead(8)==LOW)){
    EEPROM.update(0,czas);
    mignij(czas,20,50);
    
    wyjscie=true;
  }
  if(digitalRead(7)==LOW){czas++;}
  if(digitalRead(8)==LOW){czas--;}

  
  }while(wyjscie==false);
}
void mignij(int liczba,int ile,int milisek){
  for (int i=0 ; i<ile ; i++){
  display.setBrightness(1,false);
  display.showNumberDec(liczba, false);
  delay(milisek);
  display.setBrightness(1,true);
  display.showNumberDec(liczba, false);
  delay(milisek);
  }
}



/*
   uint8_t data[] = { 255,255,255,255};//[0-255]
  display.setBrightness(1);//[1-7]
                            //display.encodeDigit(1)

  // All segments on
  display.setSegments(data);
  delay(4000);
  display.showNumberDec(255, false);
delay(4000);

*/


/* if (digitalRead(8) == LOW) { //Jeśli przycisk wciśnięty
    digitalWrite(10, LOW); //Włącz diodę
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(10, HIGH); //Wyłącz diodę
  }
    if (digitalRead(7) == LOW) { //Jeśli przycisk wciśnięty
    digitalWrite(11, LOW); //Włącz diodę
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(11, HIGH); //Wyłącz diodę
  }*/
