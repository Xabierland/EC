int ledG = 9;
int ledY = 10;
int ledR = 11;
int pulsador = 12;

int sonido = 2;
int N=1; 

int contadorSemaforo = 0; 

int contadorPulsador = 0; 
int estadoPulsador = 0; 
int estadoPrevioPulsador = 0;
void setup() { 
   pinMode(ledG, OUTPUT);
   pinMode(ledY, OUTPUT);
    pinMode(ledR, OUTPUT);
    pinMode(sonido, OUTPUT);
    pinMode(pulsador, INPUT);
}
void loop() {
  digitalWrite(ledG, LOW); 
  digitalWrite(ledY, LOW);   
digitalWrite(ledR, HIGH);
 
 estadoPulsador = digitalRead(pulsador);
 if (estadoPulsador == HIGH) {
   contadorPulsador++;
  digitalWrite(ledR, LOW); 
digitalWrite(ledY, HIGH);
delay(5000);
  digitalWrite(ledY, LOW); 
digitalWrite(ledG, HIGH);
delay(5000);
  contadorSemaforo=0;
  while (contadorSemaforo <=25) {
    digitalWrite(ledG, LOW);
    tone (sonido, N*2000, 100);
    delay(100);
    digitalWrite(ledG, HIGH);
    delay(100); 
    contadorSemaforo=contadorSemaforo+1;
  }

}
}
