# IEL-823_FinalProject
Aplicaciones de Microcontroladores
Universidad Técnica Nacional
Carrera de Ingeniería Electrónica
Sede central

Ill Cuatrimestre, 2022

Aplicaciones de Microcontroladores

Profesor
Ing. Arnoldo Ramírez

“Proyecto Final”

Responsable:
Aaron Camacho


07 de diciembre del 2022

Metodología
El proceso de realización del proyecto conlleva a una serie de pasos que se ejecutaran a lo largo del desarrollo. El tema a profundizar es analizar y adaptar el código del hardware del sensor MIKROE Angle Click , que es una serie de familias muy utilizadas en el campo, el cual posee una biblioteca y sus códigos principales en lenguaje de programación “C” los archivos de encabezado “.h” y código fuente “.c”, esto validando su funcionamiento.
La ejecución será de manera probar y adaptar el código más la implementación de Arduino IDE para realizar 3 pruebas a nivel de software, logrando simular el hardware del sensor con la finalidad de realizar pruebas para obtener datos aproximados de calibración antes de poner a prueba el hardware en condiciones reales ambientales.

Se describe a continuación el diagrama de bloques:


















Se describe a continuación el diagrama de flujo:






















			Si




Se describe a continuación el código encabezado
/*Se definen todos los registros para el microcontrolador*/
extern "C"{
#ifndef ANGLE_H
#define ANGLE_H
#define ANGLE_OK           0x00
#define ANGLE_INIT_ERROR   0xFF

/**
 * \defgroup error_register_status Error register status
 * \{
 */
#define ANGLE_ERROR_REG_MASK              0x34 
#define ANGLE_EXTENDED_ERROR_REG_MASK     0x36 
#define ANGLE_EXTENDED_ERROR_REG          0x26 
#define ANGLE_ERROR_REG                   0x24 
#define ANGLE_STATUS_REG                  0x22 
#define ANGLE_SETTINGS_REG                0x1E 
/** \} */

/**
 * \defgroup processor_state Change Processor State
 * \{
 */
#define ANGLE_CDS_NO_CHANGLE              0x0000 << 13
#define ANGLE_CDS_IDLE_MODE               0x0002 << 13
#define ANGLE_CDS_RUN_MODE                0x0003 << 13
/** \} */

/**
 * \defgroup hard_reset Hard reset
 * \{
 */
#define ANGLE_HDR_RESET_0                 0x0000 << 12
#define ANGLE_HDR_RESET_1                 0x0001 << 12
/** \} */

/**
 * \defgroup soft_reset Soft Reset
 * \{
 */
#define ANGLE_SFR_RESET_0                 0x0000 << 11
#define ANGLE_SFR_RESET_1                 0x0001 << 11

#define ANGLE_CSR_STA_0                   0x0000 << 9
#define ANGLE_CSR_STA_1                   0x0001 << 9

#define ANGLE_CXE_0                       0x0000 << 8
#define ANGLE_CXE_1                       0x0001 << 8

#define ANGLE_CER_0                      0x0000 << 7
#define ANGLE_CER_1                      0x0001 << 7
/** \} */

/** \} */

// Se definen las estructuras que se van a utilizar solo para las pruebas

typedef struct
{
 
} angle_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{

} angle_cfg_t;

#ifdef __cplusplus
#endif

//se define y contempla las funciones y punteros para el codigo fuente
void angle_cfg_setup ( angle_cfg_t *cfg );

int angle_get_angle ( angle_t *ctx );

int angle_get_temperature ( angle_t *ctx );

int angle_get_magnetics ( angle_t *ctx );
}
#ifdef __cplusplus
#endif
#endif

Se describe a continuación el código fuente
#include "angle.h"          //Se incluye la libreria de encabezados

//Cuatro funciones a definir par la realizacion de las pruebas
void angle_generic_read ( angle_t *ctx, int reg, int *data_buf, int len )
{
}

//Esta funcion obtiene el angulo en dicha posicion del objeto

int angle_get_angle ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int angle;
    int angle_val;
    angle_generic_read( ctx, 0x20, read_reg, 2 );
    angle = read_reg[ 0 ];
    angle <<= 8;
    angle |= read_reg[ 1 ];
    angle &= 0x0FFF;
    angle_val = ( int )( angle * (360 / 4096.0));
    return angle_val;
}

//Esta funcion obtiene la temperatura de operacion del dispositivo

int angle_get_temperature ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int temp;
    int temp_val;
    angle_generic_read( ctx, 0x28, read_reg, 2 );
    temp = read_reg[ 0 ];
    temp <<= 8;
    temp |= read_reg[ 1 ];
    temp &= 0x0FFF;
    temp_val = ( int )temp / 8 - 273;
    return temp_val;
}

//Esta funcion me realiza el calculo de la fuerza magentica

int angle_get_magnetics ( angle_t *ctx )
{
    int read_reg[ 2 ];
    int magnet;
    int magnet_val;
    angle_generic_read( ctx, 0x2A, read_reg, 2 );
    magnet = read_reg[ 0 ];
    magnet <<= 8;
    magnet |= read_reg[ 1 ];
    magnet &= 0x0FFF;
    magnet_val = ( int )magnet;

    return magnet_val;
}


Se describe a continuación el código de pruebas

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






















