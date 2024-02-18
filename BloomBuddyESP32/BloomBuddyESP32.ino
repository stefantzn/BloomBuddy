#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define RXp2 16
#define TXp2 17

const char* ssid = "S iPhone";
const char* password = "password";
const char* apiKey = "-";
const char* chatgptEndpoint = "https://api.openai.com/v1/chat/completions";


WebServer server(80);

SoftwareSerial espSerial(RXp2, TXp2);

// Define variables to store sensor values
int moistureLevel = 0;
float humidity = 0.0;
float temperature = 0.0;
int lightValue = 0;
String chatGptPrompt = ""; // Store the ChatGPT prompt

void setup() {
  Serial.begin(115200);
  espSerial.begin(9600);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData); // New handler for /data endpoint
  server.on("/prompt", HTTP_GET, handlePrompt); // New handler for /prompt endpoint

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}


void loop() {
  if (espSerial.available() > 0) {
    // Read sensor data from Arduino
    String data = espSerial.readStringUntil('\n');
    // Parse received data
    moistureLevel = data.substring(1, data.indexOf('H')).toInt();
    humidity = data.substring(data.indexOf('H') + 1, data.indexOf('T')).toFloat();
    temperature = data.substring(data.indexOf('T') + 1, data.indexOf('L')).toFloat();
    lightValue = data.substring(data.indexOf('L') + 1).toInt();
  }

  server.handleClient();
}

void handleRoot() {
  // Generate HTML with dynamic content
  String dynamicHTML = "<!DOCTYPE html>\
<html>\
<head>\
<meta charset=\"UTF-8\">\
<title>Plant Companion</title>\
<style>\
body {\
  font-family: Arial, sans-serif;\
  background-color: #8DB255; /* Plant green background */\
  margin: 0;\
  padding: 0;\
  display: flex;\
  justify-content: center;\
  align-items: center;\
  height: 100vh;\
}\
.container {\
  background-color: #ffffff;\
  border-radius: 10px;\
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);\
  padding: 20px;\
  text-align: center;\
}\
h1 {\
  color: #333333;\
}\
p {\
  font-size: 21px; /* Font size for paragraphs */\
  color: #666666;\
}\
input[type='text'] {\
  width: 60%;\
  padding: 10px;\
  margin: 10px;\
  border: 1px solid #ccc;\
  border-radius: 4px;\
  box-sizing: border-box;\
}\
button {\
  background-color: #4CAF50;\
  color: white;\
  padding: 14px 20px;\
  margin: 10px;\
  border: none;\
  border-radius: 4px;\
  cursor: pointer;\
}\
button:hover {\
  background-color: #45a049;\
}\
.chatOutput {\
  background-color: #f9f9f9;\
  border: 1px solid #ccc;\
  border-radius: 4px;\
  padding: 10px;\
  margin-top: 20px; /* Adjust margin as needed */\
}\
.imageContainer {\
  margin-top: 20px; /* Adjust margin as needed */\
}\
.plantImage {\
  max-width: 60%; /* Ensure the image fits within its container */\
  height: auto; /* Maintain aspect ratio */\
}\
</style>\
</head>\
<body>\
<div class='container'>\
<div class='container'>\
  <div style='display: flex; align-items: center; justify-content: center;'>\
    <h1 style='margin-right: 10px;'>BloomBuddy</h1>\
    <img src='https://i.ibb.co/mXbx2j5/9eb635cffdf0f9a4a6153c9b8b0d888b-t.jpg' alt='Image' style='width: 50px; height: 50px;'>\
  </div>\
<div>\
<input type='text' id='userInput' placeholder='Enter your message'>\
<button onclick='sendMessage()'>Send</button>\
</div>\
<p class='chatOutput'>BloomBuddy: </p>\
<p class='moisture'>Moisture Level: </p>\
<p class='humidity'>Humidity: </p>\
<p class='temperature'>Temperature: </p>\
<p class='light'>Light Value: </p>\
<div class='imageContainer'>\
  <img class='plantImage' src='https://i.ibb.co/0yhK7MT/bonsai.png' alt='Plant Image'>\
</div>\
<script>\
function updateSensorReadings() {\
  var xhttp = new XMLHttpRequest();\
  xhttp.onreadystatechange = function() {\
    if (this.readyState == 4 && this.status == 200) {\
      var data = JSON.parse(this.responseText);\
      document.querySelector('.moisture').innerHTML = 'Moisture Level: ' + data.moistureLevel;\
      document.querySelector('.humidity').innerHTML = 'Humidity: ' + data.humidity + ' %';\
      document.querySelector('.temperature').innerHTML = 'Temperature: ' + data.temperature + '°C';\
      document.querySelector('.light').innerHTML = 'Light Value: ' + data.lightValue;\
    }\
  };\
  xhttp.open('GET', '/data', true);\
  xhttp.send();\
}\
function sendMessage() {\
  var userInput = document.getElementById('userInput').value;\
  var xhttp = new XMLHttpRequest();\
  xhttp.onreadystatechange = function() {\
    if (this.readyState == 4 && this.status == 200) {\
      var response = this.responseText;\
      document.querySelector('.chatOutput').innerHTML = 'BloomBuddy: <br><div style=\"background-color: #f9f9f9; border: 1px solid #ccc; border-radius: 4px; padding: 10px;\">' + response + '</div>';\
    }\
  };\
  xhttp.open('GET', '/prompt?userInput=' + userInput, true);\
  xhttp.send();\
}\
setInterval(updateSensorReadings, 1000);\
</script>\
</div>\
</body>\
</html>\
";

  server.send(200, "text/html", dynamicHTML);
}



