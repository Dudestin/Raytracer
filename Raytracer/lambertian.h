#pragma once
#include "material.h"

Eigen::Vector3d random_in_unit_sphere();

class lambertian :
	public material
{
public:
	lambertian(const Eigen::Vector3d& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec,
        Eigen::Vector3d& attenuation, ray& scattered) const {
        Eigen::Vector3d target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Eigen::Vector3d albedo;
};

