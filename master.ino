#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Wire.h>

// Define DNS server port
#define DNS_PORT 53

// Define an IP address for the access point (AP)
IPAddress APIP(192, 168, 1, 1);

// Create instances of DNS server and web server
ESP8266WebServer webServer(80);

// Initialize an empty HTML page
String index_html;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Configure ESP8266 to work in AP (Access Point) mode
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.setSleep(false);

  // Define routes for the web server
  webServer.on("/", Index);
  webServer.on("/button_run", button_run);
  webServer.on("/post", recCommand);
  webServer.onNotFound(Index);

  // Start the web server
  webServer.begin();

  // Initialize the I2C communication
  Wire.begin();
}

// Function to handle the main web page
void Index() {
  String _html = "";

  _html = "<!DOCTYPE html><html><head>";
  _html += "<meta charset=\"UTF-8\">";
  _html += "<title>";
  _html += "</title>";
  _html += "<style>";
  _html += "</style>";
  _html += "</head>";
  _html += "<body>";
  _html += "<div id=\"networkBar\">";
  _html += "</div>";
  _html += "<div id=\"content\">";
  _html += "<h1 class='center'>OMG-duino</h1>";
  _html += "<p>Write down your command inside the text field</p>";
  _html += "<p>Press the run button to access the RUN menu on Windows</p>";
  _html += "<form action=\"/post\">";
  _html += "<input placeholder=\"Command\" name=\"command\" required>";
  _html += "<button type='submit'>Execute</button>";
  _html += "</form>";
  _html += "<a href=\"/button_run\"><button style=\"color: green;\">RUN</button></a>";
  _html += "</div>";
  _html += "</body></html>";

  // Send the HTML page as a response to the client
  webServer.send(200, "text/html", _html);
}

// Loop function
void loop() {
  // Process DNS requests
  dnsServer.processNextRequest();

  // Handle incoming client requests
  webServer.handleClient();
}

// Function to sanitize and process input string
String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200); // Limit the length of the input string
  return a;
}

// Function to send a string to an I2C-connected device
void I2C_string(String inputString) {
  int asciiArray[inputString.length()];

  // Convert the input string to an array of ASCII values
  for (int i = 0; i < inputString.length(); i++) {
    asciiArray[i] = inputString.charAt(i);
  }

  int arrayLength = sizeof(asciiArray) / sizeof(asciiArray[0]);

  // Begin an I2C transmission to device address 9
  Wire.beginTransmission(9);
  for (int i = 0; i < arrayLength; i++) {
    // Send each ASCII value over I2C
    Wire.write(asciiArray[i]);
  }
  // End the I2C transmission
  Wire.endTransmission();
}

// Function to simulate the "RUN" button press
void button_run() {
  // Send the "(run)" command to the I2C device
  I2C_string("(run)");

  // Redirect the client back to the main page
  webServer.sendHeader("Location", "/", true);
  webServer.send(302);
}

// Function to receive and process a command
void recCommand() {
  // Get the command from the input field
  String inputString = input("command");

  int asciiArray[inputString.length()];
  // Convert the input string to an array of ASCII values
  for (int i = 0; i < inputString.length(); i++) {
    asciiArray[i] = inputString.charAt(i);
  }

  int arrayLength = sizeof(asciiArray) / sizeof(asciiArray[0]);

  // Begin an I2C transmission to device address 9
  Wire.beginTransmission(9);
  for (int i = 0; i < arrayLength; i++) {
    // Send each ASCII value over I2C
    Wire.write(asciiArray[i]);
  }
  // End the I2C transmission
  Wire.endTransmission();

  // Redirect the client back to the main page
  webServer.sendHeader("Location", "/", true);
  webServer.send(302);
}
