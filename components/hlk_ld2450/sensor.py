import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    STATE_CLASS_MEASUREMENT,
    UNIT_CENTIMETER,
    DEVICE_CLASS_DISTANCE,
    CONF_DISTANCE,
)

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@jrote1"]

hlk_ld2450_ns = cg.esphome_ns.namespace("hlk_ld2450")

HLKLD2450 = hlk_ld2450_ns.class_(
    "HLKLD2450", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONF_PRESENCE = "presence"
CONF_MOTION = "motion"
UNIT_BOOL = "true/false"

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.declare_id(HLKLD2450),
            cv.Optional(CONF_DISTANCE): sensor.sensor_schema(
                HLKLD2450,
                unit_of_measurement=UNIT_CENTIMETER,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_DISTANCE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_PRESENCE): cv.int_range(min=0, max=1),
            cv.Optional(CONF_MOTION): cv.int_range(min=0, max=1),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    
    if distance_config := config.get(CONF_DISTANCE):
        sens = await sensor.new_sensor(distance_config)
        cg.add(var.set_distance_sensor(sens))
    
    if presence_config := config.get(CONF_PRESENCE):
        sens = await sensor.new_sensor(presence_config)
        cg.add(var.set_presence_sensor(sens))
    
    if motion_config := config.get(CONF_MOTION):
        sens = await sensor.new_sensor(motion_config)
        cg.add(var.set_motion_sensor(sens))