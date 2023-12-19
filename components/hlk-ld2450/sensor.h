#pragma once

#include "esphome.h"

namespace esphome
{
  namespace serial
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

  } // namespace serial
} // name