This is a project taken from https://www.hackster.io/s-wilson/iot-garage-door-yes-another-one-a2a6fb and modified with WiFi Manager so you don't have to input your SSID and password before flashing it to your microcontroller. The pin designations are for the NodeMCU I used for the original proof-of-concept, so don't forget to update those if your ESP8266 is of a different configuration. Below I've listed what pins I used and which lines in the code to modify for your personal use. I have included the code for both a single door configuration and double door configuration with the pins used and what lines to modify so the PIN, webpage header, and port match your configuration. Enjoy!

For single door set-up:

openClosePin = 5;    //actuate relay (D1)
statusPin = 2;       //pin to tell if the door is open/closed (D4)

Change lines:
37 for their port
45 for their pin
127 for their header


For double door set-up:

openClosePin1 = 5;   //actuate relay 1, door 1 D1
statusPin1 = 2;      //pin to tell if the door is open/closed on door 1 (D4)
openClosePin2 = 4;   //actuate relay 2, door 2 D2
statusPin2 = 3;      //pin to tell if the door is open/closed on door 2 (RX)

Change lines:
39 for their port
47 for their pin
142 for their header