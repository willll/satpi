<p align="center">
  <img src="logo/logo.svg" alt="satpi logo" height="128"/>
</p>

# satpi

[![Build (Linux x64)](https://github.com/willll/satpi/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)](https://github.com/willll/satpi/actions/workflows/cmake-multi-platform.yml)
[![Doxygen Docs](https://github.com/willll/satpi/actions/workflows/doxygen.yml/badge.svg?branch=main)](https://github.com/willll/satpi/actions/workflows/doxygen.yml)

**satpi** is a modern C++17 project for managing modem and PPP (Point-to-Point Protocol) connections, with a focus on flexibility, logging, and easy configuration. It is designed for use on Linux systems, including embedded and Raspberry Pi environments.

## Features

- Loads configuration from a simple `config.json` file
- Supports custom modem port, baud rate, PPPD options, and network interfaces
- Uses Boost.PropertyTree for robust JSON parsing
- Logging via Boost.Log, with easy integration and configuration
- CMake-based build system for portability and easy integration
- Includes NAT setup/teardown utilities for PPP tunnels
- Well-structured codebase with Doxygen documentation and UML diagrams

## Requirements

- C++17 or later
- [Boost](https://www.boost.org/) (including Boost.Log and Boost.PropertyTree)
- CMake 3.10+
- Linux (tested on x86_64 and Raspberry Pi)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

The main binary will be located in `bin/` or `build/` depending on your configuration.

## Configuration

Edit `config.json` in the project root. Example:

```json
{
  "modem_port": "/dev/ttyUSB0",
  "baud_rate": 115200,
  "pppd_options": [
    "local",
    "noauth",
    "nodetach",
    "proxyarp",
    "debug"
  ],
  "lan_interface": "wlan0",
  "ppp_interface": "ppp0"
}
```

- **modem_port**: Serial port for the modem (e.g., `/dev/ttyUSB0`)
- **baud_rate**: Baud rate for the modem connection
- **pppd_options**: List of options passed to `pppd`
- **lan_interface**: LAN interface for NAT (e.g., `wlan0`)
- **ppp_interface**: PPP interface name (e.g., `ppp0`)

## Logging

Logging is handled by the `Logger` class in `include/Logger.h`. By default, logs are printed to the console, but you can easily extend this to log to files or other sinks.

## Documentation

Doxygen documentation is generated automatically via GitHub Actions. You can find the latest build artifacts in the Actions tab or generate locally with:

```bash
doxygen Doxyfile
```

UML and relationship diagrams are included in the generated documentation.

## Cleaning

To remove build artifacts:

```bash
rm -rf build bin
```

## Contributing

Contributions, bug reports, and feature requests are welcome! Please open an issue or submit a pull request.

## License

[MIT](LICENSE)

---

**satpi** is maintained by [willll](https://github.com/willll)