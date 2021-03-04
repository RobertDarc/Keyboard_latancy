

#include <PWMServo.h>
PWMServo myservo;  // create servo object to control a servo

 
// set pin numbers:
const int ButtonPin = 2;     // the number of the pushbutton pin for test-servo
const int SensorPin = 3;     // the number of the pushbutton pin for sensor-Key
const int SensorValue = A1;  // the numer  of the Annalog pin for de Potmeter-servo trim

const int ledPin = 12;
int incomingByte = 0;

// variables will change:
int ButtonState = 0;         // variable for reading the pushbutton status
int SensorState = 0;         // variable for reading the pushbutton status
int Sensor=0;

bool knop=false;

//---------------------------------------------------------------------------------------------
void setup() {

    myservo.attach(SERVO_PIN_A);         // attaches the servo on pin 9 to the servo object
  //myservo.attach(SERVO_PIN_A, 1000, 2000); // some motors need min/max setting
  
   pinMode(ledPin, OUTPUT);
   pinMode(ButtonPin, INPUT);
   pinMode(SensorPin, INPUT);
}




//----------------------------------------------------------------------------------------------
void loop() {

    Serial.begin(115200);
    
         Sensor = analogRead(SensorValue);
     //  Serial.println(Sensor);

 

// val = analogRead(potpin);                 // reads the value of the potentiometer (value between 0 and 1023)
  Sensor = map(Sensor, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(Sensor);                    // sets the servo position according to the scaled value
 // delay(15);                             // waits for the servo to get there



     if (Serial.available() > 0) {
            // read the incoming byte:
          incomingByte = Serial.read();

     }
     
       if (incomingByte == 112)                //  Toets p for Servo 
           {                              
            //myservo.write(Sensor-25);      //stuur servo aan via seriaal char S
             myservo.write(Sensor);         // stuur servo terug naar begin stand
            delay(75);
           }  
                     
       if (incomingByte == 114)                //  recieved R for led io 12  from presentation
           {                              
               digitalWrite(ledPin, HIGH);   
               delay(30);
              digitalWrite(ledPin, LOW);        
           }  
           
   
 
  
    // read the state of the pushbutton value:
      ButtonState = digitalRead(ButtonPin);
      SensorState = digitalRead(SensorPin);

 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:


if (SensorState == HIGH) {
    // turn LED on:
        //digitalWrite(ledPin, HIGH);
        Serial.print("S");
    // Serial.println("");
     
  } else {
    // turn LED off:
   // digitalWrite(ledPin, LOW);
  }


 

//----------------------------------------------------------------


      
  
  if (ButtonState == HIGH && knop== false) {

         
         myservo.write(Sensor-25);
         delay(75);
        // myservo.write(Sensor);
         knop=true;          
   }


if (ButtonState == LOW && knop== true) {
  

       knop=false;

}

//delay(10);
  
}
