// Copyright (c) 2023 Yuma Matsumura All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "diagnostic_updater_template/diagnostic_updater_template_component.hpp"

namespace
{
constexpr const char * hardware_name = "sample_hardware";
}

namespace diagnostic_updater_template
{

DiagnosticUpdaterTemplate::DiagnosticUpdaterTemplate(const rclcpp::NodeOptions & options)
: Node("diagnostic_updater_template_node", options),
  updater_(this),
  error_(true)
{
  using msec = std::chrono::milliseconds;

  // エラーを扱う対象の名前（ハードウェアに対応する名前）
  updater_.setHardwareID(hardware_name);

  // エラー状態を判断する関数を登録
  updater_.add("Motor Temperature Info", this, &DiagnosticUpdaterTemplate::SampleDiagnostic1);

  timer_ = this->create_wall_timer(msec(500), std::bind(&DiagnosticUpdaterTemplate::update, this));
}

DiagnosticUpdaterTemplate::~DiagnosticUpdaterTemplate() {}

void DiagnosticUpdaterTemplate::update()
{
  // 診断を強制的に更新する
  updater_.force_update();

  // 更新間隔を超えた場合に診断を更新する
  // updater_.update();
}

// エラー状態を判断する関数のサンプル1
void DiagnosticUpdaterTemplate::SampleDiagnostic1(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  // エラー判定
  if (error_) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "High Temperature");

    // エラー情報追加（第1引数：string、第2引数：template<T>）
    stat.add("Motor Temperature", 100.0);
  } else {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "ok");
  }
}

}  // namespace diagnostic_updater_template
