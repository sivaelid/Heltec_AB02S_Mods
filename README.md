HELTEC AB02S GPS module GALILEO Settings and Best configuration

I have added this repository to enable information for the configuration to get the best form the CubeCell GPS board, particularly to   be able to configure the Air530 GPS. I have to say very pleased with the overall module but have comments regarding the configuration and support of GALILEO GNSS on this device. This GALILEO GNSS is supposed to have a better general user precision and HDOP that can go down below 1.0m using a single GNS network.

I have now carried out some tests on the Air530 using the Sketch configAir530_Vaelid to allow testing of the stated GALILEO setting specified in the Luat Air530 manual. These do not work and that the only settings that work are for GPS, BEIDOU, and GLONASS.

My comments on recommendations are:

First: I have altered the Example “LoRaWan_OnBoardGPS_Air530” Sketch as when I tried it was consuming 3.3ma as configured as the display was always on, so changed some settings namely adding “display. Stop ()” to sketch and set AT support to “OFF” and RGB “DEACTIVE” in the board manager. This got the idle current down to 35uA (Very good).

Second:  The above sketch did not show the Satellites seen by the Air530 on the display, so I have added that to the display in the updated Example Sketch.

Thirdly: I wanted a manual in English that I could use to configure the Air530 and that I could understand. To this end I have spent some time to translate this manual and amend where necessary and have placed here as there are many commands that people may find interesting. 

Fourthly: and most importantly is that I wanted to use the Air530 as I had seen that the Air530 will support European GALILEO satellites. 
With the push to only the use US or European Infrastructure, I wanted to enable GPS and GALILEO GNSS.

The setting for the configuration of the Satellite constellations received is in the NEMA command 115 that can be used to configure the Air530. It is noted that this command when tested did not behave as the manufactures specification and failed to Generate any “GA” or “GN” messages when used as either a single setting or combined with “GPS” to detect GALILEO satellite network.  From testing this is a function that does not work. This is does not comply with the setting process in the user manual.

It is also worth noting that the Air530 can only support 2 GNSS system and not 4 as expected. So, based on testing for Europe, then the settings that give the most satellites visible and hence accuracy, is with GPS and GLONASS set for the search mode. Using   the command $PGKC115,1,1,0,0*2A<CR><LF>.
  
Within the Sketch this setting can been added by placing in the void setup () { Air530.setmode(MODE_GPS_GLONASS);

The above setting is the best from my location in the UK   and measured as an average over a 4-hour window. Though this will vary by time of day and satellite locations. 
Satellite network used	      No of Satellites seen by GSV messages 	      No of Satellites seen by GGA messages
GPS - GP	                                      12	                                          9
BEIDOU - BD	                                    7                                           	5
GLONASS - GL	                                  8	                                            7
GALILEO - GA	                                  0	                                            0
GPS- GP + BEIDOU - BD	                      GP 11, BD 7	                                      10
GPS- GP + GLONASS- GL	                      GP 11, GL 8	                                      15
GPS- GP + GALILEO - GA	                    GP 11, GA 0	                                      9

To do the above test, I have had to amend the GPS_Air530.cpp and GPS_Air530.h as they had not been configured for GALILEO or what I hope would be 4 Multiple GNSS arrangement to test for multiple satellites. 
In addition, I have added to the example sketch “LoRaWan_OnBoardGPS_Air530” the line “#define GPS.setmode(MODE_GPS_GLONASS); “this was the best setting I could achieve to receive the most concurrent satellites.

The code file use

The GPS_Air530.h and GPS_Air530.cpp files held here can be down loaded and copied to typically to the location below to replace the current version. These only add the following commands to allow testing or use of the GALILEO or Mult GNSS setting (note these do not work in the AIR530) these do not alter any other functionality so can be used as replacements. They add to the set of the GPS.set modes as follows:

The modes supported: 
GPS:    MODE_GPS					                    	- this works
GPS+BEIDOU:    MODE_GPS_BEIDOU 				          - this works 
GPS+GLONASS:    MODE_GPS_GLONASS 			          - this works 
GPS+GALILEO:    MODE_GPS_GALILEO			        	- this does not work
GPS+BEIDOU+GLONASS+GALILEO:   MODE_GPS_MULTI   	- this does not work
The default mode is GPS+BEIDOU.

The file locations are: 

C:\Users\User\AppData\Local\Arduino15\packages\CubeCell\hardware\CubeCell\1.0.0\libraries\OnBoardGPS_Air530
The Example files may be stored and used from any location the user wants.  

Checksum Calculation

As part of the NEMA configuration commands  there is a checksum e.g. *2A. the most convenient way to calculate this is with a NEMA Checksum calculator the one I used was https://nmeachecksum.eqth.net/  this worked well.

I hope this is of use to others as the unit works well and I have several good uses for them.
Simon
