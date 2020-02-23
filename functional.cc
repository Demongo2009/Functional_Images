//
// Created by demongo on 02.02.2020.
//
#include "functional.h"

auto compose(){
	return [&] (auto x) {return x;};
};