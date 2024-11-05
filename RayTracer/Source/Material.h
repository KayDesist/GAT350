#pragma once
#include "Color.h"
#include "Ray.h"

class Material {
public:
	Material() = default;
	Material(const color3_t& albedo) : m_albedo{ albedo } {}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) = 0;
	virtual color3_t GetEmmissive() const { return color3_t{ 0 }; }
	color3_t& GetColor() { return m_albedo; };

protected:
	color3_t m_albedo;
};

class Lambertian : public Material {
public:
	Lambertian(const color3_t& albedo) : Material(albedo) {}

	// Inherited via Material
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) override;
};

class Metal : public Material {
public:
	Metal(const glm::vec3& albedo, float fuzz) : Material(albedo), m_fuzz(fuzz) {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) override;

protected:
	float m_fuzz = 0;
};

class Emissive : public Material {
public:
	Emissive(const color3_t& albedo, float intensity = 1) : Material(albedo), m_intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycasthit, color3_t& attenuation, ray_t& scatter) override { return false; }
	color3_t GetEmmissive() const override { return m_albedo * m_intensity; }
protected:
	float m_intensity = 0;
};

class Dielectric : public Material {
public:
	Dielectric(const glm::vec3& albedo, float ri) : Material(albedo), m_ri(ri) {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) override;

protected:
	//I aint typeing All that
	//imagine being named Snell, couldn't be me
	float m_ri = 0;
};