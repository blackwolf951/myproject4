#include <SoftwareSerial.h> 
#include <Wire.h>
#include <Servo.h> // servo library
#define MT_L 3  //ENA
#define IN1 4
#define IN2 2
Servo myservo1, myservo2, myservo3, myservo4, myservo5; // servo name
SoftwareSerial BT(12, 13);
char Car_status;
int Speed_value=150;
void setup(){
  pinMode(MT_L,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
    myservo1.attach(5); // attach servo signal wire to pin 9 1舵機左右
    myservo2.attach(6); // 舵機上下右
    myservo3.attach(9); // 舵機上下左 
    myservo4.attach(10); // 舵機夾子
    myservo5.attach(11); // 車子轉向



  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  BT.begin(9600);
}

void loop()

{
  if(Serial.available() == true){   
    Car_status = Serial.read();  
  }
  
  //Read from bluetooth and write to usb serial
  if(BT.available()>= 2 )
  {
    
    unsigned int servopos = BT.read();
    unsigned int servopos1 = BT.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.println(realservo);


    

    if (realservo >= 6000 && realservo <6180) {
      int servo1 = realservo;
      servo1 = map(servo1, 6000, 6180, 0, 180);
      myservo1.write(servo1);
      Serial.println("Servo 1 ON");
      delay(10);
    }
        if (realservo >= 2000 && realservo < 2180) {
            int servo2 = realservo;
            servo2 = map(servo2, 2000, 2180, 0, 180);
            myservo2.write(servo2);
            Serial.println("Servo 2 ON");
            delay(10);
        }
        if (realservo >= 3000 && realservo < 3180) {
            int servo3 = realservo;
            servo3 = map(servo3, 3000, 3180, 0, 180);
            myservo3.write(servo3);
            Serial.println("Servo 3 ON");
            delay(10);
        }
        if (realservo >= 4000 && realservo < 4180) {
            int servo4 = realservo;
            servo4 = map(servo4, 4000, 4180, 0, 180);
            myservo4.write(servo4);
            Serial.println("Servo 4 ON");
            delay(10);
        }
        if (realservo >= 5000 && realservo < 5180) {
            int servo5 = realservo;
            servo5 = map(servo5, 5000, 5180, 0, 180);
            myservo5.write(servo5);
            Serial.println("Servo 5 ON");
            delay(10);
        }
  }
else if(BT.available()<2){
     
    Car_status =BT.read();  
    Serial.println(Car_status);  
  }
  
//依照Car_status的字元來選擇車子方向控制
 switch(Car_status){   
  case 'F':
    Forward();
    Serial.println("Forward");
    Car_status='N';
    break;
  case 'B':
    Backward();
    Serial.println("Backward");
    Car_status='N';
    break;
  case 'S':
    Stop();
    Serial.println("Stop");
    Car_status='N';
    break;
  case 'v':
    Speed_value=0; //先將速度歸0
    do{
      if (BT.available()){
        Car_status =BT.read();  //讀取藍芽傳送字元
        Serial.println(Car_status); 
        //當藍芽讀取到字元'e'時，就會跳出迴圈。
        if( Car_status=='e'){        
          Serial.println(Speed_value);
          break;
        }         
        else
        //將傳送來的速度數值字元轉成整數。
        Speed_value=10*Speed_value+(Car_status-48); 
      }
    }while(true);      
  }
}

//下面是停止、前進、後退、左轉、右轉的函式。
void Stop() 
{
  analogWrite(MT_L,0);

}

void Forward()
{
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(MT_L,Speed_value); 
}
void Backward()
{
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   analogWrite(MT_L,Speed_value); 
}
