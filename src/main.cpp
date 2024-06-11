#include "Arduino.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// ����һ��short���������洢���յ�������
// �����СΪ512����Ϊÿ��short���Դ洢�����ֽڣ����Կ��Դ洢1024���ֽ�
short receivedData[512];
int dataIndex = 0; // ���ڸ��������е�ǰ�洢λ�õ�����

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); // �����豸����
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  static byte byteBuffer[2]; // �����ݴ������ֽ�
  static int bufferIndex = 0; // byteBuffer������

  // ����Ƿ��д��������յ�������
  while (SerialBT.available() > 0 && dataIndex < 512) {
    int byteRead = SerialBT.read(); // ��ȡһ���ֽ�

    // ���read()�Ƿ���Ķ�ȡ��������
    if (byteRead != -1) {
      byteBuffer[bufferIndex++] = (byte)byteRead; // �洢��buffer��

      // ����Ƿ��ռ��������ֽ�
      if (bufferIndex == 2) {
        // �������ֽںϲ�Ϊһ��short�ͱ���
        // ע�⣺���������Ҫ����ʵ�ʵ��ֽ���������
        receivedData[dataIndex++] = (short)((byteBuffer[0] << 8) | byteBuffer[1]);

        // ����bufferIndex�Ա��ڽ�����һ���ֽ�
        bufferIndex = 0;
      }
    }
  }
  
  // ��������Դ�����յ���short����������
}