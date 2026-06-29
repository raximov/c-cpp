#pragma once
#include <memory>
#include "../geometry/mesh.h"

namespace s21 {

// Strategy pattern: different shading algorithms
class IShadingStrategy {
 public:
  virtual ~IShadingStrategy() = default;
  virtual const char* GetVertexShader() const = 0;
  virtual const char* GetFragmentShader() const = 0;
  virtual RenderMode GetMode() const = 0;
};

class WireframeStrategy : public IShadingStrategy {
 public:
  const char* GetVertexShader() const override;
  const char* GetFragmentShader() const override;
  RenderMode GetMode() const override { return RenderMode::kWireframe; }
};

class FlatShadingStrategy : public IShadingStrategy {
 public:
  const char* GetVertexShader() const override;
  const char* GetFragmentShader() const override;
  RenderMode GetMode() const override { return RenderMode::kFlatShading; }
};

class GouraudShadingStrategy : public IShadingStrategy {
 public:
  const char* GetVertexShader() const override;
  const char* GetFragmentShader() const override;
  RenderMode GetMode() const override { return RenderMode::kGouraudShading; }
};

class PhongShadingStrategy : public IShadingStrategy {
 public:
  const char* GetVertexShader() const override;
  const char* GetFragmentShader() const override;
  RenderMode GetMode() const override { return RenderMode::kPhongShading; }
};

class ShadingModel {
 public:
  ShadingModel();
  void SetStrategy(RenderMode mode);
  IShadingStrategy* GetStrategy() const { return strategy_.get(); }

 private:
  std::unique_ptr<IShadingStrategy> strategy_;
};

}  // namespace s21
