
Overview

For this project, I turned my life into a movie by adding a personalized soundtrack by using an Adafruit accelerometer, which plays a song depending on how fast I am walking. There is already an existing product on the market by Think Geek called 'The Personal Soundtrack T-shirt' that plays a song through a speaker located in a shirt. One limitation of this product is that you have to press a button in order for it to start playing a song. My project changes the song automatically depending on the speed that the person is moving. If a person is walking slowly, it will play a slow song, if the person then decides to walk faster then it will play a faster paced song.

Remember to change the names of your tracks to the names in the file. In this file I used track_001, track_002, and track_003. You can also change the speeds that you would like the songs to play too by adjusting the FAST, MEDIUM, and SLOW thresholds. 

Technology used:

Arduino UNOu8232 FLORA Accelerometer/Compass Sensor - LSM303 (v1.0)
VS1053 Codec + MicroSD Breakout - MP3/WAV/MIDI/OGG Play + Record SD/MicroSD Memory Card (4 GB SDHC)
Speaker
Breadboard
Wires

Libraries needed:
AdafruitLSM303master
Adafruit_VS1053
*these can be downloaded from the Adafruit website

Conclusion:

In the end the logic of the code worked but when the device tried to process the movements it lagged causing the device to not be able to keep up with the users movements. If anyone can contribute to fixing this issue that would be greatly appreciated! 

Cool projects like this and more can be found on my portfolio website at www.jennifervandermeer.ca!