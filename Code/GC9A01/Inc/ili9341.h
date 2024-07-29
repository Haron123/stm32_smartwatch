#ifndef ILI9341
#define ILI9341

#ifdef __cplusplus
extern "C" {
#endif

#include "timer.h"
#include "Soft_SPI.h"
 
#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 240

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0xD3
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0D
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_MADCTL  0x36
#define ILI9341_PIXFMT  0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1

// Color definitions
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

#define RDX_SETUPTIME_US 0
#define DATA_SETUPTIME_US 0

#define CONTROL_PORT GPIOA /* GPIO_TypeDef* */
#define LCD_RST 5
#define LCD_DC 4

/**
 * @brief Sets up the LCD
*/
void lcd_setup(Soft_SPI spi);

/**
 * @brief sends a command to the interfaced device
 * @param command the byte value of the command
*/
void writecmd(Soft_SPI spi, uint8_t command);

/**
 * @brief writes data to the interfaced device
 * @param data 16 bits of data that will be put on the bus
*/
void writedata(Soft_SPI spi, uint16_t data);

/**
 * @brief read a byte of data, usually used after sending a command
 * and expecting a reply
*/
uint8_t read8();

/**
 * @brief reads the id register 0x04 of the lcd 
*/
uint32_t readID();

/**
 * @brief Draws a Rectangle on the LCD
 * @param x start x position
 * @param y start y position
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @param color the color of the rectangle
*/
void lcd_rect(Soft_SPI spi, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

/**
 * @brief Draws a single pixel on the LCD
 * @param x x position of the pixel
 * @param y y position of the pixel
 * @param color color of the pixel
*/
void lcd_drawpixel(Soft_SPI spi, int16_t x, int16_t y, uint16_t color);

/**
 * @brief no clue what this does honestly
*/
void lcd_pushcolor(Soft_SPI spi, uint16_t color);

/**
 * @brief setup an address window
 * @param x0 x position start
 * @param y0 y position start
 * @param x1 x position end
 * @param y1 y position end
*/
void lcd_setwindow(Soft_SPI spi, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void lcd_drawimage(Soft_SPI spi, uint16_t* img, uint16_t x, uint16_t y, uint32_t size, uint32_t scaling);

#ifdef __cplusplus
}
#endif

#endif