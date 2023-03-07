
#pragma once

#include <iostream>

#include "rtweekend.h"

class colorUtils{
public:
   static void write_color(std::ostream& out, color pixel_color, int samples_per_pixel);
};
