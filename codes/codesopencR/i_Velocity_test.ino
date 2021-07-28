

/*auteur:Charles PAGANEL*/

#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)//utilise ici pour l opencr
  #define DEVICE_NAME "3"
  #define DEVICE_NAME2 "2"
#endif   
//definition baudrate et attribution ids
#define BAUDRATE  1000000
#define DXL_ID1    1
#define DXL_ID2    2
#define DXL_ID3    20
#define DXL_ID4    10
#define DXL_ID5    5
#define BAUDRATE_NUM 7

//attribution des bibliotheques
DynamixelWorkbench dxl1_wb,dxl2_wb,dxl3_wb,dxl4_wb,dxl5_wb;
int incomingByte = 0;
int initpos=500;//position initiale des moteurs du bras

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(9600);//vitesse de lecture du serial 1
  Serial1.begin(9600);//vitesse de lecture du serial 2
  // while(!Serial); // Wait for Opening Serial Monitor, demarrage direct du code
 //check des connections moteurs , attribution d ids interprétables en uint8_t
 
  const char *log;
  bool result1 = false;
  bool result2 = false;
  bool result3 = false;
  bool result4 = false;
  bool result5 = false;

  uint8_t dxl_id = DXL_ID1;
  uint8_t dxl_id2 = DXL_ID2;
  uint8_t dxl_id3 = DXL_ID3;
  uint8_t dxl_id4 = DXL_ID4;
  uint8_t dxl_id5 = DXL_ID5;
  
  uint16_t model_number = 0;
  uint8_t scanned_id[100];
  uint8_t dxl_cnt = 0;
  
  //tableau des baudrate ,pour selectionner celui des moteurs ,ici 1000000
  uint32_t baudrate[BAUDRATE_NUM] = {9600, 57600, 115200, 1000000, 2000000, 3000000, 4000000};
  uint8_t range = 253;
  uint8_t index = 0;
  //check de connection
  result1 = dxl1_wb.init(DEVICE_NAME, baudrate[3], &log);
  result2 = dxl2_wb.init(DEVICE_NAME, baudrate[3], &log);
  result3 = dxl3_wb.init(DEVICE_NAME2, baudrate[3], &log);
  result4 = dxl4_wb.init(DEVICE_NAME2, baudrate[3], &log);
  result5 = dxl5_wb.init(DEVICE_NAME2, baudrate[3], &log);
  
  if (result1 == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  if (result2 == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  if (result3 == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  if (result4 == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  if (result5 == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(baudrate[index]);  
  }
  //fin du check de connection
  
  //dxl_cnt = 0;   //zone de test 1
  //for (uint8_t num = 0; num < 100; num++) scanned_id[num] = 0;

  //result3 = dxl3_wb.scan(scanned_id, &dxl_cnt, range, &log);
  //result4 = dxl4_wb.scan(scanned_id, &dxl_cnt, range, &log);
  //result5 = dxl5_wb.scan(scanned_id, &dxl_cnt, range, &log); //fin de zone de test 1
  
  //check de ping des moteurs
  result1 = dxl1_wb.ping(dxl_id, &model_number, &log);
  result2 = dxl2_wb.ping(dxl_id2, &model_number, &log);
  result3 = dxl3_wb.ping(dxl_id3, &model_number, &log);
  result4 = dxl4_wb.ping(dxl_id4, &model_number, &log);
  result5 = dxl5_wb.ping(dxl_id5, &model_number, &log);
  
  if (result1 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  if (result2 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  if (result3 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  if (result4 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  if (result5 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(dxl_id2);
    Serial.print(dxl_id3);
    Serial.print(dxl_id4);
    Serial.print(dxl_id5);
    
    Serial.print(" model_number : ");
    Serial.println(model_number);
    //fin de check ping moteurs
  }
  //moteurs des chenilles 
  result1 = dxl1_wb.wheelMode(dxl_id, 0, &log);
  result2 = dxl2_wb.wheelMode(dxl_id2, 0, &log);
  if (result1 == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  if (result2 == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
  else   // indicateur du démarrage du robot ( a changer plus tard pour plus de discretion )
  {
    Serial.println("Succeed to change wheel mode");
    Serial.println("Dynamixel is moving...");

    for (int count = 0; count < 1; count++)
    {
      dxl1_wb.goalVelocity(dxl_id, (int32_t)-100);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)100);
      delay(100);

      dxl1_wb.goalVelocity(dxl_id, (int32_t)100);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)-100);
      delay(100);
    }

    dxl1_wb.goalVelocity(dxl_id, (int32_t)0);
    dxl2_wb.goalVelocity(dxl_id2, (int32_t)0);
    dxl3_wb.goalPosition(dxl_id3, (int32_t)500);
    dxl4_wb.goalPosition(dxl_id4, (int32_t)500);
    dxl5_wb.goalPosition(dxl_id5, (int32_t)500);
  }
}

//definition des fonctions de mouvements

void Avancer(){
      //uint32_t baudrate[BAUDRATE_NUM] = {9600, 57600, 115200, 1000000, 2000000, 3000000, 4000000};
      uint8_t dxl_id = DXL_ID1;
      uint8_t dxl_id2 = DXL_ID2;
      uint16_t model_number = 0;

      dxl1_wb.goalVelocity(dxl_id, (int32_t)200);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)-200);
      delay(1500);
      dxl1_wb.goalVelocity(dxl_id, (int32_t)0);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)0);
      Serial.print("go");
}
void Reculer(){
      uint8_t dxl_id = DXL_ID1;
      uint8_t dxl_id2 = DXL_ID2;
      uint16_t model_number = 0;
      //uint32_t baudrate[BAUDRATE_NUM] = {9600, 57600, 115200, 1000000, 2000000, 3000000, 4000000};
    
      dxl1_wb.goalVelocity(dxl_id, (int32_t)-200);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)200);
      delay(1500);
      dxl1_wb.goalVelocity(dxl_id, (int32_t)0);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)0);
      Serial.print("gop");
}
void TournerDroite(){
      uint8_t dxl_id = DXL_ID1;
      uint8_t dxl_id2 = DXL_ID2;
      uint16_t model_number = 0;
      dxl1_wb.goalVelocity(dxl_id, (int32_t)-200);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)-200);
      delay(1500);
      dxl1_wb.goalVelocity(dxl_id, (int32_t)0);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)0);
}
void TournerGauche(){
      uint8_t dxl_id = DXL_ID1;
      uint8_t dxl_id2 = DXL_ID2;
      uint16_t model_number = 0;
      dxl1_wb.goalVelocity(dxl_id, (int32_t)200);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)200);
      delay(1500);
      dxl1_wb.goalVelocity(dxl_id, (int32_t)0);
      dxl2_wb.goalVelocity(dxl_id2, (int32_t)0);
      
}
void Dynaniveau1droite(){
}//ces fonctions ont été mises dans le loop pour faciliter les tests
void Dynaniveau1gauche(){
}
void Dynaniveau2droite(){
}
void Dynaniveau2gauche(){
}
void Dynaniveau3droite(){
}
void Dynaniveau3gauche(){
}
/*tournerTourelleDroite()*/
/*tournerTourelleGauche()*/
//fonctions de gotoposition du bras , position donnée selon un plan
void positionBras(float Ox,float Oy){
  uint8_t dxl_id5 = DXL_ID5;
  //position désirée dans l'espace , referentiel de base de bras 
  //float Ox=-5;
  //float Oy=5;
  //angle de rotation de la baseselon y
  float q1;
  float angleq1;
  //q1=2*atan(Oy/(sqrt(pow(Ox,2)+pow(Oy,2))+Ox));
  //equation d'angle
  q1=atan2(Oy,Ox);
  angleq1=(q1*1023)/(2*3.14);
  Serial.print(angleq1);
  Serial.print("\n");
  dxl5_wb.goalPosition(dxl_id5, (int32_t)angleq1);
  }

