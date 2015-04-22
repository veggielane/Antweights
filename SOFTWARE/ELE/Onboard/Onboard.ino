#include <PololuMaestro.h>

#include <SoftwareSerial.h>
#define lemonRxPin 9
#define lcdTxPin 8
#define maestroTxPin 7

#define lemonTxPin 10
#define lcdRxPin 11
#define maestroRxPin 12

SoftwareSerial lemonSerial(lemonRxPin, lemonTxPin);
SoftwareSerial lcd(lcdRxPin, lcdTxPin);

SoftwareSerial maestroSerial(maestroRxPin, maestroTxPin);
MiniMaestro maestro(maestroSerial);

byte channels[10];//<Throttle><Aileron><Elevator><Rudder><Gear><Aux1><Aux2><Aux3><Aux4><Aux5>

void setup()  
{
  maestroSerial.begin(9600);
  
  lcd.begin(115200);
  lcd_setup(&lcd);
  
  lemonSerial.begin(115200);
  lcd_clear();
  lcd_print("init");
}

void loop()
{
  if (lemonSerial.available()){
    int bytesRead = lemonSerial.readBytesUntil(0xD,channels,10);
    switch (bytesRead) {
      case 10:
        Update();
        break;
      case 5:
        //Serial.write("LemonError\n");
        lcd_print("R");
        break;
    }
  }
}
char buffer [50];
void Update(){
  lcd_clear();
  int pos = 1500 + (channels[1] - 127)*3;
  sprintf (buffer, "%d,%d,%d,%d,%d,%d", pos,channels[1],channels[2], channels[3],channels[4],channels[5]);
  lcd_print(buffer);
  
  
  
  maestro.setTarget(0, pos * 4);
}


