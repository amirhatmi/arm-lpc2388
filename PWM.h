#ifndef __PWM_H
#define __PWM_H

#define PWM_CYCLE		1000

#define TCR_CNT_EN		0x00000001
#define TCR_PWM_EN		0x00000008

#define PWMSEL2			1 << 2
#define PWMSEL3			1 << 3
#define PWMSEL4			1 << 4
#define PWMSEL5			1 << 5
#define PWMSEL6			1 << 6

#define PWMENA1			1 << 9
#define PWMENA2			1 << 10
#define PWMENA3			1 << 11
#define PWMENA4			1 << 12
#define PWMENA5			1 << 13
#define PWMENA6			1 << 14

#define LER0_EN			1 << 0
#define LER1_EN			1 << 1
#define LER2_EN			1 << 2
#define LER3_EN			1 << 3
#define LER4_EN			1 << 4
#define LER5_EN			1 << 5
#define LER6_EN			1 << 6



void PWM0init0(void);

void PWM_Start(int ChannelNum);

void PWM0_WidthSet1(double Width);
void PWM0_WidthSet2(double Width);




#endif
