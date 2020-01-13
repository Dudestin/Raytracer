#include "lambertian.h"
#include "random.h"

Eigen::Vector3d random_in_unit_sphere() {
    Eigen::Vector3d p;
    do {
        p = 2.0 * Eigen::Vector3d(random_double(), random_double(), random_double()) - Eigen::Vector3d(1, 1, 1);
    } while (p.norm() >= 1.0);
    return p;
}
