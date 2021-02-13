#pragma once
#include <DirectXMath.h>
#include "ChiliMath.h"
#include "IndexedTriangleList.h"
#include "DrawableBase.h"
class TrangleCube: public DrawableBase<TrangleCube>
{
public:
	TrangleCube(Graphics& gfx, 
		std::mt19937& rng,
		std::uniform_real_distribution<float> adist,
		std::uniform_real_distribution<float> ddist,
		std::uniform_real_distribution<float> odist,
		std::uniform_real_distribution<float> rdist);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;


	template<class V>
	static IndexedTriangleList<V> MakeTesselated(int longDiv = 3)
	{
		namespace dx = DirectX;
		
		const auto base = dx::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
		const float longitudeAngle = 2.0f * PI / longDiv;
		std::vector<V> vertices;
		for (int iLong = 0; iLong < longDiv; iLong++)
		{
			vertices.emplace_back();
			auto v = dx::XMVector3Transform(
				base,
				dx::XMMatrixRotationZ(longitudeAngle * iLong)
			);
			dx::XMStoreFloat3(&vertices.back().pos, v);
		}
		//ther center
		vertices.emplace_back();
		vertices.back().pos = { 0.0f,0.0f,1.0f };
		const auto iTip = (unsigned short)(vertices.size() - 1);
		
		//base indices
		std::vector<unsigned short> indices;


		//indices.push_back(0);
		//indices.push_back(1);
		//indices.push_back(3);

		//indices.push_back(0);
		//indices.push_back(2);
		//indices.push_back(3);

		//indices.push_back(1);
		//indices.push_back(2);
		//indices.push_back(3);
		for (unsigned short iLong = 0; iLong < longDiv; iLong++) 
		{
			indices.push_back(iTip);
			indices.push_back(iLong);
			indices.push_back((iLong + 1) % longDiv);

		}
		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(0);

 		return { std::move(vertices),std::move(indices) };

	}
private:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;

};