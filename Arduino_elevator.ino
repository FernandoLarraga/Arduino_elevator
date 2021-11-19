
/* LCD */
#include <LiquidCrystal.h> /* Se incluye la libreia de LyquidCrystal para poder controlar el LCD*/
LiquidCrystal lcd(17, 18, 19, 20, 21 , 22);
#define echoPin 12 // Pin eco
#define trigPin 13 // Pin Trigger
int maximumRange = 200; // Rango maximo
int minimumRange = 0; // Rango minimo
float duration, distance; // Duracion usada para medir la distacia


bool boton1, boton2, boton3, boton4, boton5; /* En esta parte del programa declaramos cada uno de los botones como variables de tipo bool por que solo manejamos dos estados 1 y 0 */

int i, j, x;
float z = 4.4; /* En la variable z es en donde se guarda la distancia a la que se encuentra el elvador, es inicializada en 4.4 por que al inicio el elevador esta a 4.4 centimetros del sensor */
/* Estas variables "piso" y "control" van a ser los que definan la direccion y el teimpo del recorrido del elevador */
int control = 1, piso = 0;
int paro = 0; /* La varibale paro la incrementaremos al oprimir el boton de paro */

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
attachInterrupt( 0, ServicioBoton, RISING);
/*En esta parte del programa vamos a declarar entradas y salidas */
for ( i = 4; i < 9; i++)
{
  pinMode(i, INPUT);
}
/* Declaración de los pines de los puentes H */
/* Se declararon salidas del pin 4 al pin 15 estas incluyen el puente H */
pinMode(15, OUTPUT);
pinMode(23, OUTPUT);
pinMode(24, OUTPUT);
pinMode(25, OUTPUT);
pinMode(26, OUTPUT);

/* LCD */
lcd.begin(16, 2);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}




