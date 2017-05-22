#include "brick.h"

Brick::Brick() 
{
	init();
}

Brick::~Brick()
{
}

void Brick::led_off()
{
	TM_DISCO_LedOff(LED_GREEN);
	TM_DISCO_LedOff(LED_RED);
}

void Brick::led_green()
{
	led_off();
	TM_DISCO_LedOn(LED_GREEN);
}

void Brick::led_red()
{
	led_off();
	TM_DISCO_LedOn(LED_RED);
}

void Brick::wait(unsigned int milliseconds)
{
	Delayms(milliseconds);
}

unsigned int Brick::read_analog_sensor(char *port)
{
    unsigned int result = 0;
    if (strcmp(port, "PA0") == 0)
	{
        result = TM_ADC_Read(ADC1, ADC_Channel_0);
	} else if (strcmp(port, "PA1") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_1);
	} else if (strcmp(port, "PA2") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_2);
	} else if (strcmp(port, "PA3") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_3);
	} else if (strcmp(port, "PA4") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_4);
	} else if (strcmp(port, "PA5") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_5);
	} else if (strcmp(port, "PA6") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_6);
	} else if (strcmp(port, "PA7") == 0)
	{
		result = TM_ADC_Read(ADC1, ADC_Channel_7);
	}
    return result;
}

void Brick::set_display_background_color(char *color)
{
	if (strcasecmp(color, "red") == 0)
	{
		TM_ILI9341_Fill(ILI9341_COLOR_RED);
	} else if (strcasecmp(color, "green") == 0)
	{
		TM_ILI9341_Fill(ILI9341_COLOR_GREEN);
	}
}

void Brick::init()
{
	/* Initialize system */
	SystemInit();
	
	/* Initialize Delay library */
	TM_DELAY_Init();
	
	/* Initialize leds on board */
	TM_DISCO_LedInit();

	/* Initialize ADC3 on channel 14, this is pin PF4 */
	TM_ADC_Init(ADC1, ADC_Channel_0);

	/* Initialize ILI9341 with LTDC */
	/* By default layer 1 is used */
	TM_ILI9341_Init();

	/* Rotate LCD for 90 degrees */
	// TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

	// 	/* Go to layer 1 */
 	TM_ILI9341_SetLayer1();
}


void Brick::display_addLabel(const char * text, int x, int y) {
	TM_ILI9341_Puts(x, y, const_cast<char *> (text), &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);

}

void Brick::display_addLabel(int v, int x, int y) {
	char str[40];
	sprintf(str,"%d",v);
    display_addLabel(str,x,y);	
}
