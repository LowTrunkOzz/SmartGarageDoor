This is a project taken from https://www.hackster.io/s-wilson/iot-garage-door-yes-another-one-a2a6fb and modified with WiFi Manager so you don't have to input your SSID and password before flashing it to your microcontroller and ArduinoOTA to update remotely.<br>

The pin designations are for the NodeMCU I used for the original proof-of-concept, so don't forget to update those if your ESP8266 is of a different configuration. Below I've listed what pins I used and which lines in the code to modify for your personal use. I have included the code for both a single door configuration and double door configuration with the pins used and what lines to modify so the PIN, webpage header, and port match your configuration. Enjoy!<br>

For single door set-up:<br>

openClosePin = 5;    //actuate relay (D1)<br>
statusPin = 2;       //pin to tell if the door is open/closed (D4)<br>

Change lines:<br>
37 for their port<br>
45 for their pin<br>
127 for their header<br>


For double door set-up:<br>

openClosePin1 = 5;   //actuate relay 1, door 1 D1<br>
statusPin1 = 2;      //pin to tell if the door is open/closed on door 1 (D4)<br>
openClosePin2 = 4;   //actuate relay 2, door 2 D2<br>
statusPin2 = 3;      //pin to tell if the door is open/closed on door 2 (RX)<br>

Change lines:<br>
39 for their port<br>
47 for their pin<br>
141 for their header<br>