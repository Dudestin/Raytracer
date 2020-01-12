// Raytracer.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <memory>
#include "sphere.h"
#include "hittable_list.h"
#include <Eigen/Core>

using namespace Eigen;

Vector3d color(const ray& r, std::unique_ptr<hittable>& world) {
    hit_record rec;
    if (world->hit(r, 0.0,114514.0, rec)) {
        return 0.5 * Vector3d(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
    std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;
    Vector3d lower_left_corner(-2.0, -1.0, -1.0);
    Vector3d horizontal(4.0, 0.0, 0.0);
    Vector3d vertical(0.0, 2.0, 0.0);
    Vector3d origin(0.0,0.0,0.0);

    std::unique_ptr<hittable> p1(std::move(new sphere(Vector3d(0.0,0.0,-1.0),0.5)));
    std::unique_ptr<hittable> p2(std::move(new sphere(Vector3d(0.0, -100.5, -1.0), 100.0)));
    std::vector<std::unique_ptr<hittable>> list;
    list.push_back(std::move(p1));
    list.push_back(std::move(p2));

    auto world(std::unique_ptr<hittable>(new hittable_list(std::move(list))));
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            double u = double(i) / double(nx);
            double v = double(j) / double(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            
            Vector3d col = color(r, world);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
