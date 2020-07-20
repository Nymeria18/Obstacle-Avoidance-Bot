# include <at89x52.h>
# include <string.h>

sbit IN1=P2^7;
sbit IN2=P2^6;
sbit IN3=P2^4;
sbit IN4=P2^3;

sfr16 DPTR =0x82;
sbit triger=P3^1;
sbit echo=P1^2;


unsigned int ch,high_byte,low_byte,high_byte,distance;
unsigned int target_range=0,d=0,left=0,right=0;
unsigned int range=0;
unsigned int s=0;
bit d1=0,d2=0,d3=0,sm1=0,sm2=0;
void init();
void delay(unsigned int delay_ms);

void get_range();
void process();


void main()
{ 
	init();
	triger=0;
	echo=1;
	triger=1;
	delay(10);
	triger=0;
	delay(41);
	d1=1;
	delay(2);
	P2=0x00;
	delay(20);
	TMOD=0x09;//timer0 in 16 bit mode with gate enable
	TR0=1;//timer run enabled
	TH0=0x00;
	TL0=0x00;
	P3=0x04;
		IN1=0;
		IN2=0;
		IN3=0;
		IN4=0;
		left=0;
		right=0;
	
	while(1)
	{
		get_range();
		delay(500);
		process();		
	}
}

void init()
	{
		TMOD=0X09;
		TR0=1;
		TH0=0X00;
		TL0=0X00;
	}

void delay(unsigned int delay_ms)
	{
	unsigned int count,i;
		for(count = 0;count<delay_ms;count++)
		{
			for(i =0;i < 120;i++);
		}
		delay_ms--;
	}
  
void get_range()
	{
		TH0=0X00;
		TL0=0X00;
		triger=1;
		delay(10);
		triger=0;
		while(!echo);
		while(echo);
		DPH=TH0;
		DPL=TL0;
		TH0=0XFF;
		TL0=0XFF;
		if(DPTR<35000)
		range=DPTR/78.66;
		else
		range=0;
	}

void process()
{ 

if(range<=150)
	{
	  	if(sm2==1)
		{
			IN1=0;
			IN2=0;
			IN3=0;
			IN4=0;
			sm2=0;
			delay(100);
		}
		IN1=1;
		IN2=0;
		IN3=0;
		IN4=1;
		sm1=1;
		delay(1000);
	  	left++;

	  	if(left<=3)
		{
			IN1=0;
			IN2=0;
			IN3=1;
			IN4=0;
		}
		
		else if(left==4)
		{
			IN1=0;
			IN2=1;
			IN3=0;
			IN4=0;
			left=0;
		}

		delay(2000);
		IN1=0;
		IN2=0;
		IN3=0;
		IN4=0;

	}
	else 
  if(range>40 ||range==0)
	{
		if(sm1==1)
		{
			IN1=0;
			IN2=0;
			IN3=0;
			IN4=0;
			sm1=0;
			delay(100);
		}
		IN1=0;
		IN2=1;
		IN3=1;
		IN4=0;
		sm2=1;
    }
   if(range<2 )
	{
		IN1=0;
		IN2=0;
		IN3=0;
		IN4=0;
		sm1=1;
		sm2=1;
	}
    else 
  if(range>40 ||range==0)
	{
		if(sm1==1)
		{
			IN1=0;
     		IN2=0;
			IN3=0;
			IN4=0;
			sm1=0;
			delay(100);
		}
		IN1=0;
		IN2=1;
		IN3=1;
		IN4=0;
		sm2=1;
	}
 else 
   if(range<20 && range>2)
	{
	  	if(sm2==1)
		{
			IN1=0;
			IN2=0;
			IN3=0;
     		IN4=0;
			sm2=0;
			delay(100);
		}
		IN1=1;
		IN2=0;
		IN3=0;
		IN4=1;
		sm1=1;
		delay(1000);
	  	left++;

	  	if(left<=3)
		{
			IN1=0;
			IN2=0;
			IN3=1;
			IN4=0;
		}
		
		else if(left==4)
		{
			IN1=0;
			IN2=1;
     		IN3=0;
			IN4=0;
			left=0;
		}

		delay(2000);
		IN1=0;
		IN2=0;
		IN3=0;
        IN4=0;	}
	
}