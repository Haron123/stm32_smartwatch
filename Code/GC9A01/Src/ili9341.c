#include "ili9341.h"

static inline  void enter_command_mode()
{
  CONTROL_PORT->BSRR = ((1 << LCD_DC) << 16);
  #if CSX_SETUPTIME_US > 0
  //timer_delay_us(CSX_SETUPTIME_US);
  #endif
}

static inline  void enter_data_mode()
{
  CONTROL_PORT->BSRR = (1 << LCD_DC);
  #if CSX_SETUPTIME_US > 0
  //timer_delay_us(CSX_SETUPTIME_US);
  #endif
}

static inline void reset()
{
  CONTROL_PORT->BSRR = (1 << LCD_RST);
  timer_delay_ms(5);
  CONTROL_PORT->BSRR = ((1 << LCD_RST) << 16);
  timer_delay_ms(20);
  CONTROL_PORT->BSRR = (1 << LCD_RST);
  timer_delay_ms(150);
}

static void begin(Soft_SPI spi) 
{
 /*Regulative Initiation*/
	reset();
	writecmd(spi, 0xef); //Inter Register Enable2
	writecmd(spi, 0xeb);
	writedata(spi, 0x14);
	writecmd(spi, 0xfe); //Inter Register Enable1
	writecmd(spi, 0xef); //Inter Register Enable2

	writecmd(spi, 0xeb);
	writedata(spi, 0x14);

	writecmd(spi, 0x84);        // ?
	writedata(spi, 0x40);
	writecmd(spi, 0x85);        // ?
	writedata(spi, 0xFF);
	writecmd(spi, 0x86);        // ?
	writedata(spi, 0xFF);
	writecmd(spi, 0x87);        // ?
	writedata(spi, 0xFF);
	writecmd(spi, 0x88);        // ?
	writedata(spi, 0x0A);
	writecmd(spi, 0x89);        // ?
	writedata(spi, 0x21);
	writecmd(spi, 0x8A);        // ?
	writedata(spi, 0x00);
	writecmd(spi, 0x8B);        // ?
	writedata(spi, 0x80);
	writecmd(spi, 0x8C);        // ?
	writedata(spi, 0x01);
	writecmd(spi, 0x8D);        // ?
	writedata(spi, 0x01);
	writecmd(spi, 0x8E);        // ?
	writedata(spi, 0xFF);
	writecmd(spi, 0x8F);        // ?
	writedata(spi, 0xFF);

	writecmd(spi, 0xb6); //Scan direction S360 -> S1
	writedata(spi, 0x00);
	writedata(spi, 0x20);
	writecmd(spi, 0x3a); //Pixel format set
	writedata(spi, 0x05); //MCU 16 bit

	writecmd(spi, 0x90);        // ?
	writedata(spi, 0x08);
	writedata(spi, 0x08);
	writedata(spi, 0x08);
	writedata(spi, 0x08);
	writecmd(spi, 0xBD);        // ?
	writedata(spi, 0x06);
	writecmd(spi, 0xBC);        // ?
	writedata(spi, 0x00);
	writecmd(spi, 0xFF);        // ?
	writedata(spi, 0x60);
	writedata(spi, 0x01);
	writedata(spi, 0x04);

	writecmd(spi, 0xc3); //Power 2
	writedata(spi, 0x13);
	writecmd(spi, 0xc4); //Power 3
	writedata(spi, 0x13);
	writecmd(spi, 0xc9); //Power 4
	writedata(spi, 0x22);

	writecmd(spi, 0xBE);        // ?
	writedata(spi, 0x11);
	writecmd(spi, 0xE1);        // ?
	writedata(spi, 0x10);
	writedata(spi, 0x0E);
	writecmd(spi, 0xDF);        // ?
	writedata(spi, 0x21);
	writedata(spi, 0x0c);
	writedata(spi, 0x02);

	writecmd(spi, 0xF0); //Gamma 1
	writedata(spi, 0x45);
	writedata(spi, 0x09);
	writedata(spi, 0x08);
	writedata(spi, 0x08);
	writedata(spi, 0x26);
	writedata(spi, 0x2a);
	writecmd(spi, 0xF1); //Gamma 2
	writedata(spi, 0x43);
	writedata(spi, 0x70);
	writedata(spi, 0x72);
	writedata(spi, 0x36);
	writedata(spi, 0x37);
	writedata(spi, 0x6f);
	writecmd(spi, 0xF2); //Gamma 3
	writedata(spi, 0x45);
	writedata(spi, 0x09);
	writedata(spi, 0x08);
	writedata(spi, 0x08);
	writedata(spi, 0x26);
	writedata(spi, 0x2a);
	writecmd(spi, 0xF3); //Gamma 4
	writedata(spi, 0x43);
	writedata(spi, 0x70);
	writedata(spi, 0x72);
	writedata(spi, 0x36);
	writedata(spi, 0x37);
	writedata(spi, 0x6f);

	writecmd(spi, 0xED);        // ?
	writedata(spi, 0x1B);
	writedata(spi, 0x0B);
	writecmd(spi, 0xAE);        // ?
	writedata(spi, 0x77);
	writecmd(spi, 0xCD);        // ?
	writedata(spi, 0x63);
	writecmd(spi, 0x70);        // ?
	writedata(spi, 0x07);
	writedata(spi, 0x07);
	writedata(spi, 0x04);
	writedata(spi, 0x0E);
	writedata(spi, 0x0F);
	writedata(spi, 0x09);
	writedata(spi, 0x07);
	writedata(spi, 0x08);
	writedata(spi, 0x03);

	writecmd(spi, 0xe8); //4 dot inversion
	writedata(spi, 0x34);

	writecmd(spi, 0x62);        // ?
	writedata(spi, 0x18);
	writedata(spi, 0x0D);
	writedata(spi, 0x71);
	writedata(spi, 0xED);
	writedata(spi, 0x70);
	writedata(spi, 0x70);
	writedata(spi, 0x18);
	writedata(spi, 0x0F);
	writedata(spi, 0x71);
	writedata(spi, 0xEF);
	writedata(spi, 0x70);
	writedata(spi, 0x70);

	writecmd(spi, 0x63);        // ?
	writedata(spi, 0x18);
	writedata(spi, 0x11);
	writedata(spi, 0x71);
	writedata(spi, 0xF1);
	writedata(spi, 0x70);
	writedata(spi, 0x70);
	writedata(spi, 0x18);
	writedata(spi, 0x13);
	writedata(spi, 0x71);
	writedata(spi, 0xF3);
	writedata(spi, 0x70);
	writedata(spi, 0x70);

	writecmd(spi, 0x64);        // ?
	writedata(spi, 0x28);
	writedata(spi, 0x29);
	writedata(spi, 0xF1);
	writedata(spi, 0x01);
	writedata(spi, 0xF1);
	writedata(spi, 0x00);
	writedata(spi, 0x07);

	writecmd(spi, 0x66);        // ?
	writedata(spi, 0x3C);
	writedata(spi, 0x00);
	writedata(spi, 0xCD);
	writedata(spi, 0x67);
	writedata(spi, 0x45);
	writedata(spi, 0x45);
	writedata(spi, 0x10);
	writedata(spi, 0x00);
	writedata(spi, 0x00);
	writedata(spi, 0x00);

	writecmd(spi, 0x67);        // ?
	writedata(spi, 0x00);
	writedata(spi, 0x3C);
	writedata(spi, 0x00);
	writedata(spi, 0x00);
	writedata(spi, 0x00);
	writedata(spi, 0x01);
	writedata(spi, 0x54);
	writedata(spi, 0x10);
	writedata(spi, 0x32);
	writedata(spi, 0x98);

	writecmd(spi, 0x74);        // ?
	writedata(spi, 0x10);
	writedata(spi, 0x85);
	writedata(spi, 0x80);
	writedata(spi, 0x00);
	writedata(spi, 0x00);
	writedata(spi, 0x4E);
	writedata(spi, 0x00);

	writecmd(spi, 0x98);        // ?
	writedata(spi, 0x3e);
	writedata(spi, 0x07);

	writecmd(spi, 0x36); //Memory data access control
	writedata(spi, 0x00);//0x08 bgr, 0x00 rgb

	writecmd(spi, 0x34); //Tearing effect OFF

	writecmd(spi, 0x21); //Inversion ON
	writecmd(spi, 0x11); //Sleep mode OUT
	timer_delay_ms(120);
	writecmd(spi, 0x29); //Display ON
	timer_delay_ms(20);

  	//lcd_rect(spi, 0, 0, 240, 240, BLACK);
}

