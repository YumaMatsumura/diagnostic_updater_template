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

#pragma once

#include <chrono>
#include <memory>
#include <string>

#include <diagnostic_updater/diagnostic_updater.hpp>
#include <rclcpp/rclcpp.hpp>

namespace diagnostic_updater_template
{

class DiagnosticUpdaterTemplate : public rclcpp::Node
{
public:
  explicit DiagnosticUpdaterTemplate(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~DiagnosticUpdaterTemplate();

private:
  void update();
  void SampleDiagnostic1(diagnostic_updater::DiagnosticStatusWrapper & stat);

  rclcpp::TimerBase::SharedPtr timer_;
  diagnostic_updater::Updater updater_;

  bool error_;
};

}  // namespace diagnostic_updater_template
