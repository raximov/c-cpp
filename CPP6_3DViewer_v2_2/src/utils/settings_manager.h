#pragma once
#include "../model/model_data.h"
#include <string>

namespace s21 {

// Design pattern: Singleton (settings is globally accessible read/write store)
class SettingsManager {
 public:
  static SettingsManager& Instance() {
    static SettingsManager inst;
    return inst;
  }

  void Save(const SceneSettings& s);
  SceneSettings Load();

  void SetValue(const std::string& key, const std::string& value);
  std::string GetValue(const std::string& key,
                       const std::string& default_val = "") const;

 private:
  SettingsManager();
  std::string settings_path_;

  void Write() const;
  void Read();

  std::string Serialize(const SceneSettings& s) const;
  SceneSettings Deserialize(const std::string& data) const;

  SceneSettings cached_;
  bool loaded_ = false;
};

}  // namespace s21
