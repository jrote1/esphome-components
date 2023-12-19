import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@jrote1"]

hlk_ld2450_ns = cg.esphome_ns.namespace("hlk_ld2450")

HLKLD2450 = hlk_ld2450_ns.class_(
    "HLKLD2450", sensor.Sensor, cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.declare_id(HLKLD2450),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
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
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)