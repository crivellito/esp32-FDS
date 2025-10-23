#ifndef LOGICA_H
#define LOGICA_H
#define CHAT_ID "-1003100355289"                                                       //"7720847255"

#include <UniversalTelegramBot.h>
#include <LiquidCrystal.h>
#include <Arduino.h>

extern UniversalTelegramBot bot;
extern LiquidCrystal lcd;

void logica (bool, float, int);
void buzzer (int);

#endif