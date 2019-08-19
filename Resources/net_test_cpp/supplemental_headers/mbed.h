#include <thread>

#define RAND_MACRO_DIGITAL() rand() % 2;
#define RAND_MACRO_FLOAT() static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
#define RAND_MACRO_USHORT() rand() % sizeof(unsigned short)-1;

#define __IO volatile
#define RCC_BASE 0x3800U
#define IWDG_BASE 0x00U
#define RCC_CSR_WDGRSTF 0
#define RCC_CSR_RMVF 0
#define RCC ((RCC_TypeDef *) RCC_BASE)
#define IWDG ((IWDG_TypeDef *) IWDG_BASE)

#ifndef MBED_H
#define MBED_H

typedef struct
{
	__IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
	__IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
	__IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
	__IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
} IWDG_TypeDef;

typedef struct
{
	__IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
	__IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	__IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
	__IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	__IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	__IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	__IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
	__IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	__IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
	__IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	__IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	__IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
	__IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	__IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
	__IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	__IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	__IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
	__IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	__IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
	__IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	__IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
	uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
	__IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	__IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
	__IO uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
	__IO uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_TypeDef;

typedef enum {
	PC_2,
	PC_3,
	PC_0,

	/* Inputs */
	PC_14,
	PC_15,
	PD_4,
	PD_5,
	PD_6,
	PD_7,
	PF_0,
	PF_1,
	PG_0,
	PE_1,

	/* OUTPUTS */
	PD_13,
	PD_12,
	PD_11,
	PE_10,
	PE_12,
	PE_14,
	PE_15,
	PE_13,
	PF_13,
	PF_12,

	LED1,
	LED2,
	LED3
} PinName;

typedef struct {
	//
} gpio_t;

class DigitalIn {
public:
	DigitalIn(PinName pin) {
		//
	}
	int read() {
		return RAND_MACRO_DIGITAL();
	}
protected:
	gpio_t gpio;
};

class DigitalOut {
public:
	DigitalOut(PinName pin) {
		//
	}
	void write(int value) {
		//
	}
protected:
	gpio_t gpio;
};

class AnalogIn {
public:
	AnalogIn(PinName pin) {
		//
	}
	float read() {
		return RAND_MACRO_FLOAT();
	}
	unsigned short read_u16(){
		return RAND_MACRO_USHORT();
	}
};

using namespace std;

#endif