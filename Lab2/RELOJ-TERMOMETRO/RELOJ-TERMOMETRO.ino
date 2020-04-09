/*############################################################################## 
 Conexiones:
 * LCD    -> ARDUINO
 * RS     -> 7
 * Enable -> 6
 * D4     -> 5
 * D5     -> 4
 * D6     -> 3
 * D7     -> 2
 * R/W    -> GND
 * light  -> 9
 * La fila de botones se encuentra en el PIN A0
##############################################################################*/

// Sensor de temperatura https://programarfacil.com/tutoriales/fragmentos/leer-el-sensor-de-temperatura-lm35-en-arduino/


// Aqui se incluye la libreria de la pantalla LCD:
#include <LiquidCrystal.h>

// Inicializa la libreria con el numero de los pines
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


// Define constants and variables
const int inputPin = A0;    // Alimentacion de la fila de botones 
const int sensorPin = A1;
const int ledPin =  9;      // Alimentacion de los leds de la placa
uint16_t inputValue = 0;    // Valor que se lee de la fila de botones
boolean Menu;               // Nos dice si nos encontramos dentro del menu
int car1;                   // Impide las repetidas impresiones de texto por pantalla
boolean vTime;              // Nos dice si nos encontramos dentro del menu de tiempo
boolean vTemp;              // Nos dice si nos encontramos dentro del menu de temperatura
boolean setTime;            // Nos dice si nos encontramos dentro del menu de elegir el tiempo
float tempC;                // Guarda los grados que se detectan
int pinLM35 = 0;            // En input del termometro
int HORA;              // El valor de la hora
int MIN;               // El valor de los minutos
int SEG;               // El valor de los segundos
int pos;                // Nos permite decidir que editar, si horas (1) o minutos (2)
long time1;
long time2;

// Initialization
void setup() 
{
  pinMode(ledPin, OUTPUT);        // Se declara la pantalla como un periferico de SALIDA
  digitalWrite(ledPin, HIGH);     // La pantalla esta encendida
  lcd.begin(16, 2);               // Decide los limites de la pantalla a 16 columnas y 2 filas
  lcd.print("MENU PRINCIPAL");    // Imprime el titulo del menu principal
  lcd.setCursor(0, 1);            // Coloca el cursos en las coordenadas 0,1
  lcd.print("1.TM 2.TP 3.ST");    // Imprime el boton asociado a cada submenu
  Menu=true;                      //""""""""""""""""""""""""""""""
  car1=1;                         //""""""""""""""""""""""""""""""
  vTime=false;                    //""""""""""""""""""""""""""""""
  vTemp=false;                    //""""""""""""""""""""""""""""""
  setTime=false;                  // Inicializa las variables...
  pos=1;                          //""""""""""""""""""""""""""""""
  HORA=00;                        //""""""""""""""""""""""""""""""
  MIN=00;                         //""""""""""""""""""""""""""""""
  SEG=00;                         //""""""""""""""""""""""""""""""
  Serial.begin(9600);             //
  time1=millis();
  
}



