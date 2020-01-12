#pragma once
#include <Eigen/Core>

class ray
{
public:
	ray() {}
	ray(const Eigen::Vector3d& a, const Eigen::Vector3d& b) { A = a; B = b; }
	Eigen::Vector3d origin() const { return A; }
	Eigen::Vector3d direction() const { return B; }
	Eigen::Vector3d point_at_parameter(float t) const { return A + t * B; }

	Eigen::Vector3d A, B;
};

