#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <EEPROM.h>


// EEPROM
#define EEPROM_SIZE 100
#define addrNumber1 0
#define addrNumber2 13
#define addrNumber3 26
#define addrNumber4 39
#define addrNumber5 52
#define addrper1A 70
#define addrper1B 71
#define addrper2A 72
#define addrper2B 73
#define addrper3A 74
#define addrper3B 75
#define addrper4A 76
#define addrper4B 77
#define addrper5A 78
#define addrper5B 79
#define addrONTIME 80
#define addrKeepAlive 81
#define addrNumberKeepAlive 82

//SERVER CONFIGS

#define SERVER_PORT 80

//Wifi config
const char *ssid = "Your SSID";
const char *password = "YourPassword";

//SIMG NUMBERS CONFIG
#define MAXNUMBERSIZE 12
//numbers size
int SZnumberKeepAlive = 0;
int SZnumber1 = 0;
int SZnumber2 = 0;
int SZnumber3 = 0;
int SZnumber4 = 0;
int SZnumber5 = 0;
//numbers
int numberKeepAlive[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int number1[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int number2[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int number3[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int number4[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int number5[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

//permitions

bool  per1A = false;
bool  per1B = false;
bool  per2A = false;
bool  per2B = false;
bool  per3A = false;
bool  per3B = false;
bool  per4A = false;
bool  per4B = false;
bool  per5A = false;
bool  per5B = false;

// on timer relays
int onTimer = 0;

//keep alive interval
int keepInterval = 0;

//webserver
WebServer server(SERVER_PORT);


String getCSS() {
  String temp = "";
  temp += "  <style>";
  temp += " body{background:#BAD7D4;font-family:'Lucida Grande', Tahoma, Arial, Verdana, sans-serif;font-size:small;margin:8px 0 16px;text-align:center;}";
  temp += "#form_container{background:#fff;margin:0 auto;text-align:left;width:640px;}";
  temp += "#footer{width:640px;clear:both;color:#999999;text-align:center;width:640px;padding-bottom: 15px;font-size: 85%;}#footer a{color:#999999;text-decoration: none;border-bottom: 1px dotted #999999;}";
  temp += "#bottom{display:block;height:10px;margin:0 auto;width:650px;}form.appnitro{margin:20px 20px 0;padding:0 0 20px;}";
  temp += ".appnitro li{width:61%;}form ul{font-size:100%;list-style-type:none;margin:0;padding:0;width:100%;}form li{display:block;margin:0;padding:4px 5px 2px 9px;position:relative;}form li:after{clear:both;content:'.';display:block;height:0;visibility:hidden;}";
  temp += ".buttons:after{clear:both;content:'.';display:block;height:0;visibility:hidden;}.buttons{clear:both;display:block;margin-top:10px;}";
  temp += "* html form li{height:1%;}* html .buttons{height:1%;}* html form li div{display:inline-block;}form li div{color:#444;margin:0 4px 0 0;padding:0 0 8px;}form li span{color:#444;float:left;margin:0 4px 0 0;padding:0 0 8px;}form li div.left{display:inline;float:left;width:48%;}";
  temp += "form li div.right{display:inline;float:right;width:48%;}form li div.left .medium{width:100%;}form li div.right .medium{width:100%;}.clear{clear:both;}form li div label{clear:both;color:#444;display:block;font-size:9px;line-height:9px;margin:0;padding-top:3px;}";
  temp += "input.button_text{overflow:visible;padding:0 7px;width:auto;}.buttons input{font-size:120%;margin-right:5px;}label.description{border:none;color:#222;display:block;font-size:95%;font-weight:700;line-height:150%;padding:0 0 1px;}input.text{background:#fff;border-bottom:1px solid #ddd;border-left:1px solid #c3c3c3;border-right:1px solid #c3c3c3;border-top:1px solid #7c7c7c;color:#333;font-size:100%;margin:0;padding:2px 0;}";
  temp += "input.currency{text-align:right;}input.checkbox{display:block;height:13px;line-height:1.4em;margin:6px 0 0 3px;width:13px;}label.choice{color:#444;display:block;font-size:100%;line-height:1.4em;margin:-1.55em 0 0 25px;padding:4px 0 5px;width:90%;}input.medium{width:50%;}";
  temp += " </style>";
  return temp;
}
String GetHTMLSaving() {
  String temp = "";
  temp += "<html xmlns='http://www.w3.org/1999/xhtml'>";
  temp += "<head>";
  temp += "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>";
  temp += "<title>Gateway</title>";
  temp += "</head>";
  temp += "<body id='main_body' >";
  temp += getCSS();
  temp += " <div id='form_container'>";
  temp += "   <form class='appnitro'  method='post' action='/save'><div class='form_description'><center><h2><br>Saving ....</h2></center>";
  temp += "   </div><br></form><div id='footer'>by <a href='https://github.com/jplajpla23'>JPLA</a></div></div><script>setTimeout(function(){ window.location.href=window.location.origin; }, 3000);</script>";
  temp += "</body></html>";

  return temp;
}
void handleRoot() {
  String temp = "";
  temp += "<html xmlns='http://www.w3.org/1999/xhtml'>";
  temp += "<head>";
  temp += "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>";
  temp += "<title>Gateway</title>";
  temp += "</head>";
  temp += "<body id='main_body' >";
  temp += getCSS();
  temp += " <div id='form_container'>";
  temp += "   <form class='appnitro'  method='post' action='/save'><div class='form_description'><center><h2><br>Gateway Configurations</h2></center>";
  temp += "   </div><ul><br><label class='description'>SIM 1 Status </label><div><span>" + getStatusSIM1() + "</span>";
  temp += "   </div><br><label class='description'>SIM 2 Status </label><div><span>" + getStatusSIM1() + "</span></div><hr>";
  temp += "   <li  >";
  temp += "   <label class='description' >Allowed Number 1 </label><div><input name='element_1' class='element text medium' type='text' maxlength='12' onkeypress='onlynumberkeyPress(event)' value='" + getNumber1AsSTR() + "'/> ";
  temp += "   </div></li><li ><label class='description' >Allowed Number 2 </label><div><input  name='element_2' class='element text medium' type='text' onkeypress='onlynumberkeyPress(event)'maxlength='12' value='" + getNumber2AsSTR() + "'/> </div></li><li id='li_3' >";
  temp += "   <label class='description' >Allowed Number 3 </label><div><input  name='element_3' class='element text medium' type='text' maxlength='12' onkeypress='onlynumberkeyPress(event)' value='" + getNumber3AsSTR() + "'/></div> ";
  temp += "   </li><li  ><label class='description' >Allowed Number 4 </label><div><input name='element_4' class='element text medium' type='text' onkeypress='onlynumberkeyPress(event)'  maxlength='12' value='" + getNumber4AsSTR() + "'/></div> ";
  temp += "   </li><li  ><label class='description' >Allowed Number 5 </label>";
  temp += "   <div><input name='element_5' class='element text medium' type='text' maxlength='12' onkeypress='onlynumberkeyPress(event)' value='" + getNumber5AsSTR() + "'/> ";
  temp += "   </div></li><hr><li  ><label class='description' >Relay 1 </label>";
  temp += "   <span><input  name='element_8_1' class='element checkbox' type='checkbox' value='1' " + getState1A() + "/>";
  temp += "<label class='choice'>Number 1</label><input  name='element_8_2' class='element checkbox' type='checkbox' value='1' " + getState2A() + "/>";
  temp += "<label class='choice' >Number 2</label><input  name='element_8_3' class='element checkbox' type='checkbox' value='1' " + getState3A() + "/>";
  temp += "<label class='choice' >Number 3</label><input name='element_8_4' class='element checkbox' type='checkbox' value='1' " + getState4A() + "/>";
  temp += "<label class='choice' >Number 4</label><input  name='element_8_5' class='element checkbox' type='checkbox' value='1' " + getState5A() + "/>";
  temp += "<label class='choice'>Number 5</label></span> ";
  temp += "   </li><li  ><label class='description' >Relay 2 </label>";
  temp += "   <span><input  name='element_9_1' class='element checkbox' type='checkbox' value='1' " + getState1B() + "/>";
  temp += "<label class='choice' >Number 1</label><input  name='element_9_2' class='element checkbox' type='checkbox' value='1' " + getState2B() + "/>";
  temp += "<label class='choice' >Number 2</label><input  name='element_9_3' class='element checkbox' type='checkbox' value='1' " + getState3B() + "/>";
  temp += "<label class='choice' >Number 3</label><input  name='element_9_4' class='element checkbox' type='checkbox' value='1' " + getState4B() + "/>";
  temp += "<label class='choice' >Number 4</label><input  name='element_9_5' class='element checkbox' type='checkbox' value='1' " + getState5B() + "/>";
  temp += "<label class='choice' for='element_9_5'>Number 5</label></span> ";
  temp += "   </li><li ><label class='description'>Relay ON Timer (miliseconds)<br> <small>This value will be multiplied by 4 (Eg: 255*4=1020ms )</small></label>";
  temp += "   <div><input name='element_6' class='element text medium' type='number' max='255' min='1' value='" + IntasString(onTimer) + "'/> ";
  temp += "   </div></li><hr><li ><label class='description'>SIM Keep Alive Activation - Days </label>";
  temp += "   <div><input name='element_10' class='element text medium' type='number' max='60' value='" + IntasString(keepInterval) + "'/> ";
  temp += "   </div></li><li ><label class='description' >SIM Activation Number </label><div>";
  temp += "   <input name='element_7' class='element text medium' type='text' maxlength='12' onkeypress='onlynumberkeyPress(event)' value='" + getNumberKeepAsSTR() + "'/> ";
  temp += "   </div></li><li class='buttons'><input id='saveForm' class='button_text' type='submit' name='submit' value='Save' />";
  temp += "   </li></ul></form><div id='footer'>by <a href='https://github.com/jplajpla23'>JPLA</a></div></div>";
  temp += "<script>function onlynumberkeyPress(event){if(!isTelNumber(event.key)){event.preventDefault();}}";
  temp += " function isTelNumber(s){switch(s){case '1': case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':return true;default:return false;}return false;}";
  temp += "</script></body></html>";

  server.send(200, "text/html", temp);

}

String getStatusSIM1() {
  return "Unknown";
}
String getStatusSIM2() {
  return "Unknown";
}
String IntasString(int val) {
  return String(val);
}


String getState1A() {
  if (per1A) {
    return " checked ";
  }
  return "";
}
String getState1B() {
  if (per1B) {
    return " checked ";
  }
  return "";
}

String getState2A() {
  if (per2A) {
    return " checked ";
  }
  return "";
}
String getState2B() {
  if (per2B) {
    return " checked ";
  }
  return "";
}

String getState3A() {
  if (per3A) {
    return " checked ";
  }
  return "";
}
String getState3B() {
  if (per3B) {
    return " checked ";
  }
  return "";
}

String getState4A() {
  if (per4A) {
    return " checked ";
  }
  return "";
}
String getState4B() {
  if (per4B) {
    return " checked ";
  }
  return "";
}

String getState5A() {
  if (per5A) {
    return " checked ";
  }
  return "";
}
String getState5B() {
  if (per5B) {
    return " checked ";
  }
  return "";
}

String getNumberKeepAsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumberKeepAlive ; i++) {
    out += numberKeepAlive[i];
  }
  return out;
}

String getNumber1AsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumber1 ; i++) {
    out += number1[i];
  }
  return out;
}

String getNumber2AsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumber2 ; i++) {
    out += number2[i];
  }
  return out;
}
String getNumber3AsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumber3 ; i++) {
    out += number3[i];
  }
  return out;
}
String getNumber4AsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumber4 ; i++) {
    out += number4[i];
  }
  return out;
}
String getNumber5AsSTR() {
  String out = "";
  for (int i = 0 ; i < SZnumber5 ; i++) {
    out += number5[i];
  }
  return out;
}
void handleSave() {
  if (server.args() == 0) {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    server.send(404, "text/plain", message);
    return;
  }
  String message = "";
  //clear all permitions
  per1A = false;
  per1B = false;
  per2A = false;
  per2B = false;
  per3A = false;
  per3B = false;
  per4A = false;
  per4B = false;
  per5A = false;
  per5B = false;
  for (uint8_t i = 0; i < server.args(); i++) {
    processArgument(server.argName(i), server.arg(i));
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  //save to flash
  StoreToFlash();
  //saving
  server.send(200, "text/html", GetHTMLSaving());

}
void StoreToFlash() {
  //store numbers
  //1
  EEPROM.write(addrNumber1, SZnumber1); //store size
  for (int i = 0 ; i < SZnumber1 ; i++)
  {
    EEPROM.write( addrNumber1 + 1 + i, number1[i]);
  }
  //2
  EEPROM.write(addrNumber2, SZnumber2); //store size
  for (int i = 0 ; i < SZnumber2 ; i++)
  {
    EEPROM.write( addrNumber2 + 1 + i, number2[i]);
  }
  //3
  EEPROM.write(addrNumber3, SZnumber3); //store size
  for (int i = 0 ; i < SZnumber3 ; i++)
  {
    EEPROM.write( addrNumber3 + 1 + i, number3[i]);
  }
  //4
  EEPROM.write(addrNumber4, SZnumber4); //store size
  for (int i = 0 ; i < SZnumber4 ; i++)
  {
    EEPROM.write( addrNumber4 + 1 + i, number4[i]);
  }
   //5
  EEPROM.write(addrNumber5, SZnumber5); //store size
  for (int i = 0 ; i < SZnumber5 ; i++)
  {
    EEPROM.write( addrNumber5 + 1 + i, number5[i]);
  }
  //store permitions

  EEPROM.write(addrper1A, per1A);
  EEPROM.write(addrper2A, per2A);
  EEPROM.write(addrper3A, per3A);
  EEPROM.write(addrper4A, per4A);
  EEPROM.write(addrper5A, per5A);
  EEPROM.write(addrper1B, per1B);
  EEPROM.write(addrper2B, per2B);
  EEPROM.write(addrper3B, per3B);
  EEPROM.write(addrper4B, per4B);
  EEPROM.write(addrper5B, per5B);
  //store timer
  EEPROM.write(addrONTIME, onTimer);
  //store sim config
  EEPROM.write(addrKeepAlive, keepInterval);
  //styore keep alive number
   //keep alive number
  EEPROM.write(addrNumberKeepAlive, SZnumberKeepAlive); //store size
  for (int i = 0 ; i < SZnumberKeepAlive ; i++)
  {
    EEPROM.write( addrNumberKeepAlive + 1 + i, numberKeepAlive[i]);
  }
  //save
  EEPROM.commit();

}

void processArgument(String nm, String val) {
  if (nm == "element_8_1") {
    if (val.toInt() == 1) {
      per1A = true;
    } else {
      per1A = false;
    }
    return;
  }
  if (nm == "element_8_2") {
    if (val.toInt() == 1) {
      per2A = true;
    } else {
      per2A = false;
    }
    return;
  }
  if (nm == "element_8_3") {
    if (val.toInt() == 1) {
      per3A = true;
    } else {
      per3A = false;
    }
    return;
  }
  if (nm == "element_8_4") {
    if (val.toInt() == 1) {
      per4A = true;
    } else {
      per4A = false;
    }
    return;
  }
  if (nm == "element_8_5") {
    if (val.toInt() == 1) {
      per5A = true;
    } else {
      per5A = false;
    }
    return;
  }
  if (nm == "element_9_1") {
    if (val.toInt() == 1) {
      per1B = true;
    } else {
      per1B = false;
    }
    return;
  }
  if (nm == "element_9_2") {
    if (val.toInt() == 1) {
      per2B = true;
    } else {
      per2B = false;
    }
    return;
  }
  if (nm == "element_9_3") {
    if (val.toInt() == 1) {
      per3B = true;
    } else {
      per3B = false;
    }
    return;
  }
  if (nm == "element_9_4") {
    if (val.toInt() == 1) {
      per4B = true;
    } else {
      per4B = false;
    }
    return;
  }
  if (nm == "element_9_5") {
    if (val.toInt() == 1) {
      per5B = true;
    } else {
      per5B = false;
    }
    return;
  }
  if (nm == "element_1") {
    //allowed number 1
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        number1[a] = 255; //clear
      }
      SZnumber1 = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        number1[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumber1 = sz;
    }

    return;
  }

  if (nm == "element_2") {
    //aloowed number 2
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        number2[a] = 255; //clear
      }
      SZnumber2 = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        number2[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumber2 = sz;
    }
    return;
  }
  if (nm == "element_3") {
    //aloowed number 3
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        number3[a] = 255; //clear
      }
      SZnumber3 = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        number3[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumber3 = sz;
    }
    return;
  }
  if (nm == "element_4") {
    //aloowed number 4
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        number4[a] = 255; //clear
      }
      SZnumber4 = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        number4[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumber4 = sz;
    }
    return;
  }
  if (nm == "element_5") {
    //aloowed number 5
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        number5[a] = 255; //clear
      }
      SZnumber5 = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        number5[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumber5 = sz;
    }
    return;
  }
  if (nm == "element_6") {

    int intval = val.toInt();
    if (intval > 255) {
      intval = 255;
    }
    if (intval < 0) {
      intval = 0;
    }
    onTimer = intval;
    return;
  }
  if (nm == "element_10") {

    int intval = val.toInt();
    if (intval > 60) {
      intval = 60;
    }
    if (intval < 0) {
      intval = 0;
    }
    keepInterval = intval; //save in miliseconds
    return;
  }

  if (nm == "element_7") {
    //keep alive number
    if (val.length() == 0) {
      for (int a = 0; a < 12; a++) {
        numberKeepAlive[a] = 255; //clear
      }
      SZnumberKeepAlive = 0;
    } else {
      int sz = val.length();
      if (sz > 12) {
        sz = 12;
      }
      for (int a = 0; a < sz; a++) {
        numberKeepAlive[a] = ((int)val[a]) - 48; //get assci decimal value from char and substract 48 to get int value
      }
      SZnumberKeepAlive = sz;
    }
    return;
  }
}
void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  server.send(404, "text/plain", message);

}


