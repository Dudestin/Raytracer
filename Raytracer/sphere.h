#pragma once
#include <Eigen/Core>

#include "hittable.h"

class sphere:public hittable
{
public:
	sphere() :radius(0), center{0,0,0} {};
	sphere(Eigen::Vector3d cen, double r) : center(cen), radius(r) {}
	 ~sphere() {};
	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const;
	Eigen::Vector3d center;
	double radius;
};

