/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 12/09/2023 | Document creation		                         |
 *
 * @author Patricio D'Andrea
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include <hc_sr04.h>
#include <lcditse0803.h>
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void distancias(void);
void app_main(void){
    LedsInit();
    HcSr04Init(GPIO_3,GPIO_2); // Inicializa el sensor de ultrasonido
    LcdItsE0803Init(); // Inicializa el display
    
    while (1) {
        distancias();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Refresca cada 100 ms
    }
    

   
}

void distancias(void){
    uint16_t distancia = HcSr04ReadDistanceInCentimeters();
   // printf("Distancia medida: %u\n", distancia);
    uint8_t rango = 0;
    LcdItsE0803Write(distancia);
    // Mostrar la distancia en el display
    

    if (distancia < 10) {
        rango = 0;
    } else if (distancia < 20) {
        rango = 1;
    } else if (distancia < 30) {
        rango = 2;
    } else {
        rango = 3;
    }

    switch(rango) {
        case 0:
            LedsOffAll();
            break;
        case 1:
            LedOn(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);
            break;
        case 2:
            LedOn(LED_1);
            LedOn(LED_2);
            LedOff(LED_3);
            break;
        case 3:
            LedOn(LED_1);
            LedOn(LED_2);
            LedOn(LED_3);
            break;

    }
}
/*==================[end of file]============================================*/