#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "Helper.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Dielectric.h"

#include <vector>


#define CHANNELS 3
typedef uint8_t uint;

static std::string imagePath = "D:/Other/RAY_TRACING/Ray_Tracing_in_a_Weekend/Ray_Tracing_in_a_Weekend/output/";


//void writePPM(int width, int height) {
//
//	std::ofstream out(imagePath + "out.ppm");
//
//	out << "P3\n" << width << " " << height << "\n255\n";
//
//	for (int j = height - 1; j >= 0; j--) {
//		std::cout << "Scanlines remaining " << j << "\n";
//		for (int i = 0; i < width; i++) {
//			Vec3 color((double)i / (double)width, (double)j / (double)height, 0.2f);
//			out << color;
//		}
//	}
//	std::cout << "Done\n";
//	out.close();
//}

Vec3 rayColor(const Ray& ray, const Hittable& world, int depth) {
	HitRecord rec;

	//ray bounce limit reached, no more light contribution
	if (depth <= 0)
		return Vec3(0.0f, 0.0f, 0.0f);

	if (world.hit(ray, 0.001f, infinity, rec)) {
		//Vec3 target = rec.position + rec.normal + Vec3::randUSphere();

		Ray scattered;
		Vec3 attenuation;
		if (rec.material->scatter(ray, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);
		//return 0.5f * rayColor(Ray(rec.position, target - rec.position), world, depth - 1);
		return Vec3(0.0f, 0.0f, 0.0f);
	}

	Vec3 unitV = ray.getDirection().unitVector();
	double t = 0.5f * (unitV[1] + 1.0f);
	return ((1.0f - t) * Vec3(1.0f, 1.0f, 1.0f)) + (t * Vec3(0.5f, 0.7f, 1.0f));
}

//void writePNG(int width, int height, const Hittable& world) {
//	
//	std::vector<uint> data;
//	for (int j = height - 1; j >= 0; j--) {
//		for (int i = 0; i < width; i++) {
//
//			//linear interpolation ray based gradient coloring
//			double u = (double)i / (double)width;
//			double v = (double)j / (double)height;
//			Ray ray(origin, lowerLeft + (u * horizontal) + (v * vertical));
//			Vec3 color = rayColor(ray, world);
//			data.push_back(color[0] * 255.999);
//			data.push_back(color[1] * 255.999);
//			data.push_back(color[2] * 255.999);
//		}
//	}
//	stbi_write_png((imagePath + "out.png").c_str(), width, height, CHANNELS, data.data(), width * CHANNELS);
//}

//With AA
void writePNG(int width, int height, int samples, int depth, const Hittable& world, const Camera& cam) {

	std::vector<uint> data;
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {

			//linear interpolation ray based gradient coloring
			Vec3 color;
			for (int k = 0; k < samples; k++) {
				double u = (double)(i + randDouble()) / (double)width;
				double v = (double)(j + randDouble()) / (double)height;
			
				Ray ray = cam.getRay(u, v);
				color += rayColor(ray, world, depth);
			}
			//Divide by number of samples, and gamma correction applied, for a gamma value of 2.0
			double scale = 1.0f / samples;
			double r = sqrt(scale * color[0]);
			double g = sqrt(scale * color[1]);
			double b = sqrt(scale * color[2]);
			
			data.push_back(static_cast<uint>(256 * clamp(r, 0.0f, 0.999f)));
			data.push_back(static_cast<uint>(256 * clamp(g, 0.0f, 0.999f)));
			data.push_back(static_cast<uint>(256 * clamp(b, 0.0f, 0.999f)));
		}
	}
	stbi_write_png((imagePath + "out.png").c_str(), width, height, CHANNELS, data.data(), width * CHANNELS);
}

HittableList randomScene() {
	HittableList world;

	world.add(std::make_shared<Sphere>(
		Vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5))));

	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randDouble();
			Vec3 center(a + 0.9 * randDouble(), 0.2, b + 0.9 * randDouble());
			if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = Vec3::random() * Vec3::random();
					world.add(
						std::make_shared<Sphere>(center, 0.2, std::make_shared<Lambertian>(albedo)));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = Vec3::random(.5, 1);
					auto fuzz = randDouble(0, .5);
					world.add(
						std::make_shared<Sphere>(center, 0.2, std::make_shared<Metal>(albedo, fuzz)));
				}
				else {
					// glass
					world.add(std::make_shared<Sphere>(center, 0.2, std::make_shared<Dielectric>(1.5)));
				}
			}
		}
	}

	world.add(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));

	world.add(
		std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1))));

	world.add(
		std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0)));

	return world;
}

int main() {

	const int width = 1000;
	const int height = 500;
	const int samplesPerPixel = 100;
	const int maxDepth = 50;
	const double aspectR = (double)width / (double)height;
	const double aperture = 0.1;
	const double vFov = 35.0f;

	//Vec3 lookFrom(-2.0, 2.0, 1.0), lookAt(0.0, 0.0, -1.0), vUp(0.0, 1.0, 0.0);
	Vec3 lookFrom(13.0, 2.0, 3.0), lookAt(0.0, 0.0, 0.0), vUp(0.0, 1.0, 0.0);
	//const double focusDist = (lookFrom - lookAt).length();
	const double focusDist = 10.0;
	
	Camera cam(lookFrom, lookAt, vUp, vFov, aspectR, aperture, focusDist);

	HittableList world = randomScene();
	/*world.add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Lambertian>(Vec3(0.1f, 0.2f, 0.5f))));
	world.add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_shared<Lambertian>(Vec3(0.5f, 0.5f, 0.5f))));

	world.add(std::make_shared<Sphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Metal>(Vec3(0.8f, 0.6f, 0.2f), 0.0f)));
	world.add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<Dielectric>(1.5f)));
	world.add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), -0.45f, std::make_shared<Dielectric>(1.5f)));*/

	writePNG(width, height, samplesPerPixel, maxDepth, world, cam);
}