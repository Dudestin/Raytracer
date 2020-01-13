#include "metal.h"

Eigen::Vector3d reflect(const Eigen::Vector3d& v, const Eigen::Vector3d& n) {
	return v - 2.0 * v.dot(n) * n;
}