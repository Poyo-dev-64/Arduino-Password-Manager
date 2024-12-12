#include <SD.h>
#include <Wire.h>
#include <DoublyLinkedList.h>
#include <Keypad.h>
#include <Keyboard.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIN_SPI_CS 10
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DoublyLinkedList<String> files(true);
uint16_t currentFile = 0;
const int COLUMN_NUM = 5;
const int ROW_NUM = 1;
char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3', '4', '5'},
};
byte pin_rows[ROW_NUM] = {4};
byte pin_column[COLUMN_NUM] = {5, 6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void updateDisplay()
{
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.println(files[currentFile]);
    oled.display();
}

void checkSD()
{
    if (!SD.begin(PIN_SPI_CS))
    {
        oled.clearDisplay();
        oled.setCursor(0, 0);
        oled.println("SD not found");
        oled.println("Insert & reboot");
        oled.display();
        while (1);
    }
}

void setup()
{
    Serial.begin(115200);
    if (!oled.begin(SSD1306_I2C_ADDRESS, 0x3C))
    {
        Serial.println("OLED init failed");
        while (1);
    }
    oled.clearDisplay();
    oled.display();

    Keyboard.begin();
    checkSD();
    File root = SD.open("/");
    File entry = root.openNextFile();

    while (entry)
    {
        if (!entry.isDirectory())
            files.add(entry.name());
        entry.close();
        entry = root.openNextFile();
    }

    root.close();
    updateDisplay();
}

void loop()
{
    checkSD();
    char key = keypad.getKey();

    if (key == '4' && currentFile > 0)
    {
        currentFile--;
        updateDisplay();
    }

    if (key == '5' && currentFile < files.size() - 1)
    {
        currentFile++;
        updateDisplay();
    }

    if (key == '1')
    {
        File pwdFile = SD.open(files[currentFile]);
        String pwd = pwdFile.readString();
        pwd.replace("\n", "");
        Keyboard.print(pwd);
    }
}
