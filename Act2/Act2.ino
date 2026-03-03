void setup() {
  ledcAttach(25,5000,8);
}
void loop() {
  // put your main code here, to run repeatedly:
  ledWrite(25,255);

}
