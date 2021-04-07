#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_4);
AnalogIn ain(D11);
InterruptIn dwn(D8);
InterruptIn sel(D9);
InterruptIn up(D5);
uLCD_4DGL uLCD(D1, D0, D2);

float rates;
float T = 0.24;
int sample_ = 240*50 / T / 500;
int ratio;
Thread t;
float ADCdata[500];
EventQueue queue(32 * EVENTS_EVENT_SIZE);

void add() { 
    rates *= 2.0;
    uLCD.locate(0,2);
    uLCD.printf("%f", rates);
}

void down() {
    rates /= 2.0;
    uLCD.locate(0,2);
    uLCD.printf("%f", rates);
}

void gener() {
    int ratio = 1;

    while (rates == 1) {
        if (ratio == 240*50) ratio = 0;  
        if (ratio <= 80*50) aout = ratio / 80.0 / 1.1 / 50;                
        if (ratio > 160*50) aout = (240*50 - ratio) / 80.0 / 1.1 / 50;
        if (ratio > 80*50 && ratio <= 160*50) aout = 1 / 1.1;
        ratio++;
        wait_us(T/240);
    }
    while (rates == 0.5) {
        if (ratio == 240*50) ratio = 0;  
        if (ratio <= 40*50) aout = ratio / 40.0 / 1.1 / 50;                
        if (ratio > 200*50) aout = (240*50 - ratio) / 200.0 / 1.1 / 50;
        if (ratio > 40*50 && ratio <= 200*50) aout = 1/1.1;
        ratio++;
        wait_us(T/240);
    }
    while (rates == 0.25) {
        if (ratio == 240*50) ratio = 0;  
        if (ratio <= 20*50) aout = ratio / 20.0 / 1.1 / 50;                
        if (ratio > 220*50) aout = (240*50 - ratio) / 220.0 / 1.1 / 50;
        if (ratio > 20*50 && ratio <= 220*50) aout = 1/1.1;
        ratio++;
        wait_us(T/240);
    }
    while (rates == 0.125) {
        if (ratio == 240*50) ratio = 0; 
        if (ratio <= 10*50) aout = ratio / 10.0 / 1.1 / 50;                
        if (ratio > 230*50) aout = (240*50 - ratio) / 230.0 / 1.1 / 50;
        if (ratio > 10*50 && ratio <= 230*50) aout = 1 / 1.1;
        ratio++;  
        wait_us(T/240);
    }
   // queue.call(&sample);
}

void sample() {
    int sample_pt = 1;
    int count_loop = 1;

    while (1) {
        if (sample_pt >= 500) { // sample 
            sample_pt = 0; 
            count_loop = 0;
        } 
        else if (count_loop % sample_ == 0) {
            ADCdata[sample_pt] = ain;
            sample_pt++;
        }
    count_loop++;
    }
}

int main()
{   
   int l;

   t.start(callback(&queue, &EventQueue::dispatch_forever));
   rates = 0.125; 
   uLCD.text_width(2); 
   uLCD.text_height(2);
   uLCD.color(RED);
   uLCD.locate(0,2);
   uLCD.printf("%f", rates); 
   up.rise(queue.event(add)); // attach the address of the flip function to the rising edge
   dwn.rise(queue.event(down));
   sel.rise(queue.event(gener));
  // for (l = 0; l < 500; l++)
    //   printf("%f\r\n", ADCdata[l]);
}