
uint8_t write_register_drv8908(uint8_t write_register, uint8_t write_data){
  digitalWrite(CHIP_SEL, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  delayMicroseconds(1);
  drv8908_status = SPI.transfer(write_register);
  uint8_t received_data = SPI.transfer(write_data);
  SPI.endTransaction();
  delayMicroseconds(1);
  digitalWrite(CHIP_SEL, HIGH);
  delayMicroseconds(1);
  // delay(1);
  return received_data;
}

uint8_t read_register_drv8908(uint8_t read_register){
  digitalWrite(CHIP_SEL, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  delayMicroseconds(1);
  drv8908_status = SPI.transfer(0b01000000 | read_register);
  uint8_t received_data = SPI.transfer(0x00);
  SPI.endTransaction();
  delayMicroseconds(1);  
  digitalWrite(CHIP_SEL, HIGH);
  delay(1);
  return received_data;
}

uint8_t prepare_motor_register(uint8_t motor, uint8_t register){
  uint8_t motor_register = 0;

  return motor_register;
}

void drive_motor_A(uint8_t new_state, uint8_t PWM){
  switch (MOTOR_LAYOUT) {
    case PARALEL_AC_BD:
      switch (new_state) {
        case FORWARD:
          MOTOR_A1_STATE = A1_FORWARD;
          MOTOR_A2_STATE = A2_FORWARD;
          MOTOR_C1_STATE = C1_FORWARD;
          MOTOR_C2_STATE = C2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_A1_STATE = A1_BACKWARD;
          MOTOR_A2_STATE = A2_BACKWARD;
          MOTOR_C1_STATE = C1_BACKWARD;
          MOTOR_C2_STATE = C2_BACKWARD;
          break;
        case COAST: 
          MOTOR_A1_STATE = A1_COAST;
          MOTOR_A2_STATE = A2_COAST;
          MOTOR_C1_STATE = C1_COAST;
          MOTOR_C2_STATE = C2_COAST;
          break;
        case BREAK:
          MOTOR_A1_STATE = A1_BREAK;
          MOTOR_A2_STATE = A2_BREAK;
          MOTOR_C1_STATE = C1_BREAK;
          MOTOR_C2_STATE = C2_BREAK;
          break;
      }
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(PWM_DUTY_1, 0);
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      // Serial.print("OCP STATUS: ");
      // Serial.print(read_register_drv8908(OCP_STAT_1), BIN);
      // Serial.print(" : ");
      // Serial.println(read_register_drv8908(OCP_STAT_2), BIN);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_1, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_1, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
    case INDIVIDUAL_A_B_C_D:
      switch (new_state) {
        case FORWARD:
          MOTOR_A1_STATE = A1_FORWARD;
          MOTOR_A2_STATE = A2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_A1_STATE = A1_BACKWARD;
          MOTOR_A2_STATE = A2_BACKWARD;
          break;
        case COAST: 
          MOTOR_A1_STATE = A1_COAST;
          MOTOR_A2_STATE = A2_COAST;
          break;
        case BREAK:
          MOTOR_A1_STATE = A1_BREAK;
          MOTOR_A2_STATE = A2_BREAK;
          break;
      }
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      // write_register_drv8908(PWM_DUTY_1, 0);
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      // Serial.print("OCP STATUS: ");
      // Serial.print(read_register_drv8908(OCP_STAT_1), BIN);
      // Serial.print(" : ");
      // Serial.println(read_register_drv8908(OCP_STAT_2), BIN);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_1, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_1, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
  }
}

void drive_motor_B(uint8_t new_state, uint8_t PWM){
  switch (MOTOR_LAYOUT) {
    case PARALEL_AC_BD:
      switch (new_state) {
        case FORWARD:
          MOTOR_B1_STATE = B1_FORWARD;
          MOTOR_B2_STATE = B2_FORWARD;
          MOTOR_D1_STATE = D1_FORWARD;
          MOTOR_D2_STATE = D2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_B1_STATE = B1_BACKWARD;
          MOTOR_B2_STATE = B2_BACKWARD;
          MOTOR_D1_STATE = D1_BACKWARD;
          MOTOR_D2_STATE = D2_BACKWARD;
          break;
        case COAST: 
          MOTOR_B1_STATE = B1_COAST;
          MOTOR_B2_STATE = B2_COAST;
          MOTOR_D1_STATE = D1_COAST;
          MOTOR_D2_STATE = D2_COAST;
          break;
        case BREAK:
          MOTOR_B1_STATE = B1_BREAK;
          MOTOR_B2_STATE = B2_BREAK;
          MOTOR_D1_STATE = D1_BREAK;
          MOTOR_D2_STATE = D2_BREAK;
          break;
      }
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(PWM_DUTY_2, 0);
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);
      if(motors_on){
        write_register_drv8908(PWM_DUTY_2, PWM);  // sets motor duty cycle
      }else{
        write_register_drv8908(PWM_DUTY_2, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
    case INDIVIDUAL_A_B_C_D:
      switch (new_state) {
        case FORWARD:
          MOTOR_B1_STATE = B1_FORWARD;
          MOTOR_B2_STATE = B2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_B1_STATE = B1_BACKWARD;
          MOTOR_B2_STATE = B2_BACKWARD;
          break;
        case COAST: 
          MOTOR_B1_STATE = B1_COAST;
          MOTOR_B2_STATE = B2_COAST;
          break;
        case BREAK:
          MOTOR_B1_STATE = B1_BREAK;
          MOTOR_B2_STATE = B2_BREAK;
          break;
      }
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      // Serial.print("OCP STATUS: ");
      // Serial.print(read_register_drv8908(OCP_STAT_1), BIN);
      // Serial.print(" : ");
      // Serial.println(read_register_drv8908(OCP_STAT_2), BIN);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_2, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_2, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
  }
}

void drive_motor_C(uint8_t new_state, uint8_t PWM){
  switch (MOTOR_LAYOUT) {
    case PARALEL_AC_BD:
      switch (new_state) {
        case FORWARD:
          MOTOR_A1_STATE = A1_FORWARD;
          MOTOR_A2_STATE = A2_FORWARD;
          MOTOR_C1_STATE = C1_FORWARD;
          MOTOR_C2_STATE = C2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_A1_STATE = A1_BACKWARD;
          MOTOR_A2_STATE = A2_BACKWARD;
          MOTOR_C1_STATE = C1_BACKWARD;
          MOTOR_C2_STATE = C2_BACKWARD;
          break;
        case COAST: 
          MOTOR_A1_STATE = A1_COAST;
          MOTOR_A2_STATE = A2_COAST;
          MOTOR_C1_STATE = C1_COAST;
          MOTOR_C2_STATE = C2_COAST;
          break;
        case BREAK:
          MOTOR_A1_STATE = A1_BREAK;
          MOTOR_A2_STATE = A2_BREAK;
          MOTOR_C1_STATE = C1_BREAK;
          MOTOR_C2_STATE = C2_BREAK;
          break;
      }

      
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(PWM_DUTY_1, 0);
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      // Serial.print("OCP STATUS: ");
      // Serial.print(read_register_drv8908(OCP_STAT_1), BIN);
      // Serial.print(" : ");
      // Serial.println(read_register_drv8908(OCP_STAT_2), BIN);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_1, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_1, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
    case INDIVIDUAL_A_B_C_D:
      switch (new_state) {
        case FORWARD:
          MOTOR_C1_STATE = C1_FORWARD;
          MOTOR_C2_STATE = C2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_C1_STATE = C1_BACKWARD;
          MOTOR_C2_STATE = C2_BACKWARD;
          break;
        case COAST: 
          MOTOR_C1_STATE = C1_COAST;
          MOTOR_C2_STATE = C2_COAST;
          break;
        case BREAK:
          MOTOR_C1_STATE = C1_BREAK;
          MOTOR_C2_STATE = C2_BREAK;
          break;
      }
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      // Serial.print("OCP STATUS: ");
      // Serial.print(read_register_drv8908(OCP_STAT_1), BIN);
      // Serial.print(" : ");
      // Serial.println(read_register_drv8908(OCP_STAT_2), BIN);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_3, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_3, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
  }
}

void drive_motor_D(uint8_t new_state, uint8_t PWM){
  switch (MOTOR_LAYOUT) {
    case PARALEL_AC_BD:
      switch (new_state) {
        case FORWARD:
          MOTOR_B1_STATE = B1_FORWARD;
          MOTOR_B2_STATE = B2_FORWARD;
          MOTOR_D1_STATE = D1_FORWARD;
          MOTOR_D2_STATE = D2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_B1_STATE = B1_BACKWARD;
          MOTOR_B2_STATE = B2_BACKWARD;
          MOTOR_D1_STATE = D1_BACKWARD;
          MOTOR_D2_STATE = D2_BACKWARD;
          break;
        case COAST: 
          MOTOR_B1_STATE = B1_COAST;
          MOTOR_B2_STATE = B2_COAST;
          MOTOR_D1_STATE = D1_COAST;
          MOTOR_D2_STATE = D2_COAST;
          break;
        case BREAK:
          MOTOR_B1_STATE = B1_BREAK;
          MOTOR_B2_STATE = B2_BREAK;
          MOTOR_D1_STATE = D1_BREAK;
          MOTOR_D2_STATE = D2_BREAK;
          break;
      }
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(PWM_DUTY_2, 0);
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);
      if(motors_on){
        write_register_drv8908(PWM_DUTY_2, PWM);  // sets motor duty cycle
      }else{
        write_register_drv8908(PWM_DUTY_2, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
    case INDIVIDUAL_A_B_C_D:
      switch (new_state) {
        case FORWARD:
          MOTOR_D1_STATE = D1_FORWARD;
          MOTOR_D2_STATE = D2_FORWARD;
          break;
        case BACKWARD:
          MOTOR_D1_STATE = D1_BACKWARD;
          MOTOR_D2_STATE = D2_BACKWARD;
          break;
        case COAST: 
          MOTOR_D1_STATE = D1_COAST;
          MOTOR_D2_STATE = D2_COAST;
          break;
        case BREAK:
          MOTOR_D1_STATE = D1_BREAK;
          MOTOR_D2_STATE = D2_BREAK;
          break;
      }
            
      // write_register_drv8908(PWM_CTRL_2, 0xFF);  // disable pwm generation
      write_register_drv8908(OP_CTRL_1, MOTOR_A1_STATE | MOTOR_B1_STATE | MOTOR_C1_STATE | MOTOR_D1_STATE);
      write_register_drv8908(OP_CTRL_2, MOTOR_A2_STATE | MOTOR_B2_STATE | MOTOR_C2_STATE | MOTOR_D2_STATE);

      if(motors_on){
        write_register_drv8908(PWM_DUTY_4, PWM);
      }else{
        write_register_drv8908(PWM_DUTY_4, 0);
      }
      // write_register_drv8908(PWM_CTRL_2, 0x00);  // enable pwm generation
      break;
  }
}

void read_drv8908_status(){
  digitalWrite(CHIP_SEL, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  delayMicroseconds(1);
  drv8908_status = SPI.transfer(0b01000000);
  uint8_t received_data = SPI.transfer(0b00000000);
  SPI.endTransaction();
  delayMicroseconds(1);
  digitalWrite(CHIP_SEL, HIGH);

  Serial.print(drv8908_status, BIN);
  Serial.print("\t");
  Serial.println(received_data, BIN);
  delay(1);
}

void init_drv8908(uint8_t config){
  pinMode(CHIP_SEL,OUTPUT);
  pinMode(FAULT, INPUT);
  pinMode(SLEEP, OUTPUT);
  digitalWrite(SLEEP, HIGH); 
  SPI.begin(SCK, MISO, MOSI, CHIP_SEL);
  delay(1);

  switch (config) {
  case PARALEL_AC_BD:
    // general settings for all motors
    write_register_drv8908(PWM_CTRL_1, 0b11111111);       // set all half-bridges to PWM control
    write_register_drv8908(OLD_CTRL_2, 0b01000000);       // keep driving motors if open load is detected
    write_register_drv8908(OLD_CTRL_3, 0b10000000);       // keep driving motors if open load is detected
    
    write_register_drv8908(PWM_FREQ_CTRL_1, 0b10101010);  // set pwm freq to 200hz for all motors (default: 80, runs rough)
    write_register_drv8908(PWM_FREQ_CTRL_2, 0b10101010);  // 
    // write_register_drv8908(FW_CTRL_1, 0b11111111);     // enables active freewheeling (heats motors, runs rough, meh)
    write_register_drv8908(PWM_CTRL_2, 0xFF);             // disable pwm generation
    // map PWM chanels to halfbridges
    write_register_drv8908(PWM_MAP_CTRL_1, 0b00001001);   // PWM CH2 to OUT_1 and OUT_2
    write_register_drv8908(PWM_MAP_CTRL_2, 0b00000000);   // PWM CH1 to OUT_3 and OUT_4
    write_register_drv8908(PWM_MAP_CTRL_3, 0b00000001);   // PWM CH1 to OUT_6 and PWM CH2 to OUT_5
    write_register_drv8908(PWM_MAP_CTRL_4, 0b00001000);   // PWM CH1 to OUT_7 and PWM CH2 to OUT_8

    write_register_drv8908(PWM_DUTY_1, 0);                // sets motor duty cycle
    write_register_drv8908(PWM_DUTY_2, 0);                // sets motor duty cycle

    write_register_drv8908(PWM_CTRL_2, 0x00);             // enable pwm generation
    break;
  case INDIVIDUAL_A_B_C_D:
    write_register_drv8908(PWM_CTRL_1, 0b11111111);       // set all half-bridges to PWM control
    write_register_drv8908(OLD_CTRL_2, 0b01000000);       // keep driving motors if open load is detected
    write_register_drv8908(OLD_CTRL_3, 0b10000000);       // over current protection deglitch time
    write_register_drv8908(PWM_FREQ_CTRL_1, 0b10101010);  // set pwm freq to 200hz for all motors (default: 80, runs rough)
    write_register_drv8908(PWM_FREQ_CTRL_2, 0b10101010);  //

    write_register_drv8908(PWM_CTRL_2, 0xFF);             // disable pwm generation

    // map PWM chanels to halfbridges    
    write_register_drv8908(PWM_MAP_CTRL_1, 0b00011001);   // PWM CH2 to OUT_1 and PWM CH4 to OUT_2
    write_register_drv8908(PWM_MAP_CTRL_2, 0b00000000);   // PWM CH1 to OUT_3 and OUT_4
    write_register_drv8908(PWM_MAP_CTRL_3, 0b00010001);   // PWM CH2 to OUT_5 and PWM CH3 to OUT_6
    write_register_drv8908(PWM_MAP_CTRL_4, 0b00011010);   // PWM CH3 to OUT_7 and PWM CH4 to OUT_8
    
    write_register_drv8908(PWM_DUTY_1, 0);                // sets motor duty cycle
    write_register_drv8908(PWM_DUTY_2, 0);                // sets motor duty cycle
    write_register_drv8908(PWM_DUTY_3, 0);                // sets motor duty cycle
    write_register_drv8908(PWM_DUTY_4, 0);                // sets motor duty cycle
    
    write_register_drv8908(PWM_CTRL_2, 0x00);             // enable pwm generation
    break;
  }
  // Serial.print("motor status: ");
  // read_drv8908_status();
}


void drive_motors_forward_backward(){
  // driving
  if(motorA_output == 0){
    drive_motor_A(COAST, 0);
  }else if(motorA_output > 0){
    drive_motor_A(FORWARD,  map(constrain(motorA_output,0 ,2048  ) ,0 ,2048  ,0 ,255 ));
  }else if(motorA_output < 0){
    drive_motor_A(BACKWARD, map(constrain(motorA_output,-2048 ,0 ) ,0 ,-2048 ,0 ,255 ));
  }

  if(motorB_output == 0){
    drive_motor_B(COAST, 0);
  }else if(motorB_output > 0){
    drive_motor_B(BACKWARD,  map(constrain(motorB_output ,0 ,2048  ) ,0 ,2048  ,0 ,255 ));
  }else if(motorB_output < 0){
    drive_motor_B(FORWARD, map(constrain(motorB_output ,-2048 ,0 ) ,0 ,-2048 ,0 ,255 ));
  }
  servo_1.write(map(myData.pot_1,0,4950,0,180));
  servo_2.write(map(myData.pot_1,0,4950,0,180));
}

void driving_logic(){
  if((millis()-last_receive) > 100 ){   // if no packets for 100ms assume signal lost, so turn off motors.
    failsafe();
    return;
  }


  if(myData.sw_1 == 1 && millis() - last_drive_command >= 10){    // if you write to the motors too fast, the driver wount be able to finish a full pwm cycle, so it will not drive the motors at full power
    last_drive_command = millis();
    new_rx_data = false;

    // mixing
    if(myData.y_axis > (2048 + GIMBAL_STICK_DEADZONE) || myData.y_axis < (2048 - GIMBAL_STICK_DEADZONE)){
      motorA_output = myData.y_axis-2048;
      motorB_output = motorA_output;
    }else{
      motorA_output = 0;
      motorB_output = 0;
    }
    
    if(myData.x_axis > (2048 + GIMBAL_STICK_DEADZONE) || myData.x_axis < (2048 - GIMBAL_STICK_DEADZONE)){
      motorA_output += (myData.x_axis-2048)/2;
      motorB_output -= (myData.x_axis-2048)/2;      
    }

    if(use_imu_for_yaw_rate){
      motorA_output -= round(Output);
      motorB_output += round(Output);
    }
    drive_motors_forward_backward();
  }

  if(myData.sw_1 == 2 && millis() - last_drive_command >= 10){
    last_drive_command = millis();
    new_rx_data = false;
    
    drive_motor_A(FORWARD, -1*constrain(map( myData.x_axis,2000 ,4096 ,0 ,255 ),-255,0));
    drive_motor_B(FORWARD, constrain(map( myData.x_axis,2050 ,4096 ,0 ,255 ),0,255));
    drive_motor_C(FORWARD, constrain(map( myData.y_axis,2050 ,4096 ,0 ,255 ),0,255));
    drive_motor_D(FORWARD, -1*constrain(map( myData.y_axis,2000 ,4096 ,0 ,255 ),-255,0));

    // drive_motor_A(FORWARD, map( myData.x_axis,2050 ,4096 ,0 ,255 ));
    // drive_motor_B(FORWARD, map( myData.y_axis,0 ,2000 ,0 ,255 ));
    
    // drive_motor_A(FORWARD, map( myData.x_axis,0 ,4096 ,0 ,255 ));
    // drive_motor_B(FORWARD, map( myData.y_axis,0 ,4096 ,0 ,255 ));

    Serial.print("RIGHT: ");
    Serial.print(constrain(map( myData.x_axis,2050 ,4096 ,0 ,255 ),0,255));
    Serial.print(" , LEFT: ");
    Serial.print(-1*constrain(map( myData.x_axis,2000 ,4096 ,0 ,255 ),-255,0));
    
    Serial.print(" ,UP: ");
    Serial.print(constrain(map( myData.y_axis,2050 ,4096 ,0 ,255 ),0,255));
    Serial.print(" , DOWN: ");
    Serial.print(-1*constrain(map( myData.y_axis,2000 ,4096 ,0 ,255 ),-255,0));
    
    Serial.print(" , X: ");
    Serial.print(myData.x_axis);
    Serial.print(" , Y: ");
    Serial.println(myData.y_axis);
  }

  if(myData.sw_1 == 3){
    drive_motor_A(COAST,0);
    drive_motor_B(COAST,0);
  }
}
