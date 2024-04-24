#include <calculus.hpp>
#include <iostream>
#include <numbers>

int main() {
	std::cout << "integrate x*x on 0 to 1 : " << water::calculus::integrate_by_sample<1000000>(
		[](double x) {return x * x; }, water::calculus::range<double>{0, 1}
	) << std::endl;
	std::cout << "integrate x*x + y*y on (0,0) to (2, 2) : " <<
		water::calculus::integrate_by_sample<1000000>(
			[](double x, double y) { return x * x + y*y; },
			water::calculus::area<double>{0, 0, 2, 2}
		) << std::endl;

	// calculate area of circle with radius 1.
	std::cout << "Area of unit circle : " << water::calculus::integrate_by_sample<10000>(
		[](double x, double y) {
			return x* 2 * std::numbers::pi;
		},
		water::calculus::area<double>{0, 0, 1, 1}
	) << std::endl;

	// calculate area of unit sphere
	std::cout << "Area of unit sphere : " << water::calculus::integrate_by_sample<10000>(
		[](double x, double y) {
			return 2 * std::numbers::pi;
		},
		water::calculus::area<double>{-1, 0, 2, 1}
	) << std::endl;
	return 0;
}