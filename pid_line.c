// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.h>

#define out1_pin 4
#define out2_pin 2
bool out1=0;
bool out2=0;

// Replace with your network credentials
const char* ssid = "ELEC302";
const char* password = "elec1234";

WebServer server;

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String out1_State = "off";
String out2_State = "off";

void setup() 
{
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(out1_pin, OUTPUT);
  pinMode(out2_pin, OUTPUT);
  // Set outputs to LOW
  digitalWrite(out1_pin, LOW);
  digitalWrite(out2_pin, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("");
  WiFi.begin(ssid,password);
  Serial.println("initailizing WiFi connection");                                   
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);  
  server.on("/1/on",on1); 
  server.on("/1/off",off1); 
  server.on("/2/on",on2); 
  server.on("/2/off",off2); 

  server.begin();
  Serial.println("HTTP server started");  
}

void handleRoot()
{
  server.send(200,"text/html",getHtmlPage());
}

String getHtmlPage()
{
            String strHtml = "<!DOCTYPE html><html>";
            strHtml += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
            strHtml += "<link rel=\"icon\" href=\"data:,\">";
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            strHtml += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
            strHtml += ".button { background-color: #555555; border: none; color: white; padding: 16px 40px;";
            strHtml += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
            strHtml += ".button2 {background-color: #4CAF50;}</style></head>";
            
            // Web Page Heading
            strHtml += "<body><h1>ESP32 Web Server</h1>";
            
            // Display current state, and ON/OFF buttons for out1
            strHtml += "<p>output1 - State " + out1_State + "</p>";
            // If the out1_State is off, it displays the ON button       
            if (out1_State=="off") 
            {
              strHtml += "<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>";
            } else 
            {
              strHtml += "<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>";
            } 
               
            // Display current state, and ON/OFF buttons for out2  
            strHtml += "<p>output2 - State " + out2_State + "</p>";
            // If the out2_State is off, it displays the ON button       
            if (out2_State=="off") {
              strHtml += "<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>";
            } else 
            {
              strHtml += "<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>";
            }
            strHtml += "</body></html>";

            return strHtml;
}


void loop()
{
 server.handleClient();
}

void on1()
{
  out1=1;
  digitalWrite(out1_pin,out1);
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
  out1_State="on";
  server.send(200, "text/html",getHtmlPage());
}

void on2()
{
  out2=1;
  digitalWrite(out2_pin,out2);
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
  out2_State="on";
  server.send(200, "text/html",getHtmlPage());
}

void off1()
{
  out1=0;
  digitalWrite(out1_pin,out1);
  Serial.print("out1: ");
  Serial.println(out1?"On":"Off");
  out1_State="off";
  server.send(200, "text/html",getHtmlPage());
}

void off2()
{
  out2=0;
  digitalWrite(out2_pin,out2);
  Serial.print("out2: ");
  Serial.println(out2?"On":"Off");
  out2_State="off";
  server.send(200, "text/html",getHtmlPage());
}
