#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "EEPROM.h"
//Wifi config
const char *ssid = "ASUS";
const char *password = "bidoeiradecima1A.";
//eeprom
#define EEPROM_SIZE 64
//flash eeprom store configs

///number 1
int addr = 0;
String number1="000000000000";
String number2="000000000000";
String number3="000000000000";
String number4="000000000000";
String number5="000000000000";

WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  String temp="";
temp+="<html xmlns='http://www.w3.org/1999/xhtml'>";
temp+="<head>";
temp+="<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>";
temp+="<title>Gateway</title>";
temp+="</head>";
temp+="<body id='main_body' >";
temp+="  <style>";
temp+=" body{background:#BAD7D4;font-family:'Lucida Grande', Tahoma, Arial, Verdana, sans-serif;font-size:small;margin:8px 0 16px;text-align:center;}";
temp+="#form_container{background:#fff;margin:0 auto;text-align:left;width:640px;}";
temp+="#footer{width:640px;clear:both;color:#999999;text-align:center;width:640px;padding-bottom: 15px;font-size: 85%;}#footer a{color:#999999;text-decoration: none;border-bottom: 1px dotted #999999;}";
temp+="#bottom{display:block;height:10px;margin:0 auto;width:650px;}form.appnitro{margin:20px 20px 0;padding:0 0 20px;}";
temp+=".appnitro li{width:61%;}form ul{font-size:100%;list-style-type:none;margin:0;padding:0;width:100%;}form li{display:block;margin:0;padding:4px 5px 2px 9px;position:relative;}form li:after{clear:both;content:'.';display:block;height:0;visibility:hidden;}";
temp+=".buttons:after{clear:both;content:'.';display:block;height:0;visibility:hidden;}.buttons{clear:both;display:block;margin-top:10px;}";
temp+="* html form li{height:1%;}* html .buttons{height:1%;}* html form li div{display:inline-block;}form li div{color:#444;margin:0 4px 0 0;padding:0 0 8px;}form li span{color:#444;float:left;margin:0 4px 0 0;padding:0 0 8px;}form li div.left{display:inline;float:left;width:48%;}";
temp+="form li div.right{display:inline;float:right;width:48%;}form li div.left .medium{width:100%;}form li div.right .medium{width:100%;}.clear{clear:both;}form li div label{clear:both;color:#444;display:block;font-size:9px;line-height:9px;margin:0;padding-top:3px;}";
temp+="input.button_text{overflow:visible;padding:0 7px;width:auto;}.buttons input{font-size:120%;margin-right:5px;}label.description{border:none;color:#222;display:block;font-size:95%;font-weight:700;line-height:150%;padding:0 0 1px;}input.text{background:#fff;border-bottom:1px solid #ddd;border-left:1px solid #c3c3c3;border-right:1px solid #c3c3c3;border-top:1px solid #7c7c7c;color:#333;font-size:100%;margin:0;padding:2px 0;}";
temp+="input.currency{text-align:right;}input.checkbox{display:block;height:13px;line-height:1.4em;margin:6px 0 0 3px;width:13px;}label.choice{color:#444;display:block;font-size:100%;line-height:1.4em;margin:-1.55em 0 0 25px;padding:4px 0 5px;width:90%;}input.medium{width:50%;}";
temp+=" </style>";
temp+=" <div id='form_container'>";
temp+="   <form class='appnitro'  method='post' action='/save'><div class='form_description'><center><h2>Gateway Configurations</h2></center>";
temp+="   </div><ul><br><label class='description'>SIM 1 Status </label><div><span>Status............</span>";
temp+="   </div><br><label class='description'>SIM 2 Status </label><div><span>Status............</span></div><hr>";
temp+="   <li  >";
temp+="   <label class='description' >Allowed Number 1 </label><div><input name='element_1' class='element text medium' type='text' maxlength='12' value='"+number1+"'/> ";
temp+="   </div></li><li ><label class='description' >Allowed Number 2 </label><div><input  name='element_2' class='element text medium' type='text' maxlength='12' value='"+number2+"'/> </div></li><li id='li_3' >";
temp+="   <label class='description' >Allowed Number 3 </label><div><input  name='element_3' class='element text medium' type='text' maxlength='12' value='"+number3+"'/></div> ";
temp+="   </li><li  ><label class='description' >Allowed Number 4 </label><div><input name='element_4' class='element text medium' type='text' maxlength='12' value='"+number4+"'/></div> ";
temp+="   </li><li  ><label class='description' >Allowed Number 5 </label>";
temp+="   <div><input name='element_5' class='element text medium' type='text' maxlength='12' value='"+number5+"'/> ";
temp+="   </div></li><li  ><label class='description' >Output 1 </label>";
temp+="   <span><input  name='element_8_1' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice'>Number 1</label><input  name='element_8_2' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 2</label><input  name='element_8_3' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 3</label><input name='element_8_4' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 4</label><input  name='element_8_5' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice'>Number 5</label></span> ";
temp+="   </li><li  ><label class='description' >Output 2 </label>";
temp+="   <span><input  name='element_9_1' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 1</label><input  name='element_9_2' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 2</label><input  name='element_9_3' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 3</label><input  name='element_9_4' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' >Number 4</label><input  name='element_9_5' class='element checkbox' type='checkbox' value='1' />";
temp+="<label class='choice' for='element_9_5'>Number 5</label></span> ";
temp+="   </li><li ><label class='description'>SIM Relay Timer (seconds) </label>";
temp+="   <div><input name='element_6' class='element text medium' type='number' max='10' value=''/> ";
temp+="   </div></li><li ><label class='description'>SIM Activation- Days </label>";
temp+="   <div><input name='element_6' class='element text medium' type='number' max='60' value=''/> ";
temp+="   </div></li><li ><label class='description' >SIM Activation Number </label><div>";
temp+="   <input name='element_7' class='element text medium' type='text' maxlength='255' value=''/> ";
temp+="   </div></li><li class='buttons'><input id='saveForm' class='button_text' type='submit' name='submit' value='Submit' />";
temp+="   </li></ul></form><div id='footer'>by <a href='https://github.com/jplajpla23'>JPLA</a></div></div></body></html>";
         
  server.send(200, "text/html", temp);
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
