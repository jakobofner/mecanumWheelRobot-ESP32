#include "BluetoothSerial.h"
#include <ArduinoJson.h>
#include "pwmConf.h"
#include "pinConf.h"



BluetoothSerial SerialBT;

const unsigned int MAX_MESSAGE_LENGTH = 12;

void pharseJSON(String json);

void setup()
{  
  SerialBT.begin("mecanumWheelRobot"); //Name des ESP32
  /* Initialize Serial Port */
  Serial.begin(115200);
  
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
  pinMode(dir3Pin, OUTPUT);
  pinMode(dir4Pin, OUTPUT);

  pinMode(en1Pin, OUTPUT);
  pinMode(en2Pin, OUTPUT);
  pinMode(en3Pin, OUTPUT);
  pinMode(en4Pin, OUTPUT); 
}
void loop()
{
  delay(1000);
  while(1){

    if (SerialBT.available()) {
      String json = SerialBT.readStringUntil('?');
      pharseJSON(json);
    }
  }
}

void pharseJSON(String json){

  if(json.length() < 100){
    return;
  }
  Serial.println(json);
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    //Serial.print(F("deserializeJson() failed: "));
    //Serial.println(error.f_str());
    Serial.println("error");
    return;
  }else{
    Serial.println("ok");
  }

  JsonObject obj = doc.as<JsonObject>();

  int values[28] = {  pwm1Pin,    pwm1Channel,    dir1Pin,    en1Pin,     obj["speedLF"].as<String>().toInt(),   obj["dirLF"].as<String>().toInt(),   obj["enLF"].as<String>().toInt(),
                      pwm2Pin,    pwm2Channel,    dir2Pin,    en2Pin,     obj["speedLB"].as<String>().toInt(),   obj["dirLB"].as<String>().toInt(),   obj["enLB"].as<String>().toInt(),
                      pwm3Pin,    pwm3Channel,    dir3Pin,    en3Pin,     obj["speedRF"].as<String>().toInt(),   obj["dirRF"].as<String>().toInt(),   obj["enRF"].as<String>().toInt(),
                      pwm4Pin,    pwm4Channel,    dir4Pin,    en4Pin,     obj["speedRB"].as<String>().toInt(),   obj["dirRB"].as<String>().toInt(),   obj["enRB"].as<String>().toInt()};

  for(int i = 0; i < 28; i+=7){
    /* Set PWM Output of Channel with desired dutycycle */ 
      ledcSetup(values[i+1], values[i+4], pwm_Resolution);
      ledcAttachPin(values[i], values[i+1]);
      ledcWrite(values[1+i], 128);
      
      if(values[6+i] == 1){
        digitalWrite(values[3+i],HIGH);
      }else{
        digitalWrite(values[3+i],LOW);
      }

      if(values[i+5] == 0){
        digitalWrite(values[i+2],LOW);
      }else{
        digitalWrite(values[i+2],HIGH);
      }
  }

  return;

}

