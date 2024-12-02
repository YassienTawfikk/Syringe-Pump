# Syringe-Pump


The project integrates several advanced components such as a stepper motor, flow sensor, and a DS18B20 temperature sensor, with an LCD providing real-time data display. Its modular design allows for precise fluid control, temperature monitoring, and real-time alerts, making it versatile and adaptable for various applications like infusion pumps, chemical dispensing, and more.

### **1. Project Overview**
- **Brief Description:** The Syringe Pump project is a precise, programmable fluid dispensing system designed to meet a variety of medical and laboratory needs. This system leverages a stepper motor-driven syringe mechanism, real-time monitoring, and user-friendly feedback interfaces to achieve controlled fluid flow.

#### **Key Features**
- **Precision Control**:
  - Accurate syringe movement powered by a stepper motor with 1.8° step angle (200 steps/revolution).
  - Adjustable flow rates monitored and displayed on the LCD.
  
- **Real-Time Monitoring**:
  - Integrated flow sensor tracks fluid dispensing in mL/min.
  - DS18B20 sensor monitors system or environmental temperature.

- **User Feedback**:
  - LED indicator for alarms or warnings (e.g., high temperature).
  - Real-time data display on a 16x2 I2C LCD.

- **Emergency Control**:
  - Emergency stop buttons provide safety and control during operation.

- **Versatility**:
  - Easily adaptable for various syringe sizes and fluid viscosities.
  
This project serves as an excellent foundation for building intelligent medical or laboratory devices requiring precise fluid control and real-time monitoring capabilities.

---

### **2. Components List**


| **Component**            | **Quantity** | **Specification** or **Model**             |
|---------------------------|--------------|--------------------------------------------|
| Arduino Board             | 1            | Any compatible model (e.g., Arduino Uno)  |
| Stepper Motor             | 1            | Mercury Motor SM 42BYG011-25              |
| Stepper Motor Driver      | 1            | Any compatible driver                     |
| Flow Sensor               | 1            | YF-S201                                   |
| Temperature Sensor        | 1            | DS18B20                                   |
| I2C LCD Display           | 1            | 16x2 (0x27 address)                       |
| Resistors                 | 2            | 220Ω for LED, 4.7kΩ for DS18B20           |
| LED                       | 1            | Standard LED                              |
| Power Supply              | 1            | 12V battery + Arduino-powered 5V          |
| Syringe                   | 1            | For fluid dispensing                      |
| Miscellaneous             | -            | Jumper wires, breadboard, etc.            |


---
### **3. Connections**

### **Stepper Motor**
- **Model:** Mercury Motor SM 42BYG011-25
- **Specifications:**
  - Step Angle: **1.8°** (200 steps per revolution)
  - Rated Voltage: **12V**
  - Current: **0.33A**
  - Holding Torque: **2.5 kg.cm**
- **Integration:** The stepper motor is connected to a stepper motor driver, which interfaces with the Arduino.

### **Stepper Motor Driver**
- **Description:** The stepper motor driver controls the motion of the stepper motor based on signals received from the Arduino.
- **Connections:**
  - **STEP_PIN (D3):** Connected to the STEP pin of the stepper motor driver (controls the stepping pulse).
  - **DIR_PIN (D2):** Connected to the DIR pin of the stepper motor driver (controls rotation direction).
  - **ENABLE_PIN (D4):** Connected to the EN pin of the stepper motor driver (enables/disables the motor).
  - **Power Connections:**
    - **VCC1 & GND1:** Connected to the Arduino 5V and ground, respectively.
    - **VCC2 & GND2:** Connected to a **12V battery** and its ground to power the motor.
  - **Motor Output:** The driver outputs are connected to the stepper motor’s coils to generate motion.

### **Flow Sensor**
- **Description:** The flow sensor is used to monitor the flow rate of the fluid passing through the syringe hub.
- **Connections:**
  - **Signal (D6):** Connected to the **FLOW_SENSOR_PIN**.
  - **Power (VCC):** Connect to **5V**.
  - **Ground (GND):** Connect to Arduino ground.
- **Usage:** Provides real-time flow rate data in mL/min, linked to the syringe hub for fluid monitoring.

### **Syringe Hub**
- **Integration:** The syringe hub is driven by the stepper motor, with the flow sensor monitoring the output. This setup enables precise control and real-time feedback of fluid dispensing.

### **LED**
- **Purpose:** Visual indicator for system warnings (e.g., high temperature).
- **Connection:**
  - **LED_PIN (D5):** Connected to the LED anode.
  - **Resistor (220Ω):** In series with the LED to limit current.
  - **Cathode:** Connected to Arduino ground.

### **Temperature Sensor (DS18B20)**
- **Model:** Dallas DS18B20 Digital Temperature Sensor
- **Connections:**
  - **Data (D7):** Connected to **ONE_WIRE_BUS**.
  - **Power (VCC):** Connect to **5V**.
  - **Ground (GND):** Connect to Arduino ground.
  - **Pull-Up Resistor:** **4.7kΩ** resistor between data and VCC.

### **LCD Display**
- **Model:** I2C 16x2 LCD
- **Connections:**
  - **SDA:** Connect to Arduino **SDA** (A4 on UNO or dedicated SDA pin).
  - **SCL:** Connect to Arduino **SCL** (A5 on UNO or dedicated SCL pin).
  - **Power (VCC):** Connect to **5V**.
  - **Ground (GND):** Connect to Arduino ground.

---
