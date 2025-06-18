# Automatic Speed Tracker using IR Sensors

## Overview

The IR Sensor Speed Measurement System is an embedded C project built for the LPC1768 ARM Cortex-M3 microcontroller that provides contactless speed measurement using dual infrared sensors. The system calculates object velocity by measuring the time taken for an object to travel between two precisely positioned IR sensors, displaying real-time results on a 16x2 LCD display with microsecond precision timing.

This project addresses UN Sustainable Development Goals (SDG 3.6 and SDG 11.2) by providing affordable traffic monitoring solutions for road safety improvement, making it suitable for educational institutions, small-scale commercial applications, and developing regions.

For further details on the software as well as the details on the project, please refer the `\docs` folder.

This project was done as part of our ES Lab Project.
## Features

### Core Functionality
- **Contactless Speed Detection**: Dual IR sensor configuration for non-intrusive measurement
- **High Precision Timing**: Microsecond resolution using hardware timer interrupts
- **Real-time Display**: 16x2 LCD showing speed measurements with 2-decimal precision
- **Over-limit Protection**: Automatic "OVER LIMIT" warning for speeds exceeding 30 cm/s
- **Interrupt-driven Processing**: Efficient system response with minimal CPU overhead

### Technical Specifications
- **Speed Range**: 0-30 cm/s with digital cut-off
- **Sensor Range**: 2-80cm detection distance with adjustable sensitivity
- **Timing Resolution**: 1μs precision using LPC1768 hardware timers
- **Display Format**: Real-time speed in cm/s (e.g., "Speed: 15.67 cm/s")
- **Power Requirements**: 5V DC operation

### Educational Value
- Demonstrates embedded systems principles including interrupt handling and timer operations
- Comprehensive sensor integration and signal processing techniques
- Real-time systems design with hardware-software interaction
- Practical application of embedded C programming

## Hardware Requirements

### Essential Components
- **LPC1768 Development Board** - ARM Cortex-M3 microcontroller (100MHz, 512KB Flash, 64KB SRAM)
- **2x IR Obstacle Avoidance Sensors** - Digital output with LM393 comparator, 2-80cm range
- **16x2 Character LCD Display** - HD44780 compatible controller, 5V operation
- **USB-to-TTL Serial Converter** - For programming (FT232RL recommended)
- **5V DC Power Supply** - For system power
- **Breadboard and Jumper Wires** - For prototyping connections
- **Potentiometer** - For LCD contrast adjustment

### Supporting Materials
- 2x 10-core FRC cables (8 inch length)
- USB to B-type cable
- Cross cable for programming and serial communication

**Total Cost**: $45-85 USD depending on component quality and supplier

## Software Requirements

### Development Environment
- **Keil μVision4 IDE** - Primary development environment with ARM Cortex-M3 support
- **Flash Magic v13.10+** - For In-System Programming (ISP) of LPC1768
- **Windows 7-11** - Operating system compatibility
- **USB-to-Serial Drivers** - FT232RL or CH340G drivers as needed

### Alternative Options
- MCUXpresso IDE from NXP
- ARM mbed online compiler
- PlatformIO with Visual Studio Code

## Hardware Setup

### Pin Connections

#### IR Sensors
- **IR Sensor 1** → P2.10 (GPIO interrupt input)
- **IR Sensor 2** → P2.11 (GPIO interrupt input)
- **Power**: 5V and GND to both sensors

#### LCD Display (4-bit mode)
- **Data Lines**: D4-D7 → P0.4-P0.7
- **Control Lines**: RS → P0.0, EN → P0.1
- **Power**: 5V, GND, and contrast potentiometer

#### Programming Interface
- **USB-to-TTL TX** → P0.3 (UART0 RX)
- **USB-to-TTL RX** → P0.2 (UART0 TX)
- **Common Ground** connection

### Physical Setup
1. Position IR sensors exactly **10.0 cm apart** for accurate measurements
2. Ensure sensors are aligned parallel to the measurement path
3. Connect LCD with proper contrast adjustment using potentiometer
4. Verify all power connections are stable and properly grounded

## How to Download and Run the Application

### Step 1: Download and Setup
1. **Clone the repository** or download the project files
2. **Install Keil μVision4** IDE (requires ~800MB disk space)
3. **Install Flash Magic** v13.10 or later for programming
4. **Install USB-to-Serial drivers** (FT232RL auto-installs on Windows 10/11)

### Step 2: Project Setup in Keil μVision4
1. **Create Project Folder**: Create a dedicated folder for your project
2. **Start Keil μVision4**: Launch the IDE
3. **Create New Project**: 
   - Go to Project → New μVision Project
   - Navigate to your project folder and save with a descriptive name
4. **Select Device**: 
   - Choose "NXP (founded by Philips)" as vendor
   - Select "LPC1768" 
   - Click OK and then YES to add system files

