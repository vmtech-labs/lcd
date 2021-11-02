/*
Author: VMTech Labs
Version: v1.00
LCD: 1602
*/
//*Setting Pin and Port connect to LCD1602 in here*//
#define LCD_ENABLE_PIN  GPIO_PIN_12
#define LCD_ENABLE_PORT GPIOA
#define LCD_RS_PIN      GPIO_PIN_14
#define LCD_RS_PORT     GPIOA
#define LCD_RW_PIN      GPIO_PIN_13
#define LCD_RW_PORT     GPIOA
#define LCD_DATA4       GPIO_PIN_11
#define LCD_DATA4_PORT  GPIOA
#define LCD_DATA5       GPIO_PIN_10
#define LCD_DATA5_PORT  GPIOA
#define LCD_DATA6       GPIO_PIN_9
#define LCD_DATA6_PORT  GPIOA
#define LCD_DATA7       GPIO_PIN_8
#define LCD_DATA7_PORT  GPIOA
#define LCD_LED         GPIO_PIN_15
#define LCD_LED_PORT    GPIOA

//////////////////////////////////////////////////////////////////////

#define lcd_rs1 HAL_GPIO_WritePin(LCD_RS_PORT,LCD_RS_PIN,GPIO_PIN_SET)
#define lcd_rs0 HAL_GPIO_WritePin(LCD_RS_PORT,LCD_RS_PIN,GPIO_PIN_RESET)

#define lcd_rw1 HAL_GPIO_WritePin(LCD_RW_PORT,LCD_RW_PIN,GPIO_PIN_SET)
#define lcd_rw0 HAL_GPIO_WritePin(LCD_RW_PORT,LCD_RW_PIN,GPIO_PIN_RESET)

#define lcd_e1 HAL_GPIO_WritePin(LCD_ENABLE_PORT,LCD_ENABLE_PIN,GPIO_PIN_SET)
#define lcd_e0 HAL_GPIO_WritePin(LCD_ENABLE_PORT,LCD_ENABLE_PIN,GPIO_PIN_RESET)

#define lcd_d4_1 HAL_GPIO_WritePin(LCD_DATA4_PORT,LCD_DATA4,GPIO_PIN_SET)
#define lcd_d4_0 HAL_GPIO_WritePin(LCD_DATA4_PORT,LCD_DATA4,GPIO_PIN_RESET)

#define lcd_d5_1 HAL_GPIO_WritePin(LCD_DATA5_PORT,LCD_DATA5,GPIO_PIN_SET)
#define lcd_d5_0 HAL_GPIO_WritePin(LCD_DATA5_PORT,LCD_DATA5,GPIO_PIN_RESET)

#define lcd_d6_1 HAL_GPIO_WritePin(LCD_DATA6_PORT,LCD_DATA6,GPIO_PIN_SET)
#define lcd_d6_0 HAL_GPIO_WritePin(LCD_DATA6_PORT,LCD_DATA6,GPIO_PIN_RESET)

#define lcd_d7_1 HAL_GPIO_WritePin(LCD_DATA7_PORT,LCD_DATA7,GPIO_PIN_SET)
#define lcd_d7_0 HAL_GPIO_WritePin(LCD_DATA7_PORT,LCD_DATA7,GPIO_PIN_RESET)

#define led_lcd_1 	HAL_GPIO_WritePin(LCD_LED_PORT,LCD_LED,GPIO_PIN_SET)
#define led_lcd_0 	HAL_GPIO_WritePin(LCD_LED_PORT,LCD_LED,GPIO_PIN_RESET)

///////////////LCD 1602///////////////////////////////////////////////////////////
void lcd_enable();
void lcd_sen4bit(unsigned char data);
void lcd_sendcommand(unsigned char command);
void lcd_init();
void lcd_gotoxy(char x, char y);
void lcd_clear();
void lcd_putchar(unsigned char data);
void lcd_dis_num(int data);

char lcd_d4,lcd_d5,lcd_d6,lcd_d7;//cac chan du lieu cua lcd
void lcd_enable(){
  lcd_e1;//E=1
  HAL_Delay(1);
  lcd_e0;//E=0
  HAL_Delay(1);
}

void lcd_sen4bit(unsigned char data){
  lcd_d4=data&0x01;
  lcd_d5=(data>>1)&0x01;
  lcd_d6=(data>>2)&0x01;
  lcd_d7=(data>>3)&0x01;

  if(lcd_d4==1) lcd_d4_1;
  else  lcd_d4_0;

  if(lcd_d5==1) lcd_d5_1;
  else  lcd_d5_0;

  if(lcd_d6==1) lcd_d6_1;
  else  lcd_d6_0;

  if(lcd_d7==1) lcd_d7_1;
  else  lcd_d7_0;
}

void lcd_sendcommand(unsigned char command){
  lcd_sen4bit(command>>4);
  lcd_enable();
  lcd_sen4bit(command);
  lcd_enable();
}

void lcd_init(){
  lcd_sen4bit(0x00);
  HAL_Delay(10);
  lcd_rs0;//rs=0;
  lcd_sen4bit(0x03);
  lcd_enable();
  HAL_Delay(10);// khai bao LCD che do 4bit 5x7
  lcd_enable();
  HAL_Delay(10);
  lcd_enable();
  lcd_sen4bit(0x02);
  lcd_enable();
  lcd_sendcommand(0x28);//cac ma lenh khoi tao LCD1602 voi che do 4 bit
  HAL_Delay(10);
  lcd_sendcommand(0x0c);
  HAL_Delay(10);
  lcd_sendcommand(0x06); // tang ID, khong dich khung hinh
  HAL_Delay(10);
  lcd_sendcommand(0x01); // xoa toan bo khung hinh
  HAL_Delay(10);
}

void lcd_gotoxy(char x, char y){
  unsigned char address;
  if(y==0)
		address = 0x80+x;//0x80 l� dia chi hang thu nhat
  else  address = 0xc0+x; //0xc0 l� dia chi hang thu 2
  HAL_Delay(1);
  lcd_sendcommand(address);
  HAL_Delay(1);
}

void lcd_clear(){
  lcd_sendcommand(0x01);
  HAL_Delay(100);
}

void lcd_putchar(unsigned char data){//chuong trinh goi ky tu
  lcd_rs1;//rs=1;
  lcd_sendcommand(data);
  lcd_rs0;//rs=0;
}

void lcd_puts (char *s)//chuong trinh goi chuoi ky tu
{
   while (*s)
   {
      lcd_putchar(*s);
      s++;
   }
}

void lcd_dis_num(int data){//ABCD
	if(data>99) lcd_putchar(data/100+48);
	else lcd_puts(" ");
	if(data>9) lcd_putchar((data%100)/10+48);
	else lcd_puts(" ");
	lcd_putchar(data%10+48);
}


//////////////////////////////////////////////////////////////////////////////////
