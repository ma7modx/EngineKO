#pragma once
#include "Vector3.h"

struct BaseLight {
Vector3 color;
float intensity;
};

struct DirectionalLight {
BaseLight base ;
Vector3 direction ;
};