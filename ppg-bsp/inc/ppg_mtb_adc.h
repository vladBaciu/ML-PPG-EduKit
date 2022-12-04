#ifdef __cplusplus
extern "C" {
#endif

#ifndef INC_PPG_ADC_H_
#define INC_PPG_ADC_H_


void PpgAdcInit(void);
uint32_t PpgGetResult(uint8_t channel);

#endif /* INC_PPG_ADC_H_ */

#ifdef __cplusplus
}
#endif