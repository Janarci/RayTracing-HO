#include "PoolWorkerThread.h"

#include "camera.h"
#include "material.h"

PoolWorkerThread::PoolWorkerThread(int id, int lCol, int uCol, int lRow, int uRow)
{

	this->id = id;
		this->lCol = lCol;
		this->uCol = uCol;
		this->lRow = lRow;
		this->uRow = uRow;
		finish = false;
}

void PoolWorkerThread::setValues(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth,
	int imageHeight)
{

	this->cam = cam;
	this->world = world;
	this->bounces = bounces;
	this->samplesPerPixel = samplesPerPixel;
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;
}

color PoolWorkerThread::ray_color(const ray& r, const hittable_list& world, int bounces)
{

	hit_record rec;

	if (bounces <= 0)
		return color(0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;

		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, bounces - 1);

		return color(0, 0, 0);
	}

	vec3 unit_direction = vec3::unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.getY() + 1.0);
	return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
}

void PoolWorkerThread::threadTest(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth,
	int imageHeight, RTImage* image, int lRow, int uRow)
{
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = lRow; i < uRow; ++i) {
			color pixel_color(0, 0, 0);

			for (int s = 0; s < samplesPerPixel; ++s) {
				auto u = (i + rtweekend::random_double()) / (imageWidth - 1);
				auto v = (j + rtweekend::random_double()) / (imageHeight - 1);
				ray r = cam->get_ray(u, v);
				pixel_color = pixel_color + ray_color(r, world, bounces);
			}
			image->setPixel(i, j, pixel_color.getX(), pixel_color.getY(), pixel_color.getZ(), samplesPerPixel);
			//colorUtils::write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
}

void PoolWorkerThread::setImage(RTImage* image)
{
	this->image = image;
}

void PoolWorkerThread::run()
{

	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

		for (int j = uCol - 1; j >= lCol; --j) {
		    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		    for (int i = lRow; i < uRow; ++i) {
		        color pixel_color(0, 0, 0);

		        for (int s = 0; s < samplesPerPixel; ++s) {
		            auto u = (i + rtweekend::random_double()) / (imageWidth - 1);
		            auto v = (j + rtweekend::random_double()) / (imageHeight - 1);
		            ray r = cam->get_ray(u, v);
		            pixel_color = pixel_color +  ray_color(r, world, bounces);
		        }
		        while (image->critical)
		        {
			        
		        }
		        image->setPixel(i, j, pixel_color.getX(), pixel_color.getY(), pixel_color.getZ(), samplesPerPixel);
		        //colorUtils::write_color(std::cout, pixel_color, samples_per_pixel);
		    }
		}
	finish = true;
}
