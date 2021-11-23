void checkBTcmd()  // verify if a command is received from BT remote control
 { 
    if (BT1.available()) 
    { 
      command = BT1.read();
      BT1.flush();
    }
 }
 
 //******************************************************************************//

void manualCmd()
{
  switch (command)
  {
    
    case 'm': 
      startSafe();
      Serial.print("Roomba in Safe mode");
      BT1.println("Roomba BT Ctrl OK - Safe mode");
      BT1.println('\n');
      command = 'f';
      playSound (3);
      break;
 
    case 'f': 
      driveStop(); //turn off both motors
      writeLEDs ('s', 't', 'o', 'p');
      state = command;
      Serial.println("STOP");
      break;

    case 'w':  
      drive (motorSpeed, 0); 
      writeLEDs (' ', 'g', 'o', ' ');
      state = command;  
      Serial.println("FWD");
      break;

    case 'd':     
      driveRight(motorSpeed);
      writeLEDs ('r', 'i', 'g', 'h');
      Serial.println("right");
      break;

   case 'a': 
      driveLeft(motorSpeed);
      writeLEDs ('l', 'e', 'f', 't');
      Serial.println("Left");
      break;
    
    case 's':  
      drive (-motorSpeed, 0);
      writeLEDs ('b', 'a', 'c', 'k');
      state = command;
      Serial.println("Reverse");
      break;

    case '+': 
      if (state == 'w')
      {
        motorSpeed = motorSpeed + 10;
        if (motorSpeed > MAX_SPEED) 
        { 
          motorSpeed = MAX_SPEED;
        }  
        command = 'w';
      } else {command = state;}
      break;

    case '-': 
 
      if (state == 'w')
      {
        motorSpeed = motorSpeed - 10;
      }     
      if (motorSpeed < MIN_SPEED ) 
      { 
        motorSpeed = MIN_SPEED;
      }
      Serial.println(motorSpeed); 
      command = state;
    break;
    
    case 'r':
    
      BT1.print("Ultrasonic radar enabled");
      Serial.println("Radar ON");
      for(angle = 0; angle < 180; angle++)
        {
        //Clears the trigPin condition
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
        // Displays the distance on the BTMonitor
        BT1.print("*1Distance: ");
        BT1.print(distance);
        BT1.print(" cm*");
        BT1.print("*2Angle: ");
        BT1.print(angle);
        BT1.println(" deg*");
        servo.write(angle);               
        delay(5);                   
        } 
        // now scan back from 180 to 0 degrees
        for(angle = 180; angle > 0; angle--)    
        {                                
        // Clears the trigPin condition
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
        // Displays the distance on the Serial Monitor
        BT1.print("*1Distance: ");
        BT1.print(distance);
        BT1.print(" cm*");
        BT1.print("*2Angle: ");
        BT1.print(angle);
        BT1.println(" deg*");
        servo.write(angle);     
        delay(5);       
      } 
      break;
    case 'b':
      //stop radar
      Serial.println("Radar OFF");
      servo.write(0);
      break;
    case 'u':  
       //ultrasonic no radar
       // Clears the trigPin condition
       Serial.print("Ultrasonic ON");
       BT1.print("Ultrasonic forward only");
       digitalWrite(trigPin, LOW);
       delayMicroseconds(2);
       // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(trigPin, LOW);
       // Reads the echoPin, returns the sound wave travel time in microseconds
       duration = pulseIn(echoPin, HIGH);
       // Calculating the distance
       distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
       // Displays the distance on the Serial Monitor
       BT1.print("*1Distance: ");
       BT1.print(distance);
       BT1.print(" cm*");
       delay(5);  
       break;
            
    case 'i':
      //stop ultrasonic
      Serial.println("Ultrasonic OFF");
      digitalWrite(trigPin, LOW);
      BT1.print("Ultrasonic stoped");
       
      break;
     
  }
}
