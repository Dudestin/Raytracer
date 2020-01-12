#pragma once
#include "ray.h"

class camera
{
public:
	camera() : origin(0.0,0.0,0.0),
		lower_left_corner (-2.0,-1.0,-1.0),
		vertical(0.0,2.0,0.0),
		horizontal(4.0,0.0,0.0) {}

	ray get_ray(double u, double v) {
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

	Eigen::Vector3d origin;
	Eigen::Vector3d lower_left_corner;
	Eigen::Vector3d horizontal;
	Eigen::Vector3d vertical;
};

