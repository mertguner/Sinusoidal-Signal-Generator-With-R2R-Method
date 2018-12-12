#include <main.h>

#define A Pin_A6
#define B Pin_A4
#define C Pin_A5
#define D Pin_A7

#define DP1 Pin_A3
#define DP2 Pin_B4
#define DP3 Pin_B5


#define Led_1 Pin_A2
#define Led_2 Pin_A1
#define Led_4 Pin_A0

#define frekans_up Pin_B1
#define frekans_down Pin_B0
#define led_up Pin_B2
#define led_down Pin_B3



unsigned int hangiformul=1,x1=0,frekans=1;
char string[5];
int1 ledupstate=0,leddownstate=0,frekansupstate=0,frekansdownstate=0;
div_t idiv;
long de,de1;


#int_TIMER1
void  TIMER1_isr(void) 
{
set_timer1(65535-(int16)(30968/frekans)); 
output_c(linear_Lookup_table[255-(int)(sintable[x1++]/hangiformul)]);
}



void displaysec(int sec){
switch(sec)
	{
	case 1:output_low(DP1);output_high(DP2);output_high(DP3);break;
	case 2:output_high(DP1);output_low(DP2);output_high(DP3);break;
	case 3:output_high(DP1);output_high(DP2);output_low(DP3);break;
	}
}	

void display(char karakter)
{
switch(karakter)
	{
	case '0':output_low(D);output_low(C);output_low(B);output_low(A);break;
	case '1':output_low(D);output_low(C);output_low(B);output_high(A);break;
	case '2':output_low(D);output_low(C);output_high(B);output_low(A);break;
	case '3':output_low(D);output_low(C);output_high(B);output_high(A);break;
	case '4':output_low(D);output_high(C);output_low(B);output_low(A);break;
	case '5':output_low(D);output_high(C);output_low(B);output_high(A);break;
	case '6':output_low(D);output_high(C);output_high(B);output_low(A);break;
	case '7':output_low(D);output_high(C);output_high(B);output_high(A);break;
	case '8':output_high(D);output_low(C);output_low(B);output_low(A);break;
	case '9':output_high(D);output_low(C);output_low(B);output_high(A);break;
	}		
}	


void displayebas(long sayi)
{
	if(sayi < 10){
	sprintf(string,"%lu",sayi);	
	displaysec(3);
	display(string[0]);	
	delay_ms(1);
	}	
	else if(sayi <100){
	sprintf(string,"%lu",sayi);	
	displaysec(3);
	display(string[1]);
	delay_ms(1);	
	displaysec(2);
	display(string[0]);	
	delay_ms(1);
	}	
	else{
	sprintf(string,"%lu",sayi);	
	displaysec(3);
	display(string[2]);
	delay_ms(1);	
	displaysec(2);
	display(string[1]);	
	delay_ms(1);	
	displaysec(1);
	display(string[0]);	
	delay_ms(1);
	} 
}	

void ledyak(int hangiled)
{
	
	switch(hangiled)
	{
	case 7:output_low(Led_4);output_low(Led_2);output_low(Led_1);break;
	case 6:output_low(Led_4);output_low(Led_2);output_high(Led_1);break;
	case 5:output_low(Led_4);output_high(Led_2);output_low(Led_1);break;
	case 4:output_low(Led_4);output_high(Led_2);output_high(Led_1);break;
	case 3:output_high(Led_4);output_low(Led_2);output_low(Led_1);break;
	case 2:output_high(Led_4);output_low(Led_2);output_high(Led_1);break;
	case 1:output_high(Led_4);output_high(Led_2);output_low(Led_1);break;
	case 0:output_high(Led_4);output_high(Led_2);output_high(Led_1);break;
	}	
}	

void main()
{
   port_b_pullups(TRUE);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_2(T2_DISABLED,17,11);
  // setup_timer_2(T2_DIV_BY_16,17,11);		//36.0 us overflow, 396 us interrupt
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   //enable_interrupts(INT_TIMER2);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   setup_oscillator(OSC_32MHZ);
   
    
    

    while(true){
	    ledyak(hangiformul-1);
	    if(!input(led_up)&&ledupstate==0){ledupstate=1;if(hangiformul!=8)hangiformul++;else hangiformul=1;}
	    else if(input(led_up))ledupstate=0;
	    if(!input(led_down)&&leddownstate==0){leddownstate=1;if(hangiformul!=1)hangiformul--;else hangiformul=8;}
	    else if(input(led_down))leddownstate=0;
	    displayebas(frekans);
	    if(!input(frekans_up)&&frekansupstate==0){frekansupstate=1;if(frekans!=112)frekans++;else frekans=1;}
	    else if(input(frekans_up))frekansupstate=0;
	    if(!input(frekans_down)&&frekansdownstate==0){frekansdownstate=1;if(frekans!=1)frekans--;else frekans=112;}
	    else if(input(frekans_down))frekansdownstate=0;

    }

    
    
}
