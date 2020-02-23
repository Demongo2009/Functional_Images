//
// Created by demongo on 31.01.2020.
//

#ifndef PROJETK7_IMAGES_H
#define PROJETK7_IMAGES_H

#include "functional.h"
#include "color.h"
#include "coordinate.h"

typedef long double Fraction;

template<typename T>
using Base_image = std::function<T(const Point)>;

using Region = Base_image<bool>;

using Image = Base_image<Color>;

using Blend = Base_image<Fraction>;

template <typename T>
Base_image<T> constant(const T& t){
	return [t] (Point p) { return t; };
}

//std::function< std::function< bool(const Point) >(const Point) >

//template <>
//Base_image<Image> constant<Image>(const Image& t){
//	return [t] (Point p) { return lift([](Color c){return c==Colors::Caribbean_blue? Colors::Caribbean_blue : c;}, [t] (Point p) {return t(p);}); };
//}
//
//template <>
//Base_image<Blend> constant<Blend>(const Blend& t){
//	return [t] (Point p) { return lift([](Fraction f){return f==0.42? 0.42 : f;}, [t] (Point p) {return t(p);}); };
//}




template <typename T>
Base_image<T> rotate(const Base_image<T>& image, const double& phi){
	return lift(image, [phi](Point p){
			Point given = to_polar(p);
			Point pointRotated = Point(given.first, given.second-phi, true);
			return from_polar(pointRotated);
		} );

}

template <typename T>
Base_image<T> translate(Base_image<T> image, const Vector& v){
	return lift(image, [v](Point p){
		Point translatedPoint = Point(p.first - v.first, p.second - v.second);
		return translatedPoint;
	});
}

template <typename T>
Base_image<T> scale(Base_image<T> image, const double& s){
	return lift(image, [s](Point p){
		Point scaledPoint = Point(p.first/s, p.second/s);
		return scaledPoint;
	} );
}

template <typename T>
Base_image<T> circle(const Point& q, const double& r, const T& inner, const T& outer){
	return [q,r,inner,outer] (Point p) {
//		Point givenPolar = to_polar(p);
		return (distance(p,q)<=r)? inner : outer;
	};
}

template <typename T>
Base_image<T> checker(const double& d, const T& this_way, const T& that_way){
//	return [d, this_way, that_way] (Point p) {
//		Point scaledPoint = Point(p.first/d, p.second/d);
//		return (int)(floor(scaledPoint.first)+floor(scaledPoint.second))%2==0 ? this_way : that_way;
//	};
	return scale<T>([d, this_way, that_way] (Point p) {
		return (int)(floor(p.first)+floor(p.second))%2==0 ? this_way : that_way;},
				d
	);
}

template <typename T>
Base_image<T> polar_checker(const double& d, const int& n, const T& this_way, const T& that_way){
//	return  compose(
//				to_polar,
//				[d,n](Point p){
//			return Point(p.first, p.second*(((double )n/2)/M_PI),true);
//			},
//			checker<T>(d,this_way,that_way));

//	return [n,d, this_way, that_way] (Point p) {
//		Point scaledPoint = Point(p.first/d, p.second/d);
//		Point givenPolar = to_polar(scaledPoint);
//		Point mappedOnPolar = Point(givenPolar.first, givenPolar.second*((n/2.0)/(M_PI)),false);
//
//		return (int)(floor(mappedOnPolar.first)+floor(mappedOnPolar.second))%2==0 ? this_way : that_way;
//	}
//	;

	return scale<T>(
			compose(to_polar,
			[d,n](Point p){
				return Point(p.first, p.second*((n/2.0)/M_PI));
		},
		[d](Point p){return Point(p.first*d,p.second*d);},
			checker(d,this_way,that_way)),
			d
			);

}

template <typename T>
Base_image<T> rings(const Point& q, const double& d, const T& this_way, const T& that_way){
	return lift([this_way, that_way,d](Point p){
		Point scaledPoint = Point(p.first/d, p.second/d);
			return (int)(floor(distance(scaledPoint)))%2==0 ? this_way : that_way;
		},[q](Point p){
		Coordinate shiftX = q.first;
		Coordinate shiftY = q.second;
		Point translatedPoint = Point(p.first - shiftX, p.second - shiftY);
		return translatedPoint;
	});
//	Vector vector = Vector (q.first,q.second);
//	auto f = std::bind(translate, std::placeholders::_1, vector);
//	return lift(translate,
//			constant<Color>(Colors::Caribbean_blue)
//			,
//			constant<Vector>(vector)
//			);
}


template <typename T>
Base_image<T> vertical_stripe(const double& d, const T& this_way, const T& that_way){
	return [d,this_way,that_way](Point p){
		return (std::abs(p.first) <= d/2) ? this_way : that_way;
	};
}

///////////////////////////////////////////////////////

Image cond(const Region& region,const Image& this_way,const Image& that_way);
Image lerp(const Blend& blend, const Image& this_way, const Image& that_way);
Image darken(const Image& image, const Blend& blend);
Image lighten(const Image& image, const Blend& blend);


#endif //PROJETK7_IMAGES_H