void lcd_setup(Soft_SPI spi)
{
	spi_start(&spi);

  gpio_setup_full(CONTROL_PORT, LCD_DC, OUTPUT, PULL_UP, PUSH_PULL, VERY_HIGH_SPEED);
  gpio_setup_full(CONTROL_PORT, LCD_RST, OUTPUT, PULL_UP, PUSH_PULL, VERY_HIGH_SPEED);

  enter_data_mode();

  begin(spi);
}

static inline void write8(Soft_SPI spi, uint8_t c)
{
  spi_write(&spi, c);
}

static inline void write16(Soft_SPI spi, uint16_t c)
{
  spi_write(&spi, c & 0xFF);
  spi_write(&spi, (c >> 8) & 0xFF);
}

inline void writecmd(Soft_SPI spi, uint8_t c)
{
  enter_command_mode();
  write8(spi, c);
}

inline void writedata(Soft_SPI spi, uint16_t c)
{
  enter_data_mode();
  write8(spi, c);
}

void lcd_setwindow(Soft_SPI spi, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
{								
  enter_command_mode();
  write8(spi, ILI9341_CASET); // Column addr set
  enter_data_mode();
  write8(spi, x0 >> 8);
  write8(spi, x0);     // XSTART
  write8(spi, x1 >> 8);
  write8(spi, x1);     // XEND

  enter_command_mode();
  write8(spi, ILI9341_PASET); // Row addr set
  enter_data_mode();
  write8(spi, y0 >> 8);
  write8(spi, y0);     // YSTART
  write8(spi, y1 >> 8);
  write8(spi, y1);     // YEND
  
  enter_command_mode();
  write8(spi, ILI9341_RAMWR); // write to RAM
}

void lcd_pushcolor(Soft_SPI spi, uint16_t color) 
{
  writedata(spi, color);
}

void lcd_drawpixel(Soft_SPI spi, int16_t x, int16_t y, uint16_t color) 
{
  if ((x < 0) || (x >= ILI9341_TFTWIDTH) || (y < 0) || (y >= ILI9341_TFTHEIGHT)) return;

  lcd_setwindow(spi, x, y, x + 5, y + 5);
  enter_data_mode();
  write16(spi, color);
}

// fill a rectangle
void lcd_rect(Soft_SPI spi, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
  lcd_setwindow(spi, x, y, x + w - 1, y + h - 1);

  enter_data_mode();

  // Manually unroll the loop
  for (y = h; y > 0; y--) 
  {
    // Unroll the inner loop by a factor of 8
    x = w;
    while (x >= 8) 
    {
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      write16(spi, color);
      x -= 8;
    }

    // Handle any remaining iterations
    while (x > 0) 
    {
      write16(spi, color);
      x--;
    }
  }
}

void lcd_drawimage(Soft_SPI spi, uint16_t* img, uint16_t x, uint16_t y, uint32_t size, uint32_t scaling)
{
	uint16_t current_pixel;

	uint16_t cur_x = x;
	uint16_t cur_y = y;
	uint16_t square_width = 32;

	for(uint32_t i = 0; i < 1024; i++)
	{
		current_pixel = img[i];

		cur_x = x + (i % square_width) * scaling;
        cur_y = y + (i / square_width) * scaling;

		lcd_rect(spi, cur_x, cur_y, scaling, scaling, current_pixel);
	}
}
