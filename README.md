## **Project Description**

This project is a secure **Password Manager** based on **Arduino Micro**. The device allows users to easily store and retrieve passwords.

### **Components:**

1. **microSD Adapter**  
2. **5-Button Keypad**  
3. **OLED Display**  

---

## **How It Works**

1. **File Preparation**  
   - Users create text files on the microSD card, each representing a service or application, with the corresponding password saved inside.

2. **Menu Navigation**  
   - Users can navigate the menu using the **5-button keypad**. When a file is selected, Arduino sends the corresponding password to the target device as if it were typed via a keyboard.

---

## **Usage Example**

1. Create 3 files on the microSD named: `Insta`, `Mail`, `TikTok`.  
2. Save the respective password inside each file.  

3. When a password is needed (e.g., to log in to an email account), the user selects the `Mail` file. Arduino automatically sends the password as if it were typed via a keyboard.

---

## **Convenience and Security**

- This device is extremely convenient for storing and using passwords without needing to remember or manually type them each time.  
- No complex software or app is required to access passwords; simply connect Arduino to the computer and select the desired file.  
- All passwords are stored locally on the microSD card and are not accessible via the internet or external devices. The Arduino only sends data through the serial port, ensuring no risk of unauthorized network access.  
- The only way to access the data is to physically steal the device.  
