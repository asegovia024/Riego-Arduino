#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 22
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int sensor0 = A10;
int sensor2 = A12;
int act0=20;
int act1=21;

int sector1,sector2;

boolean s1,s2=false;



LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //pines usados por la pantalla

void setup() {
  // put your setup code here, to run once: Configuracion inicial
  Serial.begin(9600);

 pinMode(s1, OUTPUT);
 pinMode(s2, OUTPUT);
   digitalWrite(s1, LOW);    
  digitalWrite(s2, LOW);    


}

void loop() {
  // put your main code here, to run repeatedly:
 delay(500);
/*
//dht11
int h = dht.readHumidity();// Lee la humedad
int t= dht.readTemperature();//Lee la temperatura
*/

sector1 =map (analogRead(sensor0),0,1024,1024,0);
sector2 = map (analogRead(sensor2),0,1024,1024,0);


sector1=sector1/10.24;
sector2=sector2/10.24;




if (sector1 <40){
  s1 = true;
   digitalWrite(act0, HIGH);    
}else if(sector1 >70){
    s1 = false;
   digitalWrite(act0, LOW);  
}



if (sector2 <40){
  s2 = true;
   digitalWrite(act1, HIGH);    

}else if (sector2 >70){
  s2 = false;
   digitalWrite(act1, LOW);    

}






  //temperatura =analogRead(sensor2);
lcd.clear();
lcd.begin(16, 2); // start the library
lcd.setCursor(0,0); //inicio del cursor 

//Sector 1
lcd.print("Sector1: "); 
lcd.setCursor(9,0);
lcd.print(sector1);
lcd.setCursor(14,0);
lcd.print(s1);

//Sector2
lcd.setCursor(0,1);
lcd.print("Sector2: "); 
lcd.setCursor(9,1);
lcd.print(sector2);
lcd.setCursor(14,1);
lcd.print(s2);

/* old version
 lcd.clear();
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0); //inicio del cursor 
 lcd.print("Humedad: "); 
lcd.setCursor(9,0);
 lcd.print(humedad);
 lcd.setCursor(0,1);

 
 lcd.print("T: "); 
 lcd.setCursor(2,1);
 lcd.print(t);
 
 lcd.setCursor(6,1);
  lcd.print("H: ");
   
 lcd.setCursor(8,1);
  lcd.print(h);*/

lcd.setCursor(9,1);
lcd.setCursor(0,1);






}
