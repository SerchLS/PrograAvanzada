//Detectar el Uid de c/tarjeta
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

Servo candado;    //Servomotor
int abierto = 0;
int cerrado = 155;
int tiempo = 1000;   

#define RST_PIN         9          // Definir Reset
#define SS_PIN          10         // Definir Slave Select

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Creamos el objeto "mfrc522" tipo "MFRC522"

byte LecturaUid [4];  //Almacenar Uid de las tajetas

byte U1 [4] = {0x2A, 0x56, 0x06, 0x85}; //Banco de datos
byte U2 [4] = {0xC4, 0x96, 0xB0, 0x29}; //de usuarios
byte U3 [4] = {0x25, 0x0B, 0x1B, 0xC3}; //registrados

byte U4 [4] = {0xFE, 0x7A, 0x90, 0x1A};
byte U5 [4] = {0x5E, 0xD3, 0x91, 0x1A};

void setup() {
  Serial.begin(9600);   // Initializar comunicacion Serial
  SPI.begin();      // Iniciar comunicacion SPI
  mfrc522.PCD_Init();   // Inicializar Modulo Lector
  
  candado.attach(3); //Inicializando Servomotor
                        //en pin 12
  pinMode(7, OUTPUT);  //LED Verde  --- Acceso Permitido
  pinMode(6, OUTPUT);  //LED Morado --- Acceso Denegado
  
  //Serial.println("Bienvenido a Polibike");
  //Serial.println("Ingrese tarjeta para continuar\n\n");
}

void loop() {
            
  digitalWrite(7, LOW);       // Condiciones iniciales           
  digitalWrite(6, LOW);       //  de la cerradura
  candado.write(cerrado);     //
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) //Si NO hay una Tarjeta regresa al "void loop"
    {return;}
  
  if ( ! mfrc522.PICC_ReadCardSerial())   //Verifica que se pueda obtener info de la tarjeta
    {return;}
//////////////////////////---Identificación de la Uid---/////////////////////////////////////////

//Serial.print("Uid: ");
  for(byte i=0; i<mfrc522.uid.size; i++)  // el tamaño de Uid puede variar
//    {                                     // mfrc522 detecta el tamaño
//     if(mfrc522.uid.uidByte[i]<0x10)
//       {Serial.print(" ");}        //Bloque para dar formato
//     else                           //cada vez que el num sea mayor a 10 (en HEX)
//       {Serial.print(" ");}          //agregara un espacio
//    Serial.print(mfrc522.uid.uidByte[i], HEX);  //Escribe el Uid
//
    LecturaUid[i] = mfrc522.uid.uidByte[i];     //Guardamos el Uid
//    }
//  Serial.print("\t");
 
//////////////////////////---Identificación de la Uid---////////////////////////////////////////
  
    //////////////////---Bloque de Comparación---////////////////////////////
      if(compara(LecturaUid, U1))       //Mandamos parametros a Funcion Compara
        {
          Serial.println("Sergio");      //Usuario 1
              digitalWrite(7,HIGH);
              candado.write(abierto);
              
              delay(tiempo);
              candado.write(cerrado);
        }     
      else if(compara(LecturaUid, U3))
        {
        Serial.println("Samantha");        //Usuario 3
              digitalWrite(7,HIGH);
              candado.write(abierto);
              
              delay(tiempo);
              candado.write(cerrado);
        }     

 else if(compara(LecturaUid, U4))
        {
        Serial.println("Upiita");        //Usuario 4
              digitalWrite(7,HIGH);
              candado.write(abierto);
              
              delay(tiempo);
              candado.write(cerrado);
        }     


        
      else
      {
        Serial.println("NO Registrado"); //Usuario No REgistrado
              digitalWrite(6,HIGH);
              delay(tiempo);
      }
    //////////////////---Bloque de Comparación---////////////////////////////
  //Serial.println();
  mfrc522.PICC_HaltA();   //Le indicamos a la tarjeta que se detenga
}

////////////////////---Funcion Compara---///////////////////////////////////////
boolean compara(byte lectura[], byte usuario[])
{
  for(byte i=0; i<mfrc522.uid.size; i++)  
  {
    if (lectura[i] != usuario[i])
        return (false);
  }
    return (true);
}
////////////////////////////////////////////////////////////////////////////////




