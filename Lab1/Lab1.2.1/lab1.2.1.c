/*
 * main.c
 *
 *  Created on: Mar 6, 2017
 *      Author: miracle
 */
#include "xparameters.h"
#include "xgpio.h"

#define LED_1 0x1
#define LED_2 0x2
#define LED_3 0x3
#define LED_4 0x4
#define LED_5 0x5
#define LED_6 0x6
#define LED_7 0x7
#define LED_8 0x8

int main(void) {

	XGpio dip, push, led;
	int i, psb_check, dip_check;
	int tmppsb, tmpdip;

	//Initialize switches
	XGpio_Initialize(&dip, XPAR_SW_8BIT_DEVICE_ID);
	//Set switches GPIO as input direction
	XGpio_SetDataDirection(&dip, 1, 0xffffffff);

	//Initialize buttons
	XGpio_Initialize(&push, XPAR_BTNS_5BITS_DEVICE_ID);
	//Set buttons GPIO as input direction
	XGpio_SetDataDirection(&push, 1, 0xffffffff);

	//Initialize LEDs
	XGpio_Initialize(&led, XPAR_LEDS_8BITS_DEVICE_ID);
	//Set LEDs GPIO as output direction
	XGpio_SetDataDirection(&led, 1, 0x0);

	//Read from switches GPIO
	//dip_check = XGpio_DiscreteRead(&dip, 1);
	//printf("dip_check=%d\n",dip_check);//my


	int tmp;
	while (1) {
		//Read from buttons GPIO
		psb_check = XGpio_DiscreteRead(&push, 1);
		//printf("psb_check=%d\n",psb_check);//my
		if (tmp == psb_check) {
			continue;
		} else {
			switch (psb_check) {
			case 1:
				printf("you press center btn\n");
				tmp = 1;
				break;
			case 2:
				printf("you press down btn\n");
				tmp = 2;
				break;
			case 4:
				printf("you press left btn\n");
				tmp = 4;
				break;
			case 8:
				printf("you press right btn\n");
				tmp = 8;
				break;
			case 16:
				printf("you press up btn\n");
				tmp = 16;
				break;
			default:
				break;
			}
		}
		//center:0 down:2 left:4 right:8 up:16

		//Write to LED
		//XGpio_DiscreteWrite(&led, 1, 0xFF);//original
		//XGpio_DiscreteWrite(&led, 1, dip_check);//my
		dip_check = XGpio_DiscreteRead(&dip, 1);
		XGpio_DiscreteWrite(&led, 1, dip_check);

	}

	//Write to UART
	xil_printf("Push Buttons Status %x\r\n", push);
	return 0;
}
