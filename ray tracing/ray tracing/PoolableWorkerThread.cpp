//#include "PoolableWorkerThread.h"
//
//#include <opencv2/core/cvstd.hpp>
//
//#include "hittable.h"
//
//
//class hittable;
//
//PoolableWorkerThread::PoolableWorkerThread(int id, int lCol, int uCol, int lRow, int uRow)
//{
//	this->id = id;
//	this->lCol = lCol;
//	this->uCol = uCol;
//	this->lRow = lRow;
//	this->uRow = uRow;
//}
//
//
//
//PoolableWorkerThread::PoolableWorkerThread(int id, int lCol, int uCol, int lRow, int uRow)
//{
//	this->id = id;
//	this->lCol = lCol;
//	this->uCol = uCol;
//	this->lRow = lRow;
//	this->uRow = uRow;
//
//
//}
//
//PoolableWorkerThread::~PoolableWorkerThread()
//{
//}
//
//int PoolableWorkerThread::getThreadID()
//{
//	return this->id;
//}
//
//void PoolableWorkerThread::setValues(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth,
//	int imageHeight)
//{
//    this->cam = cam;
//    this->world = world;
//    this->bounces = bounces;
//    this->samplesPerPixel = samplesPerPixel;
//    this->imageHeight = imageHeight;
//    this->imageWidth= imageWidth;
//
//}
//
//void PoolableWorkerThread::setImage(RTImage* image)
//{
//    this->image = image;
//}
//
//color PoolableWorkerThread::ray_color(const ray& r, const hittable& world, int bounces)
//{
//    hit_record rec;
//
//    // If we've exceeded the ray bounce limit, no more light is gathered.
//    if (bounces <= 0)
//        return color(0, 0, 0);
//
//    if (world.hit(r, 0.001, infinity, rec)) {
//        ray scattered;
//        color attenuation;
//
//        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
//            return attenuation * ray_color(scattered, world, bounces - 1);
//
//        return color(0, 0, 0);
//    }
//
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5 * (unit_direction.y() + 1.0);
//    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//}
//
//
//void PoolableWorkerThread::run()
//{
//    cv::String filename = "E:/Downloads/ImageRender.png";
//
//    for (int j = this->uCol - 1; j >= this->lCol; j--) {
//        //std::cerr << "\r Thread ID: " << this->threadID<< " Scanlines remaining: " << j << ' ' << std::flush;
//        for (int i = this->lRow; i < this->uRow; i++) {
//
//            color pixels(0.0f, 0.0f, 0.0f);
//            for (int s = 0; s < samplesPerPixel; s++)
//            {
//                float u = (float(i) + random_double()) / (this->imageWidth - 1);
//                float v = (float(j) + random_double()) / (this->imageHeight - 1);
//
//                ray r = cam->get_ray(u, v);
//                //pixels += PoolableWorkerThread::ray_color(r, world, bounces);
//            }
//
//            //ColorUtils::writeColor(this->imageFile, pixels, raySamplesPerPixel);
//            //pixelGroup.push_back(pixels);
//
//            this->image->setPixel(i, j, pixels.x(), pixels.y(), pixels.z(), this->samplesPerPixel);
//        }
//    }
//
//    image->saveImage(filename);
//
//
//	//this->action->onStartTask();
//
//
//	//this->finishedTask->onFinished(this->id);
//
//}
