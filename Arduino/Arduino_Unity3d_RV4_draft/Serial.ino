void threadSerial(){
  
  int sysTime = millis() / 1000;
  lcd.setCursor(0, 1);
  lcd.print(sysTime);
  lcd.setCursor(5, 1);
  lcd.print(incomingByte);

  if (Serial.available()>0) {
    
    incomingByte = Serial.read();
    Serial.print("Serial Input: ");
    Serial.println(incomingByte);
    
    //Input = 1   -- Display Hello World
    if (incomingByte == 49){    
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "Hello World!";
        inputTime = millis();
        lcd.print(toPrint);
    }

    //Input = a   -- Right Servo Micro Motor
    else if (incomingByte == 97){
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "Micro Servo R";
        lcd.print(toPrint);
        toggleServoMicro1();
        inputTime = millis();
    }
    
    //Input = b   -- Left Servo Micro Motor
    else if (incomingByte == 98){
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "Micro Servo L";
        lcd.print(toPrint);
        toggleServoMicro2();
        inputTime = millis();
    }

    //Input = c   -- Temperature Sensor
    else if (incomingByte == 99 || (AutoDisplay && (sysTime % 20 < 10))){
        lcd.clear();
        lcd.setCursor(0, 0);
        Serial.print(" Requesting temperatures..."); 
        sensors.requestTemperatures(); // Send the command to get temperature readings 
        Serial.println("DONE"); 

        Serial.print("Temperature is: "); 
        Serial.println(sensors.getTempCByIndex(0)); 
        float currentTemp = sensors.getTempCByIndex(0);
        if (currentTemp > -10){
          char toPrint[16] = "Temp";
          lcd.print(toPrint);
          lcd.setCursor(6, 0);
          
          lcd.print(currentTemp);
          lcd.setCursor(13, 0);
          char toPrint2[16] = "deg";
          lcd.print(toPrint2);
        }
        else{
          char toPrint[16] = "TS not detected";
          lcd.print(toPrint);
        }
        inputTime = millis();
    }

    //Input = d   -- Ultrasonic sensor
    else if (incomingByte == 100 || (AutoDisplay && (sysTime % 20 < 5))){
        lcd.clear();
        lcd.setCursor(0, 0);
        long duration, distance;
        digitalWrite(Pin_USS_Trig, LOW);  
        delayMicroseconds(2); 
        digitalWrite(Pin_USS_Trig, HIGH);
        delayMicroseconds(10); 
        digitalWrite(Pin_USS_Trig, LOW);
        duration = pulseIn(Pin_USS_Echo, HIGH);
        distance = (duration/2) / 29.1;
        if (distance >= 200 || distance <= 0){
          Serial.println("Out of range");
          char toPrint[16] = "Dis";
          lcd.print("USS not detected");
        }
        else {
          Serial.print(distance);
          Serial.println(" cm");
          char toPrint[16] = "Dis";
          lcd.print(toPrint);
          lcd.setCursor(4, 0);
          lcd.print(distance);
          lcd.setCursor(9, 0);
          char toPrint2[16] = "cm";
          lcd.print(toPrint2);
        }
        inputTime = millis();
    }

    // Input = e   -- Light Sensor
    else if (incomingByte == 101 || (AutoDisplay && (sysTime % 20 < 5))){
        lcd.clear();
        lcd.setCursor(0, 0);
        
        char toPrint[16] = "LS not detected";
        lcd.print(toPrint);
        
        inputTime = millis();
    }

    // Input = f   -- Motion Sensor
    else if (incomingByte == 102 || (AutoDisplay && (sysTime % 20 < 5))){
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "MS not detected";
        lcd.print(toPrint);
        
        inputTime = millis();
       
    }
    // Input = g   -- IMU Sensor
    else if (incomingByte == 103 || (AutoDisplay && (sysTime % 20 < 5))){
        lcd.clear();
        lcd.setCursor(0, 0);
        printIMUoutput();
        char toPrint1[16] = "IMU R:";
        lcd.print(toPrint1);
        lcd.setCursor(6, 0);
        lcd.print(IMUroll);
        lcd.setCursor(0, 1);
        char toPrint2[16] = "P:";
        lcd.print(toPrint2);
        lcd.setCursor(2, 1);
        lcd.print(IMUpitch);
        char toPrint3[16] = " H:";
        lcd.setCursor(7, 1);
        lcd.print(toPrint3);
        lcd.setCursor(10, 1);
        lcd.print(IMUheading);
        inputTime = millis() - 4000;
    }
    
    // Input = h   -- LED red
    else if (incomingByte == 104){
        lcd.clear();
        lcd.setCursor(0, 0);
        LEDmode = "Danger";
        char toPrint[16] = "LED Red";
        lcd.print(toPrint);
        inputTime = millis();
    }

    // Input = i   -- LED green
    else if (incomingByte == 106){
        lcd.clear();
        lcd.setCursor(0, 0);
        LEDmode = "Safe";
        char toPrint[16] = "LED Green";
        lcd.print(toPrint);
        inputTime = millis();
    }

    // Input = j   -- LED yellow
    else if (incomingByte == 105){
        lcd.clear();
        lcd.setCursor(0, 0);
        LEDmode = "Warning";
        char toPrint[16] = "LED Yellow";
        lcd.print(toPrint);
        inputTime = millis();
    }   
    // Input = k   -- Camera Servo R
    else if (incomingByte == 107){
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "Camera Servo R";
        lcd.print(toPrint);
        toggleServoCamera1();
        inputTime = millis();
    }
    
    //Input = l   -- Camera Servo L
    else if (incomingByte == 108){
        lcd.clear();
        lcd.setCursor(0, 0);
        char toPrint[16] = "Camera Servo L";
        lcd.print(toPrint);
        toggleServoCamera2();
        inputTime = millis();
    }

  }else if (millis() - inputTime > 2000){
      lcd.clear();
      lcd.setCursor(0, 0);
      char toPrint[16] = "CubeSat System";
      inputTime = millis();
      lcd.print(toPrint);
  }
}
