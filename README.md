 Embedded JSON Serializer for w-M-Bus Gateways

 Project Overview
This project implements a lightweight, embedded-friendly C library that serializes structured smart-meter data into a predefined JSON format.  
It is designed for use in w-M-Bus gateway firmware and backend integration pipelines.

w-M-Bus communication, OMS decoding, encryption, and hardware interaction are intentionally out of scope.

---

 Platform and Language
- Language: C
- Target platforms: STM32 (STM32CubeIDE), ESP32 (ESP-IDF), Arduino
- Justification: Deterministic memory usage, minimal runtime overhead, and wide adoption in embedded firmware.

---

 Features
- No external JSON libraries
- Caller-provided output buffer
- Safe snprintf-based serialization
- Deterministic memory usage
- Clear error handling
- Transport-agnostic design

---

 Project Structure
