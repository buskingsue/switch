#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// ��� ��Ʈ ���� (PORTB�� ���)
	DDRB = 0xFF;
	// �Է� ��Ʈ ���� (PORTD�� 0, 1, 2�� ���� �Է�)
	DDRD &= ~((1 << 0) | (1 << 1) | (1 << 2));

	uint8_t ledData = 0x01;
	uint8_t buttonData; // ��ư �Է��� ���� ����

	PORTB = 0x00;
	
	while (1)
	{
		buttonData = PIND;  // PIND�� ���� �Է� �޾Ƽ� ������ ����
		
		// ��ư 0�� ������ ��
		if((buttonData & (1 << 0)) == 0)
		{
			_delay_ms(10); // ª�� ���� �ð� (��ٿ��)
			buttonData = PIND;  // ��ư ���� ��Ȯ��
			
			if((buttonData & (1 << 0)) == 0) // ������ ���¿��� ��ư ���� Ȯ��
			{
				PORTB = ledData;  // LED ���� ����
				ledData = (ledData >> 7) | (ledData << 1);  // LED ȸ��
				_delay_ms(100); // ��ư �Է¿� ���� ���� ����
			}
		}

		// ��ư 1�� ������ ��
		if((buttonData & (1 << 1)) == 0)
		{
			_delay_ms(10); // ª�� ���� �ð� (��ٿ��)
			buttonData = PIND;  // ��ư ���� ��Ȯ��

			if((buttonData & (1 << 1)) == 0) // ������ ���¿��� ��ư ���� Ȯ��
			{
				PORTB = ledData;  // LED ���� ����
				ledData = (ledData >> 1) | (ledData << 7);  // LED ȸ��
				_delay_ms(100); // ��ư �Է¿� ���� ���� ����
			}
		}
	}
}
