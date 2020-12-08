#include <LiquidCrystal_I2C.h> //Libreria para funciones de la LCD via I2C 
#include <RTClib.h> //Libreria para el Reloj, en mi caso RTC DS3231 via I2C
#include <Wire.h> //Libreria para el Reloj.

LiquidCrystal_I2C lcd (0x27, 16, 2); // 0x27 direccion facilitada por el I2C scanner, 16 caracteres, y 2 lineas (cada uno tendrá que cambiarlo dependiendo de su direccion o su tipo de lcd)

RTC_DS3231 RTC;

// Variables
int array_diasmeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String anterior;
String plural = "OOOS";
String plural2 = "MESES";
String plural3 = "DIAS";


// Caracteres
byte Corazon1 [] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100
};

byte feliz[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B10001,
  B01110,
  B00000
};

byte n[] = {
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
    //RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); // El modulo RTC coge la hora que hay en tu pc. (Puedes configurarlo a mano). Tienes que descomentarlo usarlo 1 vez y comentarlo de nuevo.

    //Iniciamos la LCD y le ponemos luz de fondo
    lcd.init ();
    lcd.backlight();

    //Sustituimos el valor de la izquierda por el de la derecha
    lcd.createChar(0, Corazon1);
    lcd.createChar(1, feliz);
    lcd.createChar(2, n);

}

void loop() {
  
    DateTime ahora = RTC.now();
    DateTime elmejordia = (1573413540); //Esta puesto en unixtime para poder hacer las operaciones 
    
    int contadorhora = ahora.hour();// - elmejordia.hour();
    int contadoranos = ahora.year() - elmejordia.year();
    
    if (contadoranos == 1){
      plural = "OOO";
    }
  
    
    String ano = String(contadoranos) + " " + "A";
    String textonoche = "Descansa enana";
    String textodia = "BUENOS DIAS";
  
    texto();

    if(contadorhora >= 24 && contadorhora < 7){
        lcd.noBacklight(); //La luz no molestará por la noche
       
    }

    else { 
      lcd.backlight(); // Luz encendida el resto del día
    }

    if (contadorhora == 23){
      lcd.clear();
      imprimir(String(textonoche)); //A las 11 de la noches un buenas noches de larga duración
      lcd.home();
      lcd.setCursor(15,0);
      lcd.write(0);
      delay(300000);
      lcd.clear();
    }
    
    if (contadorhora == 7){
      lcd.clear();
      imprimir(String(textodia)); //A las 7 de la mañana un buenos dias de larga duración
      delay(300000);
      lcd.clear();
    }

    if (contadorhora == 16){ //Recordar ese añito <3
        lcd.clear();
        imprimir(String(ano));
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

void imprimir (String stringimp) { //Lee los strings y los imprime

  if (anterior != stringimp){
    String paraimp = stringimp;

    int anchura = paraimp.length();
    char cadena[anchura + 1]; 

    paraimp.toCharArray(cadena, anchura + 1);
    for (int i = 0; i < anchura; i++){
        lcd.setCursor(i, 0);
        lcd.print(cadena[i]);
    }
  }
  anterior = stringimp;
} 



void texto(){

    DateTime ahora2 = RTC.now();
    DateTime elmejordia2 = (1573413540);

    if (ahora2.year()% 4 == 0)  {
        array_diasmeses[1] = 29;
    }
    else 
        array_diasmeses[1] = 28;
    
    int contadordiames = array_diasmeses[ahora2.month() - 2] - elmejordia2.day() + ahora2.day();
    int contadormes = (ahora2.year() - elmejordia2.year()) * 12 + (ahora2.month() - elmejordia2.month() - 1);

    if (ahora2.day() >= elmejordia2.day()) {
        contadormes += 1;
        contadordiames = ahora2.day() - elmejordia2.day();
    }

    if (contadormes == 1){
      plural2 = "MES";
    }

    if (contadordiames == 1){
        plural3 = "DIA";
    }
    
    String fecha = String(contadormes) + " " + String(plural2) + " " + String(contadordiames) + " " + String(plural3);

    lcd.setCursor(0,0);
    imprimir(String(fecha)); //Meses totales mas dias.
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
