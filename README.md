# 📦 Accelerometer-Based Display Control – Altera DE10-Lite FPGA Project

An educational project developed for the **Electronic Design Automation (EDA)** course, integrating an **SPI accelerometer** with an **Altera DE10-Lite FPGA platform**, using the **Nios II softcore processor** to control a **7-segment HEX display** based on device tilt.

---

## 🎯 Objective

To implement an interactive application that:

- Reads data from an accelerometer on the X and Y axes.
- Calculates tilt angle and movement direction.
- Displays a circle on one of the 6 HEX displays according to the X-axis tilt.
- Lights up specific LEDs based on Y-axis motion (up/down).

---

## 🧰 Technologies & Tools

- 🔌 **FPGA Board**: Altera DE10-Lite
- 🧠 **Softcore Processor**: Nios II
- 💻 **Languages**: C (software) + Verilog (hardware)
- 🧪 **Development Tools**: Intel Quartus Prime, Nios II Software Build Tools (SBT)
- 📡 **Accelerometer Interface**: SPI (Serial Peripheral Interface)

---

## 📁 Project Structure

- `main.c` – Core application logic:
  - Initializes the accelerometer and HEX display.
  - Continuously reads sensor values.
  - Computes angle and movement direction.
  - Updates HEX display accordingly.
- `Verilog/` – Verilog modules for:
  - SPI interface.
  - LED and display control.
- `README.md` – Project documentation (this file).

---

## ▶️ How to Run the Project

1. **Open the Quartus Prime project** and compile the FPGA design.
2. **Launch Nios II SBT for Eclipse**:
   - Create a new C project using `main.c`.
   - Link it with the generated `.sopcinfo` file.
   - Compile and upload the project to the DE10-Lite board.
3. **Open a serial terminal** (115200 baud) to monitor real-time angle and direction output.

---

## 🧪 What the Application Does

- Displays a circle on one of the 6 HEX displays based on X-axis tilt.
- Lights up top or bottom LEDs depending on Y-axis inclination.
- Outputs to terminal:
  - Calculated tilt angle (in degrees).
  - Movement direction (Up, Down, Left, Right).

---

## 🧑‍💻 Author

- **Teleki Ferenc-Tibor**  
  Student, SECI-SI, IESC  
  Transilvania University of Brașov, 2025

