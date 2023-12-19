import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    DEVICE_CLASS_ILLUMINANCE,
    STATE_CLASS_MEASUREMENT,
    UNIT_LUX,
)

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@OttoWinter"]

hlk_ld2450_ns = cg.esphome_ns.namespace("hlk_ld2450")

HLKLD2450 = hlk_ld2450_ns.class_(
    "HLKLD2450", sensor.Sensor, cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        HLKLD2450,
        unit_of_measurement=UNIT_LUX,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_ILLUMINANCE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Optional("resolution"): cv.invalid(
                "The 'resolution' option has been removed. The optimal value is now dynamically calculated."
            ),
            cv.Optional("measurement_duration"): cv.invalid(
                "The 'measurement_duration' option has been removed. The optimal value is now dynamically calculated."
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA),
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)