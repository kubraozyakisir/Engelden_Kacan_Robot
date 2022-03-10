#include <NewPing.h>
#include <Servo.h>
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define signalPin 8
Servo US_motor;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

volatile bool left = false;
volatile bool right = false;
volatile bool forward = false;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  US_motor.attach(8);
  US_motor.write(110);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

}

void loop() {
  delay(1000);
  US_motor.write(110);                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");
  delay(1000);
  stopNow();

forward = lookForwardAddMap();
left = lookLeftAddMap();
right = lookRightAddMap();

if(forward){
      stopNow();
      delay(1000);
      if(left){
            stopNow();
            delay(1000);
                if(right){
                     stopNow();
                delay(1000);
                goBack();
                }else{
                  stopNow();
                  turnRight();
                }
      }else{
        stopNow();
        turnLeft();
       
      }


}else{
  moveForward();
}


}

int control(){
  if(sonar.ping_cm() < 50 && sonar.ping_cm() != 0){
    Serial.println("cisim gördüm");
    stopNow();
    return true;
  }else{
    return false;
  }
  
}

int lookRightAddMap(){
      Serial.println("saga baktım sagı gördüm");
  delay(1000);

   US_motor.write(180);                    
   if(control()){
     return true;
   }else{
    return false;
   }

}

int lookLeftAddMap(){
        Serial.println("sola baktım solu gördüm");
  delay(1000);

   US_motor.write(0);                    
   if(control()){
     return true;
   }else{
    return false;
   }

}
int lookForwardAddMap(){
        Serial.println("düz baktım düzü gördüm");
  delay(1000);

     US_motor.write(110);                    
   if(control()){
     return true;
   }else{
    return false;
   }

}
int controlLeft(){
    if(sonar.ping_cm() < 50 && sonar.ping_cm() != 0){
    Serial.println("cisim gördüm");
    stopNow();
    delay(1000);
    return true;
  }else{
    return false;
  }
}
int controlRight(){
    if(sonar.ping_cm() < 50 && sonar.ping_cm() != 0){
    Serial.println("cisim gördüm");
    stopNow();
    return true;
  }else{
    return false;
  }
}

int moveForward(){
      Serial.println("düz gidiyorum");


digitalWrite(2, LOW);
digitalWrite(3, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
}

int goBack(){
        Serial.println("geri gidiyorum");


digitalWrite(2, HIGH);
digitalWrite(3, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
}
int stopNow(){
Serial.println("durdum ");
stopRight();
stopLeft();
}
int turnLeft(){
  Serial.println("sola döndüm ");
  startLeft();  
  stopRight();
}

int turnRight(){
  Serial.println("saga döndüm ");
  startRight();
  stopLeft();
}
void startRight(){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
}
void startLeft(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void stopLeft(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}
void stopRight(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}
