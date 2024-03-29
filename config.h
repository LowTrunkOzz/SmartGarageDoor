/*
Be sure to update these parameters accordingly.
serverPort will be the port you use to connect
"YOUR_PIN" will be the pin you input into the webpage to gain control
"YOUR_NAME" will be the name displayed at the top of the webpage
"YOUR_PIN" and "YOUR_NAME" MUST be in parenthesis for the code to execute properly.
If you want the web interface available globally, set port forwarding rules from your router's settings accordingly.
I usually use 5142 for the port but you can set it to whatever you'd like as long as it isn't a commonly used port.
Pick the proper section for the number of doors your setup will use and uncomment that section so the appropriate 
pins are defined. You can change them as your setup requires, but some pins will require resistors.
Finally, update USERNAME and USERPASS to whatever you'd like the update page login credentials to be, keeping them
in quotes.
*/

int serverPort = YOUR_PORT;
#define h1_ID "YOUR_NAME"
const char* (pass_sent) = "YOUR_PIN";
const char* host = "esp8266-webupdate";
const char* update_path = "/update";
const char* USERNAME = "admin";      /*make this a fairly secure name*/
const char* USERPASS = "admin";      /*make this a STRONG password*/

//This section is for single door
int openClosePin1 = 5;    //actuate relay 1, door 1 D1
int statusPin1 = 2;         //pin to report if door 1 is open or closed D4

//Uncomment this section for dbl door
/*
int openClosePin2 = 4;     //actuate relay 2, door 2 D2
int statusPin2 = 3;        //pin to report if door 2 is open or closed RX
*/
