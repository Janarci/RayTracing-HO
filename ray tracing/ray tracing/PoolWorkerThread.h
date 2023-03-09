#pragma once

#include "WorkerThread.h"

#include <iostream>

#include "camera.h"
#include "ray.h"
#include "RTImage.h"
#include "vec3.h"
#include "hittable_list.h"
#include "Semaphores.h"


class PoolWorkerThread : public WorkerThread
{
public:
	PoolWorkerThread(int id, int lCol, int uCol, int lRow, int uRow);
	~PoolWorkerThread();

	int getThreadID();
	void setValues(camera* cam, hittable_list world, int bounces, int samplesPerPixel, int imageWidth, int imageHeight, std::vector<PoolWorkerThread*> threads, Semaphores* countingSem, Semaphores* mutexSem);
	void setImage(RTImage* image);
	color ray_color(const ray& r, const hittable_list& world, int bounces);
	void run() override;
	bool finish = false;

private:

	int id = 0;
	int lCol;
	int uCol;
	int uRow;
	int lRow;

	camera* cam;
	hittable_list world;
	int bounces;
	int samplesPerPixel;
	int imageWidth;
	int imageHeight;
	int critical;
	RTImage* image;
	std::vector<PoolWorkerThread*> threads;

	Semaphores* countingSem;
	Semaphores* mutexSem;

};


