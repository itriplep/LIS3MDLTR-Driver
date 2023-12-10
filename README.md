# LIS3MDLTR Driver

## Introduction

This C program serves as a driver for the LIS3MDLTR Digital Output Magnetic Sensor. The LIS3MDLTR is an ultralow-power, high-performance 3-axis magnetometer. The driver adopts an object-oriented style and employs a two-layer architecture consisting of HAL (Hardware Abstraction Layer) and PAL (Platform Abstraction Layer). Unit testing is facilitated using the Unity/Ceedling framework.

## Features

- Retrieve the device’s full-scale configuration
- Retrieve and set the device’s output data rate
- Enable or disable the device’s interrupt pin
- Read the output data of a specific axis

## Documentation

For detailed information about the project, including API documentation, please refer to the [Doxygen Output](Doxygen%20Output/html/index.html).

## Getting Started

To build and use this driver, follow the steps below:

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/LIS3MDLTR-Driver.git
2. Navigate to the project directory:
   ```bash
   cd LIS3MDLTR-Driver
3. Build the project using your preferred build system.
4. Refer to the Doxygen documentation for API details.

## Dependencies

- [Unity](https://github.com/ThrowTheSwitch/Unity)
- [Ceedling](https://github.com/throwtheswitch/ceedling)

## Contributing

Feel free to open issues, submit pull requests, or suggest improvements. Contributions are welcome!

## License

This project is licensed under the [MIT License](LICENSE).
