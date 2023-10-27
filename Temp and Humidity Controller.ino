#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>

#define dht_apin A1 
#define anInput     A0                        
#define digTrigger   2                        
#define co2Zero     55  
LiquidCrystal_I2C lcd(0x27, 16, 2);

int relay_1 = 8;
int relay_2 = 9;
int relay_3 = 10;
int relay_4 = 11;
int minhumidity = 80;
int maxtemp = 25;
int maxco2 = 800;

 
dht DHT;
 
void setup(){
  pinMode(anInput,INPUT);                    
  pinMode(digTrigger,INPUT);
  
 
  Serial.begin(9600);
  delay(5000);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);

 
}
 
void loop(){
 
 
    DHT.read11(dht_apin);
    int humidity = DHT.humidity;
    int temp = DHT.temperature;
    
    Serial.print("humidity = ");
    Serial.print(humidity);
    Serial.print("%  ");
    Serial.println();
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("C  ");


    int co2now[10];                              
    int co2raw = 0;                               
    int co2comp = 0;                              
    int co2ppm = 0;                               
    int zzz = 0;                                  
    int co2 = 0; 
    for (int x = 0;x<10;x++){                   
      co2now[x]=analogRead(A0);
      delay(200);
    }
    for (int x = 0;x<10;x++){                     
      zzz=zzz + co2now[x];
    }
    co2raw = zzz/10;                          
    co2comp = co2raw - co2Zero;                 
    co2ppm = map(co2comp,0,1024,400,5000);
    co2 = co2ppm;
    Serial.print("Co2 =");
    Serial.print(co2);
    Serial.print(" ppm");
    Serial.println();

    delay(1000);
  
 
    if(humidity <= 80 ){
      digitalWrite(relay_1, LOW);
    }else{
      digitalWrite(relay_1, HIGH);
    }
    if(temp >= 25 ){
      digitalWrite(relay_2, LOW);
    }else{
      digitalWrite(relay_2, HIGH);
    }
    if(co2 >= 800 ){
      digitalWrite(relay_3, LOW);
    }else{
      digitalWrite(relay_3, HIGH);
    }
    digitalWrite(11, HIGH);

 
}