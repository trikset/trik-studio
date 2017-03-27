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

unsigned int Brick::read_analog_sensor()
{
	return TM_ADC_Read(ADC1, ADC_Channel_0);
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
	//TM_ILI9341_Fill(ILI9341_COLOR_RED);
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



// 	/* Initialize ILI9341 with LTDC */
// 	/* By default layer 1 is used */
// 	TM_ILI9341_Init();
	
// 	/* Rotate LCD for 90 degrees */
// 	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
	
// 	/* Go to layer 1 */
// 	TM_ILI9341_SetLayer1();
	
// 	/* Fill screen on layer 1 */
// 	TM_ILI9341_Fill(ILI9341_COLOR_BLUE);
	
// 	/* Show text */
// 	TM_ILI9341_Puts(65, 30, "Layer 1", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
// 	TM_ILI9341_Puts(20, 130, "STM32F429 Discovery ONLY!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
// 	TM_ILI9341_Puts(60, 150, "ILI9341 LCD Module", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
// 	TM_ILI9341_Puts(70, 170, "with LTDC support", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
// 	TM_ILI9341_Puts(170, 230, "stm32f4-discovery.com", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	

// 	while (1) {		
// 		/* This will set opacity of one layer to 0, other to max (255) each time */
// 		/* This is like toggle function */
// 		/* Every 1 second */
// 		Delayms(1000);
// 		/*
// 		//Bottom code works the same as one before inside while loop
		
// 		//Turn on Layer1 and turn off Layer2
// 		TM_ILI9341_SetLayer1Opacity(255);
// 		TM_ILI9341_SetLayer2Opacity(0);
// 		Delayms(500);
		
// 		//Turn on Layer2 and turn off Layer1
// 		TM_ILI9341_SetLayer1Opacity(0);
// 		TM_ILI9341_SetLayer2Opacity(255);
// 		Delayms(500);
// 		*/
// 	}