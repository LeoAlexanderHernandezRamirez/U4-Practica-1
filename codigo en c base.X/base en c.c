//Team Microvid 7B Base en C lectura de ADC


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 8000000


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44
   int volatile RESULTHI=0;
   int volatile RESULTLO=0;           //Variables
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void delay(unsigned int time)
{
    for(int i=0;i<1000;i++){
       asm("nop"); 
    }
                         //Delay
}                           ///Delay

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44

void main(void) {
    
    //INTCON = 0b00000000;                //activamos las interrupciones globales y por perifericos (opcional)
    //PIE1 = 0b00000000;                  //activamos el adc
    
    //Reloj
    OSCCON= 0b01110100;
    /////////////////////////////////////////////////////////////////////////////////////////////////7
  
    ANSEL = 0b00000001;                 // activamos la entrada analogica 
    ANSELH= 0x00;
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    ADCON1 = 0b00000000;                //justificamos a la derecha
    ADCON0 = 0b00000001;                // colocamos a 8 y activamos las lecturas de adc
    
    //////////////////////////////////////////////////////////////////////////////////////////////
                
    PORTA = 0x00;                       //limpiamos el porta
    TRISA = 0xFF;                       //lo colocamos como entrada
    /////////////////////////////////////////////////////////////////////////////////////////////////
    PORTC = 0x00;                       //limpiamos el portb y lo ponemos como salida
    TRISC = 0x00;
    PORTB = 0x00;                       //limpiamos el portd y lo ponemos como salida
    TRISB = 0x00;
    TRISD= 0x00;
    PORTD=0x00;
   ////////////////////////////////////////////////////////////////////////////////////////////////////
    delay (1000);                //tiempo de adquisicion
                  //Activamos la conversion de adc
     
    while (1){
    ADCON0 = 0b01000011; 
    while(ADCON0bits.GO_nDONE){
     PORTB=ADRESH;
     PORTC=ADRESL;
     RESULTHI =ADRESH ;
     RESULTLO =ADRESL ; 
     }
     }
    return;
}
