#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.c"
#include "io.h"
#include "pwm.h"
#include "timer.h"
#include "note.h"
#include "shift.h"
#include "scheduler.h"
#include "joystick.h"
#include "score.h"

// variable for creating block
static unsigned char column_val = 0x00; // sets the pattern displayed on columns
static unsigned char column_sel = 0x00; // grounds column to display pattern

unsigned char i = 0x00;

unsigned char tmp = 0x00;

// for score
unsigned char c[3] = {0x30, 0x30, 0x30};

// SM1 the main game loop, adjust direction of arrow
enum SM1_States {start, end, arrow, l_1, l_2, l_3, l_4, r_1, r_2, r_3, r_4, u_1, u_2, u_3, u_4, d_1, d_2, d_3, d_4};

int SMTick1(int state) {
	switch (state) {
		case start:
		state = arrow;
		break;
		
		case end:
		if (tmp)
		{
			state = start;
		}
		state = end;
		break;
		
		case arrow:
		if (i < 32)
		{
			if (song[i] == Cb4 || song[i] == Gb4 || song[i] == Db5 || song[i] == Ab5)
			{
				state = l_1;
				if (adc_read(0) < 400)
				{
					updateScore(c); 
					LCD_ClearScreen();
					//LCD_WriteData('1');
					LCD_DisplayString(1, "PERFECT");
				}
			}
			else if (song[i] == Db4 || song[i] == Ab4 || song[i] == Eb5 || song[i] == Bb5)
			{
				state = r_1;
				if (adc_read(0) > 800)
				{
					updateScore(c);
					LCD_ClearScreen();
					//LCD_WriteData('1');
					LCD_DisplayString(1, "PERFECT");
				}
			}
			else if (song[i] == Eb4 || song[i] == F4 || song[i] == F5 || D4)
			{
				state = u_1;
				if (adc_read(1) < 400)
				{
					updateScore(c);
					LCD_ClearScreen();
					//LCD_WriteData('1');
					LCD_DisplayString(1, "PERFECT");
				}
			}
			else if (song[i] == Cb5 || song[i] == Bb4 || song[i] == Gb5)
			{
				state = d_1;
				if (adc_read(1) > 800)
				{
					updateScore(c);
					LCD_ClearScreen();
					//LCD_WriteData('1');
					LCD_DisplayString(1, "PERFECT");
				}
			}
			else if (song[i] == 0)
			{
				transmit_data(0);
				transmit_datab(0);
			}
		}
		else
		{
			state = end;
		}
		break;
		
		// draw left arrow
		case l_1:
		state = l_2;
		break;
		
		case l_2:
		state = l_3;
		break;
		
		case l_3:
		state = l_4;
		break;
		
		case l_4:
		state = arrow;
		break;
		
		// draw right arrow
		case r_1:
		state = r_2;
		break;
		
		case r_2:
		state = r_3;
		break;
		
		case r_3:
		state = r_4;
		break;
		
		case r_4:
		state = arrow;
		break;
		
		// draw up arrow
		case u_1:
		state = u_2;
		break;
		
		case u_2:
		state = u_3;
		break;
		
		case u_3:
		state = u_4;
		break;
		
		case u_4:
		state = arrow;
		break;
		
		// draw down arrow
		case d_1:
		state = d_2;
		break;
		
		case d_2:
		state = d_3;
		break;
		
		case d_3:
		state = d_4;
		break;
		
		case d_4:
		state = arrow;
		break;
		
		default:
		state = start;
		break;
	}
	
	switch (state) {
		case start:
		break;
		
		case arrow:
		column_val = 0x00;
		column_sel = 0x00;
		break;
		
		case end:
		column_val = 0x00;
		column_sel = 0x00;
		break;
		
		case l_1:
		column_val = 0x7E;
		column_sel = 0xEF;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case l_2:
		column_val = 0x7E;
		column_sel = 0xF7;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case l_3:
		column_val = 0x20;
		column_sel = 0xC3;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case l_4:
		column_val = 0x10;
		column_sel = 0x81;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case r_1:
		column_val = 0x7E;
		column_sel = 0xF7;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case r_2:
		column_val = 0x7E;
		column_sel = 0xEF;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case r_3:
		column_val = 0x04;
		column_sel = 0xC3;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case r_4:
		column_val = 0x08;
		column_sel = 0x81;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case u_1:
		column_val = 0x08;
		column_sel = 0x81;
		transmit_data(column_val); 
		transmit_datab(column_sel);
		break;
		
		case u_2:
		column_val = 0x10;
		column_sel = 0x81;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case u_3:
		column_val = 0x7E;
		column_sel = 0xF7;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case u_4:
		column_val = 0x3C;
		column_sel = 0xFB;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case d_1:
		column_val = 0x08;
		column_sel = 0x81;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case d_2:
		column_val = 0x10;
		column_sel = 0x81;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case d_3:
		column_val = 0x3C;
		column_sel = 0xDF;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		case d_4:
		column_val = 0x7E;
		column_sel = 0xEF;
		transmit_data(column_val);
		transmit_datab(column_sel);
		break;
		
		default:
		break;
	}
	
	return state;
};

