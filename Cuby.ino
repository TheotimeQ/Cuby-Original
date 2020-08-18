//-------Library-------------------------------

#include <Servo.h>

//------Declaration Objets---------------------

Servo BrasGauche;  
Servo BrasDroit;
Servo SourcilGauche;  
Servo SourcilDroit;
Servo Oeil;
Servo Bouche;
Servo Drapeau;


//truc

//------Declaration Pins-----------------------

const int NezDroitPin  = 26 ;   //Pin des Boutons du Nez
const int NezGauchePin = 27 ;
const int Rouge = 10 ;
const int Vert = 11 ;
const int Bleu = 12 ;

//------Declaration Variables------------------

int EtatNezDroit   ;   //EtatBoutonNez
int EtatNezGauche  ;
int EtatFinDroit  ;   //EtatBouton de fin de course
int EtatFinGauche ;
int PositionBrasGauche = 117  ; // Stock la position des bras
int PositionBrasDroit = 73 ;
int ButDroit = 115 ;
int ButGauche = 170 ;
int Count = 0 ;
int Humeur = 0 ;
int Veille = 0 ;
int NumAlea ;             // Nombre aleatoire qui defini la reaction


//------Initialisation-------------------------

void setup() {
  Serial.begin(9600);
  
  pinMode(NezDroitPin, INPUT);     //Declare les bouton du Nez
  pinMode(NezGauchePin, INPUT);

  EtatNezGauche = digitalRead(NezGauchePin);
  EtatNezDroit = digitalRead(NezDroitPin)  ;

  SourcilGauche.attach(4);     //Declare les ServoMoteurs
  SourcilDroit.attach(5);
  BrasGauche.attach(13);            
  BrasDroit.attach(7);
  Oeil.attach(8);
  Bouche.attach(6);
  Drapeau.attach(9);

  BrasDroit.write(PositionBrasDroit);
  BrasGauche.write(PositionBrasGauche);
  BougerBras(115,115,0,PositionBrasDroit,PositionBrasDroit,0);
  BoucheStyle(1);
  Yeux(2);
  Drapeau.write(57);
  Couleur(0,150,150);
  Sourcil(126,30) ;

  randomSeed(analogRead(0));
}

//------Boucle---------------------------------

