#include <calculus.hpp>
#include <iostream>

int main() {
	std::cout << "integrate x*x on 0 to 1 : " << water::calculus::integrate_by_sample<1000000>(
		[](double x) {return x * x; }, water::calculus::range<double>{0, 1}
	) << std::endl;
	std::cout << "integrate x*x + y*y on (0,0) to (2, 2) : " <<
		water::calculus::integrate_by_sample<1000000>(
			[](double x, double y) { return x * x + y*y; },
			water::calculus::area<double>{0, 0, 2, 2}
		) << std::endl;
	return 0;
}