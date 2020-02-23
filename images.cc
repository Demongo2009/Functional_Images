//
// Created by demongo on 02.02.2020.
//

#include "images.h"

Image cond(const Region& region,const Image& this_way,const Image& that_way){
	return lift(
			[](bool b, Color thisWayColor, Color thatWayColor){
				return b? thisWayColor: thatWayColor;
			},
			region, this_way, that_way);
}

Image lerp(const Blend& blend, const Image& this_way, const Image& that_way){
	return lift(
			[](Fraction w, Color thisWayColor, Color thatWayColor){
				return thisWayColor.weighted_mean(thatWayColor,w);
			},
			blend,this_way,that_way
	);
}

Image darken(const Image& image, const Blend& blend){
	return lerp(
			blend,
			image,
	constant<Color>(Colors::black)
	);
}

Image lighten(const Image& image, const Blend& blend){
	return lerp(
			blend,
			image,
			constant<Color>(Colors::white)
	);
}