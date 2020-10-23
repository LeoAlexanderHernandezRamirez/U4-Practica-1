;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
;Microvid adc pero en ensambler
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
PROCESSOR 16F887
    #include <xc.inc>
    ;configuración de los fuses
    CONFIG FOSC=INTRC_NOCLKOUT
    CONFIG WDTE=OFF
    CONFIG PWRTE=ON
    CONFIG MCLRE=OFF
    CONFIG CP=OFF
    CONFIG CPD=OFF
    CONFIG BOREN=OFF                ;Fuses
    CONFIG IESO=OFF
    CONFIG FCMEN=OFF
    CONFIG LVP=OFF
    CONFIG DEBUG=ON
    
    
    CONFIG BOR4V=BOR40V
    CONFIG WRT=OFF
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    PSECT udata
 tick:
    DS 1
 counter:
    DS 1
 counter2:
    DS 1
 RESULTHI:
    DS 1
 RESULTLO:
    DS 1
   
    PSECT code
    delay:                       ;Delay
    movlw 0xE1
    movwf counter
    counter_loop:
    movlw 0xE1
    movwf tick
    tick_loop:
    decfsz tick,f
    goto tick_loop
    decfsz counter,f
    goto counter_loop
    return
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    
PSECT resetVec,class=CODE,delta=2
	PAGESEL main
	goto main
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
PSECT main,class=CODE,delta=2
main:
    ;////////////////////////////////////////////
    BANKSEL PORTA
    clrf    PORTA
    BANKSEL TRISA      ;limpia PORTA y configura todos los pines como entrada
    movlw   0xFF         ;
    movwf   TRISA
    ;//////////////////////////////////////////////////////
    BANKSEL PORTC
	clrf PORTC    ;limpia PORTc y configura todos los pines como SALIDA
    BANKSEL TRISC
	clrf TRISC
	
	BANKSEL PORTB
	clrf PORTB   ;limpia PORTc y configura todos los pines como SALIDA
    BANKSEL TRISB
	clrf TRISB
    ;////////////////////////////////////////////
    BANKSEL ANSEL
    bsf ANSEL,0        ;desactiva la entrada analogica y permite la entrada de una funcion especial
    ;/////////////////////////////////////////////////
    BANKSEL ADCON0
    movlw 0b11000001      ;establece el tiempo y activa el adc
    movwf ADCON0
    ;//////////////////////////////////////////////////7
     BANKSEL ADCON1
    movlw 0b10000000         ;justifica a la derecha
    movwf ADCON1
;$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  
   ;////////////////////////////////
   call delay
   BANKSEL ADCON0
   bsf ADCON0,1          ;Ciclio que revisa si se realizo la convercion
   Btfsc ADCON0,1
   goto $-1
   ;//////////////////////
   
   BANKSEL ADRESH
   movf ADRESH,w
   BANKSEL PORTC
   movwf PORTC             ;se guardan los resultados en las variables
   BANKSEL ADRESL
   movf ADRESL,w
   BANKSEL PORTB
   movwf PORTB
   call delay
   call delay
   NOP
   ;////////////////////////
   
    
    END


