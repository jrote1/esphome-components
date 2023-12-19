#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace hlk_ld2450
  {

    class HLKLD2450 : public PollingComponent, public sensor::Sensor, public uart::UARTDevice
    {
    public:
      // constructor
      HLKLD2450() : PollingComponent(15000) {}
      void set_illuminance_sensor(sensor::Sensor *illuminance_sensor) { illuminance_sensor_ = illuminance_sensor; }

      void setup() override
      {
        // This will be called by App.setup()
      }
      void update() override {
        this->illuminance_sensor_->publish_state(42.0);
      }
    protected:
      /// Read the illuminance value and store the calculated ambient illuminance in t_fine.
      float read_illuminance_(const uint8_t *data, int32_t *t_fine);

      sensor::Sensor *illuminance_sensor_{nullptr};
    };

  } // namespace hlk_ld2450
} // namespace esphome