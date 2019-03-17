#ifndef SHIFT_H_
#define SHIFT_H_

void transmit_data(unsigned char data)
{
		unsigned char i;
		unsigned char tmp = 0x00;
		
		for (i = 0; i < 8; i++)
		{
			PORTA = 0x80;
			tmp |= ((data >> i) & 0x01);
			tmp  = tmp << 4;
			PORTA |= tmp & 0xF0;
			PORTA |= 0x40;
		}
		PORTA |= 0x20;
		PORTA = 0;
}

void transmit_datab(unsigned char data)
{
	unsigned char i;
	unsigned char tmp = 0x00;
	
	for (i = 0; i < 8; i++)
	{
		PORTB = 0x80;
		tmp |= ((data >> i) & 0x01);
		tmp  = tmp << 4;
		PORTB |= tmp & 0xF0;
		PORTB |= 0x40;
	}
	PORTB |= 0x20;
	PORTB = 0;
}

#endif /* SHIFT_H_ */