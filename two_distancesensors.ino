
int trigPin1 = 6;
int echoPin1 = 5;

int trigPin2 = 3;
int echoPin2 = 4;



void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
 

  
}

void firstsensor(){ // This function is for first sensor.
  int duration1, distance1;
  digitalWrite (trigPin1, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

      Serial.print("1st Sensor: ");
      Serial.print(distance1); 
      Serial.print("cm    ");
}
void secondsensor(){ // This function is for second sensor.
    int duration2, distance2;
    digitalWrite (trigPin2, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigPin2, LOW);
    duration2 = pulseIn (echoPin2, HIGH);
    distance2 = (duration2/2) / 29.1;
 
      Serial.print("2nd Sensor: ");
      Serial.print(distance2); 
      Serial.print("cm    ");
  
}

void loop() {
Serial.println("\n");
firstsensor();
secondsensor();
delay(1000);
}
