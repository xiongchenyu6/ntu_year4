#ifndef FONT_H_
#define FONT_H_

Uint8 tiny_font[][4] = {
								 {0x00, 0x00, 0x00, 0x00},  // ' '
                                 {0x00, 0x2E, 0x00, 0x00},  // '!'
                                 {0x06, 0x00, 0x06, 0x00},  // '"'
                                 {0x3E, 0x14, 0x3E, 0x00},  // '//'
                                 {0x14, 0x3E, 0x14, 0x00},  // '$'
                                 {0x34, 0x08, 0x16, 0x00},  // '%'
                                 {0x34, 0x2A, 0x3A, 0x00},  // '&'
                                 {0x00, 0x06, 0x00, 0x00},  // '''
                                 {0x1C, 0x22, 0x00, 0x00},  // '('
                                 {0x00, 0x22, 0x1C, 0x00},  // ')'
                                 {0x14, 0x08, 0x14, 0x00},  // '*'
                                 {0x08, 0x1C, 0x08, 0x00},  // '+'
                                 {0x00, 0x30, 0x00, 0x00},  // ','
                                 {0x08, 0x08, 0x08, 0x00},  // '-'
                                 {0x00, 0x20, 0x00, 0x00},  // '.'
                                 {0x30, 0x08, 0x06, 0x00},  // '/'
                                 {0x1C, 0x22, 0x1C, 0x00},  // '0'
                                 {0x24, 0x3E, 0x20, 0x00},  // '1'
                                 {0x32, 0x2A, 0x24, 0x00},  // '2'
                                 {0x22, 0x2A, 0x14, 0x00},  // '3'
                                 {0x0E, 0x08, 0x3E, 0x00},  // '4'
                                 {0x2E, 0x2A, 0x12, 0x00},  // '5'
                                 {0x3E, 0x2A, 0x3A, 0x00},  // '6'
                                 {0x02, 0x3A, 0x06, 0x00},  // '7'
                                 {0x3E, 0x2A, 0x3E, 0x00},  // '8'
                                 {0x2E, 0x2A, 0x3E, 0x00},  // '9'
                                 {0x00, 0x14, 0x00, 0x00},  // ':'
                                 {0x00, 0x34, 0x00, 0x00},  // ';'
                                 {0x08, 0x14, 0x22, 0x00},  // '<'
                                 {0x14, 0x14, 0x14, 0x00},  // '='
                                 {0x22, 0x14, 0x08, 0x00},  // '>'
                                 {0x02, 0x2A, 0x06, 0x00},  // '?'
                                 {0x1C, 0x2A, 0x1C, 0x00},  // '@'
                                 {0x3C, 0x0A, 0x3C, 0x00},  // 'A'
                                 {0x3E, 0x2A, 0x14, 0x00},  // 'B'
                                 {0x1C, 0x22, 0x22, 0x00},  // 'C'
                                 {0x3E, 0x22, 0x1C, 0x00},  // 'D'
                                 {0x3E, 0x2A, 0x22, 0x00},  // 'E'
                                 {0x3E, 0x0A, 0x02, 0x00},  // 'F'
                                 {0x1C, 0x22, 0x3A, 0x00},  // 'G'
                                 {0x3E, 0x08, 0x3E, 0x00},  // 'H'
                                 {0x22, 0x3E, 0x22, 0x00},  // 'I'
                                 {0x32, 0x22, 0x3E, 0x00},  // 'J'
                                 {0x3E, 0x08, 0x36, 0x00},  // 'K'
                                 {0x3E, 0x20, 0x20, 0x00},  // 'L'
                                 {0x3E, 0x0C, 0x3E, 0x00},  // 'M'
                                 {0x3C, 0x02, 0x3E, 0x00},  // 'N'
                                 {0x3E, 0x22, 0x3E, 0x00},  // 'O'
                                 {0x3E, 0x0A, 0x0E, 0x00},  // 'P'
                                 {0x1E, 0x12, 0x3E, 0x00},  // 'Q'
                                 {0x3E, 0x0A, 0x36, 0x00},  // 'R'
                                 {0x2E, 0x2A, 0x3A, 0x00},  // 'S'
                                 {0x02, 0x3E, 0x02, 0x00},  // 'T'
                                 {0x3E, 0x20, 0x3E, 0x00},  // 'U'
                                 {0x1E, 0x20, 0x1E, 0x00},  // 'V'
                                 {0x3E, 0x18, 0x3E, 0x00},  // 'W'
                                 {0x36, 0x08, 0x36, 0x00},  // 'X'
                                 {0x0E, 0x38, 0x0E, 0x00},  // 'Y'
                                 {0x32, 0x2A, 0x26, 0x00},  // 'Z'
                                 {0x3E, 0x22, 0x00, 0x00},  // '{'
                                 {0x06, 0x08, 0x30, 0x00},  // '\'
                                 {0x00, 0x22, 0x3E, 0x00},  // '}'
                                 {0x04, 0x02, 0x04, 0x00},  // '^'
                                 {0x20, 0x20, 0x20, 0x00},  // '_'
                                 {0x00, 0x02, 0x04, 0x00},  // '`'
                                 {0x10, 0x2A, 0x3C, 0x00},  // 'a'
                                 {0x3E, 0x28, 0x10, 0x00},  // 'b'
                                 {0x18, 0x24, 0x24, 0x00},  // 'c'
                                 {0x10, 0x28, 0x3E, 0x00},  // 'd'
                                 {0x1C, 0x2A, 0x2C, 0x00},  // 'e'
                                 {0x00, 0x3C, 0x0A, 0x00},  // 'f'
                                 {0x04, 0x2A, 0x3E, 0x00},  // 'g'
                                 {0x3E, 0x08, 0x38, 0x00},  // 'h'
                                 {0x00, 0x3A, 0x00, 0x00},  // 'i'
                                 {0x20, 0x3A, 0x00, 0x00},  // 'j'
                                 {0x3C, 0x10, 0x28, 0x00},  // 'k'
                                 {0x00, 0x3C, 0x00, 0x00},  // 'l'
                                 {0x3C, 0x08, 0x3C, 0x00},  // 'm'
                                 {0x38, 0x04, 0x38, 0x00},  // 'n'
                                 {0x18, 0x24, 0x18, 0x00},  // 'o'
                                 {0x3C, 0x14, 0x08, 0x00},  // 'p'
                                 {0x08, 0x14, 0x3C, 0x00},  // 'q'
                                 {0x3C, 0x08, 0x04, 0x00},  // 'r'
                                 {0x28, 0x3C, 0x14, 0x00},  // 's'
                                 {0x08, 0x3C, 0x28, 0x00},  // 't'
                                 {0x3C, 0x20, 0x3C, 0x00},  // 'u'
                                 {0x1C, 0x20, 0x1C, 0x00},  // 'v'
                                 {0x3C, 0x10, 0x3C, 0x00},  // 'w'
                                 {0x24, 0x18, 0x24, 0x00},  // 'x'
                                 {0x0C, 0x28, 0x3C, 0x00},  // 'y'
                                 {0x24, 0x34, 0x2C, 0x00},  // 'z'
                                 {0x14, 0x2A, 0x00, 0x00},  // '{'
                                 {0x00, 0x3E, 0x00, 0x00},  // '|'
                                 {0x00, 0x2A, 0x14, 0x00},  // '}'
                                 {0x04, 0x04, 0x0C, 0x00},  // '~'
                   };

#endif /*FONT_H_*/
