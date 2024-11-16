#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)    // main 함수
{
	DDRB = 0xff;         // PORTB를 출력으로 설정 (LED 8개)
	uint8_t led_status = 0xff; // 초기 LED 상태 변수 (모두 OFF)
	PORTB = led_status;  // LED 상태를 PORTB에 반영하여 모두 OFF로 설정

	DDRD = 0x00;         // PORTD를 입력으로 설정
	PORTD = 0x00;        // 내부 풀업 저항 비활성화하여 PIND의 초기값을 0x00으로 설정

	uint8_t button_state = 0x00;        // 버튼 상태 저장 변수
	uint8_t last_button_state = 0x00;   // 이전 버튼 상태 저장 변수

	while (1)         // 무한 반복
	{
		button_state = PIND & 0x01;    // 버튼의 현재 상태 읽기 (첫 번째 비트만 확인)

		if (button_state != last_button_state)  // 버튼 상태가 변경되었을 때
		{
			if (button_state == 0x01)      // 버튼이 눌린 상태일 때
			{
				led_status ^= 0xff;     // LED 상태 토글 (0x00 <-> 0xff)
				PORTB = led_status;     // LED 상태 업데이트
				_delay_ms(50);          // 디바운싱을 위한 딜레이
			}
		}

		last_button_state = button_state;   // 현재 버튼 상태를 이전 상태로 저장
	}
}
