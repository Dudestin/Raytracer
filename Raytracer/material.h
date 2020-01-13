#pragma once
#include "ray.h"
#include "hittable.h"

class material
{
public:
	virtual bool scatter(
        const ray& r_in, const hit_record& rec, Eigen::Vector3d& attenuation,
        ray& scattered) const = 0;
};

