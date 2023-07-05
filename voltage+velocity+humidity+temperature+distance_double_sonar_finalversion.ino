const float arduinoVCC = 5.01;//Your Arduino voltage
unsigned long ValueR1 = 10000;
unsigned long ValueR2 = 10000;
double Voltage_Source = 12;
const int alanogPin = A0;//the pin connecting the voltage. 
const int inputResolution =1023;//works with most Arduino boards
const float average_of = 500;//Average of 500 readings

#include "DHT.h";
 
// Include NewPing Library
#include "NewPing.h"
 
// Define Constants
 
#define DHTPIN 7       // DHT-22 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 22 (AM2302)
#define TRIGGER_PIN  6
#define ECHO_PIN     5
#define TRIGGER_PINb  3
#define ECHO_PINb     4
#define MAX_DISTANCE 400


 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonarb (TRIGGER_PINb, ECHO_PINb, MAX_DISTANCE);


// Define Variables
 
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float duration; // Stores HC-SR04 pulse duration value
float durationb; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
float distanceb; // Stores calculated distance in cm
float soundsp;  // Stores calculated speed of sound in M/S
float soundcm;  // Stores calculated speed of sound in cm/ms
float voltage;
int iterations = 5;
int trigPin2 = 3;
int echoPin2 = 4;

// Initialize DHT sensor for normal 16mhz Arduino
 
DHT dht(DHTPIN, DHTTYPE); 
 
void setup() {
  Serial.begin (9600);
  dht.begin();
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}
 
void loop()
{
 
  delay(500);  // Delay so DHT-22 sensor can stabalize
    readVoltage();

    Serial.print(getVoltageAverage());

    Serial.print(",");

    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    
    // Calculate the Speed of Sound in M/S
    soundsp = 331.4 + (0.606 * temp) + (0.0124 * hum);
    
    // Convert to cm/ms
    
    soundcm = soundsp / 10000;
    
  duration = sonar.ping_median(iterations);
  durationb = sonarb.ping_median(iterations);
  
  // Calculate the distance
  distance = (duration / 2) * soundcm;
  distanceb = (durationb / 2) * soundcm;
  // Send results to Serial Monitor
  
    
    Serial.print(soundsp);
    Serial.print(", ");
    Serial.print(hum);
    Serial.print(", ");
    Serial.print(temp);
    Serial.print(", ");
     
    if (distance >= 400 || distance <= 2) {
    Serial.print("Out of range");
    }
    else {
    Serial.print(distance);
    //delay(500);
    }
   Serial.print(", ");
    if (distanceb >= 400 || distanceb <= 2) {
    Serial.print("Out of range");
    }
    else {
    Serial.print(distanceb);
    //delay(500);
    }




  Serial.println(" ");
}

float getVoltageAverage(){
 
     
    float voltage_temp_average=0;
    for(int i=0; i < average_of; i++)
    {
       readVoltage();
       voltage_temp_average +=voltage;
    }
      
  return voltage_temp_average / average_of;
    
}
void readVoltage(){
    
    
    int A0Value = analogRead(alanogPin);
    float voltage_sensed = A0Value * (arduinoVCC / (float)inputResolution); 
      
  voltage = voltage_sensed * ( 1 + ( (float) ValueR2 /  (float) ValueR1) );
  
}