/********************************************************************************************************
  Scripted by Sid for Sid's E Classroom
  https://www.youtube.com/c/SidsEClassroom

  Modified by Kubik256 for using LilyPad Arduino USB controlled via USB ;)
  
  ---------------------------------------------------------------------------------------------------------
  NeoPixel Information for initializing the strip, below
  60ma/pixel for current load
  Parameter 1 = number of pixels in strip
  Parameter 2 = pin number (most are valid)
  Parameter 3 = pixel type flags, add together as needed:
    NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

**********************************************************************************************************/

#include <Adafruit_NeoPixel.h>

// the data pin for the NeoPixels
uint8_t neoPixelPin = 0;//Change the pin numbers according to your board

uint8_t numPixels = 8; //Change it according to the number of pixels in your neopixel
// Instatiate the NeoPixel from the ibrary
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels,neoPixelPin,NEO_GRB+NEO_KHZ800);

//Starting pixels for the Google's 4 colours
uint8_t start1=0;
uint8_t start2=2;
uint8_t start3=4;
uint8_t start4=6;

int brightness=150;
int brightDirection=-15;
#define DELAY_TIME (50)

unsigned long startTime;
uint8_t incomingByte;

void setup(){
  Serial.begin(4800);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  startTime = millis();
  activatecircle();
  activateblink();
}

void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    switch(incomingByte){
    case 0x01:
      delay(10);
      if(startTime + DELAY_TIME < millis()){
        activateblink();
        startTime = millis();
      }
      break;
    case 0x02:
      delay(10);
      if(startTime + DELAY_TIME < millis()){
        activatecircle();
        startTime = millis();
      }
      break;
    case 0x03:
      delay(10);
      knightRider(64, 3, 0x176BEF);
    default: 
      allOff();
    }        
  }
}

void allOff(){
  for(int i=0; i<numPixels; i++){strip.setPixelColor(i,0x000000);}
  strip.show();
}

//Circling effect
void activatecircle(){
  adjustStarts();
  // first 20 pixels = color set #1
  for(uint8_t i=start1;i<start1+1;i++){
    strip.setPixelColor(i, 23, 107, 239 );
  }
  // next 20 pixels = color set #2
  for(uint8_t i = start2; i < start2 + 1 ; i++ ) {
    strip.setPixelColor(i, 255, 62, 48 );
  }
  // last 20 pixels = color set #3
  for(uint8_t i = start3; i < start3 + 1; i++ ) {
    strip.setPixelColor(i, 247, 181, 41 );
  }
  for(uint8_t i = start4; i < start4 + 1; i++ ) {
    strip.setPixelColor(i, 23, 156, 82 );
  }
  strip.show();
}

//Blinking Effect. The RGB Colours are based on the Google's Logo
void activateblink(){
  for (uint8_t i = start1; i < start1 + 1; i++ ) {
    strip.setPixelColor(i, 23, 107, 239 );
    strip.setBrightness(brightness);
    strip.show();
    adjustBrightness();
  }
  for (uint8_t i = start2; i < start2 + 1 ; i++ ) {
    strip.setPixelColor(i, 255, 62, 48 );
    strip.setBrightness(brightness);
    strip.show();
    adjustBrightness();
  }
  for (uint8_t i = start3; i < start3 + 1; i++ ) {
    strip.setPixelColor(i, 247, 181, 41 );
    strip.setBrightness(brightness);
    strip.show();
    adjustBrightness();
  }
  for (uint8_t i = start4; i < start4 + 1; i++ ) {
    strip.setPixelColor(i, 23, 156, 82 );
    strip.setBrightness(brightness);
    strip.show();
    adjustBrightness();
  }
  strip.show();
}

void adjustStarts(){
  start1 = incrementStart(start1);
  start2 = incrementStart(start2);
  start3 = incrementStart(start3);
  start4 = incrementStart(start4);
}

int incrementStart(int startValue){
  (startValue == numPixels) ? 0 : startValue++;
  return startValue;
}

void adjustBrightness(){
  brightness = brightness + brightDirection;
  if(brightness < 0){
    brightness = 0;
    brightDirection = -brightDirection;
  }
  else if(brightness > 255){
    brightness = 255;
    brightDirection = -brightDirection;
  }
}

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}

void knightRider(uint16_t speed, uint8_t width, uint32_t color) {
  uint32_t old_val[numPixels];
  for(uint32_t count = numPixels-1; count>=0; count--) {
    strip.setPixelColor(count, color);
    old_val[count] = color;
    for(uint8_t x = count; x<=numPixels ;x++) {
      old_val[x-1] = dimColor(old_val[x-1], width);
      strip.setPixelColor(x+1, old_val[x+1]);
    }
    strip.setBrightness(brightness);
    strip.show();
    adjustBrightness();
    delay(speed);
  }
}
