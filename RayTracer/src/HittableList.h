#pragma once

// Add a .pch file

#include <vector>
#include "Hittable.h"

class HittableList : public Hittable
{
public:
	HittableList() = default;
	
	void Add(const std::shared_ptr<Hittable>& m_Hittable) { m_HittableList.push_back(m_Hittable); }
	inline void Clear() { m_HittableList.clear(); }

	virtual bool hit(const Ray& ray, float tMin, float tMax, Hit_Rec& data) const override;

private:
	std::vector<std::shared_ptr<Hittable>> m_HittableList;
};

bool HittableList::hit(const Ray& ray, float tMin, float tMax, Hit_Rec& data) const
{
	Hit_Rec tempRec;
	bool isHitted = false;
	float closestSoFar = tMax;

	for (auto& hittable : m_HittableList)
	{
		if (hittable->hit(ray, tMin, tMax, tempRec))
		{
			isHitted = true;
			closestSoFar = tempRec.t;
			data = tempRec;
		}
	}

	return isHitted;
}
