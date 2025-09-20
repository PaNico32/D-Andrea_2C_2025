/*! @mainpage 3_ejercicio
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
 * | 19/09/2025 | Document creation		                         |
 *
 * @author Patricio D'Andrea
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/
enum {ON, OFF, TOGGLE};
/*==================[internal functions declaration]=========================*/
struct iluminador
{
      uint8_t mode;       
	uint8_t n_led;        
	uint8_t n_ciclos;   
	uint16_t periodo;    
} led_mio; 

/*==================[external functions definition]==========================*/
void ledcontrol(struct iluminador *led)
{
    switch (led->mode)
    {
        case ON:
            if (led->n_led == LED_1) LedOn(LED_1);
            else if (led->n_led == LED_2) LedOn(LED_2);
            else if (led->n_led == LED_3) LedOn(LED_3);
            break;

        case OFF:
            if (led->n_led == LED_1) LedOff(LED_1);
            else if (led->n_led == LED_2) LedOff(LED_2);
            else if (led->n_led == LED_3) LedOff(LED_3);
            break;

        case TOGGLE:
            if (led->n_ciclos > 0) {
                for (uint8_t i = 0; i < led->n_ciclos; i++) {
                    if (led->n_led == LED_1) LedToggle(LED_1);
                    else if (led->n_led == LED_2) LedToggle(LED_2);
                    else if (led->n_led == LED_3) LedToggle(LED_3);

                    vTaskDelay(led->periodo); 
                }
            }
            break;
    }
}

/*==================[main]==========================*/
void app_main(void)
{
    LedsInit();

    struct iluminador led;

    led.mode = TOGGLE;    
    led.n_led = LED_1;    
    led.n_ciclos = 20;     
    led.periodo = 100;    

    ledcontrol(&led);
}
/*==================[end of file]============================================*/