/*
################################################################################
# File Name:             MAX7219_5.ino                                             
# Board:                 Arduino UNO         
#                      
# Objective:             Scrolling LED dot Matrix           
# Author:                Marcelo Moraes 
# Date:                  July 9th, 2013 
# Place:                 Sorocaba - SP - Brazil 
#Modified by:        Engr Fahad
#website:        www.electroniclinic.com                   
################################################################################
 
 This code is a public example.
 */



//******************************************************************************
// visit this web page for further information about MaxMatrix library
// https://code.google.com/p/arudino-maxmatrix-library/
//******************************************************************************


#include "MaxMatrix.h"
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
SoftwareSerial Blue(2, 3);

uint8_t data = 11;    // Pro Mini pin 11, DIN (MOSI)
uint8_t load = 10;    // Pro Mini pin 10, CS
uint8_t clock = 13;  // Pro Mini pin 13, CLK (SCK)

uint8_t maxInUse = 4;    //change this variable to set how many MAX7219's you'll use

MaxMatrix m(data, load, clock, maxInUse); // define module

// active sentenses
char string1[] = " WELCOME TO ELECTRONIC CLINIC ";

// just for tests
char string7[] = " A B C D E F G H I J K L M N O P Q R S T U V X W Y Z ";
char string8[] = " a b c d e f g h i j k l m n o p q r s t u v x w y z ";
char string9[] = " 1 2 3 4 5 6 7 8 9 0 - = ";
char string10[] = " ! @ # $ % ¨ & * ( ) _ + ";
char string11[] = " ' , . ; ~ ] ´ [ | < > : ^ } ` { / ?  ";

char string12[] = " Hello ! ";

int bactive = 0 ; //bluetooth active
int bdactive=0; // bluetooth deactive
char bluetooth[20]; 
char c;


void setup(){
  m.init(); // module initialize
  m.setIntensity(15); // dot matix intensity 0-15
  Serial.begin(9600); // serial communication initialize
  Blue.begin(9600);
}

void loop(){


  /*
  // this is the code if you want to entering a message via serial console
 if (Blue.available() > 0)
{
     c = Blue.read();
  //  Serial.println(c);
    printCharWithShift(c, 100);
    bluetooth[20] += c; 
 }
 
  if (Serial.available() > 0)
{
     c = Serial.read();
  //  Serial.println(c);
    printCharWithShift(c, 100);
    bluetooth[20] += c; 
 }

  delay(100);
  m.shiftLeft(false, true);
  
  
  // 1st block - print the active sentences
  // comment this block when using the 2nd messages block


 //printStringWithShift(string1, 100);
  //printStringWithShift(string2, 100);
  //printStringWithShift(string3, 100);
  //printStringWithShift(string4, 100);
  //printStringWithShift(string5, 100);
  //printStringWithShift(string6, 100);

  // 2nd block - print sentences just for tests
  // uncomment this block to use it
  /*
  printStringWithShift(string7, 100);
  printStringWithShift(string8, 100);
  printStringWithShift(string9, 100);
  printStringWithShift(string10, 100);
  printStringWithShift(string11, 100);
  */
  //m.shiftUp(true);
  m.printStringWithShift("Ayy Lmao", 20);
}
