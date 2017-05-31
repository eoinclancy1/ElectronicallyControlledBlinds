int ENA=2;//connected to Arduino's port 2
int IN1=3;//connected to Arduino's port 3
int IN2=4;//connected to Arduino's port 4
int ENB=5;//connected to Arduino's port 5
int IN3=6;//connected to Arduino's port 6
int IN4=7;//connected to Arduino's port 7
int i;
int j;
int switchPinCW = 8;
int switchPinACW = 13;
int buttonNow;
int buttonPrevious;
int debounceTime = 150;
int operationTime = 11000;
unsigned long  changeTime;
String now;
String previous;

 
void setup()
{
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 digitalWrite(ENA,HIGH);//enablae motorA
 digitalWrite(ENB,HIGH);//enable motorB
 pinMode(switchPinCW, INPUT_PULLUP);
 pinMode(switchPinACW, INPUT_PULLUP);
 Serial.begin(9600);
 pinMode(12,INPUT_PULLUP);                                                                      //Input pullup means no need to connect both Vcc and Ground, arduino does some work for you
 buttonNow = digitalRead(12);
 buttonPrevious = buttonNow;
}
void loop()
{/*In the way of 4 beats to drive the stepping motor,A group connected to motorA,B
 B group connected to motorB,Suppose A representing the forward current of A group,
 A- representing the reverse current of A group,B representing the forward current of B group,
 B- representing the reverse current of B group.
 this way run as follow:
 AB    A-B    A-B-   AB-
 or
 AB   AB-    A-B-   A-B
 */
 
 buttonNow = digitalRead(12);
 Serial.print(" ButtonNow = ");
 Serial.println(buttonNow);
 
 if (buttonNow != buttonPrevious){
          Serial.println("In if statement");
          changeTime = millis();
          Serial.println(changeTime);
          Serial.println(millis());
          while( (millis() - changeTime) < debounceTime ){
            Serial.println("Waiting.....");
          }
          buttonNow = digitalRead(12);
          if (buttonNow == buttonPrevious){                              //small glitch - ignore
               Serial.println("now and previous match");
          }
          
          else{                                                          //confirmed switch - engage blinds
                switch(buttonNow) {
                  case 1:
                          openBlindsFull();
                          Serial.println("Opening....");
                          break;
                  case 0:
                          closeBlindsFull();
                          Serial.println("Closing....");
                          break;
                  default:
                          break;
                }
          }

  
 }

  buttonPrevious = buttonNow;
  Serial.print(" ButtonPrevious = ");
  Serial.println(buttonPrevious);

 ////////////////////// Code for Rocker Switch (DPDT) /////////////////////////////
 if ((digitalRead(switchPinCW) == HIGH) && (digitalRead(switchPinACW) == HIGH))
    {
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,LOW);
       delay(1000);
    }
 else if (digitalRead(switchPinCW) == HIGH)
    {
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       delay(10);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(10);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(10);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       delay(10);
    }
else if (digitalRead(switchPinACW) == HIGH)
    {
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       delay(10);
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(10);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
       delay(10);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       delay(10);
    }

}

void openBlindsFull() {
  unsigned long currTime = millis();
  while ( (millis() - currTime) < operationTime ){
             digitalWrite(IN1,HIGH);
             digitalWrite(IN2,LOW);
             digitalWrite(IN3,HIGH);
             digitalWrite(IN4,LOW);
             delay(10);
             digitalWrite(IN1,HIGH);
             digitalWrite(IN2,LOW);
             digitalWrite(IN3,LOW);
             digitalWrite(IN4,HIGH);
             delay(10);
             digitalWrite(IN1,LOW);
             digitalWrite(IN2,HIGH);
             digitalWrite(IN3,LOW);
             digitalWrite(IN4,HIGH);
             delay(10);
             digitalWrite(IN1,LOW);
             digitalWrite(IN2,HIGH);
             digitalWrite(IN3,HIGH);
             digitalWrite(IN4,LOW);
             delay(10);
  }
}

void closeBlindsFull() {
  unsigned long currTime = millis();
  while ( (millis() - currTime) < operationTime ){
             digitalWrite(IN1,LOW);
             digitalWrite(IN2,HIGH);
             digitalWrite(IN3,HIGH);
             digitalWrite(IN4,LOW);
             delay(10);
             digitalWrite(IN1,LOW);
             digitalWrite(IN2,HIGH);
             digitalWrite(IN3,LOW);
             digitalWrite(IN4,HIGH);
             delay(10);
             digitalWrite(IN1,HIGH);
             digitalWrite(IN2,LOW);
             digitalWrite(IN3,LOW);
             digitalWrite(IN4,HIGH);
             delay(10);
             digitalWrite(IN1,HIGH);
             digitalWrite(IN2,LOW);
             digitalWrite(IN3,HIGH);
             digitalWrite(IN4,LOW);
             delay(10);
  }
}

