#include <Arduino.h>            //Se llama a la libreria de arduino para que reconoceza las funciones porpias de el
#include "testinghall.h"        //Se llama a la libreria .h de nuestro proyecto
#include "angle.h"              //Se llama a la libreria de encabezado

//Definimos las variables de referencia para un estado ideal de campo

static angle_t angle;
int angle_val;
int magnetics_val;
float distancia;
float voltaje;
float vmin = 3.5;
float resultado = -0.08 * distancia + 4;
float temp;
float tempideal = 25;

//Realizamos variables que seran llamados cuando la funcion se cumpla

String mensaje1 = "Ingrese Posicionamiento en grados";
String mensaje2 = "Sensor NO se detecta";
String mensaje3 = "Sensor SI se detecta";
String mensaje5 = "Ingrese Temperatura";
String mensaje6 = "Su distancia y temperatura son: ";

//Se inicializa el hardware en modo simulacion

void setup(){
	Serial.begin(9600);
}

//Se inicia solicitando los datos y llamando al primer mensaje
//Se toma como referencia la hoja de datos del fabricante para lograr detectar el campo magentico
//Se calcula el campo y con eso obtenemos la deteccion del objeto mas la posicion

void loop(){
	Serial.println("*****************");
  	Serial.println(mensaje1);
  while (Serial.available()==0){
  }
  	distancia = Serial.read();
  	distancia = Serial.parseInt();
  	Serial.println(mensaje5);
  while (Serial.available()==0){
  }
  	temp = Serial.read();
  	temp = Serial.parseInt();
  resultado = -0.08 * distancia + 4;
  if(resultado < vmin & (temp == tempideal)){
    Serial.println();
    Serial.println(mensaje2);
    //Serial.println(temp);
  }
  else{
    Serial.println();
    Serial.println(mensaje3);
    Serial.println();
    }
  
  distancia = 0;
  distancia = Serial.parseInt();
   temp = 0;
  temp = Serial.parseInt();

}

//La funcion a probar el cual esta me inicializa la aplicacion
void application_init ( void )
{
    angle_cfg_t cfg;
    angle_cfg_setup( &cfg );
}

//Funcion el cual detecto el angulo de medicion del obejeto con el sensor

void application_task ( void )
{
    angle_val = angle_get_angle( &angle );
    magnetics_val = angle_get_magnetics( &angle );    
    delay(1000);
}