void loop() {

  EtatNezGauche = digitalRead(NezGauchePin);
  EtatNezDroit = digitalRead(NezDroitPin)  ;

  NumAlea = 400 ;
  
  if (EtatNezGauche == HIGH){
    NumAlea = random(0, 20) ;
    Veille = 0 ;
    
  }

  if (EtatNezDroit == HIGH){
    NumAlea = random(20, 40) ;
    Veille = 0 ;
  } 

  if(Veille > 3000){
    Veille = 3001 ;
    NumAlea = 104 ;
  }
  if(Veille > 2000 and Veille < 2100){
    Veille = 2101 ;
    NumAlea = 103 ;
  }
  if(Veille > 1000 and Veille < 1100){
    Veille = 1101 ;
    NumAlea = 102 ;
  } 
  if(Veille > 500 and Veille < 600){
    Veille = 601 ;
    NumAlea = 101 ;
  }
  
  Serial.print("Count : ");
  Serial.print(Count);
  Serial.print("  Veille : ");
  Serial.print(Veille);
  Serial.print("  NumAlea : ");
  Serial.println(NumAlea);
      
  switch (NumAlea) {
    
  //------------Case Bras Gauche (0,19)-----------------

   case 0: 
      Sourcil(170,0);
      for (int i=0; i <= 10; i++){
          Couleur(0,0,0);
          delay(100);
          Couleur(0,0,255);
          delay(100);
      }
      BougerBras(PositionBrasGauche,ButGauche,0.6,PositionBrasDroit,PositionBrasDroit,0);
      delay(100);
      BougerBras(ButGauche,PositionBrasGauche,0.6,PositionBrasDroit,PositionBrasDroit,0);
      delay(100);
      Count += 1 ;

     break;
   case 1:

      Couleur(255,0,0);
      Sourcil(85,60);
      BoucheStyle(2);
      Yeux(1);
      delay(1000);
      Yeux(3);
      delay(1000);
      Yeux(1);
      delay(1000);
      BougerBras(PositionBrasGauche,ButGauche,0.8,PositionBrasDroit,PositionBrasDroit,0);
      Yeux(3);
      delay(100);
      BougerBras(ButGauche,PositionBrasGauche,0.8,PositionBrasDroit,PositionBrasDroit,0);
      Yeux(1);
      Count += 1 ;
      
     break;
   case 2:

      Couleur(0,255,0);
      Sourcil(170,0);
      Yeux(1);
      BoucheStyle(2);
      BougerBras(PositionBrasGauche,PositionBrasGauche+20,0.5,PositionBrasDroit,PositionBrasDroit,0);
      delay(1000);
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
        Couleur(0,fadeValue,0);
        delay(10);
      }
      delay(2000);
      BougerBras(PositionBrasGauche+20,ButGauche,1,PositionBrasDroit,PositionBrasDroit,0);
      delay(100);
      BougerBras(ButGauche,PositionBrasGauche,1,PositionBrasDroit,PositionBrasDroit,0);
      Count += 1 ;
      
     break;
   case 3:

      Couleur(0,150,150);
      Sourcil(125,30) ; 
      BoucheStyle(2) ;
      Yeux(2) ;
      Paix() ;

      while(EtatNezDroit == HIGH or EtatNezGauche == HIGH){
        delay(500);
        EtatNezGauche = digitalRead(NezGauchePin);
        EtatNezDroit = digitalRead(NezDroitPin)  ;
      }
     Count += 1 ;
     
     break;
   case 4:

      Couleur(190,0,180);
      Sourcil(125,30) ; 
      BoucheStyle(1) ;
      Yeux(1);
      for (int i=180; i >= 0; i -= 1){
          Couleur(i+10,0,i);
          Sourcil(125+(i/3),30+(i/3)) ; 
          delay(10);
      
        }
        Yeux(3);
      for (int i=0; i <= 180; i += 1){
          Couleur(i+10,0,i);
          Sourcil(125+(i/3),30+(i/3)) ; 
          delay(10);

        }
      delay(100);
      BougerBras(PositionBrasGauche,ButGauche,0.4,PositionBrasDroit,PositionBrasDroit,0);
      delay(100);
      BougerBras(ButGauche,PositionBrasGauche,0.4,PositionBrasDroit,PositionBrasDroit,0);
      Count += 1 ;

     break;
   case 5:

      Sourcil(140,180) ; 
      Oeil.write(125); // 125 85
      delay(500);
      
      Sourcil(140,140) ; 
      Couleur(0,150,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(500);
      Sourcil(180,180) ; 
      Couleur(200,0,150);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(200);
      Sourcil(140,140) ; 
      Couleur(150,0,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(600);
      Sourcil(180,180) ; 
      Couleur(78,32,128);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(200);
      Sourcil(140,140) ; 
      Couleur(150,0,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(100);
      Sourcil(180,180) ; 
      Couleur(255,0,150);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(200);
      Sourcil(140,140) ; 
      Couleur(255,150,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(150);
      Sourcil(180,180) ; 
      Couleur(75,255,30);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(300);
      BougerBras(PositionBrasGauche,ButGauche-3,1,PositionBrasDroit,ButDroit-3,1);
      delay(500);
      BougerBras(ButGauche-3,PositionBrasGauche,1,ButDroit-3,PositionBrasDroit,1);
      Count += 1 ;
      
     break;
   case 6:
       Couleur(0,0,0);
       Sourcil(170,0) ;
       Yeux(3) ;
       delay(500);
       Couleur(75,75,255);
       Sourcil(100,50) ;
       Yeux(2) ;
       delay(300);
       Couleur(100,255,0);
       Sourcil(30,80) ;
       Yeux(1) ;
       delay(600);
       Couleur(200,0,200);
       Sourcil(80,120) ;
       Yeux(2) ;
       delay(250);
       Couleur(100,200,0);
       Sourcil(10,90) ;
       Yeux(3) ;
       delay(400);
       Couleur(0,75,150);
       Sourcil(35,46) ;
       Yeux(1) ;
       delay(700);
       Couleur(0,150,75);
       Sourcil(0,0) ;
       Yeux(1) ;
       delay(900);
       Couleur(50,75,0);
       Sourcil(180,180) ;
       Yeux(2) ;
       delay(250);
       Couleur(75,30,255);
       Sourcil(22,17) ;
       Yeux(3) ;
       delay(450);
       Couleur(255,0,75);
       Sourcil(170,60) ;
       Yeux(1) ;
       delay(500);
       Couleur(255,60,30);
       Sourcil(170,0) ;
       Yeux(2) ;
       delay(100);
       BougerBras(PositionBrasGauche,ButGauche,1,PositionBrasDroit,PositionBrasDroit,0);
       delay(100);
       BougerBras(ButGauche,PositionBrasGauche,1,PositionBrasDroit,PositionBrasDroit,0);
       Count += 1 ;
    
     break;
   case 7: 
      delay(1000);
      Couleur(255,0,0);
      delay(150);
      Couleur(0,150,150);
      delay(1500);
      Couleur(255,0,0);
      delay(150);
      Couleur(0,150,150);
      delay(1000);
      for (int i=0; i <= 255; i += 1){
         Couleur(i,0,0);
         delay(10);
         Couleur(0,255-i,255-i);
         delay(10);
      }
      Couleur(255,0,0);
      Sourcil(86,60) ;
      BoucheStyle(2) ;
      Yeux(1) ;
      delay(1000);
      Yeux(3) ;
      delay(1000);
      Yeux(1) ;
      delay(1000);
      Yeux(3) ;
      delay(1000);
      Humeur = 1 ;
      delay(100);
      BougerBras(PositionBrasGauche,ButGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
      delay(100);
      BougerBras(ButGauche,PositionBrasGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
      Count += 1 ;
      
     break;
   case 8:
    Couleur(255,0,0);
    delay(1000);
    Couleur(0,255,0);
    delay(1000);
    Sourcil(170,0);
    Couleur(0,0,255);
    delay(1000);
    BoucheStyle(2);
    delay(1000);
    BougerBras(PositionBrasGauche,ButGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
    delay(500);
    BougerBras(ButGauche,PositionBrasGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
     
    
     break;
   case 9:

     
   
     break;
   case 10:

     
    
     break;
   case 11:

     
      
     break;
   case 12:
  
     
    
     break;
   case 13:

     
     
     break;
   case 14:
   
     
     
     break;
   case 15:

     
     
     break;
   case 16:

     Sourcil(126,5);
     Yeux(3);
     delay(1000);
     Sourcil(155,30);
     Yeux(1);
     delay(1000);
     Sourcil(126,30);
     BougerBras(PositionBrasGauche,ButGauche-3,1,PositionBrasDroit,ButDroit-3,1);
     delay(500);
     BougerBras(ButGauche-3,PositionBrasGauche,1,ButDroit-3,PositionBrasDroit,1);
     Count += 1 ;
     
     break;
   case 17:

     delay(300);
     BougerBras(PositionBrasGauche,ButGauche-3,1.2,PositionBrasDroit,ButDroit-3,0.3);
     delay(500);
     BougerBras(ButGauche-3,PositionBrasGauche,0.3,ButDroit-3,PositionBrasDroit,1.2);
     Count += 1 ;
     
     break;
   case 18:

      Couleur(0,150,150);
      Sourcil(170,0) ;
      BoucheStyle(2) ;
      Yeux(1) ;

      for (int i=57; i <= 140; i += 1){
          BrasDroit.write(PositionBrasDroit+(i/5));
          Drapeau.write(i);
          delay(20);
      }
      Couleur(0,0,0);
      delay(500);
      Couleur(255,0,0);
      delay(100);
      Couleur(0,0,0);
      delay(100);
      for (int i=0; i <= 20; i += 1){
          Couleur(0,150,150);
          delay(80-i);
          Couleur(255,0,0);
          delay(80-i);
      }
      delay(500);
      Sourcil(85,60);
      Couleur(255,0,0);
      BougerBras(PositionBrasGauche+15,ButGauche,1.5,ButDroit,ButDroit,0);
      Drapeau.write(57);
      BoucheStyle(1) ;
      Yeux(2) ;
      delay(200);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1.5);
      delay(500);
      BougerBras(PositionBrasGauche,PositionBrasGauche+25,0.8,PositionBrasDroit,PositionBrasDroit+22,0.8);
      delay(500);
      BougerBras(PositionBrasGauche+25,PositionBrasGauche,0.8,PositionBrasDroit+25,PositionBrasDroit,0.8);
      delay(500);
      BougerBras(PositionBrasGauche,PositionBrasGauche+25,0.8,PositionBrasDroit,PositionBrasDroit+25,0.8);
      delay(500);
      BougerBras(PositionBrasGauche+25,PositionBrasGauche,0.8,PositionBrasDroit+25,PositionBrasDroit,0.8);      
      delay(800);
      Count += 1 ;
      
     break;
   case 19:

      Couleur(25,25,25);
      Sourcil(170,0) ;
      BoucheStyle(2) ;
      Yeux(2) ;
      Drapeau.write(160);

      while(EtatNezDroit == HIGH or EtatNezGauche == HIGH){
        delay(500);
        Yeux(1) ;
        delay(500);
        Yeux(2) ;
        delay(500);
        Yeux(3) ;
        delay(500);
        Yeux(2) ;
        EtatNezGauche = digitalRead(NezGauchePin);
        EtatNezDroit = digitalRead(NezDroitPin)  ;
        
      } 
        Drapeau.write(57);
        Count += 1 ;
    
     break;

//-------------Case Bras Droit (20,39)-----------------

   case 20: 
      Sourcil(170,0);
      for (int i=0; i <= 10; i++){
          Couleur(0,0,0);
          delay(100);
          Couleur(0,0,255);
          delay(100);
      }
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,0.6);
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,0.6);
      delay(100);
      Count += 1 ;

     break;
   case 21:

      Couleur(255,0,0);
      Sourcil(85,60);
      BoucheStyle(2);
      Yeux(1);
      delay(1000);
      Yeux(3);
      delay(1000);
      Yeux(1);
      delay(1000);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,0.8);
      Yeux(3);
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,0.8);
      Yeux(1);
      Count += 1 ;
      
     break;
   case 22:

      Couleur(0,255,0);
      Sourcil(170,0);
      Yeux(1);
      BoucheStyle(2);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,PositionBrasDroit+20,0.5);
      delay(1000);
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
        Couleur(0,fadeValue,0);
        delay(10);
      }
      delay(2000);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit+20,ButDroit,1);
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1);
      Count += 1 ;
      
     break;
   case 23:

      Couleur(0,150,150);
      Sourcil(125,30) ; 
      BoucheStyle(2) ;
      Yeux(2) ;
      Paix() ;

      while(EtatNezDroit == HIGH or EtatNezGauche == HIGH){
        delay(500);
        EtatNezGauche = digitalRead(NezGauchePin);
        EtatNezDroit = digitalRead(NezDroitPin)  ;
      }
     Count += 1 ;
     
     break;
   case 24:

      Couleur(190,0,180);
      Sourcil(125,30) ; 
      BoucheStyle(1) ;
      Yeux(1);
      for (int i=180; i >= 0; i -= 1){
          Couleur(i+10,0,i);
          Sourcil(125+(i/3),30+(i/3)) ; 
          delay(10);
      
        }
        Yeux(3);
      for (int i=0; i <= 180; i += 1){
          Couleur(i+10,0,i);
          Sourcil(125+(i/3),30+(i/3)) ; 
          delay(10);

        }
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,0.4);
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,0.4);
      Count += 1 ;

     break;
   case 25:

      Sourcil(140,180) ; 
      Oeil.write(125); // 125 85
      delay(500);
      
      Sourcil(140,140) ; 
      Couleur(0,150,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(500);
      Sourcil(180,180) ; 
      Couleur(200,0,150);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(200);
      Sourcil(140,140) ; 
      Couleur(150,0,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(600);
      Sourcil(180,180) ; 
      Couleur(78,32,128);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(200);
      Sourcil(140,140) ; 
      Couleur(150,0,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(100);
      Sourcil(180,180) ; 
      Couleur(255,0,150);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(200);
      Sourcil(140,140) ; 
      Couleur(255,150,0);
      for (int i=125; i >= 85; i -= 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 
      
      delay(150);
      Sourcil(180,180) ; 
      Couleur(75,255,30);
      for (int i=85; i <= 125; i += 2){
         Oeil.write(i);
         delay(20);
      }
      Sourcil(140,180) ; 

      delay(300);
      BougerBras(PositionBrasGauche,ButGauche-3,1,PositionBrasDroit,ButDroit-3,1);
      delay(500);
      BougerBras(ButGauche-3,PositionBrasGauche,1,ButDroit-3,PositionBrasDroit,1);
      Count += 1 ;
      
     break;
   case 26:
       Couleur(0,0,0);
       Sourcil(170,0) ;
       Yeux(3) ;
       delay(500);
       Couleur(75,75,255);
       Sourcil(100,50) ;
       Yeux(2) ;
       delay(300);
       Couleur(100,255,0);
       Sourcil(30,80) ;
       Yeux(1) ;
       delay(600);
       Couleur(200,0,200);
       Sourcil(80,120) ;
       Yeux(2) ;
       delay(250);
       Couleur(100,200,0);
       Sourcil(10,90) ;
       Yeux(3) ;
       delay(400);
       Couleur(0,75,150);
       Sourcil(35,46) ;
       Yeux(1) ;
       delay(700);
       Couleur(0,150,75);
       Sourcil(0,0) ;
       Yeux(1) ;
       delay(900);
       Couleur(50,75,0);
       Sourcil(180,180) ;
       Yeux(2) ;
       delay(250);
       Couleur(75,30,255);
       Sourcil(22,17) ;
       Yeux(3) ;
       delay(450);
       Couleur(255,0,75);
       Sourcil(170,60) ;
       Yeux(1) ;
       delay(500);
       Couleur(255,60,30);
       Sourcil(170,0) ;
       Yeux(2) ;
       delay(100);
       BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,1);
       delay(100);
       BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1);
       Count += 1 ;
    
     break;
   case 27: 
      delay(1000);
      Couleur(255,0,0);
      delay(150);
      Couleur(0,150,150);
      delay(1500);
      Couleur(255,0,0);
      delay(150);
      Couleur(0,150,150);
      delay(1000);
      for (int i=0; i <= 255; i += 1){
         Couleur(i,0,0);
         delay(10);
         Couleur(0,255-i,255-i);
         delay(10);
      }
      Couleur(255,0,0);
      Sourcil(86,60) ;
      BoucheStyle(2) ;
      Yeux(1) ;
      delay(1000);
      Yeux(3) ;
      delay(1000);
      Yeux(1) ;
      delay(1000);
      Yeux(3) ;
      delay(1000);
      Humeur = 1 ;
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,1.5);
      delay(100);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1.5);
      Count += 1 ;
      
     break;
   case 28:

      while(EtatNezDroit == HIGH or EtatNezGauche == HIGH){
          EtatNezGauche = digitalRead(NezGauchePin);
          EtatNezDroit = digitalRead(NezDroitPin)  ;
          Couleur(random(0,255),random(0,255),random(0,255));
          Sourcil(random(0,180),random(0,180));
          Oeil.write(random(85,125));
          delay(random(80,500));
      }
     Count += 1 ;
      
     break;
   case 29:

     
   
     break;
   case 30:

     
    
     break;
   case 31:

     
      
     break;
   case 32:
  
     
    
     break;
   case 33:
     
      
     break;
   case 34:
     delay(1000);
     Sourcil(126,0);
     Yeux(1);
     delay(1000);
     Yeux(2);
     delay(1000);
     Yeux(3);
     delay(1000);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,0.7);
     delay(100);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,0.7);
     Yeux(2);
     Sourcil(126,30);
     delay(500);
     BougerBras(PositionBrasGauche,ButGauche+8,1.5,PositionBrasDroit,PositionBrasDroit,0);
     delay(200);
     BougerBras(ButGauche+8,PositionBrasGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
     delay(200);
     Yeux(3);
     Sourcil(126,0);
     Couleur(50,150,150);
     delay(500);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit,1);
     delay(100);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1);
     Yeux(2);
     Sourcil(126,30);
     BougerBras(PositionBrasGauche,ButGauche+8,1.5,PositionBrasDroit,PositionBrasDroit,0);
     delay(200);
     BougerBras(ButGauche+8,PositionBrasGauche,1.5,PositionBrasDroit,PositionBrasDroit,0);
     Yeux(3);
     Sourcil(85,60);
     Couleur(100,100,100);
     BougerBras(PositionBrasGauche,ButGauche,1.5,PositionBrasDroit,ButDroit,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit-20,ButDroit,1);
     Couleur(100,100,100);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit-20,ButDroit,1);
     Couleur(150,75,75);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit-20,ButDroit,1);
     Couleur(200,50,50);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit-20,ButDroit,1);
     Couleur(250,50,50);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(ButGauche,ButGauche,0,ButDroit-20,ButDroit,1);
     Couleur(250,0,0);
     BoucheStyle(2) ;
     delay(200);
     BougerBras(ButGauche,PositionBrasGauche,0.5,ButDroit,ButDroit-20,1);
     delay(200);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit-20,ButDroit,1);
     delay(100);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1);
     Humeur = 1 ;
     Count += 1 ;
     
     break;
   case 35:

     Couleur(100,0,255);
     Yeux(3);
     BoucheStyle(2) ;
     
     for (int i=125; i >= 85; i -= 1){
          Oeil.write(i);
          delay(20);
      }
     for (int i=0; i <= 180; i += 1){
          Sourcil(i,180-i);
          delay(20);
      }
     for (int i=180; i >= 0; i -= 1){
          Sourcil(i,180-i);
          delay(20);
      }
     Drapeau.write(160);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit,ButDroit-20,0.4);
     delay(800);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit-20,ButDroit,1);
     delay(800);
     BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1.5);
     Count +=1 ;
       
     break;
   case 36:

     Sourcil(126,5);
     Yeux(3);
     delay(1000);
     Sourcil(155,30);
     Yeux(1);
     delay(1000);
     Sourcil(126,30);
     BougerBras(PositionBrasGauche,ButGauche-3,1,PositionBrasDroit,ButDroit-3,1);
     delay(500);
     BougerBras(ButGauche-3,PositionBrasGauche,1,ButDroit-3,PositionBrasDroit,1);
     Count += 1 ;
     
     break;
   case 37:

     delay(300);
     BougerBras(PositionBrasGauche,ButGauche-3,1.2,PositionBrasDroit,ButDroit-3,0.3);
     delay(500);
     BougerBras(ButGauche-3,PositionBrasGauche,0.3,ButDroit-3,PositionBrasDroit,1.2);
     Count += 1 ;
     
     break;
   case 38:

      Couleur(0,150,150);
      Sourcil(170,0) ;
      BoucheStyle(2) ;
      Yeux(1) ;

      for (int i=57; i <= 140; i += 1){
          BrasDroit.write(PositionBrasDroit+(i/5));
          Drapeau.write(i);
          delay(20);
      }
      Couleur(0,0,0);
      delay(500);
      Couleur(255,0,0);
      delay(100);
      Couleur(0,0,0);
      delay(100);
      for (int i=0; i <= 20; i += 1){
          Couleur(0,150,150);
          delay(80-i);
          Couleur(255,0,0);
          delay(80-i);
      }
      delay(500);
      Sourcil(85,60);
      Couleur(255,0,0);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,PositionBrasDroit+15,ButDroit,1.5);
      Drapeau.write(57);
      BoucheStyle(1) ;
      Yeux(2) ;
      delay(200);
      BougerBras(PositionBrasGauche,PositionBrasGauche,0,ButDroit,PositionBrasDroit,1.5);
      delay(500);
      BougerBras(PositionBrasGauche,PositionBrasGauche+25,0.8,PositionBrasDroit,PositionBrasDroit+22,0.8);
      delay(500);
      BougerBras(PositionBrasGauche+25,PositionBrasGauche,0.8,PositionBrasDroit+25,PositionBrasDroit,0.8);
      delay(500);
      BougerBras(PositionBrasGauche,PositionBrasGauche+25,0.8,PositionBrasDroit,PositionBrasDroit+25,0.8);
      delay(500);
      BougerBras(PositionBrasGauche+25,PositionBrasGauche,0.8,PositionBrasDroit+25,PositionBrasDroit,0.8);      
      delay(800);
      Count += 1 ;
      
     break;
   case 39:

      Couleur(25,25,25);
      Sourcil(170,0) ;
      BoucheStyle(2) ;
      Yeux(2) ;
      Drapeau.write(160);

      while(EtatNezDroit == HIGH or EtatNezGauche == HIGH){
        delay(500);
        Yeux(1) ;
        delay(500);
        Yeux(2) ;
        delay(500);
        Yeux(3) ;
        delay(500);
        Yeux(2) ;
        EtatNezGauche = digitalRead(NezGauchePin);
        EtatNezDroit = digitalRead(NezDroitPin)  ;
        
      } 
        Drapeau.write(57);
        Count += 1 ;
    
     break;

