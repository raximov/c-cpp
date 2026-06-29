#include "settings_manager.h"
#include <fstream>
#include <sstream>
#include <map>
#include <filesystem>

namespace s21 {

namespace {
std::map<std::string, std::string> g_kv;
}

SettingsManager::SettingsManager() {
  // Store in user home config dir
  const char* home = std::getenv("HOME");
  std::string dir = home ? std::string(home) + "/.config/3dviewer" : "/tmp";
  std::filesystem::create_directories(dir);
  settings_path_ = dir + "/settings.ini";
  Read();
}

void SettingsManager::SetValue(const std::string& key,
                                const std::string& value) {
  g_kv[key] = value;
  Write();
}

std::string SettingsManager::GetValue(const std::string& key,
                                       const std::string& default_val) const {
  auto it = g_kv.find(key);
  return (it != g_kv.end()) ? it->second : default_val;
}

void SettingsManager::Write() const {
  std::ofstream f(settings_path_);
  if (!f.is_open()) return;
  for (const auto& [k, v] : g_kv) f << k << "=" << v << "\n";
}

void SettingsManager::Read() {
  std::ifstream f(settings_path_);
  if (!f.is_open()) return;
  std::string line;
  while (std::getline(f, line)) {
    auto pos = line.find('=');
    if (pos == std::string::npos) continue;
    g_kv[line.substr(0, pos)] = line.substr(pos + 1);
  }
}

void SettingsManager::Save(const SceneSettings& s) {
  g_kv["bg_r"] = std::to_string(s.background_color.r);
  g_kv["bg_g"] = std::to_string(s.background_color.g);
  g_kv["bg_b"] = std::to_string(s.background_color.b);
  g_kv["show_floor"] = s.show_floor ? "1" : "0";
  g_kv["projection"] = (s.projection == ProjectionType::kCentral) ? "central" : "parallel";
  g_kv["edge_r"] = std::to_string(s.edge_style.color.r);
  g_kv["edge_g"] = std::to_string(s.edge_style.color.g);
  g_kv["edge_b"] = std::to_string(s.edge_style.color.b);
  g_kv["edge_thickness"] = std::to_string(s.edge_style.thickness);
  g_kv["edge_dashed"] = s.edge_style.dashed ? "1" : "0";
  g_kv["vertex_size"] = std::to_string(s.vertex_style.size);
  g_kv["vertex_shape"] = std::to_string(static_cast<int>(s.vertex_style.shape));
  Write();
}

SceneSettings SettingsManager::Load() {
  SceneSettings s;
  auto G = [&](const std::string& k, float def) -> float {
    auto it = g_kv.find(k);
    return (it != g_kv.end()) ? std::stof(it->second) : def;
  };
  s.background_color.r = G("bg_r", 0.1f);
  s.background_color.g = G("bg_g", 0.1f);
  s.background_color.b = G("bg_b", 0.1f);
  s.show_floor = (GetValue("show_floor", "1") == "1");
  s.projection = (GetValue("projection", "central") == "central")
                     ? ProjectionType::kCentral
                     : ProjectionType::kParallel;
  s.edge_style.color.r = G("edge_r", 0.8f);
  s.edge_style.color.g = G("edge_g", 0.8f);
  s.edge_style.color.b = G("edge_b", 0.8f);
  s.edge_style.thickness = G("edge_thickness", 1.0f);
  s.edge_style.dashed = (GetValue("edge_dashed", "0") == "1");
  s.vertex_style.size = G("vertex_size", 3.0f);
  s.vertex_style.shape = static_cast<VertexStyle::Shape>(
      static_cast<int>(G("vertex_shape", 0)));
  return s;
}

std::string SettingsManager::Serialize(const SceneSettings&) const { return ""; }
SceneSettings SettingsManager::Deserialize(const std::string&) const { return {}; }

}  // namespace s21
