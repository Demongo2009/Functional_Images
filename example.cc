//
//#include "images.h"
//#include "bmp.h"
//#include <cassert>
//#include <cmath>
//#include <cstdint>

#include "functional.h"
#include "images.h"
#include "bmp.h"
#include "color.h"
#include "coordinate.h"
#include <cassert>
#include <cmath>
#include <cstdint>

int main()
{
  const uint32_t width = 400;
  const uint32_t height = 300;
  const Region rc = circle(Point(50., 100.), 10., true, false);
  const Image vs = vertical_stripe(100, Colors::Caribbean_blue, Colors::blue);
  const Blend cb = constant<Fraction>(.42);

  create_BMP("constant1.bmp",
             width,
             height,
             constant(Colors::Caribbean_blue));
  create_BMP("rotate1.bmp",
             width,
             height,
             rotate(vs, M_PI / 4.));
  create_BMP("translate1.bmp",
             width,
             height,
             translate(vs, Vector(100., 0.)));
  create_BMP("scale1.bmp",
             width,
             height,
             scale(vs, 2.));
  create_BMP("circle1.bmp",
             width,
             height,
             circle(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("checker1.bmp",
             width,
             height,
             checker(10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("polar_checker1.bmp",
             width,
             height,
             polar_checker(10., 4, Colors::Caribbean_blue, Colors::blue));
  create_BMP("rings1.bmp",
             width,
             height,
             rings(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("vertical_stripe1.bmp",
             width,
             height,
             vs);
  create_BMP("cond1.bmp",
             width,
             height,
             cond(rc, constant(Colors::Caribbean_blue), constant(Colors::blue)));
  create_BMP("lerp1.bmp",
             width,
             height,
             lerp(cb, constant(Colors::blue), constant(Colors::white)));
  create_BMP("dark_vs1.bmp",
             width,
             height,
             darken(vs, cb));
  create_BMP("light_vs1.bmp",
             width,
             height,
             lighten(vs, cb));

  assert(compose()(42) == 42);
  assert(compose([](auto x) { return x + 1; },
                 [](auto x) { return x * x; })(1) == 4);

  const auto h1 = [](auto a, auto b) { auto g = a * b; return g; };
  const auto h2 = [](auto a, auto b) { auto g = a + b; return g; };
  const auto f1 = [](auto p) { auto a = p; return a; };
  const auto f2 = [](auto p) { auto b = p; return b; };
  assert(lift(h1, f1, f2)(42) == 42 * 42);
  assert(lift(h2, f1, f2)(42) == 42 + 42);
}
