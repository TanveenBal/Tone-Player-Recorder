// GPIO Clock
#define RCGCGPIO (*((volatile unsigned long *)0x400FE608))

//Keypad GPIO
#define PORTB_DEN (*((volatile unsigned long *) (0x4000551C)))
#define PORTB_DIR (*((volatile unsigned long *) (0x40005400)))

#define PORTC_DEN (*((volatile unsigned long *) (0x4000651C)))
#define PORTC_DIR (*((volatile unsigned long *) (0x40006400)))

#define PORTD_DEN (*((volatile unsigned long *) (0x4000751C)))
#define PORTD_DIR (*((volatile unsigned long *) (0x40007400)))

#define PORTE_DEN (*((volatile unsigned long *) (0x4002451C)))
#define PORTE_DIR (*((volatile unsigned long *) (0x40024400)))

#define PORTF_DEN (*((volatile unsigned long *) (0x4002551C)))
#define PORTF_DIR (*((volatile unsigned long *) (0x40025400)))

#define PORTB_PDR (*((volatile unsigned long *) (0x40005514))) //Pull-Down Select port B
#define PORTC_PDR (*((volatile unsigned long *) (0x40006514))) //Pull-Down Select port C
#define PORTD_PDR (*((volatile unsigned long *) (0x40007514))) //Pull-Down Select port D
#define PORTF_PDR (*((volatile unsigned long *) (0x40025514))) //Pull-Down Select port F


#define PORTB_DATA_3 (*((volatile unsigned long *) (0x40005020)))
#define PORTC_DATA_4 (*((volatile unsigned long *) (0x40006040)))
#define PORTC_DATA_5 (*((volatile unsigned long *) (0x40006080)))
#define PORTC_DATA_6 (*((volatile unsigned long *) (0x40006100)))
#define PORTC_DATA_7 (*((volatile unsigned long *) (0x40006200)))
#define PORTD_DATA_6 (*((volatile unsigned long *) (0x40007100)))
#define PORTF_DATA_3 (*((volatile unsigned long *) (0x40025020)))
#define PORTF_DATA_4 (*((volatile unsigned long *) (0x40025040)))

//LED
#define PORTE_DATA_0 (*((volatile unsigned long *) (0x40024004)))
#define PORTF_DATA_1 (*((volatile unsigned long *) (0x40025008)))
#define PORTF_DATA_2 (*((volatile unsigned long *) (0x40025010)))

// I2C GPIO
//#define PORTD_DEN (*((volatile unsigned long *) (0x4000751C))) //Digital enable register for port D
//#define PORTD_DIR (*((volatile unsigned long *) (0x40007400))) //Data direction register for port D
#define PORTD_AFSEL (*((volatile unsigned long *)(0x40007420))) // Enable alternate function
#define PORTD_PCTL (*((volatile unsigned long *) (0x4000752C))) // Control/choose alternate function
#define PORTD_DR (*((volatile unsigned long *) (0x4000750C))) //Open drain select

#define I2C3_MSA (*((volatile unsigned long *) (0x40023000))) //Specify address direction byte
#define I2C3_MCS (*((volatile unsigned long *) (0x40023004))) //Control bits for reading and writing
#define I2C3_MDR (*((volatile unsigned long *) (0x40023008))) //Control transmit or receive state
#define I2C3_MTPR (*((volatile unsigned long *) (0x4002300C))) //Set timer for SCL clock

// PWM GPIO
#define PORTB_PCTL (*((volatile unsigned long *) (0x4000552C))) // Control/choose alternate function
#define PORTB_AFSEL (*((volatile unsigned long *) (0x40005420))) // Enable alternate function
//#define PORTB_DEN (*((volatile unsigned long *) (0x4000551C))) //Digital enable register for port B
//#define PORTB_DIR (*((volatile unsigned long *) (0x40005400))) //Data direction register for port B

// PWM
#define RCGCPWM (*((volatile unsigned long *)0x400FE640))

#define PWM0_ENABLE (*((volatile unsigned long *) (0x40028008)))
#define PWM0_LOAD (*((volatile unsigned long *) (0x40028050)))
#define PWM0_CTL (*((volatile unsigned long *) (0x40028040)))
#define PWM0_CMPA (*((volatile unsigned long *) (0x40028058)))
#define PWM0_GENA (*((volatile unsigned long *) (0x40028060)))
#define PWM0_RCC (*((volatile unsigned long *) (0x400FE060)))

void Delay(long d){while(--d);}

void PWM_init(){
    PWM0_RCC = 0xE0000; //Drive PWM divisor to system clock 0001 1110 0000 0000 0000 0000
    PWM0_CTL = 0x00;    //Count down mode (mode is 2nd bit = 0 for count down)
    PWM0_GENA = 0x8C;   //0000 1000 1100
                        //chose action drive pwmA high which is the 3rd and 4th bit
                        //chose action drive pwmA low which is the 7th and 8th bit
    PWM0_LOAD = 100;    //12 bit ADC conversion therefore range 4096
    PWM0_CMPA = 0;      //Initialize comparator A
    PWM0_CTL = 0x01;    // Enable signal generator blocks (1st bit = 1)
    PWM0_ENABLE = 0x01; //0000 0001 Enable pulses
}

