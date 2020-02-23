//#include <iostream>
//#include <cassert>
//#include "images.h"
//
//int main() {
//	const uint32_t width = 400;
//  const uint32_t height = 300;
//  const Region rc = circle(Point(50., 100.), 10., true, false);
//  const Image vs = vertical_stripe(100, Colors::Caribbean_blue, Colors::blue);
//  const Blend cb = constant<Fraction>(.42);
//
//  create_BMP("constant.bmp",
//             width,
//             height,
//             constant(Colors::Caribbean_blue));
//  create_BMP("rotate.bmp",
//             width,
//             height,
//             rotate(vs, M_PI / 4.));
//
//
//	assert(compose()(42) == 42);
//   assert(compose([](auto x) { return x + 1; },
//                 [](auto x) { return x * x; })(1) == 4);
//
//	const auto h1 = [](auto a, auto b) { auto g = a * b; return g; };
//	const auto h2 = [](auto a, auto b) { auto g = a + b; return g; };
//	const auto f1 = [](auto p) { auto a = p; return a; };
//	const auto f2 = [](auto p) { auto b = p; return b; };
//	assert(lift(h1, f1, f2)(42) == 42 * 42);
//	assert(lift(h2, f1, f2)(42) == 42 + 42);
//
//}
