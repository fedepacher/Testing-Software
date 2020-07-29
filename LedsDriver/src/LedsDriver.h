#include "stdint.h"
#include "stdbool.h"

/** @brief  Initialize Leds  
 *  @param port_address  mapped port address
 *  @return void
 */
void LedsDriver_Constructor(uint16_t * port_address);

/** @brief  Deinitialize Leds  
 *  @param void
 *  @return void
 */
void LedsDriver_Destructor(void);

/** @brief  Turn on Led  
 *  @param led      led to be turned on          
 *  @return void
 */
void LedsDriver_On(int led);

/** @brief  Turn off Led  
 *  @param led      led to be turned off          
 *  @return void
 */
void LedsDriver_Off(int led);

/** @brief  Turn all leds on  
 *  @param void             
 *  @return void
 */
void LedsDriver_AllOn();

/** @brief  Turn all leds off  
 *  @param void             
 *  @return void
 */
void LedsDriver_AllOff();

/** @brief  Check is led is on  
 *  @param led             
 *  @return true/false
 */
bool LedsDriver_IsOn(int led);

/** @brief  Check is led is off  
 *  @param led             
 *  @return true/false
 */
bool LedsDriver_IsOff(int led);