//fonctions de gotoposition du bras , position donnée en (x,y,z)
 void positionBras3D(float Ox,float Oy,float Oz){
  uint8_t dxl_id3 = DXL_ID3;
  uint8_t dxl_id4 = DXL_ID4;
  uint8_t dxl_id5 = DXL_ID5;
  float test1;
  float test2;
  float test3;
  float q1;
  float angleq1;
  float q2;
  float angleq2;
  float q3;
  float angleq3;
  float k1;
  float k2;
  float a2=12.5;//longueur du premier os
  float d4=12.5;//longueur du deuxième os
  float angleplus;
  float angleplusq2;
  float angleplusq3;
  float angleplust;
  float angleplusq2t;
  float angleplusq3t;

  //equations d'angles
  q3=asin(( pow(Oz,2)+(pow(Ox,2)+pow(Oy,2))-pow(a2,2)-pow(d4,2))/(2*a2*d4));
  k1=a2+d4*sin(q3);
  k2=d4*cos(q3);
  
  
  //q1=2*atan(Oy/(sqrt(pow(Ox,2)+pow(Oy,2))+Ox));
  q1=atan2(Oy,Ox);
  q2=atan2(k1*Oz-k2*(sqrt(pow(Ox,2)+pow(Oy,2))),k2*Oz+k1*(sqrt(pow(Ox,2)+pow(Oy,2))));
  angleq1=(q1*1023)/(2*3.14);
  test1=(q1*360)/(2*3.14);
  Serial.print(angleq1);
  Serial.print("angleq1    ");
   Serial.print(test1);
   Serial.print("en degre    ");
  Serial.print("\n");
  angleq2=(q2*1023)/(2*3.14);
  test2=(q2*360)/(2*3.14);
  Serial.print(angleq2);
  Serial.print("angleq2    ");
   Serial.print(test2);
   Serial.print("en degre    ");
  Serial.print("\n");
  angleq3=(q3*1023)/(2*3.14);
  test3=(q3*360)/(2*3.14);
  Serial.print(angleq3);
  Serial.print("angleq3    ");
   Serial.print(test3);
   Serial.print("en degre    ");
  Serial.print("\n");
  angleplus=angleq1;
  angleplusq2=angleq2+255.75;
  angleplusq3=angleq3+255.75;
  Serial.print("angleplus    ");
   Serial.print(angleplus);
   Serial.print("angleplusq2    ");
  Serial.print(angleplusq2);
  Serial.print("angleplusq3    ");
   Serial.print(angleplusq3);
   Serial.print("\n");
   angleplust=(angleplus*360)/1023;
   angleplusq2t=(angleplusq2*360)/1023;
   angleplusq3t=(angleplusq3*360)/1023;
   Serial.print("angleplust    ");
   Serial.print(angleplust);
   Serial.print("angleplusq2t    ");
  Serial.print(angleplusq2t);
  Serial.print("angleplusq3t    ");
   Serial.print(angleplusq3t);
   Serial.print("\n");

   //mouvements aux positions voulues
  dxl5_wb.goalPosition(dxl_id5, (int32_t)angleplus);
  dxl4_wb.goalPosition(dxl_id4, (int32_t)angleplusq2);
  dxl3_wb.goalPosition(dxl_id3, (int32_t)angleplusq3);
  
 }






 
