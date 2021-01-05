float temp[4]={10.1, 20.2, 30.3, 40.4};
float humid[4]={50.5, 60.6, 70.7, 80.8};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=0; i<4; i++)
    Serial.println(temp[i]);
  temp[0] = 99.99;
  for(int i=0; i<4; i++)
    Serial.println(temp[i]);
  while(1);
}
