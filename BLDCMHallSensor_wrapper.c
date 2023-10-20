
/*
 * Include Files
 *
 */
#include "simstruc.h"



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
    #include <Arduino.h>
    #include <stdint.h>
    #include <math.h>

    uint8_t HallAPin = 0;
    uint8_t HallBPin = 0;
    uint8_t HallCPin = 0;

    // Hall reading algorithm variables
    volatile uint8_t HallAPinStateCurrent = 0b00000000;
    volatile uint8_t HallBPinStateCurrent = 0b00000000;
    volatile uint8_t HallCPinStateCurrent = 0b00000000;
    volatile uint8_t HallAPinStatePrevious = 0b00000000;
    volatile uint8_t HallBPinStatePrevious = 0b00000000;
    volatile uint8_t HallCPinStatePrevious = 0b00000000;
    volatile uint8_t HallABCPulsePattern = 0b00000000;
    volatile int32_t HallABCPulseCounter = 0;
    volatile bool TmpTransitionErrorFlag = 0;
    volatile uint32_t TmpTransitionErrorCounter = 0;
    volatile int8_t TmpBLDCMDirection = 0;

void HallSensorPulseEncoder()
{
  HallAPinStateCurrent = (uint8_t)digitalRead(HallAPin);
  HallBPinStateCurrent = (uint8_t)digitalRead(HallBPin);
  HallCPinStateCurrent = (uint8_t)digitalRead(HallCPin);
  HallABCPulsePattern = 0b00000000 | (HallCPinStateCurrent << 0) | (HallCPinStatePrevious << 1) | (HallBPinStateCurrent << 2) | (HallBPinStatePrevious << 3) | (HallAPinStateCurrent << 4) | (HallAPinStatePrevious << 5);
  switch ( HallABCPulsePattern )
  {
    case 0x07:
    case 0x0E:
    case 0x1C:
    case 0x23:
    case 0x31:
    case 0x38:
      HallABCPulseCounter--;
      TmpBLDCMDirection = -1;
      break;

    case 0x0B:
    case 0x0D:
    case 0x13:
    case 0x2C:
    case 0x32:
    case 0x34:
      HallABCPulseCounter++;
      TmpBLDCMDirection = 1;
      break;

    default:
      TmpTransitionErrorFlag = 1;
      TmpTransitionErrorCounter = TmpTransitionErrorCounter + 1;
  }
  HallAPinStatePrevious = HallAPinStateCurrent;
  HallBPinStatePrevious = HallBPinStateCurrent;
  HallCPinStatePrevious = HallCPinStateCurrent;
}

void IROHallPinA(){ HallSensorPulseEncoder(); }

void IROHallPinB(){ HallSensorPulseEncoder(); }

void IROHallPinC(){ HallSensorPulseEncoder(); }

#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define u_1_width 1
#define u_2_width 1
#define u_3_width 1
#define y_width 1
#define y_1_width 1
#define y_2_width 1
#define y_3_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void BLDCMHallSensor_Outputs_wrapper(const boolean_T *CPRValueResetRequest_b8,
			const int32_T *InitialCPRValue_s32,
			const boolean_T *TransitionErrorReset_b8,
			const int32_T *CPRResetValue_s32,
			int32_T *TransitionCPRValue_s32,
			boolean_T *TransitionErrorFlag_b8,
			uint32_T *TransitionErrorCounter_u32,
			int8_T *BLDCMDirection_s8,
			const real_T *xD,
			const real_T *PinA_u8, const int_T p_width0,
			const real_T *PinB_u8, const int_T p_width1,
			const real_T *PinC_u8, const int_T p_width2,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* wait until after initialization is done */
    if ( xD[0] == 1) 
    {
         /* don't do anything for mex file generation */
         # ifndef MATLAB_MEX_FILE
            /* get Hall position and set is as output */
            // Reset Hall
            if ( CPRValueResetRequest_b8[0] == 1 )
            {
                HallABCPulseCounter = CPRResetValue_s32[0];
            }
            if ( TransitionErrorReset_b8[0] == 1 )
            {
                TmpTransitionErrorFlag = 0;
                TmpTransitionErrorCounter = 0;
            }

            if ( TransitionCPRValue_s32[0] == HallABCPulseCounter )
            {
                TmpBLDCMDirection = 0;
            }
        
            BLDCMDirection_s8[0] = TmpBLDCMDirection;
            TransitionCPRValue_s32[0] = HallABCPulseCounter;
            TransitionErrorFlag_b8[0] = TmpTransitionErrorFlag;
            TransitionErrorCounter_u32[0] = TmpTransitionErrorCounter;
         # endif
    }
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void BLDCMHallSensor_Update_wrapper(const boolean_T *CPRValueResetRequest_b8,
			const int32_T *InitialCPRValue_s32,
			const boolean_T *TransitionErrorReset_b8,
			const int32_T *CPRResetValue_s32,
			int32_T *TransitionCPRValue_s32,
			boolean_T *TransitionErrorFlag_b8,
			uint32_T *TransitionErrorCounter_u32,
			int8_T *BLDCMDirection_s8,
			real_T *xD,
			const real_T *PinA_u8, const int_T p_width0,
			const real_T *PinB_u8, const int_T p_width1,
			const real_T *PinC_u8, const int_T p_width2,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if ( xD[0] != 1 ) 
    {
        /* only do the below if compiled on real hardware */
        # ifndef MATLAB_MEX_FILE
        
          // Hall HW Pins
          HallAPin = (uint8_t)PinA_u8[0];
          HallBPin = (uint8_t)PinB_u8[0];
          HallCPin = (uint8_t)PinC_u8[0];

          pinMode(HallAPin, INPUT);
          digitalWrite(HallAPin, HIGH);       // turn on pull-up resistor
          pinMode(HallBPin, INPUT);
          digitalWrite(HallBPin, HIGH);       // turn on pull-up resistor
          pinMode(HallCPin, INPUT);
          digitalWrite(HallCPin, HIGH);       // turn on pull-up resistor
          attachInterrupt(0, IROHallPinA, CHANGE);  // Hall A pin on interrupt 0 - pin 2
          attachInterrupt(1, IROHallPinB, CHANGE);  // Hall B pin on interrupt 1 - pin 3
          attachInterrupt(2, IROHallPinC, CHANGE);  // Hall C pin on interrupt 2 - pin 21
          HallAPinStateCurrent = (uint8_t)digitalRead(HallAPin);
          HallBPinStateCurrent = (uint8_t)digitalRead(HallBPin);
          HallCPinStateCurrent = (uint8_t)digitalRead(HallCPin);
          HallAPinStatePrevious = HallAPinStateCurrent;
          HallBPinStatePrevious = HallBPinStateCurrent;
          HallCPinStatePrevious = HallCPinStateCurrent;
          HallABCPulseCounter = InitialCPRValue_s32[0];
    
        # endif
        /* initialization done */ 
        xD[0] = 1;  
    }
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}

