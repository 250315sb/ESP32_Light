#include "Arduino.h"
#include "BluetoothSerial.h"

// ����Ƿ���BluetoothSerial��
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Device"); // ���������豸����
  Serial.println("Bluetooth device is ready to pair");
}

void loop() {
  if (SerialBT.available()) {
    // ����һ���ַ�����������յ���16��������
    String hexData = "";

    // �������ݿɶ�ʱ��������ȡ
    while (SerialBT.available()) {
      int byteRead = SerialBT.read(); // ��ȡһ���ֽ�

      // ����ȡ�����ֽ�ת��Ϊ16�����ַ���
      char hexStr[3]; // �����ַ�����null��ֹ��
      sprintf(hexStr, "%02X", byteRead); // ��ʽ��Ϊ��λ16������

      // ��ת�����16�����ַ�����ӵ�hexData�ַ�����
      hexData += hexStr;
      hexData += " "; // Ϊ�˿ɶ��ԣ���ÿ���ֽ�֮�����һ���ո�
    }

    // ��ӡ���յ���16��������
    Serial.print("Received data in hex: ");
    Serial.println(hexData);
  }
  delay(100); // ��΢�ӳ�һ�£��������Ƶ���ض�ȡ
}