void I2C_init(){
    PORTD_AFSEL = 0x03; // 0000 0011 Alternate function select for D0 and D1
    PORTD_PCTL = 0x33;  // 0011 0011
                        // Bits 0-3: I2C3SCL
                        // Bits 4-7: I2C3SDA
    PORTD_DR = 0x02;    // Setting bit 1 for PD1 to open drain pull up
    //PORTD_DEN = 0x03; // Digital enable D0 and D1
    //I2C3_MTPR =
}

void GPIO_init(){
    PORTB_AFSEL = 0x40; //0100 0000 = 0x40
    PORTB_PCTL = 0x04000000; //bits 27-24 = 0100 = 0x04000000 (for B6 4th alternate function)
    PORTB_DEN = 0x48; //0100 1000
    PORTB_DIR = 0x48; //0100 1000
    PORTC_DEN = 0xF0; //1111 0000
    PORTC_DIR = 0x70; //0111 0000
    PORTD_DEN = 0x43; //0100 0011
    PORTD_DIR = 0x00; //0000 0000
    PORTF_DEN = 0x1E; //0001 1110
    PORTF_DIR = 0x06; //0000 0110
    PORTE_DEN = 0x01; //0000 0001
    PORTE_DIR = 0x01; //0000 0001

    PORTB_PDR = 0x08; //0000 1000
    PORTC_PDR = 0xF0; //1111 0000
    PORTD_PDR = 0x40; //0100 0000
    PORTF_PDR = 0x18; //0001 1000
}


void clock_init(){
    //all clocks on
    RCGCGPIO = 0x3E; //0011 1111 = 0x3F
    RCGCPWM = 0x01;  //Turn on PWM0
}

int rec[5000];
int len = 0;

void Music(int i){
    PWM0_LOAD = i;
    PWM0_CMPA = PWM0_LOAD/2;
    Delay(10000);
}

void Record(int i){
    rec[len] = i;
    ++len;
}

void KEYPADHELP(int i1, int i2, int i3, int i4){
    if (PORTC_DATA_7 == 0x80){
        if (PORTE_DATA_0 == 0x01){
            Music(i1);
        }
        else if (PORTF_DATA_1 == 0x02){
            Music(i1);
            Record(i1);
        }
    }
    if (PORTD_DATA_6 == 0x40){
        if (PORTE_DATA_0 == 0x01){
            Music(i2);
        }
        else if (PORTF_DATA_1 == 0x02){
            Music(i2);
            Record(i2);
        }
    }
    if (PORTF_DATA_3 == 0x08){
        if (PORTE_DATA_0 == 0x01){
            Music(i3);
        }
        else if (PORTF_DATA_1 == 0x02){
            Music(i3);
            Record(i3);
        }
    }
    if (PORTF_DATA_4 == 0x10){
        if (i4 == 3){
            //Play recorded sequence
            int i = 0;
//            for (; i < len; ++i){
//                Music(rec[i]);
//                rec[i] = 0;
//            }
//            len = 0;
        }
        else if (i4 == 0){
            PORTE_DATA_0 = 0x01;
            PORTF_DATA_1 = 0x00;
            PORTF_DATA_2 = 0x00;
        }
        else if (i4 == 1){
            PORTE_DATA_0 = 0x00;
            PORTF_DATA_1 = 0x02;
            PORTF_DATA_2 = 0x00;
        }
        else if (i4 == 2){
            PORTE_DATA_0 = 0x00;
            PORTF_DATA_1 = 0x00;
            PORTF_DATA_2 = 0x04;
        }
        else{
            if (PORTE_DATA_0 == 0x01){
                Music(i4);
            }
            else if (PORTF_DATA_1 == 0x02){
                Music(i4);
                Record(i4);
            }
        }
    }
}

void KEYPAD(){
    PORTB_DATA_3 = 0x0;
    PORTC_DATA_4 = 0x0;
    PORTC_DATA_5 = 0x0;
    PORTC_DATA_6 = 0x0;
    PORTB_DATA_3 = 0x08;
    KEYPADHELP(1000, 1200, 1400, 0);;
    PORTB_DATA_3 = 0x0;

    PORTC_DATA_4 = 0x10;
    KEYPADHELP(2000, 2200, 2400, 1);
    PORTC_DATA_4 = 0x0;

    PORTC_DATA_5 = 0x20;
    KEYPADHELP(3000, 3200, 0, 2);
    PORTC_DATA_5 = 0x0;

    PORTC_DATA_6 = 0x40;
    KEYPADHELP(0, 0, 0, 3);
    PORTC_DATA_6 = 0x0;
}
/**
 * main.c
 */
int main(void)
{
    clock_init();
    PWM_init();
    GPIO_init();
    PORTE_DATA_0 = 0x01;
    int j = 0;
    for(; j < 5000; ++j){
        rec[j] = 0;
    }
    while(1){
        PWM0_LOAD = 0;
        PWM0_CMPA = 0;
        KEYPAD();
    }
    return 0;
}
