#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace serial {

class SerialSensor : public Component,  public sensor::Sensor, public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }
  void loop() override;
  void dump_config() override;

 protected:
  void handle_char_(uint8_t c);
  std::vector<uint8_t> rx_message_;
};

}  // namespace serial
}  // name