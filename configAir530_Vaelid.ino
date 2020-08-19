/* The example is for CubeCell_GPS,
 * GPS works only before lorawan uplink, the board current is about 35 uA when in lowpower mode.
 * Modified by Https://SecureThings.uk to take account changes see associated information 18/08/2020
 */
 
#include "Arduino.h"
#include "GPS_Air530.h"

void setup() {
  Serial.begin(115200);
  Air530.begin();
  
 /* The modes supported are: 
  * GPS        :    MODE_GPS - this works
  * GPS+BEIDOU :    MODE_GPS_BEIDOU this works 
  * GPS+GLONASS:    MODE_GPS_GLONASS this works 
  * GPS+GALILEO:    MODE_GPS_GALILEO this does not work
  * GPS+BEIDOU+GLONASS+GALILEO:   MODE_GPS_MULTI   this does not work
  * default mode is GPS+BEIDOU.
  */
  
Air530.setmode(MODE_GPS_GLONASS); // was commented out
String NMEA = Air530.getGSA();
  
  /*supported nmea sentence :
  * GLL, RMC, VTG, GGA, GSA, GSV
  */
Air530.setNMEA(NMEA_GGA|NMEA_GSV); // was commented out  and had  (NMEA_GGA|NMEA_GSA|NMEA_RMC|NMEA_VTG);
  
  /* set PPS mode and pulse width.
  *  void setPPS(uint8_t mode, uint16_t pulse_width = 500);
  *  mode : 0, pps off;
  *         1, fisrt fixed;
  *         2, 3D fixed;
  *         3, 2D/3D fixed;
  *         4, always on;
  *  width : max value is 998 ms, default value is 500ms;
  */
Air530.setPPS(3,500);     //Was commented out   
}

void loop()
{
  /*get nmea sentence
  * GPS.getNMEA() to get an any kind of nmea sentence;
  * GPS.getRMC() to get RMC sentence;
  * GPS.getGGA() to get GGA sentence;
  * GPS.getGSA() to get GSA sentence;
  * GPS.getGSV() to get GSV sentence;
  * GPS.getGLL() to get GLL sentence;
  * GPS.getVTG() to get VTG sentence;
  */
  String NMEA = Air530.getNMEA(); 
  if(NMEA != "0")
  {
    Serial.println(NMEA);
  }
}
