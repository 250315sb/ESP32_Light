#include "Arduino.h"
#include "WiFi.h"
#include "PubSubClient.h"

/* ��������WIFI SSID������ */
#define WIFI_SSID         "Redmi K60"
#define WIFI_PASSWD       "201910088047"
 
/* ���ϻ��������Ͷ˿ں� */
#define MQTT_SERVER       "�������"
#define MQTT_PORT         1883//�˿ں�
#define MQTT_USRNAME      "���username"
#define CLIENT_ID         "���clientId"
#define MQTT_PASSWD       "���password"
 
//������Ϣ�õ�topic
#define PubTopic "���topic"


//wifi��ʼ��
void wifiInit()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WiFi not Connect");
  }
 
  Serial.println("Connected to AP");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  Serial.print("espClient [");
 

}

void setup()
{
/* initialize serial for debugging */
    Serial.begin(115200); //��������
    Serial.println("Demo Start");
    wifiInit();//����wifi

}
 
// the loop function runs over and over again forever
void loop()
{
  delay(1000);
}

