#pragma once

#include "ray.h"
#include <Eigen/Core>

class material;

struct hit_record {
	double t{0.0};
	Eigen::Vector3d p{0,0,0};
	Eigen::Vector3d normal{0,0,0};
	std::shared_ptr<material> mat_ptr;
};

class hittable
{
public:
	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
	virtual ~hittable() = default;
};