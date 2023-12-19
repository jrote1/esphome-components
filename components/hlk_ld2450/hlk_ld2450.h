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
      void set_distance_sensor(sensor::Sensor *distance_sensor) { distance_sensor_ = distance_sensor; }

      void setup() override
      {
        // This will be called by App.setup()
      }
      void update() override
      {
        while (available())
        {
          bytes.push_back(read());

          // End of Frame is 0x55 0x55
          if ((bytes[bytes.size() - 2] == 0x55 && bytes[bytes.size() - 1] == 0x55) || (bytes[bytes.size() - 4] == 0x04 && bytes[bytes.size() - 3] == 0x03 && bytes[bytes.size() - 2] == 0x02 && bytes[bytes.size() - 1] == 0x01))
          {
            processPacket();
            bytes.clear();
          }
        }

        if (this->distance_sensor_ != nullptr)
          this->distance_sensor_->publish_state(42.0);
      }

      void processPacket()
      {

        std::string str = "";

        if ((bytes[0] == 0xAA) && (bytes[1] == 0xAA) && (bytes[2] == 0x00))
        {

          //presence_sensor->publish_state(0);
          //motion_sensor->publish_state(0);

          return;
        }

        if ((bytes[0] == 0xAA) && (bytes[1] == 0xAA) && (bytes[2] == 0x01))
        {

          //presence_sensor->publish_state(1);
          //motion_sensor->publish_state(1);

          unsigned char byte3 = bytes[3];
          unsigned char byte4 = bytes[4];

          unsigned int distanceHex = (byte4 << 8) | byte3;

          int distanceCm = static_cast<int>(distanceHex);

          this->distance_sensor_->publish_state(distanceCm);
          return;
        }

        if ((bytes[0] == 0xAA) && (bytes[1] == 0xAA) && (bytes[2] == 0x02))
        {

          //presence_sensor->publish_state(1);
          //motion_sensor->publish_state(0);

          unsigned char byte3 = bytes[3];
          unsigned char byte4 = bytes[4];

          unsigned int distanceHex = (byte4 << 8) | byte3;

          int distanceCm = static_cast<int>(distanceHex);

          distance_sensor_->publish_state(distanceCm);

          return;
        }

        if ((bytes[0] == 0xFD) && (bytes[1] == 0xFC) && (bytes[2] == 0xFB) && (bytes[3] == 0xFA) && (bytes[6] == 0x73) && (bytes[7] == 0x01))
        {

          unsigned char maxmlow = bytes[10];
          unsigned char maxmhigh = bytes[11];

          unsigned int maxmhex = (maxmhigh << 8) | maxmlow;

          int max_m = static_cast<int>(maxmhex);

          unsigned char minmlow = bytes[12];
          unsigned char minmhigh = bytes[13];

          unsigned int minmhex = (minmhigh << 8) | minmlow;

          int min_m = static_cast<int>(minmhex);

          unsigned char maxplow = bytes[14];
          unsigned char maxphigh = bytes[15];

          unsigned int maxphex = (maxphigh << 8) | maxplow;

          int max_p = static_cast<int>(maxphex);

          unsigned char minplow = bytes[16];
          unsigned char minphigh = bytes[17];

          unsigned int minphex = (minphigh << 8) | minplow;

          int min_p = static_cast<int>(minphex);

          unsigned char unocclow = bytes[18];
          unsigned char unocchigh = bytes[19];

          unsigned int unocchex = (unocchigh << 8) | unocclow;

          int unocc_time = static_cast<int>(unocchex);

          //max_motion_sensor->publish_state(max_m);
          //min_motion_sensor->publish_state(min_m);
          //max_presence_sensor->publish_state(max_p);
          //min_presence_sensor->publish_state(min_p);
          //unocc_time_sensor->publish_state(unocc_time / 10);

          return;
        }
      }

    protected:
      /// Read the illuminance value and store the calculated ambient illuminance in t_fine.
      float read_distance_(const uint8_t *data, int32_t *t_fine);

      sensor::Sensor *distance_sensor_{nullptr};
    };

  } // namespace hlk_ld2450
} // namespace esphome