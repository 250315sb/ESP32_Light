#include <Arduino.h>
#include <BluetoothSerial.h>
#include "light.h"
#include <string.h>
 

/***********************************************************/
BluetoothSerial SerialBT;
uint16_t    u16Light_Value = 0;
float       fLight_precent = 0;
uint8_t     u8SerialRead[100];
int        read_val = 0;
#define RXBUFFERSIZE  256     //�������ֽ���
char RxBuffer[RXBUFFERSIZE];   //��������
uint8_t aRxBuffer;			//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;		//���ջ������
/***********************************************************/

void setup()
{
    Serial.begin(115200);
    // ��ʼ��LEDC
    ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(LEDC_PIN, LEDC_CHANNEL_0);
    SerialBT.begin("BAKUMAN"); // ���û�в���������Ĭ��������������: "ESP32"
    // SerialBT.setPin("1234");   // �������ӵ������
    Serial.printf("BT initial ok and ready to pair. \r\n");

}

void Process_Recevie()
{
    aRxBuffer = SerialBT.read();
    read_val = aRxBuffer - '0';
    if(Uart1_Rx_Cnt >= 255)  //����ж�
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
	}
    else
    {
        RxBuffer[Uart1_Rx_Cnt++] = read_val;   //��������ת��
        if ((RxBuffer[0]==0XA5)&&(RxBuffer[Uart1_Rx_Cnt-1]==0X5A))
        {
            for (int i = 0; i < 7; i++)
            {
                /* code */
                Serial.write(RxBuffer[i]);
            }
            
            
            memcpy(u8SerialRead,RxBuffer,sizeof(char)*Uart1_Rx_Cnt);
            Uart1_Rx_Cnt = 0;
        }
        //Serial.write(aRxBuffer);
    }


}


void loop()
{
    if (Serial.available())
    {
        
    
        

    }
    if (SerialBT.available())
    {   
        //read_val = SerialBT.read();
        Process_Recevie();
        //Serial.write(read_val);
    }


    ledcWrite(LEDC_CHANNEL_0, u16Light_Value);
    
    delay(1);



}