// SM2 play music and detect score
enum SM2_States {wait, ON};

int SMTick2(int state)
{
	switch (state)
	{
		case wait:
		state = ON;
		break;
		
		case ON:
		state = ON;
		break;
		
		default:
		state = wait;
		break;
	}
	
	switch (state)
	{
		case wait:
		set_PWM(0);
		break;
		
		case ON:
		set_PWM(song[i]);
		if (i < 32)
		{
			i++;
		}
		else
		{
			PWM_off();
		}
		break;
		
		default:
		break;
	}
	
	return state;	
}

enum SM3_States {display};

int SMTick3(int state)
{
	switch (state)
	{
		case display:
		state = display;
		break;
		
		default:
		state = display;
		break;
	}
	
	//State machine actions
	switch(state)
	{
		case display:
		LCD_DisplayString(1, "BAD APPLE »µÆ»¹û");
		LCD_DisplayString(17, "SCORE:");
		
		// display score
		LCD_Cursor(23);
		LCD_WriteData(c[0]);
		LCD_Cursor(24);
		LCD_WriteData(c[1]);
		LCD_Cursor(25);
		LCD_WriteData(c[2]);
		
		LCD_DisplayString(26, "       ");
		
		break;
		
		default:
		break;
	}
	
	return state;
}

// Implement scheduler code from PES.
int main()
{
	// Set Data Direction Registers
	// Buttons PORTA[0-7], set AVR PORTA to pull down logic
	DDRA = 0xF0; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	 tmp = ~PINA & 0x04;
	
	// Period for the tasks
	unsigned long int SMTick1_calc = 1;
	unsigned long int SMTick2_calc = 500;
	unsigned long int SMTick3_calc = 1000;
	
	//Calculating GCD
	unsigned long int tmpGCD = 1;
	tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
	tmpGCD = findGCD(tmpGCD, SMTick3_calc);
	
	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;
	unsigned long int SMTick2_period = SMTick2_calc/GCD;
	unsigned long int SMTick3_period = SMTick3_calc/GCD;

	//Declare an array of tasks
	static task task1, task2, task3;
	task *tasks[] = {&task1, &task2, &task3 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.
	
	// Task 2
	task2.state = -1;//Task initial state.
	task2.period = SMTick2_period;//Task Period.
	task2.elapsedTime = SMTick2_period;//Task current elapsed time.
	task2.TickFct = &SMTick2;//Function pointer for the tick.
	
	// Task 3
	task3.state = -1;//Task initial state.
	task3.period = SMTick3_period;//Task Period.
	task3.elapsedTime = SMTick3_period;//Task current elapsed time.
	task3.TickFct = &SMTick3;//Function pointer for the tick.
	
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	LCD_init();
	PWM_on();
	adc_init();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}

		while(!TimerFlag);
		TimerFlag = 0;
	}

	// Error: Program should not exit!
	return 0;
}


