#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;         // PORTB를 출력으로 설정 (8개의 LED가 연결됨)
	DDRD = 0x00;         // PORTD를 입력으로 설정
	PORTD |= (1<<1) | (1<<2); // D포트 1, 2번 핀에 풀업 저항 활성화 (평소 HIGH 상태)
	//DDRD &= ~((1<<0)|(1<<1)|(1<<2));
	uint8_t led_pattern = 0x01;  // 초기 LED 패턴 (0000 0001)

	while (1)
	{
		// D포트의 0번 핀: 버튼이 눌렸을 때 LED 전체 켜기/끄기
		PORTB = (PIND & (1<<0)) ? 0x00 : 0xff;

		// D포트의 1번 핀: 왼쪽 시프트, 2번 핀: 오른쪽 시프트
		//! 부정 연산자 !써야 함  ~ 비트연산자 못씀
		if (!(PIND & (1<<1)) || !(PIND & (1<<2))) {
			led_pattern = (PIND & (1<<1)) ? led_pattern << 1 : led_pattern >> 1;
			if (led_pattern == 0) led_pattern = (PIND & (1<<1)) ? 0x01 : 0x80;
			PORTB = led_pattern;
			_delay_ms(100);
		}
	}
}
