Stream *_lcdPort;
void lcd_setup(Stream *port){
  _lcdPort = port;
}

void lcd_clear(void){
  (*_lcdPort).write(0xC);
}
void lcd_print(String text){
  (*_lcdPort).print(text);
}