### Step 3: Add Source Files
1. **Create Source File**: 
   - File → New to open editor
   - Copy the provided C code from `C_Code.c`
   - Save with `.c` extension
2. **Add to Project**:
   - Right-click "Source Group 1"
   - Select "Add Files to Group 'Source Group 1'"
   - Add your `.c` source file
   - Add `system_LPC17xx.c` from `C:\Keil\ARM\startup\NXP\LPC17xx\`

### Step 4: Build Configuration
1. **Set Output Options**:
   - Right-click "TARGET1" → Options for Target
   - Go to "Output" tab → Select "Create Hex File"
2. **Build Project**:
   - Project → Build Target (or F7)
   - Verify no errors in build output

### Step 5: Programming with Flash Magic
1. **Hardware Preparation**:
   - Connect USB-to-TTL converter to PC and LPC1768
   - Connect 9-pin DSUB cross cable from PC to CN9 on board
   - Set 2-way DIP switch SW21 and short jumper JP3
2. **Flash Magic Configuration**:
   - **Device**: LPC1768
   - **COM Port**: Select appropriate COM port
   - **Baud Rate**: 9600 (for initial programming)
   - **Interface**: None (ISP)
   - **Oscillator**: 12MHz
3. **Programming Options**:
   - **Erase**: Select "Erase Blocks Used by Hex File"
   - **Hex File**: Browse and select your generated .hex file
   - **Options**: Select "Verify After Programming"
4. **Advanced Settings**:
   - Go to Options → Advanced Options → Hardware Config
   - Select "Use DTR & RTS to control RST & ISP Pin"
   - Select "Keep RTS asserted while COM Port open"
   - T1 = 50ms, T2 = 100ms
5. **Program**: Click "Start" to download hex file to controller

### Step 6: System Testing
1. **Hardware Connections**:
   - Connect 10-pin FRC cables: CNA1 to CNA, CNB1 to CNB
   - Ensure all power connections are stable
2. **Power On**: Apply 5V power to the system
3. **Reset**: Press reset switch SW1 on the board
4. **Verify Operation**: LCD should display "Speed Meter" then "Ready..."

## Usage

### Steps to Use the Speed Measurement System

1. **Power On**: Connect 5V power supply and ensure LCD displays startup sequence
2. **System Ready**: Wait for "Ready..." message on LCD display
3. **Position Object**: Align object to pass through both IR sensor beams sequentially
4. **Measurement**: Move object through sensor gate at desired speed
5. **View Results**: Speed displays automatically in format "Speed: XX.XX cm/s"
6. **Over-limit Detection**: If speed exceeds 30 cm/s, "OVER LIMIT" warning appears
7. **Reset**: System automatically returns to "Ready..." state for next measurement

### Example Output
```
Speed Meter
Ready...
Speed: 15.67 cm/s
Speed: 23.45 cm/s
Speed: 31.20 cm/s
OVER LIMIT
Ready...
```

### Calibration and Testing
- **Sensor Alignment**: Verify 10.0 cm exact separation distance
- **Sensitivity Adjustment**: Use onboard potentiometers for optimal detection
- **Known Velocity Testing**: Validate accuracy using objects with known speeds
- **Environmental Testing**: Test under various lighting conditions

## Troubleshooting

### Common Issues and Solutions

**LCD Display Problems**:
- Check power connections (5V, GND)
- Adjust contrast using potentiometer
- Verify pin connections (P0.0-P0.7)

**Sensor Issues**:
- Adjust sensitivity potentiometers on IR sensors
- Check power supply stability (5V)
- Verify sensor alignment and 10.0 cm separation

**Programming Difficulties**:
- Verify COM port selection in Flash Magic
- Check USB-to-Serial driver installation
- Ensure proper ISP mode entry (button sequence)
- Try reducing baud rate to 9600 for problematic connections

**No Speed Detection**:
- Confirm interrupt configuration for P2.10 and P2.11
- Check sensor power and ground connections
- Verify object passes through both sensor beams sequentially

## Applications

### Educational Uses
- Embedded systems programming instruction
- Sensor integration and signal processing learning
- Real-time systems design demonstration
- Microcontroller peripheral interfacing

### Practical Applications
- Small-scale traffic speed monitoring
- Conveyor belt speed measurement
- Educational speed awareness demonstrations
- Industrial automation and material handling

### SDG Contribution
- Road safety education and awareness
- Affordable traffic monitoring for developing regions
- Data collection for transportation safety analysis
- Community-based speed enforcement initiatives

## Conclusion

The IR Sensor Speed Measurement System demonstrates practical embedded systems design while contributing to global road safety objectives. This cost-effective, educational platform provides hands-on experience with microcontroller programming, sensor integration, and real-time systems design, making it an excellent project for both learning and practical applications in traffic monitoring and industrial automation.

The project successfully bridges academic learning with real-world problem-solving, offering an accessible solution for speed measurement while serving as a comprehensive educational tool for embedded systems development.