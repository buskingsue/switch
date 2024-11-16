#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// 출력 포트 설정 (PORTB는 출력)
	DDRB = 0xFF;
	// 입력 포트 설정 (PORTD의 0, 1, 2번 핀은 입력)
	DDRD &= ~((1 << 0) | (1 << 1) | (1 << 2));

	uint8_t ledData = 0x01;
	uint8_t buttonData; // 버튼 입력을 받을 변수

	PORTB = 0x00;
	
	while (1)
	{
		buttonData = PIND;  // PIND의 값을 입력 받아서 변수에 대입
		
		// 버튼 0이 눌렸을 때
		if((buttonData & (1 << 0)) == 0)
		{
			_delay_ms(10); // 짧은 지연 시간 (디바운싱)
			buttonData = PIND;  // 버튼 상태 재확인
			
			if((buttonData & (1 << 0)) == 0) // 안정된 상태에서 버튼 눌림 확인
			{
				PORTB = ledData;  // LED 상태 변경
				ledData = (ledData >> 7) | (ledData << 1);  // LED 회전
				_delay_ms(100); // 버튼 입력에 대한 응답 지연
			}
		}

		// 버튼 1이 눌렸을 때
		if((buttonData & (1 << 1)) == 0)
		{
			_delay_ms(10); // 짧은 지연 시간 (디바운싱)
			buttonData = PIND;  // 버튼 상태 재확인

			if((buttonData & (1 << 1)) == 0) // 안정된 상태에서 버튼 눌림 확인
			{
				PORTB = ledData;  // LED 상태 변경
				ledData = (ledData >> 1) | (ledData << 7);  // LED 회전
				_delay_ms(100); // 버튼 입력에 대한 응답 지연
			}
		}
	}
}