//=============================================================|AQUI SE INICIA EL LOOP|===============================================================================
void loop()                       
{
  //Detecta que boton se esta pulsando
  inputValue = analogRead(inputPin);
  if(inputValue < 100 && inputValue >= 0) inputValue = 1;
  else if(inputValue < 250 && inputValue > 150) inputValue = 2;
  else if(inputValue < 470 && inputValue > 370) inputValue = 3;
  else if(inputValue < 670 && inputValue > 570) inputValue = 4;
  else if(inputValue < 870 && inputValue > 770) inputValue = 5;
  else if(inputValue <= 1023 && inputValue > 950) inputValue = 0;

  

//#########################################################|ESTADOS DE LOS DIFERENTES SUBMENUS|######################################################################
  if(Menu==true)            //En caso de que nos encontremos en el menu principal se PODRA ejecutar el codigo de debajo dependiento de la tecla pulsada
  {
    if(inputValue==1)       //En caso de que se pulse el boton 1 se activara el submenu vTime
    {
      lcd.clear();
      Menu=false;           //Sale del menu principal
      vTime=true;           //Activa el submenu vTime
      car1=1;               //Permite que se escriba texto una vez
    }
    if(inputValue==2)       //En caso de que se pulse el boton 2 se activara el submenu vTemp
    {
      lcd.clear();
      Menu=false;           //Sale del menu principal
      vTemp=true;           //Activa el submenu vTemp
      car1=1;               //Permite que se escriba texto una vez
    }
    if(inputValue==3)       //En caso de que se pulse el boton 3 se activara el submenu setTime
    {
      lcd.clear();
      Menu=false;           //Sale del menu principal
      setTime=true;         //Activa el submenu setTime
      car1=1;               //Permite que se escriba texto una vez
      pos=1;                //Se coloca en la posicion de cambiar las horas por DEFECTO
    }
  }
  else                      //En caso de encontrarse en una pantalla diferente a al del menu se PODRA ejecutar el codigo de debajo dependiendo de si se pulsa la tecla5
  {
    if(inputValue==5)       //En caso de que se pulse el boton 5 se activara la vuelta al menu principal
    {
      lcd.clear();          //Limpia el texto residual
      Menu=true;            //Activa la pantalla del MENU
      vTime=false;          //""""""""""""""""""""""""""""""""""""""""""""
      vTemp=false;          //Desactiva cualquier otra pantalla o submenu
      setTime=false;        //""""""""""""""""""""""""""""""""""""""""""""
      car1=1;               //Permite que se escriba texto una vez
    }
  }
//######################################################################|LOGICA DEL RELOJ|###########################################################################
time2=millis();  //Tiempo en segundos
if (time2>=time1+1000)
{
  SEG=SEG+1;
  time1=time1+1000;
}
if (SEG==60)
{
  SEG=0;
  MIN=MIN+1;
}
if (MIN==60)
{
  SEG=0;
  MIN=0;
  HORA=HORA+1;
}
if (HORA==24)
{
  SEG=0;
  MIN=0;
  HORA=0;
}

if (MIN<0)
{
  MIN=59;
  HORA=HORA-1;
}
if (HORA<0)
{
  HORA=23;
}
//###########################################################|ACTUALIZACION DE LOS DIFERENTES SUBMENUS|##############################################################
//=========================================================|SUBMENU QUE NOS DICE LA HORA DEL DISPOSITIVO|=============================================================
  if(!Menu && vTime)
  {
    if (car1==1)
    {
    lcd.setCursor(3, 0);                  //Se coloca en la posicion del titulo
    lcd.print("VIEW TIME");               //Imprime el titulo por pantalla
    lcd.setCursor(0, 1);
    lcd.print("----");
    lcd.setCursor(6,1);
    lcd.print(":");
    lcd.setCursor(9,1);
    lcd.print(":");
    lcd.setCursor(12,1);
    lcd.print("----");

    car1=2;                               //Evita que se vuelva a escribir el codigo
    }

    if (HORA<10)
    {
    lcd.setCursor(5,1);
    lcd.print(HORA);
    lcd.setCursor(4,1);
    lcd.print('0');
    }
    else
    {
      lcd.setCursor(4,1);
      lcd.print(HORA);
    }

    if (MIN<10)
    {
    lcd.setCursor(8,1);                 
    lcd.print(MIN);
    lcd.setCursor(7,1);
    lcd.print('0');
    }
    else
    {
      lcd.setCursor(7,1);
      lcd.print(MIN);
    }
    
    if (SEG<10)
    {
    lcd.setCursor(11,1);
    lcd.print(SEG);
    lcd.setCursor(10,1);
    lcd.print('0');
    }
    else
    {
      lcd.setCursor(10,1);
      lcd.print(SEG);
    }
    
    

  }
//=================================================|SUBMENU QUE NOS DICE LA TEMPERATURA EN LA QUE NOS ENCONTRAMOS|===================================================
  if(!Menu && vTemp)                      
  {
    if (car1==1)
    {
      lcd.setCursor(0, 0);
      lcd.print("TEMPERATURA");
      car1=2;                                 //Evita que se vuelva a escribir el codigo
    }
      lcd.setCursor(0, 1);
      int value = analogRead(sensorPin);
      float millivolts = (value / 1023.0) * 5000;
      float celsius = millivolts / 10; 
      lcd.print(celsius);
      lcd.print(" C");
      delay(500);
  }
//=====================================================|SUBMENU QUE NOS PERMITE SETTEAR LA HORA QUE QUERAMOS|=========================================================
  if(!Menu && setTime)                    
  {
    if (car1==1)
    {
      lcd.setCursor(0, 0);
      lcd.print("SET TIME");

      lcd.setCursor(0, 1);
      lcd.print("-----");

      lcd.setCursor(8,1);
      lcd.print(':');

      lcd.setCursor(11,1);
      lcd.print("-----");

      car1=2;                           //Evita que se vuelva a escribir el codigo
    }
    if (HORA<10)
    {
    lcd.setCursor(7,1);
    lcd.print(HORA);
    lcd.setCursor(6,1);
    lcd.print('0');
    }
    else
    {
      lcd.setCursor(6,1);
      lcd.print(HORA);
    }
    if (MIN<10)
    {
      lcd.setCursor(10,1);                 
      lcd.print(MIN);
      lcd.setCursor(9,1);
    lcd.print('0');
    }
    else
    {
      lcd.setCursor(9,1);
      lcd.print(MIN);
    }

    if (pos==1)                         //Se editan las horas
    {
      if (inputValue==1)                //Se incrementan las horas al pulsar el boton 1
      {
        HORA=HORA+1;
        delay(200);
      }
      if (inputValue==2)                //Se decrementen las horas al pulsar el boton 2
      {
        HORA=HORA-1;
        delay(200);
      }
    }

      if (pos==2)                       //Se editan los minutos
      {
        if (inputValue==1)                //Se incrementan las horas al pulsar el boton 1
          {
            MIN=MIN+1;
            delay(200);
          }
        if (inputValue==2)                //Se decrementen las horas al pulsar el boton 2
          {
            MIN=MIN-1;
            delay(200);
          }
       }
       
      if (inputValue==3)                //Se cambia entre horas y minutos
        {
          pos=1;
        }
      if (inputValue==4)                //Se editan las horas
          {
            pos=2;
          }
  }
//=====================================================================|MENU INICIAL|===========================================================================
  if(Menu==true)                          
  {
    if (car1==1)
    {
    lcd.setCursor(0, 0);
    lcd.print("MENU PRINCIPAL");          // Print a message on the LCD
    lcd.setCursor(0, 1);
    lcd.print("1.TM 2.TP 3.ST");
    car1=2;                               //Evita que se vuelva a escribir el codigo
    }
  }
}
//###########################################|Este codigo se ha desarroyado por Xabier Gabiña && Julia Wojciechowska|###########################################
