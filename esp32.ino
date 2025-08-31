#include "conexion.h"

const char *miSSID = NULL;
const char *miPASS = NULL;
const int  *miCHATID = NULL;
const char *miBOTTOKEN = NULL;

void setup(){
  Serial.begin(115200);
}

void loop (){
  conexion(&miSSID, &miPASS, &miBOTTOKEN, &miCHATID);
  delay(500);
}


