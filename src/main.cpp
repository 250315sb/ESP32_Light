#include "Arduino.h"
#include "HardwareSerial.h"        //���ô��ڿ�
#define UART_FULL_THRESH_DEFAULT 2048         //�޸Ļ�������С�������HardwareSerial.h�ļ���˵���޸ķ����������ˣ���û�з�������
#define CJ_RxPin 34                //����RX�ܽ�
#define CJ_TxPin 35                //����TX�ܽ�
HardwareSerial Serial_CJ(0);       //���򴮿�1

void Collect_Callback(){               
  String Collect_Data = "";                     //����һ��String���͵ı���
  while(Serial_CJ.available()){                 //��While�жϻ������Ƿ�������
    Collect_Data += char(Serial_CJ.read());     //ȡ������������
  } 
  Serial.print(Collect_Data);                     //���ȡ��������
  Collect_Data = "";                              //�������
 }
void setup() {
	Serial.begin(115200);           //���ó�ʼ������0
	Serial_CJ.begin(115200,SERIAL_8N1,CJ_RxPin,CJ_TxPin);  //��ʼ������1����ʼ����������ȥHardwareSerial.h�ļ��в鿴
	Serial_CJ.onReceive(Collect_Callback);    //���崮���жϺ���
}
void loop(){
	delay(1000);             //��ʱ
}


