/*
 * USART_D Library - High-performance USART communication
 * * Copyright (c) 2026 Dauda Muazu Sulaiman
 * Copyright (c) 2026 KibrisOrder                <https://ss.kibrisorder.com>
 * * Author: Dauda Muazu Sulaiman
 * Organization: KibrisOrder
 * All rights reserved.
 * * This software is licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */



#include<avr/io.h>
#include <string.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<avr/power.h>

#include "USART_D.h"


int main(void){

    clock_prescale_set(clock_div_1);

    char ch = '#';
    int8_t age = 0x22;
    int8_t neg = -123;
    char name [] = "Sadik";

    const char* input = "";

    USART_begin();

    USART_print("\r\n==== USART_TEST ====\r\n");

    while(1){

        USART_print("\r\nHello World!\r\n");
        USART_print("My name is %s.\r\n", name);
        USART_print("How are you? %c\r\n", ch);
        USART_print("I am %d years old.\r\n", age);
        USART_print("My account balance is %d.\r\n", neg);
        USART_print("\r\n");

        if(!USART_getCheck()){

            input = USART_getString();
        }

        if(strlen(input) != 0){
        
            USART_print("INPUT =  ");
            USART_print("%s.\r\n\r\n", input);

            _delay_ms(5000);
        }

        // _delay_ms(3000);
    }

    return 0;
}