Resultados de las pruebas

Se realizan tres pruebas el cual consiste en la siguientes: [1]

1.	Prueba de posicionamiento del sensor a una temperatura ambiental optima






Se ingresa el posicionamiento hipotético del objeto inicial







Se ingresa la temperatura ideal recomendado por el fabricante







El sensor si detecta correctamente el objeto.
2.	Prueba de variación de temperatura







Se ingresa la temperatura máxima del hardware que soportaría 








Sensor no logra detectar el objeto y no hay medición del ángulo.










3.	Prueba de validación de posición respecto al campo magnético






Se ingresa el posicionamiento del objeto







Se ingresa la temperatura ideal de funcionamiento







Se detecta el campo magnético lo cual se logra también calcular la distancia



Análisis de resultados

Se analiza cada una de las pruebas.

1.	Prueba Uno
Esta prueba consiste en detectar el objeto con la posición previamente definida ms un caso de temperatura ideal para el hardware, si cumplió con lo esperado, lo cual el estudiante que requiera utilizar el código de esta primera prueba para asegurarse de que el sensor detecte el objeto a cierta posición, se lograra.

2.	Prueba Dos
Se realiza esta prueba con el objetivo de verificar que a ciertas temperaturas recomendadas por el fabricante cumpla con el correcto funcionamiento, el cual se hizo la prueba a una temperatura muy agresiva para el sensor y con las características dadas no se logra medir correctamente los datos de posicionamiento y se manda un mensaje de que no se detecta por el sensor. [2]

3.	Prueba Tres
Se necesita identificar si hay presente campo magnético y cual es su valor para guardarlo en una tabla del computador, lo cual se realiza la prueba y es exitosa segundo el efecto hall y las condiciones del fabricante del sensor se aplica la ecuación el cual mide en teslas el campo magnético y con base a esto se logra calcular el posicionamiento y a que distancia se podría encontrar el objeto.










Conclusiones

1.	Se logra verificar que el sensor pueda funcionar en condiciones ya sea optimas como extremas en el tema de temperatura, dando como resultado que el código de prueba cumple y responde a este requerimiento de funcionalidad. [3]

2.	Se logra dar valores ideales de posicionamiento del objeto y en condiciones ambientales ideales nos da como resultado que si logra detectar el objeto cuando este en la posición que previamente fue guardada en una variable.

3.	Analizando la parte física del sensor se logra determinar cual es el campo magnético en ese momento producido en el objeto hacia el sensor, con base a esto se logra tener un indicar de proximidad y además de lograr identificar el posicionamiento del objeto también podemos obtener la distancia.

















Bibliografía


[1] 	Arduino.cc, «Arduino.cc,» Arduino, [En línea]. Available: https://www.arduino.cc/reference/en/language/functions/communication/serial/print/. [Último acceso: 12 11 2022].
[2] 	G. S. Charcape, Caracterización Eléctrica Por Efecto Hall Del Silicio, 2011 ed., 2. Editorial Academica Espanola, Ed., p. 56.
[3] 	E. C. D. Search, «Electronic Components Datasheet Search,» SEC Electronics Inc, [En línea]. Available: https://pdf1.alldatasheet.com/datasheet-pdf/view/473135/SECELECTRONICS/SS49E.html. [Último acceso: 12 11 2022].
[4] 	Sparkfun, «Sparkfun Sensor Modules,» Sparkfun, 05 2018. [En línea]. Available: https://www.sparkfun.com/products/20193. [Último acceso: 12 2022].
[5] 	github, «https://www.arduino.cc/reference/en/,» Arduino, [En línea]. Available: https://github.com/arduino/reference-en. [Último acceso: 12 11 2022].















Apéndice

Se recopila el procedimiento paso  a paso de como se realizo el repositorio para el control de versiones de los códigos.

1.	Descargar GIT










2.	Una vez que hayas descargado el instalador, haz doble clic sobre el ejecutable para que comience el proceso de instalación y sigue las instrucciones que te aparecerán en pantalla. Al igual que cualquier otro programa, tendrás que dar “Next” (siguiente) en varias ocasiones hasta que aparezca la opción “Finish” (terminar) para completar la instalación.

3.	Ahora tienes que abrir el símbolo de sistema y escribir los siguientes comandos en la terminal:





4.	Ahora creamos una llave SSH en GIT siguiendo el manual, una vez que consigamos la clave nos dirigimos a GitHub para realizar la carga del repositorio


5.	Ingresamos a GitHub.












6.	Dentro de nuestra cuenta hacemos el enlace con nuestra computadora para agregar la clave SSH.







7.	Ahora tenemos que crear nuestro repositorio en nuestra cuenta


8.	Ahora nos vamos a nuestra carpeta donde esta nuestros archivos y damos clic derecho y seleccionamos Git.












	



9.	Hacemos la carga al repositorio local y luego al repositorio de GitHub.



10.	Una vez realizado podemos abrir nuestros códigos en la ubicación de la carpeta con Visual Studio Code.










11.	Hacemos la caga local y remota por medio del terminal de Visual Studio Code.



12.	Verificamos en GitHub que los commits y cambios se hayan guardado correctamente.

13.Por último agregamos un archivo README para identificar y ordenar todo dentro del repositorio.
