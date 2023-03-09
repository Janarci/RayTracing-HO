 #include <iostream>



#include "rtweekend.h"

#include "camera.h"
#include "colorUtils.h"
#include "ray.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "RTImage.h"
#include "PoolWorkerThread.h"


hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int i = 0; i < 3; ++i)
    {

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = rtweekend::random_double();
                point3 center(a + 0.9 * rtweekend::random_double(), 0.2, b + 0.9 * rtweekend::random_double());

                if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                    shared_ptr<material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = color::random() * color::random();
                        sphere_material = make_shared<lambertian>(albedo);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));

                    }
                    else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = color::random(0.5, 1);
                        auto fuzz = rtweekend::random_double(0, 0.5);
                        sphere_material = make_shared<metal>(albedo, fuzz);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                    else {
                        // glass
                        sphere_material = make_shared<dielectric>(1.5);
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));

                    }


                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	auto material4 = make_shared<dielectric>(.5);
    world.add(make_shared<sphere>(point3(0, 1, 3), 1.0, material4));

    return world;
}


 float hit_sphere(const point3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = vec3::dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}
 color ray_color(const ray& r, const hittable& world, int depth) {
     hit_record rec;

     if (depth <= 0)
         return color(0, 0, 0);

     if (world.hit(r, 0.001, infinity, rec)) {
         ray scattered;
         color attenuation;

         if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
             return attenuation * ray_color(scattered, world, depth - 1);

         return color(0, 0, 0);
     }

     vec3 unit_direction = vec3::unit_vector(r.direction());
     auto t = 0.5 * (unit_direction.getY() + 1.0);
     return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
 }


 void RTThreadTest(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth,
     int imageHeight, RTImage* image, int lRow, int uRow) {

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

int main()
{

    std::vector<PoolWorkerThread*> threads;

    Semaphores* countingSem = new Semaphores(0);
    Semaphores* mutexSem = new Semaphores(1);

    // Image

    const auto aspect_ratio = 16.0f/9.0f;
    const int image_width = 1080;
    //divide width by cores
    //const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int image_height = 1080;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    int numThreads = 16;
    RTImage* rtImage = new RTImage(image_width, image_height);



    // World

    //hittable_list world;

    auto R = cos(pi / 4);
    auto world = random_scene();

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    //world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    //world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    //world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    //world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
    //world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));





    /*world.add(make_shared<sphere>(point3(-4, 0, -5), 6));
    world.add(make_shared<sphere>(point3(0, -20, -20), 20));*/

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    const int widthWindow = rint(image_width / numThreads);

    int lRow = 0;
    int uRow = widthWindow;

    for (int i = 0; i < numThreads; i++)
    {
        PoolWorkerThread* RTThread = new PoolWorkerThread(i, 0, image_height, lRow, uRow);
        threads.push_back(RTThread);

    	RTThread->setValues(&cam, world, max_depth, samples_per_pixel, image_width, image_height, threads,countingSem, mutexSem);
        RTThread->setImage(rtImage);
        RTThread->start();

        lRow = lRow + widthWindow;
        uRow = uRow + widthWindow;

    }
    bool loop = true;
    while (loop)
    {
	    for (int i = 0; i < numThreads; ++i)
	    {
            loop = false;
            if (!threads[i]->finish)
            {
                loop = true;
                break;
            }

	    }
    }


    cv::String filename = "E:/Downloads/ImageRender.png";

    //std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";


    //for (int j = image_height - 1; j >= 0; --j) {
    //    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    //    for (int i = 0; i < image_width; ++i) {
    //        color pixel_color(0, 0, 0);

    //        for (int s = 0; s < samples_per_pixel; ++s) {
    //            auto u = (i + rtweekend::random_double()) / (image_width - 1);
    //            auto v = (j + rtweekend::random_double()) / (image_height - 1);
    //            ray r = cam.get_ray(u, v);
    //            pixel_color = pixel_color +  ray_color(r, world, max_depth);
    //        }
    //        rtImage->setPixel(i, j, pixel_color.getX(), pixel_color.getY(), pixel_color.getZ(), samples_per_pixel);
    //        //colorUtils::write_color(std::cout, pixel_color, samples_per_pixel);
    //    }
    //}

    
    rtImage->saveImage(filename);


    std::cerr << "\nDone.\n";
}

