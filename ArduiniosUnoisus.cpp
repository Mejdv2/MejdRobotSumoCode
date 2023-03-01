#include <Servo.h>

const char pingPin = 7;  // Trigger Pin 
const char echoPin = 6;  // Echo Pin
const char servoPin = 5; // Servo Pin

const char M1 = 11;
const char M2 = 12;
const char M3 = 13;
const char M4 = 14;

const char EnableM = 15;


const short MaxDeg = 135;
const short MinDeg = 45;
const char speed = 3;


//Servo تحديد زواية

char Noise = 15;

const short DegDif = 15; // شكم زاوية يتحرك Servo كل مرة 
short Degree;
short OrgDeg;

Servo UltrasonicServo;

void setup() {
  pinMode(echoPin, INPUT);
	pinMode(pingPin, OUTPUT);
	
	Degree  = (MaxDeg - MinDeg) / 2;
	Degree += MinDeg;
  OrgDeg  = Degree;
	
	UltrasonicServo.attach(servoPin);
  UltrasonicServo.write(Degree);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(EnableM, OUTPUT);
  
  
	Serial.begin(9600); // يبدأ بورتات علمود نطبع إلى الشاشة
} 



void loop() { 
  float Dist = DistanceToThing(pingPin, echoPin);
  
  if (Dist > 375) {
  	UltrasonicServo.write(Degree);
  	delay(10);
  	
  	if (Degree >= MaxDeg || Degree <= MinDeg) {
      DegDif *= -1;
      
    }
    
    Degree += DegDif;
  	
    
  } else if (Dist > 112) {
  	// turn right 45 deg, walk walkdist

    float TS  = Dist * 0.5
    float TSA = Dist * 0.25
    
  	long Pwr = (TSA * TSA) + (TS * TS);
  	
  	long walkDist = pow(Pwr, 0.5) / Speed;
  	
    
    Dist = DistanceToThing(pingPin, echoPin);
    
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, LOW);
    digitalWrite(M4, LOW);
    
    analogWrite(EnableM, 64);
    delay(20);
    
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    
    analogWrite(EnableM, 128);
    delay(walkDist);
    
    // turn left 90 + X deg, walk w/ acc
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    
    Degree = 90;
    UltrasonicServo.write(Degree);
    
    Dist = DistanceToThing(pingPin, echoPin);
    
    while (Dist > 300) {
      analogWrite(EnableM, 64);
      Dist = DistanceToThing(pingPin, echoPin);
    }
    
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);

    for (int i = 0; i < 256; i++) {
      analogWrite(EnableM, i);
      delay(4);
    }
    
    while (1 == 1) {
    	analogWrite(EnableM, 255);
    }
  } else {
    
    
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    
    analogWrite(EnableM, 64);
    delay(50);
  	
  	digitalWrite(M1, LOW);
    digitalWrite(M3, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M4, HIGH);
  	
  	for (int i = 0; i < 256; i++) {
      analogWrite(EnableM, i);
      delay(4);
    }
  	
  	while (1 == 1) {
  	  // move fwd with bit noise
      
      noise = -noise;
    
      digitalWrite(M2, HIGH);
      digitalWrite(M4, LOW);
    
      analogWrite(EnableM, min(255 + noise, 255));
    
      digitalWrite(M2, LOW);
      digitalWrite(M4, HIGH);
    
      analogWrite(EnableM, min(255 - noise, 255));
    }
    
    
  	
  Serial.print(Dist);
  Serial.print(" centimeters"); 
  Serial.println(); 
} 




float DistanceToThing(int pingPinOut, echoPinIn) {
  long duration, cm;
	 				  
  digitalWrite(pingPinOut, LOW);   	   
  delayMicroseconds(2); 
  
  digitalWrite(pingPinOut, HIGH); 
  delayMicroseconds(10); 
  
  digitalWrite(pingPinOut, LOW);
  
  duration = pulseIn(echoPinIn, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  
  return cm;
  
  
  


long microsecondsToInches(long microseconds) { 
 return microseconds / (74 * 2); 
} 



long microsecondsToCentimeters(long microseconds) { 
	return microseconds / (29 * 2); 
}




short min(x1, x2) {
  if (x1 > x2) {
		return x2;
	}
	
  return x1;