#include "camera.h"

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture,
	double focus_dist)
{
	auto theta = rtweekend::degrees_to_radians(vfov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = aspect_ratio * viewport_height;

	w = vec3::unit_vector(lookfrom - lookat);
	u = vec3::unit_vector(vec3::cross(vup, w));
	v = vec3::cross(w, u);

	origin = lookfrom;
	horizontal = u * focus_dist * viewport_width;
	vertical = v * focus_dist * viewport_height ;
	lower_left_corner =  origin - horizontal / 2 - vertical / 2 - w *  focus_dist;

	lens_radius = aperture / 2;
}

ray camera::get_ray(double s, double t)
{
        vec3 rd = vec3::random_in_unit_disk() * lens_radius ;
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(
            origin + offset,
            lower_left_corner +  horizontal * s + vertical * t - origin - offset
        );
}

