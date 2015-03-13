// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  //Adafruit_VS1053_FilePlayer(SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Make my life into a movie!");
  
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT); 
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  Serial.println(F("Accelerometer LSM303 found"));
}

#define FAST_THRESHOLD 70
#define SLOW_THRESHOLD 30 
int currentTrack = musicPlayer.currentTrack;
String trackName; 
double storedVector = lsm.accelData.x*lsm.accelData.x;
double newVector = lsm.accelData.x*lsm.accelData.x;

void loop() {
  
  lsm.read();
  Serial.print("Accel X: "); Serial.print(lsm.accelData.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(lsm.accelData.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.print(lsm.accelData.z);     Serial.print(" ");
 
  // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  storedVector += lsm.accelData.y*lsm.accelData.y;
  storedVector += lsm.accelData.z*lsm.accelData.z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(1000);
  
  // get new data!
  lsm.read();
  newVector += lsm.accelData.y*lsm.accelData.y;
  newVector += lsm.accelData.z*lsm.accelData.z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);
  
  if (abs(newVector - storedVector) <= SLOW_THRESHOLD) {
    Serial.println("MOVING SLOW!!");
    trackName = "track001.mp3";
  } else if (abs(newVector - storedVector) >= FAST_THRESHOLD) {
    Serial.println("MOVING FAST!!");
    musicPlayer.startPlayingFile("track003.mp3");
  } else {
    Serial.println("MOVING MEDIUM!!");
    musicPlayer.startPlayingFile("track002.mp3");  
  }


  if (currentTrack==trackName) {
    loop();
  } else {
    musicPlayer.startPlayingFile("track001.mp3")
  }
  
  
}
  
