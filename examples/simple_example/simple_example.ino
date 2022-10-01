#include <LEDMenu.h>

//address, encoder pin 1, encoder pin 2, button pin
LEDMenu menu(0x70,7,8,6);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  menu.init();
  
  menu.addMenu("M  1");
  menu.addVal ("V1.1");
  menu.addVal ("V1.2");
  menu.addVal ("V1.3");

  menu.addMenu("M  2");
  menu.addVal ("V2.1");
  menu.addVal ("V2.2");
  menu.addVal ("V2.3");
  
  
}

void loop()
{
  menu.poll();

  Serial.println(menu.getVal(1)); //gets value for M 1, given as 1,2,3
}