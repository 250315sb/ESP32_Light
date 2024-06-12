#include "Arduino.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include <ArduinoJson.h> // ����ArduinoJson��

/* ��������WIFI SSID������ */
#define WIFI_SSID         "Redmi K60"
#define WIFI_PASSWD       "201910088047"

/* ���ϻ��������Ͷ˿ں� */
#define MQTT_SERVER       "iot-06z00faz7aul5a6.mqtt.iothub.aliyuncs.com"
#define MQTT_PORT         1883 //�˿ں�
#define MQTT_USERNAME     "MingTong&hyldTvgtqaQ"
#define CLIENT_ID         "hyldTvgtqaQ.MingTong|securemode=2,signmethod=hmacsha256,timestamp=1718180470466|"
#define MQTT_PASSWORD     "04842f2fdf439644cf6ade713edb14b62ede8d4a74ca895ab8058686d4987536"

//������Ϣ�õ�topic
#define PubTopic "/sys/hyldTvgtqaQ/MingTong/thing/event/property/post"
#define SubTopic "/sys/hyldTvgtqaQ/MingTong/thing/service/property/set"
WiFiClient espClient;
PubSubClient client(espClient);


//����һ���ַ�������Ϣ
void pubMsg() {
  // ����һ���㹻���StaticJsonDocument�������洢Ԥ�ڵ�JSON����
  StaticJsonDocument<256> doc;

  // ����JSON����
  doc["id"] = "123";
  doc["version"] = "1.0";
  doc["sys"]["ack"] = 0;
  doc["params"]["lcon"] = 120;
  doc["method"] = "thing.event.property.post";

  // ���л�JSON����Ϊ�ַ���
  char jsonOutput[256];
  serializeJson(doc, jsonOutput);

  // ʹ���޸ĺ��pubMsg��������JSON�ַ���
  if (client.publish(PubTopic, jsonOutput)) {
    Serial.println("Publish success");
    // ���ӳɹ���������
    client.subscribe(SubTopic);
  } else {
    Serial.println("Publish fail");
  }
}


void processJsonMessage(char* message) {
  StaticJsonDocument<256> doc; // ������С����Ӧ������Ҫ
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // ��JSON����ȡ��Ϣ
  const char* method = doc["method"]; // "thing.service.property.set"
  const char* id = doc["id"]; // "248166957"
  int PowerSwitch_1 = doc["params"]["PowerSwitch_1"]; // 1 or 0
  const char* version = doc["version"]; // "1.0.0"

  Serial.print("Method: ");
  Serial.println(method);
  Serial.print("ID: ");
  Serial.println(id);
  Serial.print("PowerSwitch_1: ");
  Serial.println(PowerSwitch_1);
  Serial.print("Version: ");
  Serial.println(version);

  // ����PowerSwitch_1��ִֵ�в���
  if (PowerSwitch_1 == 1) {
    // ���PowerSwitch_1Ϊ1��ִ����Ӧ����
    //digitalWrite(LED_PIN, HIGH); // ʾ������LED
    Serial.println("LED turned ON");
  } else {
    // ���PowerSwitch_1Ϊ0��ִ����Ӧ����
    //digitalWrite(LED_PIN, LOW); // ʾ�����ر�LED
    Serial.println("LED turned OFF");
  }
}


//�յ���Ϣ��Ļص�����
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // ��payloadת��Ϊ�ַ���
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';

  // ��ӡԭʼ��Ϣ
  Serial.println(message);

  // ����processJsonMessage����������Ϣ
  processJsonMessage(message);
}
//wifi��ʼ��
void wifiInit() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_SERVER, MQTT_PORT);   /* ����WiFi֮������MQTT������ */
  client.setCallback(callback);
}


//���ӵ�������
void mqttCheckConnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Server...");
    if (client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("MQTT Connected");
    } else {
      Serial.print("MQTT Connect err: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}


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

