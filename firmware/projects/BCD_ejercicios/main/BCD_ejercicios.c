/*! @mainpage BCD_ejercicios
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
 * @author Patriccio D'Andrea
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <gpio_mcu.h>
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/
typedef struct
{
    gpio_t pin;
    io_t dir;
} gpioConf_t;
gpioConf_t lcd_digit_map[3] = {
    {GPIO_19, GPIO_OUTPUT}, 
    {GPIO_18, GPIO_OUTPUT}, 
    {GPIO_9,  GPIO_OUTPUT}  
};
gpioConf_t bcd_gpio_map[4] = {
    {GPIO_20, GPIO_OUTPUT},
    {GPIO_21, GPIO_OUTPUT},
    {GPIO_22, GPIO_OUTPUT},
    {GPIO_23, GPIO_OUTPUT}
};
/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/

int8_t  convertToBcdArray (uint32_t data, uint8_t digits, uint8_t * bcd_number)
{for (uint8_t i = 0; i < digits; i++) {
        bcd_number[i] = data % 10;
        data /= 10;
    }

    return 0;


}

void setBcdToGpio(uint8_t bcd_digit, gpioConf_t *gpio_vector)
{
    for (uint8_t i = 0; i < 4; i++) {
        uint8_t bit = (bcd_digit >> i) & 0x01;
        GPIOState(gpio_vector[i].pin, bit); 
}
void displayNumberonLcd(uint32_t data, uint8_t digits, gpioConf_t *bcd_gpio_vector, gpioConf_t *digit_gpio_vector)
{
    uint8_t bcd_array[digits];
    convertToBcdArray(data, digits, bcd_array);

for (uint8_t i = 0; i < digits; i++) {
   
    for (uint8_t j = 0; j < digits; j++) {
        GPIOState(digit_gpio_vector[j].pin, false);
    }
    
    setBcdToGpio(bcd_array[digits - 1 - i], bcd_gpio_vector); 
   
    GPIOState(digit_gpio_vector[i].pin, true);

    for (volatile uint32_t d = 0; d < 10000; d++);
}}
void app_main(void){
    // Inicializa los GPIOs BCD
    for (uint8_t i = 0; i < 4; i++) {
        GPIOInit(bcd_gpio_map[i].pin, bcd_gpio_map[i].dir);
    }
    
    for (uint8_t i = 0; i < 3; i++) {
        GPIOInit(lcd_digit_map[i].pin, lcd_digit_map[i].dir);
    }

    while (1) {
        displayNumberonLcd(724, 3, bcd_gpio_map, lcd_digit_map);
       
}

/*==================[end of file]============================================*/