void handleData() {
  // Generate JSON response with sensor data
  String jsonResponse = "{\"moistureLevel\": " + String(moistureLevel) + ", \"humidity\": " + String(humidity) + ", \"temperature\": " + String(temperature) + ", \"lightValue\": " + String(lightValue) + "}";
  server.send(200, "application/json", jsonResponse);
}

void handlePrompt() {
  String chatGptPrompt;
  String userInput = server.arg("userInput");
  String userMessage = "Pretend to be a animated character based on a plant that has a few different moods depending on the associated metrics of a plant: - If the temperature is less than 10 degrees, pretend to be a plant-based character that is feeling sad because it is cold outside. Otherwise, be a plant-based character that is feeling happy because it is warm.  - If the soil moisture is between 0-300, be a plant that is dry and needs water. If the soil moisture is between 300-700, be a plant that is sufficiently watered and satisfied. If the soil moisture is above 700, be a plant that has to much water and could be potentially drowning in water.  - If the sunlight level is less than 90, be a plant that needs sunlight. Otherwise pretend to be a plant that is happy because it has plenty of sunlight.  Here are the associated metrics of the plant: - Temperature: " + String(temperature) + "  - Soil Moisture: " + String(moistureLevel) + " - Sunlight: " + String(lightValue) +  "Consider all metrics when acting as the animated plant-based character and converse with the user when they talk with you. Heres the user talking: " + String(userInput);


  DynamicJsonDocument payload(1024);
  payload["model"] = "gpt-3.5-turbo";
  
  JsonArray messages = payload.createNestedArray("messages");
  
  JsonObject systemMessage = messages.createNestedObject();
  systemMessage["role"] = "system";
  systemMessage["content"] = "You are a helpful assistant.";
  
  JsonObject userMessageObject = messages.createNestedObject();
  userMessageObject["role"] = "user";
  userMessageObject["content"] = userMessage;

  // Serialize the JSON payload
  String payloadStr;
  serializeJson(payload, payloadStr);

  // Send the request to the OpenAI API
  HTTPClient http;
  http.begin("https://api.openai.com/v1/chat/completions");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(apiKey));
  
  int httpResponseCode = http.POST(payloadStr);
  
  if (httpResponseCode == 429) {
    Serial.println("Rate limit exceeded. Waiting before retrying...");
    delay(60000); // Wait for a minute before retrying
    handlePrompt(); // Retry the request
  } else if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("API Response:");
    Serial.println(response);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    // Extract the chat prompt from the JSON
    const char* prompt = doc["choices"][0]["message"]["content"];
    chatGptPrompt = prompt;
  } else {
    Serial.println("HTTP Error: " + String(httpResponseCode));
  }

  http.end();

  // Send the ChatGPT prompt as response
  server.send(200, "text/plain", chatGptPrompt);
}