/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"
#include "pwm.h"
#define PWM_BASE XPAR_PWM_0_S00_AXI_BASEADDR

void colorChanger();
int main()
{
    init_platform();

    colorChanger();
    PWM_mWriteReg(PWM_BASE, 0, 0);
    PWM_mWriteReg(PWM_BASE, 4, 0);
    PWM_mWriteReg(PWM_BASE, 8, 255);
    printf("%lu\n",PWM_mReadReg(PWM_BASE, 0));
    printf("%lu\n",PWM_mReadReg(PWM_BASE, 4));
    printf("%lu\n",PWM_mReadReg(PWM_BASE, 8));
    char d[100];

    print("Hello World\n\r");
    scanf("%s",d);

    print("done.\n\r");
    cleanup_platform();
    return 0;
}
void colorChanger()
{
	long int r,g,b;
	r = g = b = 0;
	int i,j,k;
	i = j = k = 1;
	while (1)
	{
		r = (r+i)%(255*25000);
		g = (g+j)%(255*50000);
		b = (b+k)%(255*100000);

		if (r == 0)
			i *= -1;
		if (g == 0)
			j *= -1;
		if (b == 0)
			k *= -1;

		PWM_mWriteReg(PWM_BASE, 0, r/25000);
		PWM_mWriteReg(PWM_BASE, 4, g/50000);
		PWM_mWriteReg(PWM_BASE, 8, b/100000);
	}

}
