/*! @mainpage ejercicio_2
 *
 * \section genDesc General Description
 *
 * 
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 19/09/2025 | Document creation		                         |
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
#include "switch.h"
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 100
/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void app_main(void){
    uint8_t teclas;

    LedsInit();
    SwitchesInit();
    LedOff(LED_3);

    while(1)
    {
        teclas = SwitchesRead();

       
        if(teclas & SWITCH_1){
            LedToggle(LED_1);
        }

        
        if(teclas & SWITCH_2){
            LedToggle(LED_2);
        }else {
            LedOff(LED_2);
		}
       
        if((teclas & SWITCH_1) && (teclas & SWITCH_2)){
            LedToggle(LED_3);
			LedOff(LED_2);
			LedOff(LED_1);
        } else {
            LedOff(LED_3);
        }

        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}