#include "Arduino.h"

#include "aliyun.h"




void setup() {
  Serial.begin(115200); //��������
  Serial.println("Demo Start");
  wifiInit(); //����wifi
  mqttCheckConnect(); //����MQTT������
  pubMsg();
}

void loop() {
  client.loop(); //���ֿͻ��˵�����
}