void loop() {
  // put your main code here, to run repeatedly:
  /* Se inicia el sensor ultrasonico */
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
 
 
  //Medimos el tiempo que tarda en llegar el eco
 duration = pulseIn(echoPin, HIGH);
 //Calculamos la distancia
 distance = float (duration*0.017);
 Serial.println(distance);
 Serial.println(z);
  digitalWrite(15, LOW);
  lcd.clear();
   {
   lcd.write(" Introduzca un "); /* Se manda a imprimir en pantalla */
   lcd.setCursor(0,1);
   lcd.write("  piso     ");
   lcd.print(control);
   }
   
{
/* Indicamos que cada uno de los botones van a dar una lectura digital a cada uno de los pines digitales que se mensioanan en el codigo */
boton1 = digitalRead(4);
boton2 = digitalRead(5);
boton3 = digitalRead(6);
boton4 = digitalRead(7);
boton5 = digitalRead(8);
/* 
 *  En esta parte del programa vamos a hacer que la variable piso cada que se aplane un boton se va cambair su valor, cuando:
 *  boton1, piso = 1
 *  btton2, piso = 2
 *  boton3, piso = 3 
 *  boton4, piso = 4
 *  boton5, piso = 5
 */
 {
 if (boton1)
 {
  piso = 1;
  Serial.print("boton1");
 }
 else if (boton2)
 {
  piso = 2;
  Serial.print("boton2");
 }
 else if (boton3)
 {
  piso = 3;
  Serial.print("boton3");
 }
 else if (boton4)
 {
  piso = 4;
  Serial.print("boton4");
 }
 else if (boton5)
 {
  piso = 5;
  Serial.print("boton5");
 }
 Serial.println(piso);
 }
 
 /* En esta parte del codigo el primer if es el que va definir la direccion que tendra el elvador ya sea de bajada o de subida */ 
 if (control < piso) /* Este quire decir que va de subida por que control va a ser la variable en donde se almacene el piso en donde está */
 {


  
  if (control == 1 && piso == 2 || control == 2 && piso == 3 || control == 3 && piso == 4 || control == 4 && piso == 5) /* Estas son las convonaciones que recorreon solo un piso */
  {
    /* Esra parte del programa esta dividida en if con convinaciones distintas de pisos y esto es que cada una de estas convinaciones recorrenen exactamente la misma
     *  ditancia así que se almacenan todas en un solo if 
     */
  Subida(z, 15);  /* En esta parte del programa se llama a la funcion subida*/  
  control = piso; /* Al final de cada if se le da el valor de piso a control indicando en que piso se encuentra */
  }
  else if (control == 1 && piso == 3 || control == 2 && piso == 4 || control == 3 && piso == 5)
  {
    /* Se establece la distancia deceada */  
  Subida(z, 30);
  control = piso;
  }
  else if (control == 1 && piso == 4 || control == 2 && piso == 5)
  {
    /* Se establecera la distancia deceada */
  Subida(4.5, 45);
  control = piso;
  }
  else if (control == 1 && piso == 5 )
  {
    /* Se estbalecera la ditancia */
  Subida(z, 60);
  control = piso; 
  }
 }




  
 else if ( control > piso ) /* Esre else if es el que indicara que el elevador va de bajada */
 {
   if (control == 2 && piso == 1 || control == 3 && piso == 2 || control == 4 && piso == 3 || control == 5 && piso == 4) /* Estas son las convonaciones que recorreon solo un piso */
  {
    /* Esra parte del programa esta dividida en if con convinaciones distintas de pisos y esto es que cada una de estas convinaciones recorrenen exactamente la misma
     *  ditancia así que se almacenan todas en un solo if 
     */
  Bajada(z, 15); /* Se llama a la funcion Bajada */ 
  control = piso;
  }
  else if (control == 3 && piso == 1 || control == 4 && piso == 2 || control == 5 && piso == 3)
  {
    /* Se establece la distancia deceada */
  Bajada(z, 30);
  control = piso;
  }
  else if (control == 4 && piso == 1 || control == 5 && piso == 2)
  {
    /* Se establecera la distancia deceada */
  Bajada(z, 45);
  control = piso;
  }
  else if (control == 5 && piso == 1 )
  {
  Bajada(z, 60);
  control = piso; 
  }
 }
 else 
 {
  Serial.println("Introduzca otro piso");
 }
}











}
/* Declaracio de fuciones */
void Motorpuerta()
{
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  delay(100);
   digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  delay(4000);
   digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  delay(100);
  digitalWrite(23, HIGH);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
}
/* esta funcion es la funcion de la interrupcion cada vbes que oprimamos el boton de paro este le pondra el valor de  a paro y entrara la funcion de paro total */ 
void ServicioBoton()
{
  Serial.println("Paro total");
  paro = 1;
  return;
}
/* Parototal es la funcion que para el funcionamiento del elevador*/
void Parototal(){
  if (paro == 1)
  {
    int t;
    lcd.clear();
    lcd.write("   Paro total");
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(15, LOW);
    for ( t = 0; t < 5; t++)
    {
      digitalWrite(26, HIGH);
      delay(500);
      digitalWrite(26,LOW);
      delay(500);
    }
    paro = 0;
  }
}
/* En la funcion subida se le la orden al motor de subir hasta que se le indique con un ciclo while */
void Subida(float x, int y)
{
  lcd.clear();
  lcd.write("Abriendo puertas");
    Motorpuerta();
    lcd.clear();
  while(distance <= x + y)
  {
    PantallaLCDbotones();
    digitalWrite(15, HIGH);
      digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
 //Calculamos la distancia
 distance = float (duration*0.017);
 Serial.println(x + y);
 Serial.println(distance);
 Parototal();
  digitalWrite(10 ,LOW);
  digitalWrite(11, HIGH);
  if ( distance >= x + y)
  {
  lcd.clear();
  lcd.write("Abriendo puertas");
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(15, LOW);
  z = x + y;
  break;
  }
  }
  Motorpuerta();
  return;
}


/* En la función bajada se le indica al motor que baje hasta el piso que se le indique */
void Bajada (float x, int y)
{
  lcd.clear();
  lcd.write("Abriendo puertas");
    Motorpuerta();
  lcd.clear();
  while(distance >= x - y)
  {
    PantallaLCDbotonesbajada();
     digitalWrite(15, HIGH);
      digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
 //Calculamos la distancia
 distance = float (duration*0.017);
 Serial.println(x - y);
 Serial.println(distance);
  Parototal();
  digitalWrite(10 ,HIGH);
  digitalWrite(11, LOW);
  if ( distance <= x - y)
  {
  lcd.clear();
  lcd.write("Abriendo puertas");
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
   digitalWrite(15, LOW);
  z = x - y;
  break;
  }
  }
  Motorpuerta();
  return;
}


/* Intrucciones para la pantalla lcd de subida */
 void PantallaLCDbotones(){
            lcd.write("Subiendo al ");
            lcd.print(piso);
            lcd.setCursor(0,1);
            lcd.write("Porfavor espere");
            return; 
 }    



/* Intrucciones para la pantallada lcd de bajada*/  
 void PantallaLCDbotonesbajada(){
            lcd.write("Bajando al ");
            lcd.print(piso);
            lcd.setCursor(0,1);
            lcd.write("Porfavor espere");
            return;
 }