void setup(void) {
  //init EEprom
  EEPROM.begin(EEPROM_SIZE);
  //init serial
  Serial.begin(115200);
  //Init wifi
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

  //WEBSERVER Endpoints

  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");



  /*Load COonfigs*/
  Serial.println("LOAD CONFIGS");
  //load allowed numbers
  loadNumbers();
  //loads permitions
  loadPermitions();
  //load Relay config
  loadRelayConfigs();
  //load sim activations settings
  loadSimConfigs();
  //set status GSM

}
void loadRelayConfigs() {
  /*addrONTIME*/
  int v = EEPROM.read(addrONTIME);
  onTimer = v;
}
void loadSimConfigs() {
  int v = EEPROM.read(addrKeepAlive);
  if (v > 60) {
    keepInterval = 60;
  } else {
    keepInterval = v ;
  }
  //load kepp alive number(82)
  for (int a = 0; a < 12; a++) {
    numberKeepAlive[a] = 255; //clear

  }
  SZnumberKeepAlive = 0;
  int sz = EEPROM.read(addrNumberKeepAlive); //size of 1st number

  if (sz == 255) {
    sz = 0;
  }
  else {
    if (sz > 12) {
      sz = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumberKeepAlive = sz;
  int j = 0;
  for (int i = ((addrNumberKeepAlive) + 1) ; i < (addrNumberKeepAlive + SZnumberKeepAlive + 1) ; i++) //read 1st number
  {

    numberKeepAlive[j] = EEPROM.read(i); //append to array

    if (numberKeepAlive[j] > 9) {
      numberKeepAlive[j] = 255;
    }
    j++;
  }
}
void loadPermitions() {
  //1
  int pa = EEPROM.read(addrper1A);
  if (pa == 1) {
    per1A = true;
  } else {
    per1A = false;
  }
  int pb = EEPROM.read(addrper1B);
  if (pb == 1) {
    per1B = true;
  } else {
    per1B = false;
  }
  //2
  int ppa = EEPROM.read(addrper2A);
  if (ppa == 1) {
    per2A = true;
  } else {
    per2A = false;
  }
  int ppb = EEPROM.read(addrper2B);
  if (ppb == 1) {
    per2B = true;
  } else {
    per2B = false;
  }
  //3
  int pppa = EEPROM.read(addrper3A);
  if (pppa == 1) {
    per3A = true;
  } else {
    per3A = false;
  }
  int pppb = EEPROM.read(addrper3B);
  if (pppb == 1) {
    per3B = true;
  } else {
    per3B = false;
  }
  //4
  int ppppa = EEPROM.read(addrper4A);
  if (ppppa == 1) {
    per4A = true;
  } else {
    per4A = false;
  }
  int ppppb = EEPROM.read(addrper4B);
  if (ppppb == 1) {
    per4B = true;
  } else {
    per4B = false;
  }
  //5
  int pppppa = EEPROM.read(addrper5A);
  if (pppppa == 1) {
    per5A = true;
  } else {
    per5A = false;
  }
  int pppppb = EEPROM.read(addrper5B);
  if (pppppb == 1) {
    per5B = true;
  } else {
    per5B = false;
  }
}
void loadNumbers() {
  for (int a = 0; a < 12; a++) {
    number1[a] = 255; //clear
    number2[a] = 255; //clear
    number3[a] = 255; //clear
    number4[a] = 255; //clear
    number5[a] = 255; //clear
  }
  SZnumber1 = 0;
  SZnumber2 = 0;
  SZnumber3 = 0;
  SZnumber4 = 0;
  SZnumber5 = 0;

  //1st number

  int sz1 = EEPROM.read(addrNumber1); //size of 1st number

  if (sz1 == 255) {
    sz1 = 0;
  }
  else {
    if (sz1 > 12) {
      sz1 = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumber1 = sz1;
  int j = 0;
  for (int i = ((addrNumber1) + 1) ; i < (addrNumber1 + sz1 + 1) ; i++) //read 1st number
  {

    number1[j] = EEPROM.read(i); //append to array

    if (number1[j] > 9) {
      number1[j] = 255;
    }
    j++;
  }


  Serial.print(".");

  delay(100);//smmall delay

  //2nd number

  int sz2 = EEPROM.read(addrNumber2); //size of 1st number


  if (sz2 == 255) {
    sz2 = 0;
  }
  else {
    if (sz2 > 12) {
      sz2 = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumber2 = sz2;
  int jj = 0;
  for (int i = ((addrNumber2) + 1) ; i < (addrNumber2 + sz2 + 1) ; i++) //read 1st number
  {

    number2[jj] = EEPROM.read(i); //append to array

    if (number2[jj] > 9) {
      number2[jj] = 255;
    }
    jj++;
  }


  Serial.print(".");

  delay(100);//smmall delay

  //3 number

  int sz3 = EEPROM.read(addrNumber3); //size of 1st number


  if (sz3 == 255) {
    sz3 = 0;
  }
  else {
    if (sz3 > 12) {
      sz3 = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumber3 = sz3;
  int jjj = 0;
  for (int i = ((addrNumber3) + 1) ; i < (addrNumber3 + sz3 + 1) ; i++) //read 1st number
  {

    number3[jjj] = EEPROM.read(i); //append to array

    if (number3[jjj] > 9) {
      number3[jjj] = 255;
    }
    jjj++;
  }


  Serial.print(".");

  delay(100);//smmall delay

  //4 number

  int sz4 = EEPROM.read(addrNumber4); //size of 1st number


  if (sz4 == 255) {
    sz4 = 0;
  }
  else {
    if (sz4 > 12) {
      sz4 = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumber4 = sz4;
  int jjjj = 0;
  for (int i = ((addrNumber4) + 1) ; i < (addrNumber4 + sz4 + 1) ; i++) //read 1st number
  {

    number4[jjjj] = EEPROM.read(i); //append to array

    if (number4[jjjj] > 9) {
      number4[jjjj] = 255;
    }
    jjjj++;
  }


  Serial.print(".");

  delay(100);//smmall delay
  //5 number

  int sz5 = EEPROM.read(addrNumber5); //size of 1st number


  if (sz5 == 255) {
    sz5 = 0;
  }
  else {
    if (sz5 > 12) {
      sz5 = 12; //only alowed number wiht max 12 digits
    }
  }
  SZnumber5 = sz5;
  int jjjjj = 0;
  for (int i = ((addrNumber5) + 1) ; i < (addrNumber5 + sz5 + 1) ; i++) //read 1st number
  {

    number5[jjjjj] = EEPROM.read(i); //append to array

    if (number5[jjjjj] > 9) {
      number5[jjjjj] = 255;
    }
    jjjjj++;
  }


  Serial.print(".");

  delay(100);//smmall delay
}
void loop(void) {
  server.handleClient();
}
