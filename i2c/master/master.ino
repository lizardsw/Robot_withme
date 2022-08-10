#include <Wire.h>


#define LED 3

// 슬레이브 주소
int SLAVE[4] = {1, 2, 3, 4}; 

void setup() {
	// Wire 라이브러리 초기화
	Wire.begin(); 
	// 직렬 통신 초기화
	Serial.begin(9600);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
 
}

void loop() {
	digitalWrite(LED, HIGH);
	delay(500);
	digitalWrite(LED, LOW);
	delay(500);
	if (Serial.available()) {
		char e = Serial.read();
		Serial.println(e);

		if (1) {
			// I2C 통신을 통한 전송 시작
			Serial.println("sending.....");
			
			Wire.beginTransmission(4);
			// 슬레이브 주소를 시리얼 창에 입력시 해당 시리얼 주소로 'o'문자와 데이터 요구를 보냅니다.
			Wire.write(e);
			Wire.write('\n');
			Wire.endTransmission(4);
			
			Wire.beginTransmission(3);
			// 슬레이브 주소를 시리얼 창에 입력시 해당 시리얼 주소로 'o'문자와 데이터 요구를 보냅니다.
			Wire.write(e);
			Wire.write('\n');
			Wire.endTransmission(3);

			delay(10);
			// 슬레이브로 데이터 요구 및 수신 데이터 처리
			i2c_communication(3); 
			i2c_communication(4); 
			delay(10);
		}
	}
}

void i2c_communication(int i) {
	// 12 바이트 크기의 데이터 요청
	Wire.requestFrom(SLAVE[i], 12); 
	// 12 바이트 모두 출력할 때까지 반복
	for (int j = 0 ; j < 12 ; j++) {  
		// 수신 데이터 읽기
		char c = Wire.read(); 
		// 수신 데이터 출력
		Serial.print(c); 
	}
	Serial.println();
}