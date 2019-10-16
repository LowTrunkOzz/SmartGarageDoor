This is a project taken from https://www.hackster.io/s-wilson/iot-garage-door-yes-another-one-a2a6fb and modified with WiFi Manager so you don't have to input your SSID and password before flashing it to your microcontroller and ArduinoOTA to update remotely.<br>

The pin designations listed below are for the NodeMCU I used for the original proof-of-concept, so don't forget to update those if your ESP8266 is of a different configuration. I have included the code for both a single door and double door configurations. Please update the config.h file to your required port, PIN, and what you want the header to display (PIN and header name MUST be in quotes or it WILL NOT work) and drop that in the same folder as your sketch before you upload. Enjoy!<br>

For single door set-up:<br>

openClosePin = 5;    //actuate relay (D1)<br>
statusPin = 2;       //pin to tell if the door is open/closed (D4)<br>


For double door set-up:<br>

openClosePin1 = 5;   //actuate relay 1, door 1 D1<br>
statusPin1 = 2;      //pin to tell if the door is open/closed on door 1 (D4)<br>
openClosePin2 = 4;   //actuate relay 2, door 2 D2<br>
statusPin2 = 3;      //pin to tell if the door is open/closed on door 2 (RX)<br>
