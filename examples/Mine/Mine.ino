//We always have to include the library
#include "LedControl.h"
#include <stdio.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define PIN_DIN 13
#define PIN_CLK 12
#define PIN_CS 14

LedControl lc=LedControl(PIN_DIN, PIN_CLK, PIN_CS, 5);

/* we always wait a bit between updates of the display */
unsigned long delaytime=800;

const unsigned char CH[] = {
3, 8, B0000000, B0000000, B0000000, B0000000, B0000000, // space
1, 8, B1111101, B0000000, B0000000, B0000000, B0000000, // !
3, 8, B1100000, B0000000, B1100000, B0000000, B0000000, // "
5, 8, B0010100, B0111110, B0010100, B0111110, B0010100, // #
4, 8, B0010010, B0101011, B1101010, B0100100, B0000000, // $
5, 8, B1100011, B1100100, B0001000, B0010011, B1100011, // %
5, 8, B0110110, B1001001, B0110101, B0000010, B0000101, // &
1, 8, B1100000, B0000000, B0000000, B0000000, B0000000, // '
3, 8, B0011100, B0100010, B1000001, B0000000, B0000000, // (
3, 8, B1000001, B0100010, B0011100, B0000000, B0000000, // )
5, 8, B0001010, B0001100, B0111000, B0001100, B0001010, // *
5, 8, B0001000, B0001000, B0111110, B0001000, B0001000, // +
2, 8, B00001101, B0000111, B0000000, B0000000, B0000000, // ,
4, 8, B0001000, B0001000, B0001000, B0001000, B0000000, // -
2, 8, B0000011, B0000011, B0000000, B0000000, B0000000, // .
4, 8, B0000011, B0001100, B0110000, B1000000, B0000000, // /
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // 0
3, 8, B0100001, B1111111, B0000001, B0000000, B0000000, // 1
4, 8, B0100011, B1000101, B1001001, B0110001, B0000000, // 2
4, 8, B0100010, B1000001, B1001001, B0110110, B0000000, // 3
4, 8, B0001100, B0010100, B0100100, B1111111, B0000000, // 4
4, 8, B1110010, B1010001, B1010001, B1001110, B0000000, // 5
4, 8, B0111110, B1001001, B1001001, B0000110, B0000000, // 6
4, 8, B1000011, B1000100, B1001000, B1110000, B0000000, // 7
4, 8, B0110110, B1001001, B1001001, B0110110, B0000000, // 8
4, 8, B0110000, B1001001, B1001001, B0111110, B0000000, // 9
2, 8, B00001010, B0000000, B0000000, B0000000, B0000000, // :
2, 8, B00000001, B00001010, B0000000, B0000000, B0000000, // ;
3, 8, B0000100, B0001010, B0010001, B0000000, B0000000, // <
3, 8, B0010100, B0010100, B0010100, B0000000, B0000000, // =
3, 8, B0010001, B0001010, B0000100, B0000000, B0000000, // >
4, 8, B0100000, B1001101, B1001000, B0110000, B0000000, // ?
5, 8, B0111110, B1001001, B1010101, B1011101, B0111000, // @
4, 8, B0111111, B1000100, B1000100, B0111111, B0000000, // A
4, 8, B1111111, B1001001, B1001001, B0110110, B0000000, // B
4, 8, B0111110, B1000001, B1000001, B0100010, B0000000, // C
4, 8, B1111111, B1000001, B1000001, B0111110, B0000000, // D
4, 8, B1111111, B1001001, B1001001, B1000001, B0000000, // E
4, 8, B1111111, B1001000, B1001000, B1000000, B0000000, // F
4, 8, B0111110, B1000001, B1001001, B0101111, B0000000, // G
4, 8, B1111111, B0001000, B0001000, B1111111, B0000000, // H
3, 8, B1000001, B1111111, B1000001, B0000000, B0000000, // I
4, 8, B0000110, B0000001, B1000001, B1111110, B0000000, // J
4, 8, B1111111, B0001000, B0010100, B1100011, B0000000, // K
4, 8, B1111111, B0000001, B0000001, B0000001, B0000000, // L
5, 8, B1111111, B0100000, B0011000, B0100000, B1111111, // M
5, 8, B1111111, B0010000, B0001000, B0000100, B1111111, // N
4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // O
4, 8, B1111111, B1001000, B1001000, B0110000, B0000000, // P
4, 8, B0111110, B1000001, B1000001, B01111101, B0000000, // Q
4, 8, B1111111, B1001000, B1001000, B0110111, B0000000, // R
4, 8, B0110001, B1001001, B1001001, B0100110, B0000000, // S
5, 8, B1000000, B1000000, B1111111, B1000000, B1000000, // T
4, 8, B1111110, B0000001, B0000001, B1111110, B0000000, // U
5, 8, B1111000, B0000110, B0000001, B0000110, B1111000, // V
5, 8, B1111110, B0000001, B0001110, B0000001, B1111110, // W
5, 8, B1100011, B0010100, B0001000, B0010100, B1100011, // X
5, 8, B1110000, B0001000, B0000111, B0001000, B1110000, // Y
4, 8, B1000011, B1000101, B1001001, B1110001, B0000000, // Z
2, 8, B1111111, B1000001, B0000000, B0000000, B0000000, // [
4, 8, B1000000, B0110000, B0001100, B0000011, B0000000, // backslash
2, 8, B1000001, B1111111, B0000000, B0000000, B0000000, // ]
3, 8, B0100000, B1000000, B0100000, B0000000, B0000000, // hat
4, 8, B0000001, B0000001, B0000001, B0000001, B0000000, // _
2, 8, B1000000, B0100000, B0000000, B0000000, B0000000, // `
4, 8, B0000010, B0010101, B0010101, B0001111, B0000000, // a
4, 8, B1111111, B0010001, B0010001, B0001110, B0000000, // b
4, 8, B0001110, B0010001, B0010001, B0001010, B0000000, // c
4, 8, B0001110, B0010001, B0010001, B1111111, B0000000, // d
4, 8, B0001110, B0010101, B0010101, B0001100, B0000000, // e
3, 8, B0010000, B0111111, B1010000, B0000000, B0000000, // f
4, 8, B00011001, B00100101, B00100101, B00011110, B0000000, // g
4, 8, B1111111, B0010000, B0010000, B0001111, B0000000, // h
3, 8, B0010001, B1011111, B0000001, B0000000, B0000000, // i
4, 8, B0000001, B00000001, B00100001, B1011111, B0000000, // j
4, 8, B1111111, B0000100, B0001010, B0010001, B0000000, // k
3, 8, B1000001, B1111111, B0000001, B0000000, B0000000, // l
5, 8, B0011111, B0010000, B0011111, B0010000, B0001111, // m
4, 8, B0011111, B0010000, B0010000, B0001111, B0000000, // n
4, 8, B0001110, B0010001, B0010001, B0001110, B0000000, // o
4, 8, B00111111, B0010010, B0010010, B0001100, B0000000, // p
4, 8, B0001100, B0010010, B0010010, B00111111, B0000000, // q
4, 8, B0011111, B0001000, B0010000, B0010000, B0000000, // r
4, 8, B0001001, B0010101, B0010101, B0010010, B0000000, // s
3, 8, B0010000, B1111110, B0010001, B0000000, B0000000, // t
4, 8, B0011110, B0000001, B0000001, B0011111, B0000000, // u
5, 8, B0011100, B0000010, B0000001, B0000010, B0011100, // v
5, 8, B0011110, B0000001, B0011110, B0000001, B0011110, // w
5, 8, B0010001, B0001010, B0000100, B0001010, B0010001, // x
4, 8, B00111001, B00000101, B00000101, B0011111, B0000000, // y
3, 8, B0010011, B0010101, B0011001, B0000000, B0000000, // z
3, 8, B0001000, B0110110, B1000001, B0000000, B0000000, // {
1, 8, B1111111, B0000000, B0000000, B0000000, B0000000, // |
3, 8, B1000001, B0110110, B0001000, B0000000, B0000000, // }
4, 8, B0001000, B0010000, B0001000, B0010000, B0000000, // ~
};

