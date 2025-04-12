int A_Enable = 5;  // Chân PWM
int input_1 = 7;
int input_2 = 8;
int B_Enable = 6;  // Chân PWM
int input_3 = 9;
int input_4 = 10;

//------------------------------------------------------------
//************ Khai bao chan cam bien hong ngoai
int Truoc_T = 11;  // Hong ngoai truoc bên trái
int Truoc_P = 12;  // Hong ngoai truoc bên phải
int Sau_T = 3;     // Hong ngoai sau bên trái
int Sau_P = 4;     // Hong ngoai sau bên phải

//------------------------------------------------------------
// ************ Khai bao chan cam bien sieu am
int distancef1;          // Cam bien sieu am 1
const int trig_f1 = A1;  // chân trig của HC-SR04
const int echo_f1 = A0;
int distancef2;          // Cam bien sieu am 1
const int trig_f2 = A2;  // chân trig của HC-SR04
const int echo_f2 = A3;
//------------------------------------------------------------
// ************ Luu bien bat dau
int deger = 0;

void setup() {
  // Thoi gian cho (1 giay = 1000)
  delay(3000);

  // khai bao su dung cho cam bien sieu am
  pinMode(trig_f1, OUTPUT);  //xuat tin hieu ra(output)
  pinMode(echo_f1, INPUT);   //nhan tin hieu vao(input)
pinMode(trig_f2, OUTPUT);  //xuat tin hieu ra(output)
  pinMode(echo_f2, INPUT);   //nhan tin hieu vao(input)
  //khai bao su dung cam bien hong ngoai truoc sau
  pinMode(Truoc_T, INPUT);
  pinMode(Truoc_P, INPUT);
  pinMode(Sau_T, INPUT);
  pinMode(Sau_P, INPUT);

  // khai bao su dung cac chan dieu khien dong co
  pinMode(A_Enable, OUTPUT);
  pinMode(input_1, OUTPUT);
  pinMode(input_2, OUTPUT);
  pinMode(B_Enable, OUTPUT);
  pinMode(input_3, OUTPUT);
  pinMode(input_4, OUTPUT);
}

//------------------------------------------------------------
// ************ Chuong trinh chinh
void loop() {
  int f1 = sr04sensor1(distancef1);  // HC-SR04
  int f2 = sr04sensor2(distancef2);  // HC-SR04
  {
    if (f1 < 40 && f2 > 40) {
      deger = 1; }  //nếu khoảng cách f1 nhỏ hớn 40cm và f2 lớn hưn 40cm thì cho chạy thẳng về phía bên trái 
     else if (f1 > 40 && f2 < 40) {
      deger = 2;}  //nếu khoảng cách f1 lớn hớn 40cm và f2 nhỏ hưn 40cm thì cho chạy thẳng về phía bên phải 
    else if (f1 < 40 && f2 < 40) {
      deger = 3;}  //nếu khảng cách 2 cảm biến đều nhỏ hơn 40 thì cho chạy thẳng max tốc 
  else if (f1 > 40 && f2 > 40) {
      deger = 4;}  //nếu khảng cách 2 cảm biến đều lớn hơn 40 thì cho dò dối thủ
  }


  int Truoc_TT = digitalRead(Truoc_T);
  int Truoc_PP = digitalRead(Truoc_P);
  int Sau_TT = digitalRead(Sau_T);
  int Sau_PP = digitalRead(Sau_P);
// 0 là trắng 1 là đen
  {
    if (Truoc_TT == 1 && ((Sau_TT == 0) || (Sau_PP == 0)) && Truoc_PP == 0)  //1000
    { deger = 5;}
    else if (Truoc_TT == 0 && ((Sau_TT == 0) || (Sau_PP == 0)) && Truoc_PP == 1)  //0001
    { deger = 5;}
    else if (Truoc_TT == 1 && ((Sau_TT == 0) || (Sau_PP == 0)) && Truoc_PP == 1)  //1001
    {deger = 5;}
    else if (Truoc_TT == 0 && ((Sau_TT == 1) || (Sau_PP == 0)) && Truoc_PP == 0)  //0100
    { deger = 3;}
    else if (Truoc_TT == 0 && ((Sau_TT == 0) || (Sau_PP == 1)) && Truoc_PP == 0)  //0010
    { deger = 3;}
    else if (Truoc_TT == 0 && ((Sau_TT == 1) || (Sau_PP == 1)) && Truoc_PP == 0)  //0110
    { deger = 3;}
  }
  switch (deger) {
    case 1:
      Chay_thang_trai();
      break;
    case 2:
      Chay_thang_phai();
      break;
    case 3:
      Thang_max();
      break;
    case 4:
     Do_doi_thu();
      break;
    case 5:
      Lui_ve_sau();
  }
}

void Chay_thang_trai() {
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, HIGH);
  digitalWrite(input_4, LOW);
  analogWrite(A_Enable, 250);
  analogWrite(B_Enable, 230);
}

void Chay_thang_phai() {
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, HIGH);
  digitalWrite(input_4, LOW);
  analogWrite(A_Enable, 230);
  analogWrite(B_Enable, 250);
}

void Thang_max() {
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, HIGH);
  digitalWrite(input_4, LOW);
  analogWrite(A_Enable, 255);
  analogWrite(B_Enable, 255);
}
void Do_doi_thu() {
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, HIGH);
  analogWrite(A_Enable, 190);
  analogWrite(B_Enable, 190);
}
void Lui_ve_sau() {
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, HIGH);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, HIGH);
  analogWrite(A_Enable, 255);
  analogWrite(B_Enable, 255);
  delay(600);
  // digitalWrite(input_1, LOW);
  // digitalWrite(input_2, HIGH);
  // digitalWrite(input_3, HIGH);
  // digitalWrite(input_4, LOW);
  // analogWrite(A_Enable, 230);
  // analogWrite(B_Enable, 250);
}

int sr04sensor1(int distancef1)  // thư vien cho cảm biến siêu âm.
{
  unsigned long duration;  // biến đo thời gian
  /* Phát xung từ chân trig */
  digitalWrite(trig_f1, 0);  // tắt chân trig
  delayMicroseconds(2);      // xung có độ dài 5 microSeconds
  digitalWrite(trig_f1, 1);  // phát xung từ chân trig
  delayMicroseconds(5);      // xung có độ dài 5 microSeconds
  digitalWrite(trig_f1, 0);  // tắt chân trig
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo_f1, HIGH);
  // Tính khoảng cách đến vật.
  distancef1 = int(duration / 2 / 29.412);
  return (distancef1);
}
int sr04sensor2(int distancef2)  // thư vien cho cảm biến siêu âm.
{
  unsigned long duration;  // biến đo thời gian
  /* Phát xung từ chân trig */
  digitalWrite(trig_f2, 0);  // tắt chân trig
  delayMicroseconds(2);      // xung có độ dài 5 microSeconds
  digitalWrite(trig_f2, 1);  // phát xung từ chân trig
  delayMicroseconds(5);      // xung có độ dài 5 microSeconds
  digitalWrite(trig_f2, 0);  // tắt chân trig
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo_f2, HIGH);
  // Tính khoảng cách đến vật.
  distancef2 = int(duration / 2 / 29.412);
  return (distancef2);
}