#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include <memory>
#include <vector>
#include "Hittable.h"

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object)
    {
        add(object);
    }
    void clear() { hittableList.clear(); }
    void add(std::shared_ptr<Hittable> object)
    {
        hittableList.push_back(object);
    }
    virtual bool intersect(
        const Ray &r, float t_min, float t_max, Hit &rec, float tnear) const override;

public:
    std::vector<std::shared_ptr<Hittable>> hittableList;
};

bool HittableList::intersect(const Ray &r, float t_min, float t_max, Hit &rec, float tnear) const
{
    Hit temp;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object : hittableList)
    {
        if (object->intersect(r, t_min, closest_so_far, temp, tnear))
        {
            hit_anything = true;
            closest_so_far = temp.t;
            rec = temp;
        }
    }

    return hit_anything;
}
#endif