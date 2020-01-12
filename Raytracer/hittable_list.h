#pragma once
#include <vector>
#include "hittable.h"

class hittable_list : public hittable {
public:
    hittable_list() {};
    hittable_list(std::vector<std::unique_ptr<hittable>>&& l) { list = std::move(l); }
    ~hittable_list() { std::vector<std::unique_ptr<hittable>>().swap(list); };
    virtual bool hit(
        const ray& r, double tmin, double tmax, hit_record& rec) const;
    std::vector<std::unique_ptr<hittable>> list;  
};