//-------------------Veille + Animation ennui----------------------------

   case 101:
     Sourcil(105,30);
     delay(2000); 
     Sourcil(105,0);
     delay(2000);     
     
     break;
   case 102:
     Yeux(1) ;
     delay(1000);
     Yeux(2) ;
     delay(1000);
     Yeux(3) ;
     
     break;
   case 103:
      BougerBras(PositionBrasGauche,ButGauche+8,0.8,PositionBrasDroit,PositionBrasDroit,0);
      delay(500);
      BougerBras(ButGauche+8,PositionBrasGauche,0.8,PositionBrasDroit,PositionBrasDroit,0);
      delay(500);
      BougerBras(PositionBrasGauche,ButGauche-3,0.8,PositionBrasDroit,ButDroit-3,0.8);
      delay(300);
      BougerBras(ButGauche-3,PositionBrasGauche,1,ButDroit-3,PositionBrasDroit,1);
     break;

   case 104:
     Couleur(0,0,0);
     break;

//-------------------Default---------------------------

   default:
      BrasDroit.write(PositionBrasDroit);
      BrasGauche.write(PositionBrasGauche);
      BougerBras(115,115,0,PositionBrasDroit,PositionBrasDroit,0);
      BoucheStyle(1);
      Yeux(2);
      Drapeau.write(57);
      if(Humeur == 0 or Count >= 4){
        Couleur(0,150,150);
        Sourcil(126,30) ;
        Count = 0 ;
        Humeur = 0 ;
      }
      if(Humeur == 1){
        Couleur(255,0,0);
        Sourcil(85,60);
      }

     Veille += 1 ;
     break;
  }
    // Sourcil(85,60) Enervé , Sourcil(170,0) étoné , Sourcil(126,30) normal

}





