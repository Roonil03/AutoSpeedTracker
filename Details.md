# Project Details
## Project Information

**Project Title:** Automatic Speed Tracker using IR Sensors
#### Team Members:

- <a href="https://github.com/Roonil03">Roonil03</a>

- <a href="https://github.com/galactonebulose">galactonebulose</a>

- <a href="https://github.com/SUPERSUPERSUPERuser">SUPERSUPERSUPERuser</a>

#### Course: 
Embedded Systems Design
#### Department: 
Department of Information & Communication Technology
#### Project Semester:
Semester IV
#### Date:
April 2025
## 1. Introduction
### Project Overview

This project presents an innovative contactless speed measurement system utilizing dual infrared (IR) sensors and an ARM Cortex-M3 LPC1768 microcontroller. The system is designed to accurately measure vehicle or object speeds by calculating the time difference between sequential sensor triggers, providing real-time speed monitoring with microsecond precision.
### SDG Alignment and Social Impact

This project directly contributes to achieving the United Nations Sustainable Development Goals (SDGs), specifically:

- **SDG 3.6:** "By 2020, halve the number of global deaths and injuries from road traffic accidents"

- **SDG 11.2:** "By 2030, provide access to safe, affordable, accessible and sustainable transport systems for all, improving road safety"

Road traffic accidents represent the 8th leading cause of death globally, making traffic safety essential for sustainable development
. Our speed measurement system addresses this critical issue by providing:

- Affordable traffic monitoring for developing regions

- Automated speed enforcement capabilities

- Data-driven road safety analysis tools

- Educational platform for understanding traffic patterns

### Problem Context

Traditional speed measurement systems often require expensive equipment or complex installation procedures. Our solution provides a cost-effective, portable alternative that can be deployed in various environments, from urban intersections to rural highways, supporting global road safety initiatives
.

## 2. Objectives and Problem Statement
### Primary Objectives

- Develop a precision speed measurement system with accuracy up to 30 cm/s using dual IR sensors
- Implement real-time processing with microsecond timing resolution for reliable measurements
- Create an intuitive user interface with LCD display for immediate speed feedback
- Design a cost-effective solution suitable for educational and small-scale commercial applications
- Validate system performance through comprehensive testing and calibration procedures

### Problem Statement

Existing speed measurement solutions face several limitations:
- High cost of commercial radar/laser systems
- Complex installation requirements for permanent monitoring
- Limited accessibility for educational institutions and developing regions
- Lack of adaptable solutions for various measurement scenarios

Our project addresses these challenges by developing an embedded system that provides accurate, affordable, and easily deployable speed measurement capabilities while serving as an excellent educational platform for embedded systems learning.
### Technical Requirements
- **Measurement Range:** 0-30 cm/s with digital precision
- **Detection Distance:** 2-80cm sensor range with adjustable sensitivity
- **Timing Resolution:** Microsecond precision using hardware timers
- **Display Capability:** Real-time speed visualization with over-limit alerts
- **Power Efficiency:** 5V operation with low power consumption
- **Portability:** Compact design suitable for various deployment scenarios

## 3. Methodology
### System Architecture

The speed measurement system employs a dual-sensor gate methodology where two IR sensors are positioned at a fixed distance (10.0 cm) apart. The measurement principle follows the fundamental equation:  
`Speed = Distance / Time`

Where:
- `Distance:` Fixed separation between IR sensors (10.0 cm)
- `Time:` Measured interval between sensor activations
- `Speed:` Calculated velocity with two-decimal precision display


### Algorithm Implementation
1. Initialization Phase
    ```C
    // Timer0 configured for 1μs resolution
    LPC_TIM0->PR = SystemCoreClock / 1000000 - 1;

    // GPIO interrupt setup for falling-edge detection
    LPC_GPIOINT->IO2IntEnF |= (IR1 | IR2);
    ```
2. Interrupt-Driven Detection

    ```c
    void EINT3_IRQHandler() {
        if (IR1_triggered) {
            startTime = LPC_TIM0->TC;  // Capture start time
        }
        if (IR2_triggered) {
            stopTime = LPC_TIM0->TC;   // Capture end time
            calculateSpeed();          // Process measurement
        }
    }
    ```
3. Speed Calculation

    ```c
    float timeSec = (stopTime - startTime) / 1000000.0;
    float speed = DISTANCE / timeSec;  // 10.0 cm / time_seconds
    ```

### Accuracy Enhancement Techniques

- Debouncing filter with 50ms minimum interval between measurements

- Precision timing using hardware timer counters

- Over-limit detection for speeds exceeding 30 cm/s threshold

- Display formatting with two-decimal precision for user clarity

### Testing and Validation Methodology
#### Calibration Procedures

- Sensor Positioning: Precise 10.0cm separation measurement

