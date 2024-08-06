#include <Arduino.h>

/**
* @brief Set pins to input pull up
*
* @param PinsToSet Array of pins to set
*     
* @param size Size of the array 
* 
* @example SetPinsPullUP(AllPins, sizeof(AllPins));
* 
* @return void
*/
void SetPinsPullUP(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(PinsToSet[i],INPUT_PULLUP);
  }
}
/**
* @brief Set pins to input pull down
*
* @param PinsToSet Array of pins to set
*     
* @param size Size of the array 
* 
* @example SetPinsPullDown(AllPins, sizeof(AllPins));
* 
* @return void
*/
void SetPinsPullDown(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(PinsToSet[i],INPUT_PULLDOWN);
  }
}
/**
* @brief Set pins to output
*
* @param PinsToSet Array of pins to set
*     
* @param size Size of the array 
* 
* @example SetPinsOutput(AllPins, sizeof(AllPins));
* 
* @return void
*/
void SetPinsOutput(uint8_t* PinsToSet, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(PinsToSet[i],OUTPUT);
  }
}
/**
* @brief Confirm shorts from array
*
* @param pins Array of pins to confirm short
*     
* @param size Size of the array 
* 
* @example ShortsConfirm(Shorts_YellowDB,sizeof(Shorts_YellowDB));
* 
* @return uint8_t, error=1, pass=0
*/
uint8_t ShortsConfirm(uint8_t* pins, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],LOW);
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j!=i)  pinMode(pins[j],INPUT_PULLUP);
    }
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j==i) continue;
      if(digitalRead(pins[j]))
      {
        pinMode(pins[i],INPUT_PULLUP);
        delay(1);
        return 1; //Short not found
      }
    }
    pinMode(pins[i],INPUT_PULLUP);
    delay(1);
  }
  return 0; //No error
}
/**
* @brief Confirm NC from array
*
* @param pins Array of pins to confirm NC
*     
* @param size Size of the array 
* 
* @example NCConfirm(Shorts_YellowDB,sizeof(Shorts_YellowDB));
* 
* @return uint8_t, error=1, pass=0
*/
uint8_t NCConfirm(uint8_t* pins, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],LOW);
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j!=i)  pinMode(pins[j],INPUT_PULLUP);
    }
    delay(1);
    for (size_t j = 0; j < size; j++)
    {
      if(j==i) continue;
      if(!digitalRead(pins[j]))
      {
        pinMode(pins[i],INPUT_PULLUP);
        delay(1);
        return 1; //Short found error
      }
    }
    digitalWrite(pins[i],HIGH);
    delay(1);
    pinMode(pins[i],INPUT_PULLUP);
    delay(1);
  }
  return 0; //No error
}
/**
* @brief Blink LED fast (70ms). Non-Inverted.
*
* @param pinNo LED pin number
*     
* @param times Count of ON/OFF cycles
* 
* @return void
*/
void BlinkLED_fast(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 1);
    delay(70);
    digitalWrite(pinNo, 0);
    delay(70);
  }
} 
/**
* @brief Blink LED slow (300ms). Non-Inverted.
*
* @param pinNo LED pin number
*     
* @param times Count of ON/OFF cycles
* 
* @return void
*/
void BlinkLED_slow(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 1);
    delay(300);
    digitalWrite(pinNo, 0);
    delay(300);
  }
}
/**
* @brief Blink LED fast (70ms). Inverted.
*
* @param pinNo LED pin number
*     
* @param times Count of ON/OFF cycles
* 
* @return void
*/
void BlinkLED_fast_inv(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 0);
    delay(70);
    digitalWrite(pinNo, 1);
    delay(70);
  }
}
/**
* @brief Blink LED slow (300ms). Inverted.
*
* @param pinNo LED pin number
*     
* @param times Count of ON/OFF cycles
* 
* @return void
*/
void BlinkLED_slow_inv(uint8_t pinNo, int times)
{
  for(int j=0; j < times; j++)
  {
    digitalWrite(pinNo, 0);
    delay(300);
    digitalWrite(pinNo, 1);
    delay(300);
  }
}
/**
* @brief Set LEDSs for error state. Ends with while(1). Non-Inverted.
*
* @param PinErrorLED Error LED pin number
*     
* @param PinPassLED Pass LED pin number
* 
* @return while(1)
*/
void SetErrorLEDS(uint8_t PinErrorLED, uint8_t PinPassLED)
{
  digitalWrite(PinPassLED, LOW);
  digitalWrite(PinErrorLED, HIGH);
  while(1);
}
/**
* @brief Set LEDSs for pass state. Pass LED blinks 5 times for 500ms.  Non-Inverted.
*
* @param PinErrorLED Error LED pin number
*     
* @param PinPassLED Pass LED pin number
* 
* @return void
*/
void SetPassLEDS(uint8_t PinErrorLED, uint8_t PinPassLED)
{
  digitalWrite(PinErrorLED, LOW);
  for(int i=0; i<5; i++)
  {
    digitalWrite(PinPassLED, HIGH);
    delay(500);
    digitalWrite(PinPassLED, LOW);
    delay(500);
  }
}
/**
* @brief Calculates measured value * scale factor, e.g. ADC measurement.
*
* @param ScaleFactor Scaling factor, e.g. 1.5
*     
* @param MeasuredValue Value to be scaled
* 
* @return float
*/
float VoltageScale(float ScaleFactor, uint16_t MeasuredValue)
{
  float CalculatedValue = MeasuredValue*ScaleFactor;
  if(CalculatedValue<0)
  {
    Serial.print("Error calculated value cannot be negative number");
    return 0;
  }
  return CalculatedValue;
}
/**
 * @brief Calculates measured value * scale factor, e.g. ADC measurement.
 * 
 * @param ScaleFactor Scaling factor, e.g. 1.5
 * 
 * @param MeasuredValue Value to be scaled
 * 
 * @return float
 */
float CurrentScale(float ScaleFactor, uint16_t MeasuredValue)
{
  float CalculatedValue = MeasuredValue*ScaleFactor;
  if(CalculatedValue<0)
  {
    Serial.print("Error calculated value cannot be negative number");
    return 0;
  }
  return CalculatedValue;
}