1.enum QSerialPort::StopBits:
The default value is OneStop, i.e. 1 stop bit.
Constant	Value	Description
QSerialPort::OneStop	1	1 stop bit.
QSerialPort::OneAndHalfStop	3	1.5 stop bits. This is only for the Windows platform.
QSerialPort::TwoStop	2	2 stop bits.
QSerialPort::UnknownStopBits	-1	Unknown number of stop bits. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.

2.enum QSerialPort::Parity
The default value is NoParity, i.e. no parity.
Constant	Value	Description
QSerialPort::NoParity	0	No parity bit it sent. This is the most common parity setting. Error detection is handled by the communication protocol.
QSerialPort::EvenParity	2	The number of 1 bits in each character, including the parity bit, is always even.
QSerialPort::OddParity	3	The number of 1 bits in each character, including the parity bit, is always odd. It ensures that at least one state transition occurs in each character.
QSerialPort::SpaceParity	4	Space parity. The parity bit is sent in the space signal condition. It does not provide error detection information.
QSerialPort::MarkParity	5	Mark parity. The parity bit is always set to the mark signal condition (logical 1). It does not provide error detection information.
QSerialPort::UnknownParity	-1	Unknown parity. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.

3.enum QSerialPort::DataBits
The default value is Data8, i.e. 8 data bits.
This enum describes the number of data bits used.

Constant	Value	Description
QSerialPort::Data5	5	The number of data bits in each character is 5. It is used for Baudot code. It generally only makes sense with older equipment such as teleprinters.
QSerialPort::Data6	6	The number of data bits in each character is 6. It is rarely used.
QSerialPort::Data7	7	The number of data bits in each character is 7. It is used for true ASCII. It generally only makes sense with older equipment such as teleprinters.
QSerialPort::Data8	8	The number of data bits in each character is 8. It is used for most kinds of data, as this size matches the size of a byte. It is almost universally used in newer applications.
QSerialPort::UnknownDataBits	-1	Unknown number of bits. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.

4.enum QSerialPort::BaudRate
The default value is Baud9600, i.e. 9600 bits per second.
This enum describes the baud rate which the communication device operates with.

Note: Only the most common standard baud rates are listed in this enum.

Constant	Value	Description
QSerialPort::Baud1200	1200	1200 baud.
QSerialPort::Baud2400	2400	2400 baud.
QSerialPort::Baud4800	4800	4800 baud.
QSerialPort::Baud9600	9600	9600 baud.
QSerialPort::Baud19200	19200	19200 baud.
QSerialPort::Baud38400	38400	38400 baud.
QSerialPort::Baud57600	57600	57600 baud.
QSerialPort::Baud115200	115200	115200 baud.
QSerialPort::UnknownBaud	-1	Unknown baud. This value is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.


通信协议

