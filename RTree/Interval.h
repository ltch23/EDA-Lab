#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>

using namespace std;

/*
	Aquí n es el número de dimensión y Ii es un intervalo cerrado limitado [a, b]
    que describe la extensión del objeto a lo largo de la dimensión i. 
    Alternativamente Ii puede tener uno o ambos extremos iguales al infinito, 
    indicando que el objeto se extiende hacia fuera indefinidamente No-nodos de hoja ... "
*/

class Interval {

public:
	Interval ( float , float );
	Interval ();
	float getMin ();
	float getMax ();	
	void setMin (float);
	void setMax (float);

private:

	float min; //a
	float max; //b

};


Interval::Interval( float min , float max ){
	this->min = min;
	this->max = max;
	cout << "Interval created, min: " << min << "  max:" << max << endl;
}

Interval::Interval(){
	this->min = 0;
	this->max = 0;
	cout << "Interval created" << endl;
}

float Interval::getMin () { return this->min; }
float Interval::getMax () { return this->max; }

void Interval::setMin (float min) { 
	this->min = min;
	cout << " Interval minValue: " << this->min << endl;
}
void Interval::setMax (float max) { 
	this->max = max; 
	cout << " Interval maxValue: " << this->max << endl;
}


#endif //INTERVAL_H