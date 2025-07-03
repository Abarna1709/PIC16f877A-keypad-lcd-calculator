# 📟 Calculator Using PIC16F877A + 4x4 Keypad + 16x2 LCD

This is a mini embedded systems project that implements a **simple calculator** using the **PIC16F877A microcontroller**. The input is taken through a 4x4 matrix keypad, and the output is displayed on a 16x2 LCD.

---

## ✅ Features

- Supports basic operations: `+`, `-`, `*`, `/`
- Displays both input and result on LCD
- Clears screen with 'C' key
- Handles zero division safely

---

## 🧰 Components Used

- PIC16F877A
- 16x2 LCD Display (4-bit mode)
- 4x4 Matrix Keypad
- Resistors for pull-ups (10k)
- MPLAB X IDE + XC8 Compiler
- Proteus 8 for simulation

---

## 📁 Project Structure

PIC_Calculator_Project/
│
├── calculator.c → Main code for LCD + keypad + logic
├── proteus_simulation/ → Contains .dsn and .hex files
│ └── calculator.dsn
│ └── calculator.hex
├── README.md → You are reading this!


---

## ⚙️ How It Works

- Keypad rows: RB4–RB7  
- Keypad columns: RC0–RC3  
- LCD: RD0 (RS), RD1 (EN), RD4–RD7 (Data lines)

On boot:
1. Displays `"Calculator"` briefly
2. Takes input via keypad (e.g., `12+3=`)
3. Displays result on second line
4. Clears screen after a short delay

---


## 👤 Author

**ABARNA V**  

---
