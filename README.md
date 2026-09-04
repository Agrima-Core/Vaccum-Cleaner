# BLDC based light weight vaccum cleaner

## Overview

Automation has transformed domestic and industrial cleaning systems. Existing robotic cleaners are often costly and complex. This project demonstrates an affordable solution that performs suction and cleaning tasks effectively using simple hardware components controlled by Arduino UNO. The system aims to promote accessibility and innovation in home automation.

This prototype presents the design and implementation of a low-cost, autonomous robotic vacuum cleaner using Arduino UNO. The system integrates suction, cleaning, and driving mechanisms to achieve efficient cleaning performance. The project focuses on affordability and modularity, aiming to develop a system suitable for homes, schools, and workplaces.

---

## Components Required and System Design

### 2.1 Suction Mechanism
•	BLDC Motor (A2212/6T 12V 2200KV): Creates suction airflow
•	ESC 20A: Controls BLDC motor speed
•	Li-Po Battery: High discharge current for BLDC motor
•	Vacuum Chamber: Directs airflow efficiently


### 2.2 Cleaning Mechanism
Micro Servo Motor: Controls cleaning brush motion synchronized with suction system
### 2.3 Driving Mechanism
•	4 Gear Motors: Provide movement
•	2 L298N Motor Drivers: Control motor speed and direction
•	UV Sensor: Obstacle detection and surface edge sensing
•	Breadboard: Circuit prototyping
•	Li-ion Battery: Powers driving circuit
### 2.4 Charging Mechanism
Integrated charging port: Connected to battery terminals for convenient charging

---

## Working Principle
When powered on, the Arduino initializes all modules. The BLDC motor generates suction while the servo-controlled cleaning brush collects debris. The gear motors enable robot movement, and the UV sensor assists in obstacle detection. The system can operate in semi-autonomous mode and is rechargeable via the integrated charging port.


### Prototype
<img width="506" height="285" alt="image" src="https://github.com/user-attachments/assets/68d02cd6-e4fc-4a8b-9b1f-079d188da851" />

### Internal Components
<img width="294" height="503" alt="image" src="https://github.com/user-attachments/assets/90ac5cc2-d296-45d1-a5f3-6ee14cda65c7" />




## 5. Advantages
•	Low-cost and modular design
•	Efficient suction due to high-speed BLDC motor
•	Lightweight and portable
•	Demonstrates practical use of embedded systems



---

## 6. Applications
•	Home and office cleaning automation
•	Classroom and laboratory floor maintenance
•	Educational demonstration of embedded control and mechatronics



---
### 9. Conclusion
Future improvements may include IoT integration, AI-based path planning, automatic docking, smart mapping, and AI-based dirt detection to optimize cleaning performance.
The Robo-Vacuum prototype by Team Destiny demonstrates that low-cost components can be integrated to build an effective autonomous cleaning robot. The project successfully integrates suction, cleaning, and navigation mechanisms controlled by Arduino, providing a strong foundation for future intelligent robotic cleaners.The project  was collectively done by:-
Pranav Patil(Hardware Implementation and prototype developnment),
Agrima Adarsh(System design,hardware implementation and prototype developnment),
Abhisekh Kumar Singh(App Developnment) and
Prisha Chourasia(Market Analysis)


---

## Referances

1.	Arduino.cc — Official Documentation
2.	Datasheet: A2212/6T 2200KV BLDC Motor(Texas Instruments)
3.	L298N Motor Driver Module Specifications
4.	ESC 20A User Manual
5.	Li-Po and Li-ion Battery Performance Comparison — IEEE Spectrum, 2023


---


---