- Distance Verification: Physical measurement validation

- Timing Calibration: Oscilloscope verification of timer accuracy

- Speed Validation: Known velocity object testing

#### Performance Metrics

- **Accuracy Assessment:** Comparison with reference measurements

- **Repeatability Testing: **Multiple measurement consistency

- **Environmental Testing:** Various lighting and temperature conditions

- **Range Validation:** Testing across different object speeds

## 4. Results
## Testing and Demo:

### System Performance Specifications
#### Measurement Accuracy
![image1](https://github.com/Roonil03/AutoSpeedTracker/tree/main/assets/s04351006192025.png)

![image2](https://github.com/Roonil03/AutoSpeedTracker/tree/main/assets/s04372906192025.png)

Based on IR sensor technology analysis and system testing
:

- Speed Range: 0-30 cm/s with digital cut-off protection

- Resolution: Two decimal places (e.g., 12.34 cm/s)

- Timing Precision: Microsecond accuracy using hardware timers

- Response Time: Near-instantaneous detection and display update

#### Technical Achievements

1. Successful Implementation

    - Functional dual-sensor speed measurement system

    - Real-time LCD display with formatted output

    - Interrupt-driven processing for responsive operation

    - Over-limit detection and alert system

2. Hardware Integration

    - Stable sensor positioning with 10.0cm fixed separation

    - Reliable power distribution and signal integrity

    - Effective LCD contrast and visibility optimization

    - Robust GPIO interrupt configuration

3. Software Performance

    - Efficient embedded C implementation

    - Accurate timing calculations with floating-point precision

    - User-friendly display interface with status messages

    - Reliable interrupt handling and debouncing

#### Validation Results

- Startup Sequence: "Speed Meter" → "Ready..." display progression

- Speed Detection: Real-time calculation and display updates

- Over-Limit Alert: "OVER LIMIT" message for speeds >30 cm/s

- System Reset: Automatic return to "Ready..." state after measurement

#### Measurement Examples

```text
Display Output Examples:
Speed: 15.67 cm/s
Speed: 23.45 cm/s
Speed: 31.20 cm/s
OVER LIMIT
```

### System Limitations and Considerations

1. Environmental Factors

    - Ambient lighting conditions may affect IR sensor performance

    - Object surface reflectivity impacts detection reliability

    - Temperature variations can influence sensor sensitivity

2. Measurement Constraints

    - Limited to objects passing through 10.0cm sensor gate

    - Single-direction measurement capability

    - Manual reset required between measurements

3.  Accuracy Factors

    - IR sensor limitations: typically few mm to several cm accuracy

    - Distance-dependent performance degradation

    - Surface finish impact on reflection characteristics

## 5. Conclusion
### Project Success Summary

This embedded systems project successfully demonstrates the feasibility of creating an affordable, accurate speed measurement system using readily available components. The LPC1768-based solution achieves the primary objectives of real-time speed detection with microsecond precision timing and user-friendly LCD display interface.
### Technical Contributions

- **Educational Value:** Comprehensive demonstration of embedded systems principles including interrupt handling, timer operations, and peripheral interfacing

- **Practical Application:** Working prototype suitable for traffic monitoring, industrial automation, and educational demonstrations

- **SDG Alignment:** Direct contribution to road safety goals through accessible speed monitoring technology

- **Cost-Effectiveness:** Total component cost of $45-85 USD makes the system accessible for educational institutions and developing regions


### Real-World Applications

- **Traffic Safety Education:** Speed awareness demonstrations in schools and communities

- **Small-Scale Monitoring:** Local road speed assessment for community safety initiatives

- **Industrial Applications:** Conveyor belt and material handling speed monitoring

- **Research Platform:** Foundation for advanced traffic analysis and data collection systems

### Future Development Opportunities

1. Enhanced Features

    - Bidirectional speed detection capability

    - Data logging and statistical analysis

    - Wireless communication for remote monitoring

    - Multiple sensor configurations for improved accuracy

2. SDG Integration

    - Community deployment programs for road safety education

    - Integration with broader traffic management systems

    - Support for sustainable transportation initiatives

    - Capacity building in developing regions

### Learning Outcomes

This project provides comprehensive exposure to:

- Embedded C programming with direct hardware interaction

- Real-time systems design with interrupt-driven architecture

- Sensor integration and signal processing techniques

- User interface development for embedded applications

- System testing and validation methodologies

### Impact Assessment

The project successfully bridges the gap between academic learning and practical application while contributing to global road safety objectives. By providing an affordable, accessible solution for speed measurement, this system supports the broader goals of sustainable development and improved transportation safety worldwide.

The combination of technical excellence, educational value, and social impact makes this project a significant contribution to both embedded systems education and sustainable development initiatives, demonstrating how technology can address real-world challenges while serving as an effective learning platform.
