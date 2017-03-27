#include <stdio.h>
extern "C" {
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_adc.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_ili9341_ltdc.h"
#include "tm_stm32f4_fonts.h"

}
class Brick
{
public:
	Brick();
	~Brick();

	void led_off();
	void led_green();
	void led_red();
	void wait(unsigned int milliseconds);
	unsigned int read_analog_sensor();
	void set_display_background_color(char *color);
	void display_redraw() {}
	void display_clear() {}
	
	void display_addLabel(const char * text, int x, int y);
	void display_addLabel(int v, int x, int y);

	
private:
	void init();
};