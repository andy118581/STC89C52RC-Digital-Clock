#include <REGX52.H>


/**
  * @brief  UART初始化函式
  * @param  無
  * @retval 無
  */
void UART_Init()		//4800bps@11.0592MHz
{
	SCON = 0x50;
	PCON &= 0x7F; //鮑率不加倍,PCON&=0x7F==PCON=PCON&0111 1111 (讓最高位為0,其餘不變)
	TMOD &= 0x0F; //若TMOD=0000 1010,TMOD&0x0F==0000 1010&0000 1111==0000 1010
	TMOD |= 0x20; //TMOD=TMOD|0x20==TMOD=0000 1010|0020 0000==TMOD=0020 1010
	//*這也是不改變高位之寫法
	TH1 = 0xFA;  //4800 bps 的自動重裝值
	TL1 = 0xFA;  //設定初始計數值
	ET1 = 0;     //T1的溢出中斷允許位,當ET1=1時允許T1中斷
	TR1 = 1; //定時器T1運作控制位,若GATE=0,則TR1=1定時器T1才開始計數(反之TR1=0,定時器T1無法計數)
		     //若GATE=1,TR1=0,fu且INT0=1時,定時器T1才允許開始計數
}


/**
  * @brief  UART向電腦發送數據之函式
  * @param  欲向電腦串口助手發送之數據
  * @retval 無
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}


void UART_SendTime(unsigned int hr,unsigned int min,unsigned int sec)
{
    // 傳送小時：兩位數
    UART_SendByte(hr / 10 + '0');
    UART_SendByte(hr % 10 + '0');
	//以hr=11為例,代表11點;hr/10=1;hr/10+'0'==1+'0'=='1'
	//同理hr%10+'0'得字元'1'
	
    UART_SendByte(':');

    // 傳送分鐘：兩位數
    UART_SendByte(min / 10 + '0');
    UART_SendByte(min % 10 + '0');

    UART_SendByte(':');

    // 傳送秒數：兩位數
    UART_SendByte(sec / 10 + '0');
    UART_SendByte(sec % 10 + '0');

    // 傳送換行，方便下一次輸出顯示在新的一行
    UART_SendByte('\r');
    UART_SendByte('\n');
}
