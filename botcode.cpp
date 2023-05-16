/* Bluetooth Controlled Obstacle Avoidance Robot
   by Shubhang Gupta
*/

#include<SoftwareSerial.h>  // To use any pin on Arduino for Serial communication.

// Define the digital  pins for L298 motor control module.

#define IN1 5    // for right motor
#define  IN2 4    // for right motor
#define IN3 3    // for left motor
#define IN4  2    // for left motor
#define ENA 9    // Enable A for PWM control of right  motor
#define ENB 10    // Enable B for PWM control of left motor

// Define  the digital pins for RGB LED control

#define redLED   8
#define greenLED  A0
#define blueLED 11

// Set up the HC-SR04 Ultrasonic sensor module

const  int trigPin = 6;      // TRIG pin connected to pin D6 of Arduino Nano
const int  echoPin = 7;      // ECHO pin connected to pin D7 of Arduino Nano

int i,j,k  = 0;

float duration,distance;  // variables for distance measurement

//  Set up the HC05 Bluetooth module

SoftwareSerial mySerial(12,13); // (12 -->  RX , 13 --> TX)

String data;                    // variables for Bluetooth  control
int btVal;

void setup() {
  // put your setup code here, to  run once:

  pinMode(trigPin,OUTPUT);       // Configure pin D6 to transmit  ultrasonic pulses
  pinMode(echoPin,INPUT);        // Configure pin D7 to receive  ultrasonic pulses

  mySerial.begin(9600);          // Configure the Software  serial at Baud rate 9600

  pinMode(IN1,OUTPUT);           // Configure IN1  - IN4 as OUTPUT to control motors
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(redLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
  pinMode(greenLED,OUTPUT);

  digitalWrite(IN1,LOW);         // Configure the status of the IN1 - IN4 as LOW
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);


  analogWrite(redLED,255);    // Switch OFF LED's. RGB LED is common anode type.
  digitalWrite(blueLED,HIGH);
  digitalWrite(greenLED,HIGH);
}

void  loop()
{
  // put your main code here, to run repeatedly:

  while (mySerial.available())
  {
     data = mySerial.readStringUntil('\n');
  }

     btVal = (data.toInt());

     switch (btVal) 
   {
      case 1:                                
        
        forward();
        digitalWrite(greenLED,LOW);
        analogWrite(redLED,255);
        digitalWrite(blueLED,HIGH);
        dist();
        break;

      case 2:                 
       
        reverse();
        digitalWrite(greenLED,HIGH);
        analogWrite(redLED,255);
        digitalWrite(blueLED,LOW);
        break;

      case 3:         
       
        left();
        break;
        
      case 4:                     
        
        right();
        break;
        
      case 5:                                            
        
        stoprobot();
        digitalWrite(greenLED,HIGH);
        analogWrite(redLED,0);
        digitalWrite(blueLED,HIGH);
        break;

      default:
        digitalWrite(greenLED,HIGH);
        analogWrite(redLED,255);
        digitalWrite(blueLED,HIGH);
        break;

             
    }

        if (mySerial.available()  < 0)                              
    {
     //Serial.println("No Bluetooth  Data ");          
    }
}
     // motor control function declarations

     

     void forward()
     {
       for(i=0;i<=100;i++)
       {
       analogWrite(ENA,i);
       analogWrite(ENB,i);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       }
     }

     void reverse()
     {
       for(j=0;j<=100;j++)
       {
       analogWrite(ENA,j);
       analogWrite(ENB,j);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       }
     }

     void left()
     {
       analogWrite(ENA,127);
       analogWrite(ENB,0);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,HIGH);
     }

     void right()
     {
       analogWrite(ENA,0);
       analogWrite(ENB,127);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
     }

     void stoprobot()
     {
       analogWrite(ENA,0);
       analogWrite(ENB,0);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,LOW);
     }
      void dist()
     {
       digitalWrite(trigPin,LOW);          //  to send a pulse via the TRIG pin of HC-SR04
       delayMicroseconds(2);
       digitalWrite(trigPin,HIGH);
       delayMicroseconds(10);
       digitalWrite(trigPin,LOW);

       duration = pulseIn(echoPin,HIGH);   // read the duration of the pulse

       distance = (duration*0.0343)/2;     // measure the distance in cms. Speed  of sound is 340 m/s or 0.0343 cm/us
       if(distance<20)                     //  if distance is < 20 cms , STOP robot 
       {
        stoprobot();
        digitalWrite(greenLED,HIGH);
        analogWrite(redLED,0);
        digitalWrite(blueLED,HIGH);
       }
        delay(1000);

     }
    
    
