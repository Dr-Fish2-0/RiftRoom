#include <FastLED.h>

#define NUM_LED 100

CRGB leds[NUM_LED];

//don't alter; later in the code
uint8_t colorIndex = 0; //iterates through color in palette
uint8_t baseIndex = 0;  //changes the starting value of colorIndex to make movement
uint8_t moveFactor = 3; //how much to increase colorIndex by for color selection

int currByte = 0;

uint8_t movementSpeed = 30; //speed of movement, alters how much to increase baseIndex by each iteration
uint8_t currEffect = 0;    //current effect,
/*
0 -> base
1 -> static
3 -> finale
*/

uint8_t paletteSize = 32; //how many colors are stored in the palettes
uint8_t currPalIndex = 0;

//palettes for the effects
CRGBPalette32 basePalette[4];
CRGBPalette32 staticPalette[4];

CRGBPalette32 currPalette;

bool isStatic = false;
bool show = false;

//sets up the base palette
void setupBase(uint8_t paletteIndex, CHSV color)
{
    fill_solid(basePalette[paletteIndex], paletteSize, color); //fill the whole palette with light blue

    for(int i = 0; i < paletteSize; i += 4)
    {
      basePalette[paletteIndex][i] = CRGB::Black; //fill every fourth color with black
    }
}

//set up the palette for the static effect
void setupStatic(uint8_t paletteIndex, CHSV color)
{
  fill_solid(staticPalette[paletteIndex], paletteSize/2, color); //only fill half to achieve more strobe

  for(uint8_t i = 0; i < paletteSize/2; i += 4) //fill up to halfway
  {
    staticPalette[paletteIndex][i] = CRGB::Black;
  }
}

void setup() {
  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LED);

  setupBase(0, CHSV(144, 200, 120.5));  //blue
  setupBase(1, CHSV(192, 255, 100));         //purple
  setupBase(2, CHSV(0, 255, 90));        //red
  setupBase(3, CHSV(0, 0, 100));        //white

  setupStatic(0, CHSV(144, 200, 120.5));  //blue
  setupStatic(1, CHSV(192, 255, 74));         //purple
  setupStatic(2, CHSV(0, 255, 90));        //red
  setupStatic(3, CHSV(0, 0, 100));        //white

  Serial.begin(9600);
}

void loop() {
  colorIndex = baseIndex;

  if(Serial.available()) Serial.write(1);
  currByte = Serial.read();
  
  //read in the serial info to control the state
  if(currByte == 98) isStatic = false;
  if(currByte == 115) isStatic = true;
  if(currByte == 116) show = !show;
  
  //randomly select a color palette for a static effect
  if(isStatic) 
  {
    currPalIndex = random(0,4);
    currPalette = staticPalette[currPalIndex];
  }
  if(!isStatic) currPalette = basePalette[currPalIndex]; 
  
  //assign the colors to the LEDs
  if(show)
  {
    for(int i = 0; i < NUM_LED; i++)
    {
      //select a color from the palette and assign it to the current LED
      leds[i] = ColorFromPalette(currPalette, colorIndex, 120.5, LINEARBLEND); 
      colorIndex += moveFactor;
    }
  }
  
  baseIndex += movementSpeed;
  
  //display the colors
  FastLED.show();
  FastLED.delay(10);
}


