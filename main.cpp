#include "mbed.h"
#include "uLCD_4DGL.h"

AnalogOut aout(PA_4);
AnalogIn ain(D11);
InterruptIn down(D8);
InterruptIn sel(D9);
InterruptIn up(D5);
uLCD_4DGL uLCD(D1, D0, D2);

float rates;
float T = 0.24;
Thread t;
EventQueue queue(32 * EVENTS_EVENT_SIZE);

void add() { 
    rates = rates * 2.0;
    uLCD.locate(0,2);
    uLCD.printf("%f", rates);
}

void minus() {
    rates /= 2;
    uLCD.locate(0,2);
    uLCD.printf("%f", rates);
}

/*void nex() {
    queue.call(generate);
}*/

/*void generate() {
    int ratio = 1;
    
    while (1) {
        if (rates == 1) {
            if (ratio == 240) ratio = 0; // generate triangular wave & S = 2 
            else if (ratio <= 80) aout = ratio / 80.0 / 1.1;                
            else if (ratio > 160) aout = (240 - ratio) / 80.0 / 1.1;
            else aout = ratio / 1.1;
            ratio++;
        }
        if (rates == 1/2) {
            if (ratio == 240) ratio = 0; // generate triangular wave & S = 2 
            else if (ratio <= 40) aout = ratio / 40.0 / 1.1;                
            else if (ratio > 200) aout = (240 - ratio) / 200.0 / 1.1;
            else aout = ratio / 1.1;
            ratio++;
        }
        if (rates == 1/4) {
            if (ratio == 240) ratio = 0; // generate triangular wave & S = 2 
            else if (ratio <= 20) aout = ratio / 20.0 / 1.1;                
            else if (ratio > 220) aout = (240 - ratio) / 220.0 / 1.1;
            else aout = ratio / 1.1;
            ratio++;
        }
        if (rates == 1/8) {
            if (ratio == 240) ratio = 0; // generate triangular wave & S = 2 
            else if (ratio <= 10) aout = ratio / 10.0 / 1.1;                
            else if (ratio > 230) aout = (240 - ratio) / 230.0 / 1.1;
            else aout = ratio / 1.1;
            ratio++;
        }
    }
}*/

/*void sample() {
    if (sample_pt >= 500) { // sample 
            sample_pt = 0; 
            count_loop = 0;
        } 
        else if (count_loop % sample == 0) {
            ADCdata[sample_pt] = ain;
            sample_pt++;
        }
        count_loop++;
        wait_us(T/100);
}*/

int main()
{   
   t.start(callback(&queue, &EventQueue::dispatch_forever));
   rates = 0.125; 
   uLCD.text_width(2); 
   uLCD.text_height(2);
   uLCD.color(RED);
   uLCD.locate(0,2);
   uLCD.printf("%f", rates); 
   
    up.rise(&add); // attach the address of the flip function to the rising edge
   //down.rise(&minus);
  // sel.rise(&nex);
   
}