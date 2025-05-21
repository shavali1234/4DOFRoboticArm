# 🤖 4 DOF Robot Arm Control Using Arduino Nano

This project demonstrates how to control a **4 DOF robotic arm** (frame purchased externally) using an **Arduino Nano**, **2-axis joystick**, **PCA9685 servo driver**, **2 push buttons**, and a **6-pin DPDT switch**. A **XY-3606 buck converter** is used to power the system by converting a 12V DC input to 5V for the Arduino and servos.

---

## 🧰 Hardware Components

- 🧠 Arduino Nano  
- 🦿 4 DOF Robot Arm Frame (purchased separately; electronics assembled manually)  
- 🎮 2-Axis Joystick Module  
- 🔘 2x Push Buttons  
- 🔀 6-pin DPDT Toggle Switch  
- 🧰 PCA9685 16-channel Servo Driver  
- 🔋 XY-3606 Buck Converter (12V to 5V)  
- ⚡ 12V DC Power Supply  
- 🧵 Jumper Wires, Breadboard or Custom PCB  

---

## 🔌 Power Supply Setup

- **XY-3606 Buck Converter** takes 12V input and outputs 5V.
- **5V Output Connections**:
  - Powers the **PCA9685 servo driver** (V+ pin)
  - Powers the **Arduino Nano** directly via the 5V and GND pins
- Ensure output is a stable 5V using a multimeter before connecting.

---

## ⚙️ Control Logic

- **Joystick X-axis** → Controls the **base rotation**
- **Joystick Y-axis** → Controls either the **shoulder** or the **elbow** (selected via DPDT switch):
  - DPDT Switch ON → Shoulder controlled
  - DPDT Switch OFF → Elbow controlled
- **Push Button 1** → Opens the **gripper**
- **Push Button 2** → Closes the **gripper**
- All servos are controlled through **PCA9685** over **I2C**, reducing PWM load on the Nano.

---

## 💻 Software Tools

- [Arduino IDE](https://www.arduino.cc/en/software)

### Required Libraries:

- `Adafruit PWM Servo Driver`  
- `Wire.h` (for I2C communication)

---

## 📁 Project Structure

4DOF_Robot_Arm/
├── code/
│ └── robot_arm_control.ino
├── images/
│ ├── wiring_diagram.png
│ ├── assembled_arm.jpg
├── README.md

yaml
Copy
Edit

---

## 🔧 How to Use

1. Set the **XY-3606** output to **5V** using a multimeter.
2. Connect the 12V power source to the XY-3606 input.
3. Upload the Arduino sketch to your Nano using the Arduino IDE.
4. Connect all components as per the wiring diagram.
5. Use the joystick, buttons, and switch to manually control the robotic arm.

---

## 🎥 Demo Video

[![Watch the demo](https://youtu.be/rfESmiidwMw?si=YtfuWVCvDmEFDHLR)

> Replace `VIDEO_ID` with your YouTube video ID or leave this section empty until video is available.

---

## 📌 Notes

- ✅ **Servo Angle Testing & Safety Notes**:
  - Before final operation, **test each servo individually** using a basic test code.
  - Gradually increase/decrease the angle using joystick or test script.
  - Observe the **mechanical range of each joint** to avoid:
    - **Over-rotating** the servo (usually beyond 0°–180°)
    - **Hitting the mechanical stops**, which can **damage servo gears or stress the frame**
  - Most hobby servos operate reliably within **20° to 160°**, but always **test per joint**.
  - If the arm jerks or vibrates at endpoints, **reduce the range immediately**.

- You are responsible for all **wiring, power management, and programming**; only the mechanical frame was purchased.
- Ensure proper mounting of servos to prevent mechanical strain.
- Always test movements gradually to avoid damaging servos or joints.
- If using high-torque servos, consider using external power with sufficient current.

---

