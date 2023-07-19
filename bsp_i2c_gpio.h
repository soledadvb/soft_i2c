#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H

#include <inttypes.h>

#define BSP_I2C_WR 0 /* д����bit */
#define BSP_I2C_RD 1 /* ������bit */

/* ����I2C�������ӵ�GPIO�˿�ʱ�ӿ��� */

#define I2Cx_SDA_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����3�д��뼴������ı�SCL��SDA������ */
#define BSP_GPIO_PORT_I2C GPIOB    /* GPIO�˿� */
#define BSP_I2C_SCL_PIN GPIO_PIN_8 /* ���ӵ�SCLʱ���ߵ�GPIO */
#define BSP_I2C_SDA_PIN GPIO_PIN_9 /* ���ӵ�SDA�����ߵ�GPIO */

/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 0                                                                /* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
#define BSP_I2C_SCL_1() digitalH(BSP_GPIO_PORT_I2C, BSP_I2C_SCL_PIN) /* SCL = 1 */
#define BSP_I2C_SCL_0() digitalL(BSP_GPIO_PORT_I2C, BSP_I2C_SCL_PIN) /* SCL = 0 */

#define BSP_I2C_SDA_1() digitalH(BSP_GPIO_PORT_I2C, BSP_I2C_SDA_PIN)         /* SDA = 1 */
#define BSP_I2C_SDA_0() digitalL(BSP_GPIO_PORT_I2C, BSP_I2C_SDA_PIN)         /* SDA = 0 */
	
	//#define BSP_I2C_SDA_READ()  GPIO_ReadInputDataBit(BSP_GPIO_PORT_I2C, BSP_I2C_SDA_PIN)	/* ��SDA����״̬ */
#define BSP_I2C_SDA_READ() ((BSP_GPIO_PORT_I2C->IDR & BSP_I2C_SDA_PIN) != 0) /* ��SDA����״̬ */

#else                                                                              /* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
/*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
#define BSP_I2C_SCL_1() BSP_GPIO_PORT_I2C->BSRR = (uint32_t)BSP_I2C_SCL_PIN        /* SCL = 1 */
#define BSP_I2C_SCL_0() BSP_GPIO_PORT_I2C->BSRR = (uint32_t)BSP_I2C_SCL_PIN << 16U /* SCL = 0 */

#define BSP_I2C_SDA_1() BSP_GPIO_PORT_I2C->BSRR = (uint32_t)BSP_I2C_SDA_PIN        /* SDA = 1 */
#define BSP_I2C_SDA_0() BSP_GPIO_PORT_I2C->BSRR = (uint32_t)BSP_I2C_SDA_PIN << 16U /* SDA = 0 */

#define BSP_I2C_SDA_READ() ((BSP_GPIO_PORT_I2C->IDR & BSP_I2C_SDA_PIN) != 0) /* ��SDA����״̬ */
#endif

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalH(p, i) \
    {                  \
        p->BSRR = i;   \
    } // ����Ϊ�ߵ�ƽ
#define digitalL(p, i)               \
    {                                \
        p->BSRR = (uint32_t)i << 16; \
    } // ����͵�ƽ

void i2c_CfgGpio(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);

#endif
