/*
 * PushButton.c
 *
 *  Created on: 24/02/2019
 *      Author: Lilia Lobato
 */

#include "PushButton.h"
#include "MK64F12.h"
#include "GPIO.h"

uint8_t pb0_flag_g = FALSE;
uint8_t pb1_flag_g = FALSE;
uint8_t pb2_flag_g = FALSE;
uint8_t pb3_flag_g = FALSE;
uint8_t pb4_flag_g = FALSE;
uint8_t pb5_flag_g = FALSE;
uint8_t pb6_flag_g = FALSE;

gpio_pin_control_register_t dma_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | DMA_FALLING_EDGE; /* GPIO configured to trigger the DMA*/
gpio_pin_control_register_t input_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE | GPIO_PFE;	//Configuración del GPIO

void PushButton_sw2_config(void) {
	GPIO_clock_gating(GPIO_C);								  //Activa el puerto C
	GPIO_pin_control_register(GPIO_C, 6, &dma_intr_config); //Configuracion del GPIO C para el sw2
	GPIO_data_direction_port(GPIO_C, ~(SW2));				  //Configura el puerto del sw2 del GPIO C como Input
}

void PushButton_sw3_config(void) {
	GPIO_clock_gating(GPIO_A);								  //Activa el puerto A
	GPIO_pin_control_register(GPIO_A, 4, &input_intr_config); //Configuracion del GPIO A para el sw3
	PORTA->PCR[4] = (GPIO_MUX1 | GPIO_PE | GPIO_PS |INTR_FALLING_EDGE);
	GPIO_data_direction_port(GPIO_A, ~(SW3));				  //Configura el puerto del sw3 del GPIO A como Input

}

void PushButton_external_config(gpio_port_name_t GPIOx, BitsType pin, uint32_t MASK)
{
GPIO_clock_gating(GPIOx);								  //Activa el puerto x
GPIO_pin_control_register(GPIO_B, pin, &input_intr_config); //Configuracion del GPIO x para el pin n
GPIO_write_port(GPIOx, ~(MASK));						  //Escribe un valor seguro pin n
GPIO_data_direction_port(GPIOx, ~(MASK));				  //Configura el puerto del GPIO C como Input
}

uint32_t PushButton_read(PushButton_SW_name sw) {
	uint32_t push_value = 0;
	switch (sw) {
	case PB_SW2:/** PB_SW2 is selected*/
		push_value = GPIO_read_pin(GPIO_C, SW2);
		break;
	case PB_SW3:/** PB_SW3 is selected*/
		push_value = GPIO_read_pin(GPIO_A, SW3);
		break;
	default:/**If doesn't exist the option*/
		push_value = 0x00000000;
		break;
	}
	return push_value;
}

void PushButton_external_handler(void)
{
	uint8_t pb0_state = GPIO_read_pin(GPIO_B, bit_2); //Obtiene el estado del B0
	uint8_t pb1_state = GPIO_read_pin(GPIO_B, bit_3); //Obtiene el estado del B1
	uint8_t pb2_state = GPIO_read_pin(GPIO_B, bit_10); //Obtiene el estado del B2
	uint8_t pb3_state = GPIO_read_pin(GPIO_B, bit_11); //Obtiene el estado del B3
	uint8_t pb4_state = GPIO_read_pin(GPIO_B, bit_9); //Obtiene el estado del B4
	uint8_t pb5_state = GPIO_read_pin(GPIO_B, bit_19); //Obtiene el estado del B5
	uint8_t pb6_state = GPIO_read_pin(GPIO_B, bit_18); //Obtiene el estado del B6

		/**PB has logic 0 when its pressed*/
	if((FALSE == pb0_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb0_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb1_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb1_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb2_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb2_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb3_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb3_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb4_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb4_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb5_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb5_flag_g = TRUE; //activa la bandera correspondiente
	}

	if((FALSE == pb6_state))//Pregunta quien fue el que interrumpio, para saber que bandera activar
	{
		pb6_flag_g = TRUE; //activa la bandera correspondiente
	}
}

uint8_t get_pbn_flag(EXTERNAL_PushButton_SW_name ext_PB){
	switch(ext_PB)
	{
	case PB0:
		return(pb0_flag_g);
		break;
	case PB1:
		return(pb1_flag_g);
		break;
	case PB2:
		return(pb2_flag_g);
		break;
	case PB3:
		return(pb3_flag_g);
		break;
	case PB4:
		return(pb4_flag_g);
		break;
	case PB5:
		return(pb5_flag_g);
		break;
	case PB6:
		return(pb6_flag_g);
		break;
	}
}


void clear_pbn_flag(EXTERNAL_PushButton_SW_name ext_PB){
	switch(ext_PB)
	{
	case PB0:
		pb0_flag_g = FALSE;
		break;
	case PB1:
		pb1_flag_g = FALSE;
		break;
	case PB2:
		pb2_flag_g = FALSE;
		break;
	case PB3:
		pb3_flag_g = FALSE;
		break;
	case PB4:
		pb4_flag_g = FALSE;
		break;
	case PB5:
		pb5_flag_g = FALSE;
		break;
	case PB6:
		pb6_flag_g = FALSE;
		break;
	case ALL:
		pb0_flag_g = FALSE;
		pb1_flag_g = FALSE;
		pb2_flag_g = FALSE;
		pb3_flag_g = FALSE;
		pb4_flag_g = FALSE;
		pb5_flag_g = FALSE;
		pb6_flag_g = FALSE;
		break;
	}
}
