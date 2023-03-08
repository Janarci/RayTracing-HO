//#pragma once
//
//#include "rtweekend.h"
//
//#include "WorkerThread.h"
//
//
//class ray;
//class RTImage;
//class camera;
//class hittable_list;
//
//
//class PoolableWorkerThread : public WorkerThread
//{
//
//public:
//	PoolableWorkerThread(int id, int lCol, int uCol, int lRow, int uRow);
//	~PoolableWorkerThread();
//
//	int getThreadID();
//	void setValues(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth, int imageHeight);
//	void setImage(RTImage* image);
//	color ray_color(const ray& r, const hittable_list& world, int bounces);
//
//	void run() override;
//
//private:
//
//	int id = 0;
//	int lCol;
//	int uCol;
//	int uRow;
//	int lRow;
//
//	camera* cam;
//	hittable_list* world;
//	int bounces;
//	int samplesPerPixel;
//	int imageWidth;
//	int imageHeight;
//	RTImage* image;
//};
//
