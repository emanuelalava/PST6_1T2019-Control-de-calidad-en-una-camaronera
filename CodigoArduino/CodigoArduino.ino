#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;

void setup() 
{
delay(1000);
Serial.begin(9600);
Serial.println("ElectronTools.blogspot.com.ar");
Serial.println("sensor ds1820");
delay(1000);
sensors.begin();
Serial.begin(9600);
}


void loop() 
{
Serial.println();
sensors.requestTemperatures(); //Le pido sensar
Serial.print(sensors.getTempCByIndex(0));
Serial.println(" grados centigrados");
}



float pH(){
  for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + 21.34;
 Serial.print("sensor = ");
 Serial.println(phValue);
 
 delay(20);
 return phValue;
}

