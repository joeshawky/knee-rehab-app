# Knee Rehabilitation Control App

A cross-platform Qt application (Qt 6.6.3) built with QML (frontend) and C++ (backend), developed as part of my graduation project for controlling a knee rehabilitation robot.

This application acts as the main user interface to communicate with a Raspberry Pi over Bluetooth, enabling real-time motor control and feedback. It is deployable on both desktop and Android thanks to the flexibility of the Qt Framework.

## Features

- Cross-platform compatibility – runs on desktop and Android
- Bluetooth socket communication with Raspberry Pi
- Real-time telemetry: motor angle, active mode, power usage, etc.
- QML-based frontend for a responsive and user-friendly interface
- C++ backend for Bluetooth logic and hardware communication

## Project Structure

```
knee-rehab-app/
├── android/            # Android deployment config
├── src/                # C++ backend code
├── ui/                 # QML frontend components
├── Resources.qrc       # Qt resource file
├── CMakeLists.txt      # Build configuration
└── README.md
```

## Built With

- Qt Framework – version 6.6.3
- QML – UI layer
- C++ – backend logic and Bluetooth communication

## Getting Started

## Build & Run

### Desktop

1. Open the project in **Qt Creator**.
2. Select the kit: **Desktop Qt 6.6.3 MSVC2019 64bit**.
3. Click **Build** to compile the project.
4. Click **Run** to launch the application on desktop.

### Android

1. Open the project in **Qt Creator**.
2. Select the kit: **Desktop Qt 6.6.3 MinGW 64-bit** (configured for Android).
3. Connect your Android device via USB with developer mode enabled.
4. Click **Build and Run** to deploy the app to your device.

## How It Works

- The app connects to a paired Raspberry Pi via Bluetooth.
- Commands are sent to control the robot’s motor.
- Sensor data such as current angle, mode, and power consumption is received from the Raspberry Pi and displayed in the UI displayed in real time.

## User Interface

The application features a clean and responsive interface built with QML, designed for intuitive control and monitoring. The UI includes:

- A dashboard displaying real-time motor angle, power usage, and mode.
- Mode selection buttons to switch between available rehabilitation states.
- Bluetooth status indicator and connection controls.
- Platform-adaptive layout for both desktop and Android screens.
- A debug page that includes extra debugging information such as power consumption.
  
<img src="./docs/homepage.png" alt="Knee Rehab UI" width="300"/>

## Contact

Created by [@joeshawky](https://github.com/joeshawky)  
Feel free to open an issue or reach out with feedback or questions.

