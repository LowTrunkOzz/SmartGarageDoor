/*
Be sure to update these parameters accordingly.
serverPort will be the port you use to connect
"YOUR_PIN" will be the pin you input into the webpage to gain control
"YOUR_NAME" will be the name displayed at the top of the webpage
"YOUR_PIN" and "YOUR_NAME" Smart Garage Door" MUST be in parenthesis for the code to execute properly.
If you want the web interface available globally, set port forwarding rules from your router's settings accordingly.
I usually use 5142 for the port but you can set it to whatever you'd like as long as it isn't a commonly used port.
Finally, update USERNAME and USERPASS to whatever you'd like the update page login credentials to be.
*/


int serverPort = YOUR_PORT;
const char* (pass_sent) = "YOUR_PIN";
#define h1_ID "YOUR_NAME"
const char* host = "esp8266-webupdate";
const char* update_path = "/update";
const char* USERNAME = "admin";      //make this a fairly secure name
const char* USERPASS = "admin";      //make this a STRONG password