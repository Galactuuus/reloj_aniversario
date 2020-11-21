#include <LiquidCrystal_I2C.h> //Library for LCD functions via I2C 
#include <RTClib.h> //Library for the Clock, in my case RTC DS3231 via I2C
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 16, 2); // 0x27 address provided by the I2C scanner, 16 characters, and 2 lines (each one will have to change depending on your address or your LCD type)

RTC_DS3231 RTC;


// Variables
int array_monthdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String last;
String plural = "OOOS";
String plural2 = "MESES";
String plural3 = "DIAS";

// Caracteres

byte heart [] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100
};

byte happy[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B10001,
  B01110,
  B00000
};

byte spanishn[] = {
  B11111,
  B00000,
  B10001,
  B11001,
  B10101,
  B10011,
  B10001,
  B00000
};

void setup() {
    //RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); //The RTC module takes the time that is on your pc. (You can set it as you want)

    //We start the LCD and put it backlight
    lcd.init ();
    lcd.backlight();

    //We substitute the value on the left for the one on the right
    lcd.createChar(0, heart);
    lcd.createChar(1, happy);
    lcd.createChar(2, spanishn);

}

void loop() {
  
    DateTime now = RTC.now();
    DateTime aniversary = (1573413540); //It is set in unixtime to be able to do the operations
    
    int hourcounter = now.hour();// - aniversary.hour();
    int yearcounter = now.year() - aniversary.year();
    
    if (yearcounter == 1){
      plural = "OOO";
    }
  
    
    String year = String(yearcounter) + " " + "A";
    String nightext = "Descansa enana";
    String daytext = "BUENOS DIAS";

    texto();

    if(hourcounter >= 1 && hourcounter <= 7){
        lcd.noBacklight(); // The light will not disturb at night
       
    }

    else { 
      lcd.backlight(); // Light on the rest of the day
    }

    if (hourcounter == 23){
      lcd.clear();
      print(String(nightext)); //At 11 p.m. a long-lasting good night (1hour 5 minutes)
      lcd.home();
      lcd.setCursor(15,0);
      lcd.write(0);
      delay(300000);
      lcd.clear();
    }
    
    if (hourcounter == 7){
      lcd.clear();
      print(String(daytext)); //At 7 in the morning a long lasting good morning (1 hour 5 minutes)
      delay(300000);
      lcd.clear();
    }

    if (hourcounter == 16){ // Remember that year <3
        lcd.clear();
        print(String(year));
        lcd.write(2);
        lcd.print(plural);
        lcd.setCursor(0,1);
        lcd.print("SOPORTANDOME");
        lcd.home();
        lcd.setCursor(13,0);
        lcd.write(0);
        lcd.write(0);
        lcd.setCursor(13,1);
        lcd.write(1);
        lcd.write(1);
        delay(300000);
        lcd.clear();
    }
}

void print (String stringprint) { // Read the strings and print them

  if (last != stringprint){
    String stringtoprint = stringprint;

    int stringlength = stringtoprint.length();
    char stringchar[stringlength + 1]; 

    stringtoprint.toCharArray(stringchar, stringlength + 1);
    for (int i = 0; i < stringlength; i++){
        lcd.setCursor(i, 0);
        lcd.print(stringchar[i]);
    }
  }
  last = stringprint;
} 



void texto(){

    DateTime now2 = RTC.now();
    DateTime aniversary2 = (1573413540);

    if (now2.year()% 4 == 0)  {
        array_monthdays[1] = 29;
    }
    else 
        array_monthdays[1] = 28;
    
    int monthdaycounter = array_monthdays[now2.month()] - aniversary2.day() + now2.day();
    int monthcounter = (now2.year() - aniversary2.year()) * 12 + (now2.month() - aniversary2.month() - 1);

    if (now2.day() >= aniversary2.day()) {
        monthcounter += 1;
        monthdaycounter = now2.day() - aniversary2.day();
    }

    if (monthcounter == 1){
      plural2 = "MES";
    }

    if (monthdaycounter == 1){
        plural3 = "DIA";
    }
    
    String Date = String(monthcounter) + " " + String(plural2) + " " + String(monthdaycounter) + " " + String(plural3);

    lcd.setCursor(0,0);
    print(String(Date)); // Total months plus days
    lcd.setCursor(0, 1);
    lcd.print("TE QUIERO");
    lcd.home();
    lcd.setCursor(10, 1);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
}
