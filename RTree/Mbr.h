#ifndef MBRH_H
#define MBRH_H

/*Mbr coleccion de N intervalos(interval),
N= dimensiones */


class Mbr{
private:
    Interval * mbr_intervals;
public:
    Mbr(int,float**);
    Interval* getIntervals();
    float findArea(int);
    float findNewArea();
    bool  checkOverlap(Mbr, int);
    void refreshIntervals(mbr,int);
   
};

Mbr::Mbr(int N, float **m){
    this->intervals=new Interval[N];
    for(int i=0;i<N;i++){
        this.intervals[i].setMin(m[1][i]);
        this.intervals[i].setMax(m[2][i]);
    }
    cout<<"Mbr created"<<endl;
}

Interval* Mbr::getIntervals(){
	return this->intervals; 
}

float Mbr::findArea( int N ){
	float area = 1;
	for(int i=0 ; i<N ; i++)
		area *= intervals[i].getMax() - intervals[i].getMin();
	return area;
}

float Mbr::findNewArea( Mbr newMbr , int N ){
	float area = 1;
	Interval *intervals1 = newMbr.getIntervals();
	for(int i=0 ; i<N ; i++)	{
		float min = intervals1[i].getMin() < this->intervals[i].getMin() ? intervals1[i].getMin() : intervals[i].getMin(); 
		float max = intervals1[i].getMax() > this->intervals[i].getMax() ? intervals1[i].getMax() : intervals[i].getMax(); 
		area *= min - max;
	}
	return area;
};

bool Mbr::checkOverlap( Mbr mbr , int N ){
	Interval *intervals1 = mbr.getIntervals();
	for(int i=0 ; i<N ; i++){
		if( intervals[i].getMin() > this->intervals[i].getMax() || intervals[i].getMax() < this->intervals[i].getMin() )
			return false;
	}
	return true;
}

void Mbr::refreshIntervals( Mbr mbr , int N ){
	for( int i=0 ; i<N ; i++ ){
		intervals[i].setMax( intervals[i].getMax() >= mbr.getIntervals()[i].getMax() ? intervals[i].getMax() : mbr.getIntervals()[i].getMax() );
		intervals[i].setMin( intervals[i].getMin() >= mbr.getIntervals()[i].getMin() ? intervals[i].getMin() : mbr.getIntervals()[i].getMin() );
	}
}

#endif //MBRH_H