void setup() {  
  for(int addr=0; addr<lc.getDeviceCount(); addr++) {
    /*
     The MAX72XX is in power-saving mode on startup,
     we have to do a wakeup call
     */
    lc.shutdown(addr,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(addr, 5);
    /* and clear the display */
    lc.clearDisplay(addr);
  }
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5]={B01111110,B10001000,B10001000,B10001000,B01111110};
  byte r[5]={B00111110,B00010000,B00100000,B00100000,B00010000};
  byte d[5]={B00011100,B00100010,B00100010,B00010010,B11111110};
  byte u[5]={B00111100,B00000010,B00000010,B00000100,B00111110};
  byte i[5]={B00000000,B00100010,B10111110,B00000010,B00000000};
  byte n[5]={B00111110,B00010000,B00100000,B00100000,B00011110};
  byte o[5]={B00011100,B00100010,B00100010,B00100010,B00011100};

  /* now display them one by one with a small delay */
  lc.setColumn(0,0,a[0]);
  lc.setColumn(0,1,a[1]);
  lc.setColumn(0,2,a[2]);
  lc.setColumn(0,3,a[3]);
  lc.setColumn(0,4,a[4]);
  delay(delaytime);
  lc.setColumn(0,0,r[0]);
  lc.setColumn(0,1,r[1]);
  lc.setColumn(0,2,r[2]);
  lc.setColumn(0,3,r[3]);
  lc.setColumn(0,4,r[4]);
  delay(delaytime);
  lc.setColumn(0,0,d[0]);
  lc.setColumn(0,1,d[1]);
  lc.setColumn(0,2,d[2]);
  lc.setColumn(0,3,d[3]);
  lc.setColumn(0,4,d[4]);
  delay(delaytime);
  lc.setColumn(0,0,u[0]);
  lc.setColumn(0,1,u[1]);
  lc.setColumn(0,2,u[2]);
  lc.setColumn(0,3,u[3]);
  lc.setColumn(0,4,u[4]);
  delay(delaytime);
  lc.setColumn(0,0,i[0]);
  lc.setColumn(0,1,i[1]);
  lc.setColumn(0,2,i[2]);
  lc.setColumn(0,3,i[3]);
  lc.setColumn(0,4,i[4]);
  delay(delaytime);
  lc.setColumn(0,0,n[0]);
  lc.setColumn(0,1,n[1]);
  lc.setColumn(0,2,n[2]);
  lc.setColumn(0,3,n[3]);
  lc.setColumn(0,4,n[4]);
  delay(delaytime);
  lc.setColumn(0,0,o[0]);
  lc.setColumn(0,1,o[1]);
  lc.setColumn(0,2,o[2]);
  lc.setColumn(0,3,o[3]);
  lc.setColumn(0,4,o[4]);
  delay(delaytime);
  lc.setColumn(0,0,0);
  lc.setColumn(0,1,0);
  lc.setColumn(0,2,0);
  lc.setColumn(0,3,0);
  lc.setColumn(0,4,0);
  delay(delaytime);
}

