/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                 //
//Be sure to update these parameters accordingly. "YOUR_PIN" and "YOUR_NAME Smart Garage Door" MUST be in          //
//in parenthesis for the code to execute properly. If you want the web interface available globally, set port      //
//forwarding rules from your router's settings accordingly. I usually use 5142 for the port but you can set it to  //
//whatever you'd like as long as it isn't a commonly used port. "YOUR_PIN" should be any easily remembered four    //
//digit string and is required for operation. I really wouldn't suggest making 0000 or any easily guessed string.  //
//                                                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int serverPort = YOUR_PORT;
const char* (pass_sent) = "YOUR_PIN";
#define h1_ID "YOUR_NAME Smart Garage Door"

const char* host = "esp8266-webupdate";
const char* update_path = "/firmware";
const char* update_username = "admin";      //make this a fairly secure name
const char* update_password = "passw0rd";   //make this a STRONG password