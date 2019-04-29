/*
 * PushButton.c
 *
 *  Created on: 24/02/2019
 *      Author: Lilia Lobato
 */

#include "PushButton.h"
#include "MK64F12.h"
#include "GPIO.h"

gpio_pin_control_register_t input_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;	//Configuración del GPIO
gpio_pin_control_register_t dma_intr_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | DMA_FALLING_EDGE; /* GPIO configured to trigger the DMA*/

void PushButton_sw2_config(void) {
	GPIO_clock_gating(GPIO_C);								  //Activa el puerto C
	GPIO_pin_control_register(GPIO_C, 6, &dma_intr_config); //Configuracion del GPIO C para el sw2
	GPIO_write_port(GPIO_C, ~(SW2));						  //Escribe un valor seguro
	GPIO_data_direction_port(GPIO_C, ~(SW2));				  //Configura el puerto del sw2 del GPIO C como Input
}

void PushButton_sw3_config(void) {
	GPIO_clock_gating(GPIO_A);								  //Activa el puerto A
	GPIO_pin_control_register(GPIO_A, 4, &input_intr_config); //Configuracion del GPIO A para el sw3
	PORTA->PCR[4] = (GPIO_MUX1 | GPIO_PE | GPIO_PS |INTR_FALLING_EDGE);
	GPIO_write_port(GPIO_A, ~(SW3));						  //Escribe un valor seguro
	GPIO_data_direction_port(GPIO_A, ~(SW3));				  //Configura el puerto del sw3 del GPIO A como Input
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

void GPIO_write_port(gpio_port_name_t portName, uint32_t data)
{
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDOR |= data; /**assigns a safe value to PORT A*/
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDOR |= data; /**assigns a safe value to PORT B*/
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDOR |= data; /**assigns a safe value to PORT C*/
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDOR |= data; /**assigns a safe value to PORT D*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDOR |= data; /**assigns a safe value to PORT E*/
					break;
				default:/**If doesn't exist the option*/

				break;
				}
}
void GPIO_data_direction_port(gpio_port_name_t port_name ,uint32_t direction)
{
	switch(port_name)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PDDR |= direction; /**assigns direction to PORT A*/
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PDDR |= direction;/**assigns direction to PORT B*/
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PDDR |= direction;/**assigns direction to PORT C*/
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PDDR |= direction;/**assigns direction to PORT D*/
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PDDR |= direction;/**assigns direction to PORT E*/
				break;
			default:/**If doesn't exist the option*/

			break;
			}
}
