
#include "Arduino.h" 



/* IoT Garage Door Opener
Forked from https://www.hackster.io/s-wilson/iot-garage-door-yes-another-one-a2a6fb and modified with code
from https://hieromon.github.io/AutoConnect/otabrowser.html#how-to-embed-esp8266httpupdateserver-in-autoconnect

Good solution for operating garage doors without the need to have an actual remote, only an internet connection
is required. Easily updated with .bin files through a web interface. All credit to the two links above, I just
hacked them together!
*/


#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <AutoConnect.h>
ESP8266WebServer httpServer;                
ESP8266HTTPUpdateServer httpUpdate;         
AutoConnect portal(httpServer);             
AutoConnectAux update("/update", "UPDATE"); 
AutoConnectAux hello;   
#include "config.h"

extern "C" {
  #include "user_interface.h"
}
 


int openClosePin = 5; //actuate relay D1
int statusPin = 2; //pin to tell open/close D4


String HTTP_req;
String code;

WiFiServer server(serverPort);

//*-- IoT Information
char codeOK='0';//start Code is blank....

static const char HELLO_PAGE[] PROGMEM = R"(
{ "title": "Smart Garage ", "uri": "/", "menu": true, "element": [
    { "name": "caption", "type": "ACText", "value": "<h2>Your Smart Garage Updater!</h2>",  "style": "text-align:center;color:#2f4f4f;padding:10px;" },
    { "name": "content", "type": "ACText", "value": "Select menu button for options." } ]
}
)";

void setup() {
    ESP.wdtDisable();
    Serial.begin(115200);
    pinMode(openClosePin, OUTPUT);
    pinMode(statusPin, INPUT);
    digitalWrite(openClosePin, LOW);
    unsigned long startedAt = millis();
    delay(50);
 

  WiFi.printDiag(Serial); //Remove this line if you do not want to see WiFi password printed
  Serial.println("Opening configuration portal");
  
  //Local intialization. Once its business is done, there is no need to keep it around
 
  WiFiManager wifiManager;  
  //sets timeout in seconds until configuration portal gets turned off.
  //If not specified device will remain in configuration mode until
  //switched off via webserver.
  if (WiFi.SSID()!="") wifiManager.setConfigPortalTimeout(60); //If no access point name has been previously entered disable timeout.
 
  //it starts an access point 
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.startConfigPortal("ESP8266AP","passw0rd"))  //Delete these two parameters if you do not want a WiFi password on your configuration access point
  {
     Serial.println("Not connected to WiFi but continuing anyway.");
  } 
  else 
  {
     //if you get here you have connected to the WiFi
     Serial.println("connected...yay :)");
  }
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();
    //Print the IP Address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.print(":");
    Serial.print(serverPort,DEC);
    Serial.println("/");

httpUpdate.setup(&httpServer, USERNAME, USERPASS);
  hello.load(HELLO_PAGE);                                
  portal.join({ hello, update });                        
  if (portal.begin()) {                                  
    if (MDNS.begin("esp-webupdate"))                     
        MDNS.addService("http", "tcp", 80);              
    }
    
}

// send the state of the switch to the web browser
void GetSwitchState(WiFiClient cl) {
    if (digitalRead(statusPin) == 1) {
      cl.println("<p>Garage Door is <span style='background-color:#FF0000; font-size:18pt'>Open</span></p>");
    }
    else {
      cl.println("<p>Garage Door is <span style='background-color:#00FF00; font-size:18pt'>Closed</span></p>");
    }
  }
 
  void GetCode() {
      codeOK='1';
  }
 
  void DoorActivate() {
    digitalWrite(openClosePin, HIGH);
    delay(1000);
    digitalWrite(openClosePin, LOW);
    codeOK='0';
  }


void loop() {
  
  MDNS.update();            
  portal.handleClient();    
  
  // Check if a client has connected
  WiFiClient client = server.available();
 
  if (!client) {
    return;
  }

  Serial.println("found client");
 
  // Return the response
  boolean currentLineIsBlank = true;
  codeOK='0';
  while (client.connected()) {
    if (client.available()) {   // client data available to read
      char c = client.read(); // read 1 byte (character) from client
      HTTP_req += c;  // save the HTTP request 1 char at a time
      // last line of client request is blank and ends with \n
      // respond to client only after last line received
      if (c == '\n' && currentLineIsBlank) {
        client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive");
        client.println();
        if (HTTP_req.indexOf("ajax_switch") > -1) {
          // read switch state and send appropriate paragraph text
          GetSwitchState(client);
          delay(0);
        }
        else {  // HTTP request for web page
          // send web page - contains JavaScript with AJAX calls
          client.print("<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<title>IoT Garage Door</title>\r\n<meta name='viewport' content='width=device-width', initial-scale='1'>");
          client.print("<script>\r\nfunction GetSwitchState() {\r\nnocache = \"&nocache=\" + Math.random() * 1000000;\r\nvar request = new XMLHttpRequest();\r\nrequest.onreadystatechange = function() {\r\nif (this.readyState == 4) {\r\nif (this.status == 200) {\r\nif (this.responseText != null) {\r\ndocument.getElementById(\"switch_txt\").innerHTML = this.responseText;\r\n}}}}\r\nrequest.open(\"GET\", \"ajax_switch\" + nocache, true);\r\nrequest.send(null);\r\nsetTimeout('GetSwitchState()', 1000);\r\n}\r\n</script>\n");
          client.print("<script>\r\nfunction DoorActivate() {\r\nvar request = new XMLHttpRequest();\r\nrequest.open(\"GET\", \"door_activate\" + nocache, true);\r\nrequest.send(null);\r\n}\r\n</script>\n");
          client.print("</head>\r\n<body onload=\"GetSwitchState()\">\r\n<center><h1>"h1_ID" Smart Garage Door</h1><hr>\r\n<div id=\"switch_txt\">\r\n</div>\r\n<br>\n");
          client.print("Input password to control Garage Door.\r\n<br><br><form name=\"passcode\" onSubmit=\"GetCode()\"><input type=\"password\" name=\"password\" size='8' maxlength='4'>&nbsp;<input type=submit name=\"Submit\" value=\"Submit\" onClick=\"GetCode()\" style='height:22px; width:80px'></form><br><br>\n");
          if (HTTP_req.indexOf(pass_sent) > 0) {
            GetCode();
          }
          if (codeOK == '0') {
            client.print("<button type=\"button\" disabled style='height:50px; width:225px'>Activate the Door</button><br><br>\n");
          }
          if (codeOK == '1') {
            client.print("<button type=\"button\" onclick=\"DoorActivate()\" style='height:50px; width:225px'>Activate the Door</button><br><br>\n");
          }
          //client.println(system_get_free_heap_size());
          if (HTTP_req.indexOf("door_activate") > -1) {
            // read switch state and send appropriate paragraph text
            DoorActivate();
          }
          //}
          client.print("</body>\r\n</html>\n");
          delay(0);
        }
 
        // display received HTTP request on serial port
        Serial.println(HTTP_req);
        HTTP_req = "";            // finished with request, empty string
        break;
      }
      // every line of text received from the client ends with \r\n
      if (c == '\n') {
          // last character on line of received text
          // starting new line with next character read
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // a text character was received from client
          currentLineIsBlank = false;
        }
      } // end if (client.available())
  } // end while (client.connected())
  delay(1);      // give the web browser time to receive the data
  client.stop(); // close the connection
  delay(0);
}



