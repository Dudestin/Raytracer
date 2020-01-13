// Raytracer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Core>
#include <string>
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "random.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"

using namespace Eigen;

Vector3d color(const ray& r, std::unique_ptr<hittable>& world,int depth) {
    hit_record rec;
    if (world->hit(r, 0.0001,DBL_MAX, rec)) {
        ray scattered;
        Vector3d attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation.array() * color(scattered, world, depth + 1).array();
        }
        else {
            return Vector3d(0, 0, 0);
        }
    }
    else {
        auto unit_direction = r.direction().normalized();
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3d(1.0, 1.0, 1.0) + t * Vector3d(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;
    Vector3d lower_left_corner(-2.0, -1.0, -1.0);
    Vector3d horizontal(4.0, 0.0, 0.0);
    Vector3d vertical(0.0, 2.0, 0.0);
    Vector3d origin(0.0,0.0,0.0);

    std::unique_ptr<hittable> p1(std::move(new sphere(Vector3d(0.0,0.0,-1.0),0.5,std::move(std::make_shared<lambertian>(Vector3d(0.8,0.3,0.3))))));
    std::unique_ptr<hittable> p2(std::move(new sphere(Vector3d(0.0, -100.5, -1.0), 100.0,std::move(std::make_shared<lambertian>(Vector3d(0.8,0.8,0.8))))));
    std::unique_ptr<hittable> p3(std::move(new sphere(Vector3d(1.0, 0.0, -1.0), 0.5, std::move(std::make_shared<metal>(Vector3d(0.8, 0.6, 0.2))))));
    std::unique_ptr<hittable> p4(std::move(new sphere(Vector3d(-1.0, 0.0, -1.0), 0.5, std::move(std::make_shared<metal>(Vector3d(0.8, 0.8, 0.8))))));
    std::vector<std::unique_ptr<hittable>> list;
    list.push_back(std::move(p1));
    list.push_back(std::move(p2));
    list.push_back(std::move(p3));
    list.push_back(std::move(p4));

    auto world(std::unique_ptr<hittable>(new hittable_list(std::move(list))));
    camera cam;
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            Vector3d col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                double u = double(i + random_double()) / double(nx);
                double v = double(j + random_double()) / double(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= double(ns);
            col = Vector3d(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }    std::cout << sizeof(sphere) << std::endl;
}