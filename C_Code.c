#include <lpc17xx.h>
#include <stdio.h>

/* IR Sensor Configuration */
#define IR1 (1 << 10)  // P2.10 (Port 2, pin 10) for first IR sensor
#define IR2 (1 << 11)  // P2.11 (Port 2, pin 11) for second IR sensor
#define MAXSPD 30.0    // Maximum allowed speed in cm/s
#define DIST 10.0      // Distance between sensors in cm

/* LCD Pin Configuration (4-bit mode) */
#define LCDRS (1 << 0) // Register Select (P0.0)
#define LCDEN (1 << 1) // Enable (P0.1)
#define LCDD4 (1 << 4) // Data bit 4 (P0.4)
#define LCDD5 (1 << 5) // Data bit 5 (P0.5)
#define LCDD6 (1 << 6) // Data bit 6 (P0.6)
#define LCDD7 (1 << 7) // Data bit 7 (P0.7)

/*
            Core Functions 
void EINT3_IRQHandler() - Interrupt handler for IR sensor triggers
  • Manages timing between sensor activations
  • Calculates speed using time difference
  • Triggers LCD display update

void tmrInit() - Timer0 initialization
  • Configures 1μs resolution timer
  • Used for precise time measurements

void ioInit() - GPIO configuration
  • Sets up IR sensor pins as inputs
  • Enables falling-edge interrupts
  • Configures NVIC for interrupt handling

void showSpd(float) - LCD display control
  • Clears display and shows current speed
  • Displays "OVER LIMIT" if speed exceeds MAXSPD
  • Formats speed value with 2 decimal places

void lcdInit() - LCD initialization
  • Sets 4-bit interface mode
  • Configures display settings (2-line, cursor off)
  • Executes standard LCD power-on sequence


            LCD Communication 
void lcdCmd() - Sends control commands to LCD
void lcdDat() - Writes character data to LCD
void lcdStr() - Outputs full strings to display


            Main Program Flow
int main()
  • Initializes hardware peripherals
  • Displays startup message
  • Maintains continuous measurement loop
  • Resets display after each measurement cycle
*/


void wait(unsigned int ms);
void lcdInit(void);
void lcdCmd(unsigned char);
void lcdDat(unsigned char);
void lcdStr(char *);
void tmrInit(void);
void ioInit(void);
void showSpd(float);

volatile unsigned int startT = 0, stopT = 0;
volatile float spd = 0.0;
volatile int measDone = 0;

void EINT3_IRQHandler() {
    static unsigned int lastInt = 0;    
		float timeSec;
    if ((LPC_TIM0->TC - lastInt) > 50000){
        if (LPC_GPIOINT->IO2IntStatF & IR1){
            startT = LPC_TIM0->TC;
            LPC_GPIOINT->IO2IntClr = IR1;
        } 
        else if (LPC_GPIOINT->IO2IntStatF & IR2){
            stopT = LPC_TIM0->TC;
            LPC_GPIOINT->IO2IntClr = IR2;
            timeSec = (stopT - startT) / 1000000.0;
            spd = DIST / timeSec;            
            showSpd(spd);
            measDone = 1;
        }
        lastInt = LPC_TIM0->TC;
    }
}

void tmrInit() {
    LPC_SC->PCONP |= (1 << 1);
    LPC_SC->PCLKSEL0 |= (1 << 2);
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->PR = SystemCoreClock / 1000000 - 1;
    LPC_TIM0->TCR = 0x01;
}

void ioInit() {
    LPC_PINCON->PINSEL4 &= ~(3 << 20);
    LPC_PINCON->PINSEL4 &= ~(3 << 22);
    LPC_GPIO2->FIODIR &= ~(IR1 | IR2);    
    LPC_GPIOINT->IO2IntEnF |= (IR1 | IR2);
    NVIC_EnableIRQ(EINT3_IRQn);
}

void showSpd(float spd) {
    char buf[16];
    lcdCmd(0x01);
    lcdStr("Speed:");    
    sprintf(buf, "%.2f cm/s", spd);
    lcdStr(buf);    
    if (spd > MAXSPD) {
        lcdCmd(0xC0);
        lcdStr("OVER LIMIT");
    }
}

void wait(unsigned int ms) {
		unsigned int i;
    for(i=0; i<ms*(SystemCoreClock/3000); i++);
}

void lcdInit(){	
		int i;
    LPC_GPIO0->FIODIR |= (LCDRS|LCDEN|LCDD4|LCDD5|LCDD6|LCDD7);
    wait(50);
    for(i=0; i<3; i++) {
        LPC_GPIO0->FIOCLR = (LCDD4|LCDD5|LCDD6|LCDD7);
        LPC_GPIO0->FIOSET = ((0x30>>i) & 0xF0);
        LPC_GPIO0->FIOSET = LCDEN;
        wait(1);
        LPC_GPIO0->FIOCLR = LCDEN;
        wait(5);
    }    
    lcdCmd(0x28);
    lcdCmd(0x0C);
    lcdCmd(0x06);
    lcdCmd(0x01);
}

void lcdCmd(unsigned char cmd) {
    LPC_GPIO0->FIOCLR = LCDRS;
    LPC_GPIO0->FIOCLR = (LCDD4|LCDD5|LCDD6|LCDD7);    
    LPC_GPIO0->FIOSET = (cmd & 0xF0);
    LPC_GPIO0->FIOSET = LCDEN;
    wait(1);
    LPC_GPIO0->FIOCLR = LCDEN;    
    LPC_GPIO0->FIOCLR = (LCDD4|LCDD5|LCDD6|LCDD7);    
    LPC_GPIO0->FIOSET = ((cmd<<4) & 0xF0);
    LPC_GPIO0->FIOSET = LCDEN;
    wait(1);
    LPC_GPIO0->FIOCLR = LCDEN;    
    if(cmd <= 2){
			wait(2);
		}
}

void lcdDat(unsigned char dat) {
    LPC_GPIO0->FIOSET = LCDRS;    
    LPC_GPIO0->FIOCLR = (LCDD4|LCDD5|LCDD6|LCDD7);    
    LPC_GPIO0->FIOSET = (dat & 0xF0);
    LPC_GPIO0->FIOSET = LCDEN;    wait(1);
    LPC_GPIO0->FIOCLR = LCDEN;    
    LPC_GPIO0->FIOCLR = (LCDD4|LCDD5|LCDD6|LCDD7);    
    LPC_GPIO0->FIOSET = ((dat<<4) & 0xF0);
    LPC_GPIO0->FIOSET = LCDEN;
    wait(1);
    LPC_GPIO0->FIOCLR = LCDEN;
}

void lcdStr(char *s) {
    while(*s) lcdDat(*s++);
}

int main() {
    SystemInit();
    ioInit();
    tmrInit();
    lcdInit();    
    lcdStr("Speed Meter");
    wait(2000);
    lcdCmd(0x01);
    lcdStr("Ready...");    
    while(1) {
        if(measDone) {
            measDone = 0;
            wait(2000);
            lcdCmd(0x01);
            lcdStr("Ready...");
        }
    }
}
