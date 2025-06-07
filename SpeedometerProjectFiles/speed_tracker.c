#include <lpc17xx.h>
#include <stdio.h>

#define IR1 (1 << 10)
#define IR2 (1 << 11)
#define MAXSPD 30.0
#define DIST 10.0

#define LCDRS (1 << 0)
#define LCDEN (1 << 1)
#define LCDD4 (1 << 4)
#define LCDD5 (1 << 5)
#define LCDD6 (1 << 6)
#define LCDD7 (1 << 7)

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
