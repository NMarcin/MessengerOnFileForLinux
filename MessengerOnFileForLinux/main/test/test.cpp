#include <gtest/gtest.h>
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

TEST(squareRoot, PositiveNos) {
	EXPECT_EQ(5,squareRoot(25));
}

TEST(squareRoot, NegativeNos) {
	EXPECT_EQ(6,squareRoot(25));
}

int main(int argc, char **argv) {
	foo();
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
