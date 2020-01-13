#pragma once
#include "material.h"

Eigen::Vector3d reflect(const Eigen::Vector3d&, const Eigen::Vector3d&);

class metal :
	public material
{
public:
    metal(const Eigen::Vector3d& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec,
        Eigen::Vector3d& attenuation, ray& scattered) const {
        Eigen::Vector3d reflected = reflect(r_in.direction().normalized(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return ((scattered.direction()).dot(rec.normal) > 0);
    }
    Eigen::Vector3d albedo;
};