void loop() 
{

delay(100);//partie bras du loop sans controle rasp pour l instant
  uint8_t dxl_id = DXL_ID1;
  uint8_t dxl_id2 = DXL_ID2;
  uint8_t dxl_id3 = DXL_ID3;
  uint8_t dxl_id4 = DXL_ID4;
  uint8_t dxl_id5 = DXL_ID5;
//attente de l'info du port pour tester les moteurs du bras a partir de l'entree de l opencr
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  int32_t positiondebase=0;
  //attribution des mouvements en fonction de l'entree sur le port
  if (incomingByte== 109){ 
      initpos=initpos-200;
      dxl3_wb.goalPosition(dxl_id3, (int32_t)initpos);
     delay(100);
  }
  if (incomingByte== 108){
      initpos=initpos+200;
      dxl3_wb.goalPosition(dxl_id3, (int32_t)initpos);
      delay(100);
  }
  if (incomingByte== 107){
      initpos=initpos-200;
      dxl4_wb.goalPosition(dxl_id4, (int32_t)initpos);
      delay(100);
  }
  if (incomingByte== 106){
      initpos=initpos+200;
      dxl4_wb.goalPosition(dxl_id4, (int32_t)initpos);
      delay(100);
  }
   if (incomingByte== 104){
      initpos=initpos-130;
      dxl5_wb.goalPosition(dxl_id5, (int32_t)initpos);
      delay(100);
  }
  if (incomingByte== 103){
      initpos=initpos+130;
      dxl5_wb.goalPosition(dxl_id5, (int32_t)initpos);
      delay(100);
  }
  if (incomingByte== 100){
      Reculer();
      delay(100);
  }
  //Fin du code test moteurs bras

  
  // put your main code here, to run repeatedly:
String readString;
String Q;

//-------------------------------Check Serial Port (code actif dans le keyboard control)---------------------------------------
 //on attend l'info venant du serial1 , sur lequel on ecrit depuis la raspberry , l'info passe du tx de l arduino au rx de l'open cr ,
 //on lit cette info
  while (Serial1.available()){
  delay(1);
  if(Serial1.available()>0){
  char c = Serial1.read();
    Serial.print(c);
    readString += c;
    Q = readString;
    if (Q=="1")
    {
      
      Serial.print("\n");
      //Serial.print(1);
      Avancer();
    }
    if (Q=="2")
    {
      
      Serial.print("\n");
      //Serial.print(2);
      Reculer();
    }
     if (Q=="4")
    {
      
      Serial.print("\n");
      //Serial.print(4);
      TournerDroite();
    }
    if (Q=="3")
    {
      
      Serial.print("\n");
      //Serial.print(3);
      TournerGauche();
    }

  
 // a rajouter pour le controle du bras
       if (Q=="5")
    {
      
      Serial.print("\n");
      //Serial.print(5);
      Dynaniveau1droite();
      initpos=initpos-200;
      dxl3_wb.goalPosition(dxl_id3, (int32_t)initpos);
    }
    if (Q=="6")
    {
      
      Serial.print("\n");
      //Serial.print(6);
      Dynaniveau1gauche();
      initpos=initpos+200;
      dxl3_wb.goalPosition(dxl_id3, (int32_t)initpos);
    }
        if (Q=="7")
    {
      
      Serial.print("\n");
      //Serial.print(7);
      Dynaniveau2droite();
      initpos=initpos-200;
      dxl4_wb.goalPosition(dxl_id4, (int32_t)initpos);
    }
    if (Q=="8")
    {
      
      Serial.print("\n");
      //Serial.print(8);
      Dynaniveau2gauche();
      initpos=initpos+200;
      dxl4_wb.goalPosition(dxl_id4, (int32_t)initpos);
    }
        if (Q=="9")
    {
      
      Serial.print("\n");
      //Serial.print(9);
      Dynaniveau3droite();
      initpos=initpos-130;
      dxl5_wb.goalPosition(dxl_id5, (int32_t)initpos);
    }
    if (Q=="0")
    {
      
      Serial.print("\n");
      //Serial.print(0);
      Dynaniveau3gauche();
      initpos=initpos+130;
      dxl5_wb.goalPosition(dxl_id5, (int32_t)initpos);
    }
    //lettres d'entree pour les positionnements des bras
     if (Q=="a")
    {
      positionBras(5,5);
      
      
    }
      if (Q=="b")
    {
      positionBras3D(14,14,15);
      
      
    }
     if (isControl(c)){
  break;
  }
   
  }
  
 }
 
}
 //FIN DU PROGRAMME
 
 /*
 while (Serial.available()) {
     delay(1000);
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      Serial.print(c);
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 } 
 */  

  
 /*Q = readString;
//--------Checking Serial Read----------
      if(Q=="on"){         
        Serial1.print("1");
        Serial.println("Sent:On");               
      }
      if(Q=="off"){         
        Serial1.print("2");  
        Serial.println("Sent:Off");                          
      }
*/
