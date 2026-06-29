#include "shading_model.h"
#include <stdexcept>

namespace s21 {

// ===================== WIREFRAME =====================
static const char* kWireVert = R"(
#version 330 core
layout(location=0) in vec3 aPos;
uniform mat4 uMVP;
void main() {
  gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* kWireFrag = R"(
#version 330 core
uniform vec4 uColor;
out vec4 FragColor;
void main() {
  FragColor = uColor;
}
)";

// ===================== FLAT SHADING =====================
static const char* kFlatVert = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
uniform mat4 uModel;
uniform mat4 uMVP;
flat out vec3 vNormal;
out vec3 vFragPos;
void main() {
  vFragPos = vec3(uModel * vec4(aPos, 1.0));
  vNormal = mat3(transpose(inverse(uModel))) * aNormal;
  gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* kFlatFrag = R"(
#version 330 core
flat in vec3 vNormal;
in vec3 vFragPos;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform vec3 uViewPos;
uniform float uAmbient;
uniform float uSpecular;
uniform int uShininess;
out vec4 FragColor;
void main() {
  vec3 norm = normalize(vNormal);
  vec3 lightDir = normalize(uLightPos - vFragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 ambient = uAmbient * uLightColor;
  vec3 diffuse = diff * uLightColor;
  vec3 viewDir = normalize(uViewPos - vFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
  vec3 specular = uSpecular * spec * uLightColor;
  vec3 result = (ambient + diffuse + specular) * uObjectColor;
  FragColor = vec4(result, 1.0);
}
)";

// ===================== GOURAUD =====================
static const char* kGouraudVert = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
uniform mat4 uModel;
uniform mat4 uMVP;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform vec3 uViewPos;
uniform float uAmbient;
uniform float uSpecular;
uniform int uShininess;
out vec3 vColor;
void main() {
  vec3 fragPos = vec3(uModel * vec4(aPos, 1.0));
  vec3 norm = normalize(mat3(transpose(inverse(uModel))) * aNormal);
  vec3 lightDir = normalize(uLightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 ambient = uAmbient * uLightColor;
  vec3 diffuse = diff * uLightColor;
  vec3 viewDir = normalize(uViewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
  vec3 specular = uSpecular * spec * uLightColor;
  vColor = (ambient + diffuse + specular) * uObjectColor;
  gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* kGouraudFrag = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
  FragColor = vec4(vColor, 1.0);
}
)";

// ===================== PHONG =====================
static const char* kPhongVert = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
uniform mat4 uModel;
uniform mat4 uMVP;
out vec3 vNormal;
out vec3 vFragPos;
void main() {
  vFragPos = vec3(uModel * vec4(aPos, 1.0));
  vNormal = mat3(transpose(inverse(uModel))) * aNormal;
  gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* kPhongFrag = R"(
#version 330 core
in vec3 vNormal;
in vec3 vFragPos;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uObjectColor;
uniform vec3 uViewPos;
uniform float uAmbient;
uniform float uSpecular;
uniform int uShininess;
out vec4 FragColor;
void main() {
  vec3 norm = normalize(vNormal);
  vec3 lightDir = normalize(uLightPos - vFragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 ambient = uAmbient * uLightColor;
  vec3 diffuse = diff * uLightColor;
  vec3 viewDir = normalize(uViewPos - vFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
  vec3 specular = uSpecular * spec * uLightColor;
  vec3 result = (ambient + diffuse + specular) * uObjectColor;
  FragColor = vec4(result, 1.0);
}
)";

// ===================== Strategy implementations =====================

const char* WireframeStrategy::GetVertexShader() const { return kWireVert; }
const char* WireframeStrategy::GetFragmentShader() const { return kWireFrag; }

const char* FlatShadingStrategy::GetVertexShader() const { return kFlatVert; }
const char* FlatShadingStrategy::GetFragmentShader() const { return kFlatFrag; }

const char* GouraudShadingStrategy::GetVertexShader() const { return kGouraudVert; }
const char* GouraudShadingStrategy::GetFragmentShader() const { return kGouraudFrag; }

const char* PhongShadingStrategy::GetVertexShader() const { return kPhongVert; }
const char* PhongShadingStrategy::GetFragmentShader() const { return kPhongFrag; }

// ===================== ShadingModel =====================

ShadingModel::ShadingModel() : strategy_(std::make_unique<WireframeStrategy>()) {}

void ShadingModel::SetStrategy(RenderMode mode) {
  switch (mode) {
    case RenderMode::kWireframe:
      strategy_ = std::make_unique<WireframeStrategy>(); break;
    case RenderMode::kFlatShading:
      strategy_ = std::make_unique<FlatShadingStrategy>(); break;
    case RenderMode::kGouraudShading:
      strategy_ = std::make_unique<GouraudShadingStrategy>(); break;
    case RenderMode::kPhongShading:
      strategy_ = std::make_unique<PhongShadingStrategy>(); break;
  }
}

}  // namespace s21
