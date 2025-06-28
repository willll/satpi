# satpi

A C++ project using CMake, designed for modem and PPP handling with configuration via JSON.

## Features

- Loads configuration from `config.json`
- Uses Boost Property Tree for JSON parsing
- Logging via Boost.Log (see `Logger.h`)
- CMake-based build system

## Requirements

- C++17 or later
- [Boost](https://www.boost.org/) (including Boost.Log and Boost.PropertyTree)
- CMake 3.10+

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
  ]
}
```

## Logging

Logging is handled by the `Logger` class in `include/Logger.h`. By default, logs are printed to the console.

## Cleaning

To remove build artifacts:

```bash
rm -rf build bin
```

## License

[MIT](LICENSE) or your