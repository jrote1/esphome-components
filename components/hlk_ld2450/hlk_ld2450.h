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

      void setup() override
      {
        // This will be called by App.setup()
      }
      void update() override {
        publish_state(42.0);
      }
    };

  } // namespace hlk_ld2450
} // namespace esphome