/**
 ******************************************************************************
 * @file    alg_temperature.c
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-5
 * @brief   The arithmetic of temperature
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "alg_temperature.h"


/* private variables declare */
static float alg_coreTemperature_param1 = 0.0f;
static float alg_coreTemperature_param2 = 0.0f;
static float alg_coreTemperature_param3 = 0.0f;
static float alg_coreTemperature_param4 = 0.0f;
static float alg_coreTemperature_param5 = 0.0f;


const uint32_t Rt_ref[NTC_LUT_LEN] = 
{
	2252,2243,2234,2225,2216,2206,2196,2186,2176,2166, //25.0~25.9
	2156,2147,2138,2129,2120,2111,2102,2093,2084,2075, //26.0~26.9
	2064,2055,2046,2037,2028,2019,2010,2001,1992,1983, //27.0~27.9
	1977,1968,1959,1950,1942,1934,1926,1918,1910,1902, //28.0~28.9
	1894,1886,1878,1870,1862,1854,1846,1838,1830,1822, //29.0~29.9
	1815,1808,1800,1793,1785,1777,1770,1762,1755,1747, //30.0~30.9
	1739,1732,1725,1717,1710,1703,1696,1689,1682,1675, //31.0~31.9
	1667,1660,1653,1646,1640,1633,1626,1619,1612,1606, //32.0~32.9
	1599,1592,1586,1579,1573,1566,1560,1553,1547,1540, //33.0~33.9
	1533,1528,1522,1515,1509,1503,1497,1490,1484,1478, //34.0~34.9
	1471,1466,1460,1454,1448,1442,1436,1430,1424,1418, //35.0~35.9
	1412,1407,1401,1395,1390,1384,1378,1372,1367,1361, //36.0~36.9
	1355,1350,1344,1339,1333,1328,1322,1317,1311,1306, //37.0~37.9
	1301,1296,1290,1285,1280,1274,1269,1264,1258,1253, //38.0~38.9
	1249,1244,1239,1234,1228,1223,1218,1213,1208,1203, //39.0~39.9
	1200,1195,1190,1185,1180,1175,1170,1166,1161,1156, //40.0~40.9
};

const float Tempurature[NTC_LUT_LEN] =
{
	25, 25.1, 25.2, 25.3, 25.4, 25.5, 25.6, 25.7, 25.8, 25.9,
	26, 26.1, 26.2, 26.3, 26.4,	26.5, 26.6,	26.7, 26.8,	26.9,
	27, 27.1, 27.2,	27.3, 27.4,	27.5, 27.6,	27.7, 27.8,	27.9,
	29,	29.1, 29.2,	29.3, 29.4,	29.5, 29.6,	29.7, 29.8,	29.9,
	28,	28.1, 28.2,	28.3, 28.4,	28.5, 28.6,	28.7, 28.8,	28.9,
	30,	30.1, 30.2,	30.3, 30.4,	30.5, 30.6,	30.7, 30.8,	30.9,
	31,	31.1, 31.2,	31.3, 31.4,	31.5, 31.6,	31.7, 31.8,	31.9,
	32,	32.1, 32.2,	32.3, 32.4,	32.5, 32.6,	32.7, 32.8,	32.9,
	33,	33.1, 33.2,	33.3, 33.4,	33.5, 33.6,	33.7, 33.8,	33.9,
	34,	34.1, 34.2,	34.3, 34.4,	34.5, 34.6,	34.7, 34.8,	34.9,
	35,	35.1, 35.2,	35.3, 35.4,	35.5, 35.6,	35.7, 35.8,	35.9,
	36,	36.1, 36.2,	36.3, 36.4,	36.5, 36.6,	36.7, 36.8,	36.9,
	37,	37.1, 37.2,	37.3, 37.4, 37.5, 37.6,	37.7, 37.8,	37.9,
	38,	38.1, 38.2,	38.3, 38.4,	38.5, 38.6,	38.7, 38.8,	38.9,
	39,	39.1, 39.2,	39.3, 39.4,	39.5, 39.6,	39.7, 39.8,	39.9,
	40,	40.1, 40.2,	40.3, 40.4,	40.5, 40.6,	40.7, 40.8,	40.9,
};

/* function declare */

/**
  * @brief  ntc_temperature_calculate
  * @note   通过NTC电阻值计算对应温度值
  * @param[in]  Rt
  * @param[out] *tVal
  * @retval None    
  */
void ntc_temperature_calculate(uint32_t Rt,float *tVal)
{
	uint16_t 	num=0;
	float 		Tamb=0;
	float 		Mid=0;
	
	for(num=0;num<NTC_LUT_LEN;num++)
	{
		if(Rt >= Rt_ref[num])
		{
			break;
		}
	}
	
	if(num >= NTC_LUT_LEN - 1)
	{
		Tamb = Tempurature[NTC_LUT_LEN - 1];
	}
	else if(num == 0)
	{
		Tamb = Tempurature[0];
	}
	else
	{
		Mid = (Rt_ref[num] - Rt_ref[num-1])/2;
		if((Rt-Rt_ref[num]) <= Mid)
		{
			Tamb = Tempurature[num-1];
		}
		else
		{
			Tamb = Tempurature[num];
		}
	}
	*tVal = Tamb;	
}
/**
  * @brief  alg_core_temperature_calculate_init
  * @note   核心温度算法初始化：将核心温度计算公式化简之后使用的参数计算
  * @param  None
  * @retval None    
  */
void alg_core_temperature_calculate_init(void)
{
	alg_coreTemperature_param1 = (float)(Ks / Kg);
	alg_coreTemperature_param2 = (float)((Kiso*Aiso_m)/(Kg*As));
	alg_coreTemperature_param3 = (float)(alg_coreTemperature_param2*alpha/(alpha+Kiso));
	alg_coreTemperature_param4 = (float)(alg_coreTemperature_param2*Ks/(alpha+Kiso));
	alg_coreTemperature_param5 = (float)(alg_coreTemperature_param2*Kiso/(2*(alpha+Kiso)));
}

/**
  * @brief  core_temperature_calculate
  * @note   通过TH1、TH2计算core temperature
*/	/***********************  core temperature calculate formula ************************************************/
	/*                                                                                                          */
	/*				 Ks				  Kiso Aiso_m	TH1+TH2		aTH2 - Ks(TH1-TH2) + Kiso((TH1+TH2)/2)          */
	/* Tcore = TH1 + --*(TH1 - TH2) + ----*------*(--------- - --------------------------------------- )        */
	/*               Kg                Kg    As        2                       a + Kiso                         */ 
	/*                                                                                                          */
	/************************************************************************************************************ 	
  * @param[in]  Th1,Th2
  * @param[out] *coreTem
  * @retval None    
  */
void core_temperature_calculate(float Th1,float Th2, float *coreTem)
{
	if(Th1 >= Th2)
	{
		*coreTem = Th1 + alg_coreTemperature_param1*(Th1-Th2) + alg_coreTemperature_param2*(Th1+Th2)/2 \
					   - alg_coreTemperature_param3*Th2 + alg_coreTemperature_param4*(Th1-Th2) \
					   - alg_coreTemperature_param5*(Th1+Th2);
	}
	else //采集错误
	{
		*coreTem = 0;
	}
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

