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



#ifndef _REG_DEFS_H
#define _REG_DEFS_H 1



/*
	First (#if) is for MODERN AVR (ATmega328P, 168, 2560,  etc.)

	Second (#if) is for LEGACY AVR (ATmega8, 16, 32,  etc.)
*/


#ifndef _ERROR_D_
	#define _ERROR_D_ "This MCU is not supported by the USART_D library yet!"
#endif

/* Output Compare Register Value */
#ifndef _OCR_VAL_
	#define _OCR_VAL_ ((F_CPU / 1024) * 16 / 1000 - 1)
#endif


/* USART Data Register */
#if defined(UDR0)
	#define _DATA_SFR_ UDR0
#elif defined (UDR)
	#define _DATA_SFR_ UDR
#else
    #error _ERROR_D_
#endif


/* USART, Rx Complete vect */
#if defined(USART_RX_vect)
	#define _RX_COMPLETE_ USART_RX_vect
#elif defined(USART_RXC_vect)
	#define _RX_COMPLETE_ USART_RXC_vect
#else
    #error _ERROR_D_
#endif


/* Timer/Counter2 Compare Match */
#if defined(TIMER2_COMPA_vect)
	#define _TIMER2_COMP_ TIMER2_COMPA_vect
#elif defined(TIMER2_COMP_vect)
	#define _TIMER2_COMP_ TIMER2_COMP_vect
#else
    #error _ERROR_D_
#endif


/* USART Control And Status Register(A, B and C) */
#if defined(UCSR0A)
	#define _UCSR_1_SFR UCSR0A
	#define _UCSR_2_SFR UCSR0B
	#define _UCSR_3_SFR UCSR0C
#elif defined(UCSRA)
	#define _UCSR_1_SFR UCSRA
	#define _UCSR_2_SFR UCSRB
	#define _UCSR_3_SFR UCSRC
#else
    #error _ERROR_D_
#endif


/* USART Data Register Empty Interrupt Enable */
#if defined(UDRIE0)
	#define _UDRIE_ UDRIE0
#elif defined(UDRIE)
	#define _UDRIE_ UDRIE
#else
    #error _ERROR_D_
#endif


/* Timer/Counter2 Output Compare Register(A) */
#if defined(OCR2A)
	#define _OCR2_ OCR2A
#elif defined(OCR2)
	#define _OCR2_ OCR2
#else
    #error _ERROR_D_
#endif


/* Timer/Counter2 Control Register(A and B) */
#if defined(TCCR2A)
	#define _TCCR2_ TCCR2A
	#define _TCCR2B_ TCCR2B
#elif defined(TCCR2)
	#define _TCCR2_ TCCR2
	#define _TCCR2B_ TCCR2
#else
    #error _ERROR_D_
#endif


/* Timer/Counte2 Mask */
#if defined(TIMSK2)
	#define _TIMSK_ TIMSK2
#elif defined(TIMSK)
	#define _TIMSK_ TIMSK
#else
    #error _ERROR_D_
#endif


/* Output Compare Interrupt Enable */
#if defined(OCIE2A)
	#define _OCIE_ OCIE2A
#elif defined(OCIE2)
	#define _OCIE_ OCIE2
#else
    #error _ERROR_D_
#endif


/* USART Baud Rate Register HIGH and LOW */
#if defined(UBRR0H)
	#define _UBRR_HIGH_ UBRR0H
	#define _UBRR_LOW_ UBRR0L
#elif defined(UBRRH)
	#define _UBRR_HIGH_ UBRRH
	#define _UBRR_LOW_ UBRRL
#else
    #error _ERROR_D_
#endif


/* USART 2X */
#if defined(U2X0)
	#define _U2X_ U2X0
#elif defined(U2X)
	#define _U2X_ U2X
#else
    #error _ERROR_D_
#endif


/* Rx and Tx Enable */
#if defined(TXEN0)
	#define _TXE_ TXEN0
	#define _RXE_ RXEN0
#elif defined(TXEN)
	#define _TXE_ TXEN
	#define _RXE_ RXEN
#else
    #error _ERROR_D_
#endif


/* USART Character Size */
#if defined(UCSR0C)
	#define _UCSZ0_ UCSZ00
	#define _UCSZ1_ UCSZ01
	#define _UCSZ2_ UCSZ02
#elif defined(URSEL)
	#define _UCSZ0_ UCSZ0
	#define _UCSZ1_ UCSZ1
	#define _UCSZ2_ UCSZ2
#else
    #error _ERROR_D_
#endif


/* USART Recieve Complete */
#if defined(RXC0)
	#define _RXC_ RXC0
#elif defined(RXC)
	#define _RXC_ RXC
#else
    #error _ERROR_D_
#endif

/* USART Rx Complete Interrupt Enable */
#if defined(RXCIE0)
	#define _RXCI_ RXCIE0
#elif defined(RXCIE)
	#define _RXCI_ RXCIE
#else
    #error _ERROR_D_
#endif


#endif /* For defining _REG_DEFS_H */