void writeArduino() {
  char msg[] = "Arduino ESP8266";
  printString( msg );
}

void printString(char* s)
{
  byte buffer[10];
  int col = 0;
  while (*s != 0)
  {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    lc.writeSprite(col, 0, buffer);
    lc.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0;row<8;row++) {
    delay(delaytime);
    lc.setRow(0,row,B10100000);
    delay(delaytime);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(0,row,B10100000);
      delay(delaytime);
      lc.setRow(0,row,(byte)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int max=0; max<lc.getDeviceCount(); max++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setColumn(max,col,B10100000);
      delay(delaytime);
      lc.setColumn(max,col,(byte)0);
      for(int i=0;i<col;i++) {
        delay(delaytime);
        lc.setColumn(max,col,B10100000);
        delay(delaytime);
        lc.setColumn(max,col,(byte)0);
      }
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int max=0; max<lc.getDeviceCount(); max++) {
    for(int row=0;row<8;row++) {
      for(int col=0;col<8;col++) {
        lc.setLed(max, row, col, HIGH);
        delay(delaytime);
        lc.setLed(max, row, col, LOW);
      }
    }
  }
}

/* 
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void screen() {
  
  for(int row=0;row<8;row++) {
    for(int max=0; max<lc.getDeviceCount(); max++) {
      for(int col=0;col<8;col++) {
        lc.setLed(max, row, col, HIGH);
        delay(delaytime);
        lc.setLed(max, row, col, LOW);
      }
    }
  }
}

void loop() { 
  writeArduino();
}
