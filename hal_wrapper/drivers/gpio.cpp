#include <pybind11/pybind11.h>
#include "gpio.h"
#include "../matrix.h"
#include "matrix_hal/gpio_control.h"
#include <stdexcept>

namespace py = pybind11;

matrix_hal::GPIOControl gpio_control;

// Convert python String to lowercase c++ string
std::string to_lower_case(py::str py_str){
    std::string str = py_str.cast<std::string>();

    for(uint i=0;i<str.length();i++)
        str.at(i)=std::tolower(str.at(i));

    return str;
}

// Helps to easily get a 0 or 1 value for GPIO settings (setMode, setFunction, etc..)
int parse_pin_setting(py::detail::tuple_accessor setting, std::string value_0, std::string value_1, std::string error){
    int result;
    // Get mode from a string or number
    if (py::isinstance<py::str>(setting)){
        if (to_lower_case(setting) == value_0)
            result = 0;
        else if (to_lower_case(setting) == value_1)
            result = 1;
        else
            throw std::runtime_error(error);
    }
    else if (py::isinstance<py::int_>(setting))
        result = setting.cast<int>();
    
    return result;
}

// **Exported GPIO class** //
void init_gpio(py::module &m) {
    py::class_<gpio>(m, "gpio")
        .def(py::init())
        .def("setMode", &gpio::setMode)
        .def("setFunction", &gpio::setFunction)
        .def("setDigital", &gpio::setDigital)
        .def("getDigital", &gpio::getDigital);
}

gpio::gpio(){
    gpio_control.Setup(&bus);
}

bool gpio::setMode(py::args args) {
    return gpio_control.SetMode(
        args[0].cast<int>(), 
        parse_pin_setting(args[1], "input", "output", 
            "Invalid string for setresult. Should be set to 'INPUT' or 'OUTPUT'")
    );
}

bool gpio::setFunction(py::args args) {
    return gpio_control.SetFunction(
        args[0].cast<int>(), 
        parse_pin_setting(args[1], "digital", "pwm", 
            "Invalid string for setFunction. Should be set to 'DIGITAL' or 'PWM'")
    );
}

bool gpio::setDigital(py::args args) {
    return gpio_control.SetGPIOValue(
        args[0].cast<int>(), 
        parse_pin_setting(args[1], "off", "on", 
            "Invalid string for setDigital. Should be set to 'ON' or 'OFF'")
    );
}

int gpio::getDigital(int pin) {
    return gpio_control.GetGPIOValue(pin);
}