//--------------------------------------------------------------------------------------------------------------------------------
//------------Daclaration fonction annexes-------------

// 1 = Droit , 2 = Centre , 3 = Gauche
void Yeux(int PosYeux){
    if (PosYeux == 1){
    Oeil.write(125);
    }
    if (PosYeux == 2){
    Oeil.write(105);
    }
    if (PosYeux == 3){
    Oeil.write(85);
    }
   
}
void Couleur(int R,int G,int B){
    analogWrite(Rouge, 255-R);
    analogWrite(Vert, 255-G);
    analogWrite(Bleu, 255-B);
    }
    
void BoucheStyle(int Style){
    if (Style == 1){
    Bouche.write(95);
    }
    if (Style == 2){
    Bouche.write(52);
    }
   
}

void Paix(){
    
    for (int i=0; i <= 5; i++){
      Drapeau.write(160);
      delay(500);
      Drapeau.write(120);
      delay(500);
      }
    Drapeau.write(57);
    delay(1000);
 
}

void Sourcil(int PosSourcilGauche,int PosSourcilDroit){
     SourcilGauche.write(PosSourcilGauche);
     SourcilDroit.write(PosSourcilDroit);
 
}

// ActuelG , FinalG , VitG ,ActuelD , FinalD , VitD
void BougerBras(float PositionActuelGauche,float PositionFinalGauche,float VitesseGauche,float PositionActuelDroit,float PositionFinalDroit,float VitesseDroit){
  while ( (PositionActuelGauche < PositionFinalGauche-VitesseGauche ) or (PositionActuelGauche > PositionFinalGauche+VitesseGauche) or (PositionActuelDroit < PositionFinalDroit-VitesseDroit ) or (PositionActuelDroit > PositionFinalDroit+VitesseDroit)){
  
  if (PositionActuelGauche < PositionFinalGauche){
    PositionActuelGauche = PositionActuelGauche + VitesseGauche ;
  }
  if (PositionActuelGauche > PositionFinalGauche){
    PositionActuelGauche = PositionActuelGauche - VitesseGauche ;
  }
  if (PositionActuelDroit < PositionFinalDroit){
    PositionActuelDroit = PositionActuelDroit + VitesseDroit ;
  }
  if (PositionActuelDroit > PositionFinalDroit){
    PositionActuelDroit = PositionActuelDroit - VitesseDroit ;
  }
  BrasGauche.write(PositionActuelGauche) ;
  BrasDroit.write(PositionActuelDroit) ;
  delay(10) ;
  }
 }


 

 
