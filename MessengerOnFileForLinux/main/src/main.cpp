#include <iostream>
#include <math.h>

double squareRoot(const double a) {
	double b = sqrt(a);
	if(b != b) { // nan check
		return -1.0;
	}else{
		return sqrt(a);
	}
}


double foo()
{
	int* x = new int(10);
	x[10] = 0;  
}

int main(int argc, char **argv) {
foo();

	//test
	//doajde tu linijke zeby sprawdzic czy pokazuje tylko diff
	//testttt
	std::cout<<"lol"<<std::endl;
	return 0;
}
