

#include <LiquidCrystal.h>
#include <Servo.h>


LiquidCrystal lcd(12,8,13,11,10,2);
Servo Tourelle;
int angle;
//buzzer et led
int buzzer = 5;//the pin of the active buzzer

int LED =3;
int x;

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);
    Tourelle.attach(7);
    //avancer
    pinMode(3,OUTPUT);
    //reculer
    pinMode(4,OUTPUT);
    //droite
    pinMode(5,OUTPUT);
    //gauche
    pinMode(6,OUTPUT);
    //buzzer et led
    pinMode(LED,OUTPUT);
    pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
    
    while (x<=255){
        analogWrite(LED,x);
        delay(10);
        x=x+1;
   
    }
    x=255;
    while (x>=0){
        analogWrite(LED,x);
        delay(10);
        x=x-1;
   
    }
    x=0;
    while (x<=200){
        analogWrite(LED,x);
        delay(10);
        x=x+1;
   
    }
    x=200;
    unsigned char i,j;
    for(i=0;i<80;i++)
    {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<100;i++)
    {
    digitalWrite(buzzer,HIGH);
    delay(2);//wait for 2ms
    digitalWrite(buzzer,LOW);
    delay(2);//wait for 2ms
    }
}
void loop() {
  //REVOLUTION SERIAL
  String readString;
  String Q;

  //-------------------------------Check Serial Port---------------------------------------
   while (Serial.available()) {
        delay(1);
      if (Serial.available() >0) {
        char c = Serial.read();  //gets one byte from serial buffer
      if (isControl(c)) {
        //'Serial.println("it's a control character");
        break;
      }
        readString += c; //makes the string readString    
      }
   }   

   Q = readString;
  //--------Checking Serial Read----------
        if(Q=="1"){         
          //digitalWrite(13,HIGH);AVANCE
          Serial.print(1);
          Serial.print("\n");
          delay(100); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);    
        }
        if(Q=="2"){   
    //RECULE      
          Serial.print(2); 
          Serial.print("\n"); 
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);         
        }
        if(Q=="3"){    
     //GAUCHE     
          //digitalWrite(13,HIGH);
          Serial.print(3); 
          Serial.print("\n");   
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);     
        }
        if(Q=="4"){   
    //DROITE      
          Serial.print(4);  
          Serial.print("\n"); 
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);          
        }
         if(Q=="5"){    
     //GAUCHE     
          //digitalWrite(13,HIGH);
          Serial.print(5); 
          Serial.print("\n");   
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);     
        }
        if(Q=="6"){   
    //DROITE      
          Serial.print(6);  
          Serial.print("\n"); 
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);          
        }
        if(Q=="7"){    
     //GAUCHE     
          //digitalWrite(13,HIGH);
          Serial.print(7); 
          Serial.print("\n");   
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);     
        }
        if(Q=="8"){   
    //DROITE      
          Serial.print(8);  
          Serial.print("\n"); 
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);          
        }
        if(Q=="9"){    
     //GAUCHE     
          //digitalWrite(13,HIGH);
          Serial.print(9); 
          Serial.print("\n");   
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);     
        }
        if(Q=="0"){   
    //DROITE      
          Serial.print(0);  
          Serial.print("\n"); 
          delay(100);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);          
        } 
          if(Q=="a"){         
          //digitalWrite(13,HIGH);AVANCE
          Serial.print("a");
          Serial.print("\n");
          delay(100); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);    
        }
          if(Q=="b"){         
          //digitalWrite(13,HIGH);AVANCE
          Serial.print("b");
          Serial.print("\n");
          delay(100); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("deplacement");
          delay(1000);    
        }
        


  //variable de commande
  char commande;
  analogWrite(LED,200);
  if (Serial.available()>0){
    commande=Serial.read();
  }
  lcd.setCursor(0,0);
  lcd.print("mode keyboard");
  lcd.setCursor(0,1);
  lcd.print("   control");
  delay(100);
   
  
  /*switch (commande){
    case 's':
      digitalWrite(5,HIGH);
      Serial.println(commande);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("deplacement");
      delay(1000);
      digitalWrite(5,LOW);
      break;
      
     case 'w':
      digitalWrite(4,HIGH);
      Serial.println(commande);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("deplacement");
      delay(1000);
      digitalWrite(4,LOW);
      break;
      
     case 'a':
      digitalWrite(7,HIGH);
      Serial.println(commande);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("deplacement");
      delay(1000);
      digitalWrite(7,LOW);
      break;
      
     case 'd':
      digitalWrite(6,HIGH);
      Serial.println(commande);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("deplacement");
      delay(1000);
      digitalWrite(6,LOW);
      break;
      
     case 'q':
       angle=angle+20;
       if (angle>170) {
         angle=angle-10;
       }
       Serial.println(commande);
       Serial.print(",angle  ");
       Serial.println(angle);
       Tourelle.write(angle);
       break;
      
      case 'e': 
       angle=angle-20;
       if (angle<10) {
         angle=angle+10;
       }
       Serial.println(commande);
       Serial.print(",angle  ");
       Serial.println(angle);
       Tourelle.write(angle);
       break;
       
      default:
       break;
  }
  */
  /*
  digitalWrite(6,LOW);  
  digitalWrite(7,LOW); 
  digitalWrite(4,LOW); 
  digitalWrite(5,LOW);  
     */

}
