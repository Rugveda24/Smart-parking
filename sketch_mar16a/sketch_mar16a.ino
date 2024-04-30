// #include <Wire.h> 
#include <Servo.h> 
#include<SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//SoftwareSerial bluetooth(0, 1); 

Servo myservo1;

int IR1 = 2;
int IR2 = 4;

int Slot = 4;

int flag1 = 4;
int flag2 = 4;
int fl = 0;
void setup() 
{
  Serial.begin(9600);
//  bluetooth.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(3);
  myservo1.write(100);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  oled.clearDisplay();
  oled.setTextSize(1);          
  oled.setTextColor(WHITE); 
  oled.setCursor(0, 0); 
  oled.display();
}

void loop() {
  //Serial.println("in loop");

  if(digitalRead(IR1) == 0)
  {
    if(flag1 == flag2 ){
     if(Slot!=0){

    // Entry from IR1
      flag1 = flag1 -1;
      myservo1.write(0);
     }
    } else{
      // exit from IR1
     if(Slot < 4){

      flag1 = flag1 + 1;
      myservo1.write(100);
      Slot = Slot + 1; 
     }  
    }
  }
    
  if(digitalRead(IR2) == 0){

    if(flag1 == flag2){
      if(Slot < 4){
        // Exit from IR2
        flag2 = flag2 + 1;
        myservo1.write(0);
      }
   } 
 
   else{ 
    if(Slot!=0){
      // Entry to IR2
      flag2 = flag2 -1;
      myservo1.write(100);
      Slot = Slot -1;
    }
      
   }
  }

  Serial.print("Slot Available = ");
  Serial.println(Slot);

  oled.clearDisplay();
  oled.setTextSize(1);          
  oled.setTextColor(WHITE); 
  oled.setCursor(0, 10);
  oled.print("Slot Available = ");
  oled.println(Slot);
  oled.display();

  // bluetooth.print("Slot Available = ");
  // bluetooth.println(Slot);
  Serial.print("Slot Available = ");
  Serial.println(Slot);
  
  delay(2000);

}
