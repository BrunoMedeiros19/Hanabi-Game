#include <stdlib.h>
#include <stdio.h>
#include "graphsettings.h"

void inicial_interf(void)
{
   for(k=0,a=0; k<5 ; a+=2 ,k++)
	{
		setColor(15,15);
	    showRectAt(45+k,2+k,5-a,12-a); //perna do H
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(60+k,2+k,5-a,12-a);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(69+k,2+k,5-a,12-a); //perna do H
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(83+k,2+k,5-a,12-a); //perna do A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(92+k,2+k,5-a,12-a);//perna do A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(118+k,2+k,5-a,12-a); //perna do 2 A
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(133+k,2+k,5-a,12-a);//perna do 2 A
	    resetColor();  
	    
	    setColor(15,15);
	    showRectAt(109+k,2+k,5-a,12-a);//perna de N
	    resetColor();
	}
	
	for (k=0; k<12; k++)
	{
		setColor(15,15);
	    showRectAt(97+k,2+k,1,1); //linha diagonal do N
	    resetColor();
	}
	    setColor(15,15);
	    showRectAt(51,6,8,3);
	    resetColor();
	    setColor(15,15);
	    showRectAt(52,7,6,1);
	    resetColor();          /*traco do A*/
	    
	    setColor(15,15);
	    showRectAt(74,2,8,1);
	    resetColor();
	    setColor(15,15);
	    showRectAt(75,3,6,0);
	    resetColor();
	    
	    setColor(15,15);
	    showRectAt(74,6,8,3);
	    resetColor();
	    setColor(15,15);
	    showRectAt(75,7,6,1);
	    resetColor();  
}

