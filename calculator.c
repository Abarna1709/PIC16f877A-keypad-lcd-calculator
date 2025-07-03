#define _XTAL_FREQ 20000000

#include <xc.h>
#include<stdio.h>
#include<stdlib.h>

#pragma config FOSC = HS  
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define RS RD0
#define EN RD1
#define ldata PORTD

void LCD_Command(char);
void LCD_Char(char);
void LCD_init();
void LCD_String(const char str[]);
void LCD_Clear();


void keypad_init();
int myAtoi(char*);



void LCD_Command(char cmd){
    ldata = (ldata & 0x0F) | (cmd & 0xF0);
     RS=0; EN=1; __delay_ms(1); EN=0;
     
     ldata = (ldata & 0x0F) | (cmd << 4);
     EN=1; __delay_ms(1); EN=0;
}

void LCD_Char(char data){
    
    ldata = (ldata & 0x0F) | (data & 0xf0);
       RS=1; EN=1; __delay_ms(1);EN=0;
            
       ldata = (ldata & 0x0F) | (data << 4);
       EN=1; __delay_ms(1); EN=0;
}

void LCD_init(){
    TRISD = 0x00;
    
    RS=0;
    EN=0;
    __delay_ms(20);
    
    LCD_Command(0x02);
    LCD_Command(0x28);
    LCD_Command(0x0c);
    LCD_Command(0x06);
    LCD_Command(0x01);
}

void LCD_String(const char str[]){
    int i=0;
    while(str[i]!='\0'){
        LCD_Char(str[i]);
        i++;
    }
}

void LCD_Clear(){
    
    LCD_Command(0x01);
    __delay_ms(2);
    
}

char keypad[4][4] = {
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};


void keypad_init(){
    TRISB = 0xF0;
    TRISC = 0x00;
    PORTB = 0xFF;
    PORTC = 0xFF;
     OPTION_REGbits.nRBPU = 0;
}

char getKey() {
    for (int col = 0; col < 4; col++) {
        PORTC = 0xFF;           
        PORTC &= ~(1 << col);  
        __delay_ms(5);

        for (int row = 4; row < 8; row++) {
            if (!(PORTB & (1 << row))) { 
                __delay_ms(20);
                while (!(PORTB & (1 << row))); 
                return keypad[row - 4][col];
            }
        }
    }
    return 0;
}

int myAtoi(char *str) {
    int res = 0;
    int i = 0;
    while (str[i] != '\0') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

void main() {
     

    char key;
    char num1[10] = "";
    char num2[10] = "";
    int i = 0, j = 0;
    char operator = 0;
    int result = 0;
    
    ADCON1 = 0x06;
    LCD_init();
    keypad_init();
    LCD_String("Calculator");
    __delay_ms(200);
    LCD_Clear();

    while (1) {
        key = getKey();
        if (key) {
            if (key >= '0' && key <= '9') {
                if (!operator) {
                    num1[i++] = key;
                    num1[i] = '\0';
                } 
                else {
                    num2[j++] = key;
                    num2[j] = '\0';
                }
                LCD_Char(key);
            } 
            else if (key == '+' || key == '-' || key == '*' || key == '/') {
                operator = key;
                LCD_Char(operator);
            } 
            else if (key == '=') {
                int n1 = myAtoi(num1);
                int n2 = myAtoi(num2);
   
                switch (operator) {
                    case '+': 
                        result = n1 + n2; 
                        break;
                    case '-': 
                        result = n1 - n2; 
                        break;
                    case '*': 
                        result = n1 * n2; 
                        break;
                    case '/': 
                        result = (n2 != 0) ? n1 / n2 : 0; 
                        break;
                }
                LCD_Command(0xC0);
                char res[16];
                sprintf(res, "=%d", result);
                LCD_String(res);

               
                i = j = 0;
                num1[0] = num2[0] = '\0';
                operator = 0;
                __delay_ms(1000);
                LCD_Clear();
            } 
            else if (key == 'C') {
                LCD_Clear();
                i = j = 0;
                num1[0] = num2[0] = '\0';
                operator = 0;
            }
        }
    }
}