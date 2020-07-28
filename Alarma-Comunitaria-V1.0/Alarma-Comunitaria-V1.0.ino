/***************************************************************
 *            Proyecto Alarma Comunitaria ITSSMT               *
 *           Autor: Gregorio San Martin Crisostomo             *
 *  Ingeniería en Tecnologías de la información y comunicación *
 ***************************************************************/
 
// Se crea la referencia a la librería SoftwareSerial
#include <SoftwareSerial.h> 

//Se crea la variable que contendrá el mensaje recibido de la tarjeta SIM900
char msj = 0;
// Se establece la variable Rx con el pin 7 el cual hará de receptor en la comunicación serial
int Rx = 7;
// Se establece la variable Tx con el pin 8 el cual hará de receptor en la comunicación serial
int Tx = 8;
// Se establece la variable "activacionPinoutput" con el pin por el cual se generará el pulso para activar el pre actuador (relevador) encargado de activar los periféricos que operen a 12V de la alarma comunitaria
int activacionPinoutput = 2;
// Se instancia la función "mySerial" con los pines de conexión serial por defecto del Arduino Uno
SoftwareSerial mySerial(Rx, Tx);

 void setup()
 {
  //Se inicia una comunicación serial hacia el puerto USB
  Serial.begin(9600);

  //Se habilita la comunicación entre los pines de comunicación del Arduino Uno y el módulo SIM900
  mySerial.begin(9600);

  //Se envía al módulo SIM900 el comando "AT" para verificar la comunicación entre dispositivos
  mySerial.println("AT");

  //Se utiliza la función conexionSerial() para escribir las información en el módulo SIM900
  conexionSerial();

  //Se envía al módulo SIM900 el comando "AT+CMGF=1" para configurar la tarjeta en modo SMS
  mySerial.println("AT+CMGF=1");
  
  //Se utiliza la función conexionSerial() para escribir las información en el módulo SIM900
  conexionSerial();

 //Se envía al módulo SIM900 el comando "AT+CNMI=1,2,0,0,0" permite decidir al módulo cuando debe enviar nuevo contenido desde el módulo SIM900 
  mySerial.println("AT+CNMI=1,2,0,0,0");

 //Se utiliza la función conexionSerial() para escribir las información en el módulo SIM900
  conexionSerial();
  
 }


 void loop()
 {
    // la variable "msj" almacena el ultimo resultado del valor obtenido de la función "mySerial.read()" la cual ejecuta una consulta al módulo SIM900
    msj = mySerial.read();
    
    //Se utiliza la estructura condicional if para definir cuando el valor almacenado en la variable "msj" es el carácter "E"
    if (msj == 'E')
    {
      //Si la condición se cumple se enviará un pulso a través del pin 2 de la distribución de la tarjeta Arduino Uno el cual activará los preactuadores del dispositivo
      digitalWrite(activacionPinoutput,HIGH); 
    }
  
    //Se utiliza la estructura condicional if para definir cuando el valor almacenado en la variable "msj" es el carácter "E"
    if (msj == 'A')
    {
      //Si la condición se cumple se enviará un pulso a través del pin 2 de la distribución de la tarjeta Arduino Uno el cual desactivará los pre actuadores del dispositivo
      digitalWrite(activacionPinoutput,LOW); 
    }
  
 }

//Se crea la función conexionSerial() para establecer un ciclo de comunicación entre ambos dispositivos
 void conexionSerial()
{
  //Se define un paro de 500 milisegundos  
  delay(500);
  
  //Mientras el puerto serial se encuentre activo se deberá ejecutar la instrucción 
  while (Serial.available()) 
  {
    //Se escribe en el modulo SIM900 los valores que son obtenidos del Arduino Uno 
    mySerial.write(Serial.read());
  }
  
  //Mientras el puerto serial se encuentre activo se deberá ejecutar la instrucción 
  while(mySerial.available()) 
  {
    //Se escribe en el Arduino Uno los valores que son obtenidos del SIM900
    Serial.write(mySerial.read());    
  }
}

 
