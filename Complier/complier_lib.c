#include "complier_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：把16进制转换为BCD格式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HexToBcd(UINT8_T hexVal)
{
	UINT8_T _return = 0;
	_return = (hexVal % 10 + (hexVal / 10) * 16);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 把16进制转换为ASCII字符
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T HexToASCII(UINT8_T hexVal)
{
	if ((hexVal >= 0x30) && (hexVal <= 0x39))
	{
		hexVal-= 0x30;
	}
	else if ((hexVal >= 0x41) && (hexVal <= 0x46)) // Capital
	{
		hexVal-= 0x37;
	}
	else if ((hexVal >= 0x61) && (hexVal <= 0x66)) //littlecase
	{
		hexVal-= 0x57;
	}
	else
	{
		hexVal = 0xff;
	}
	return hexVal;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 把ASCII字符转换为16进制
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T ASCIIToHex(UINT8_T hexVal)
{
	if ((hexVal >= 0) && (hexVal <= 9))
	{
		hexVal += 0x30;
	}
	else if ((hexVal >= 10) && (hexVal <= 15))//Capital
	{
		hexVal += 0x37;
	}
	else
	{
		hexVal = 0xff;
	}
	return hexVal
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：把BCD格式转换为10进制
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BcdToDec(UINT8_T bcdVal)
{
	UINT8_T _return = (bcdVal >> 4);
	_return = (_return * 10 + (bcdVal & 0x0F));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：把10进制转换为BCD格式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DecToBcd(UINT8_T decVal)
{
	UINT8_T _return = (decVal / 10);
	_return = ((_return << 4) + ((decVal % 10) & 0x0F));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：求解一个数据m的n次方
//////////////////////////////////////////////////////////////////////////////
UINT64_T MyPow(UINT16_T m, UINT16_T n)
{
	UINT64_T r = 0;
	UINT64_T base = m;
	while (n > 0)
	{
		if ((n & 0x01) == 1)
		{
			r *= base;
		}
		base *= base;
		n >>= 1;
	}
	return base;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 冒泡升序排列数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AscSortFun1(UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT16_T j = 0;
	UINT16_T k = length - 1;
	UINT16_T m = 0;
	UINT8_T flag;
	UINT8_T tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		m = 0;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (pVal[j] > pVal[j + 1])
			{
				tmp = pVal[j];
				pVal[j] = pVal[j + 1];
				pVal[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AscSortFun2(UINT16_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT16_T j = 0;
	UINT16_T k = length - 1;
	UINT16_T m = 0;
	UINT8_T flag;
	UINT16_T tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		m = 0;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (pVal[j] > pVal[j + 1])
			{
				tmp = pVal[j];
				pVal[j] = pVal[j + 1];
				pVal[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 冒泡降序排列数据
//////输入参数:
//////输出参数:
//////说		明：现在发现降序有问题，需要后续调试
//////////////////////////////////////////////////////////////////////////////
UINT8_T DescSortFun1(UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT16_T j = 0;
	UINT16_T k = length - 1;
	UINT16_T m = 0;
	UINT8_T flag;
	UINT8_T tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		m = 0;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (pVal[j] < pVal[j + 1])
			{
				tmp = pVal[j + 1];
				pVal[j + 1] = pVal[j];
				pVal[j] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 冒泡降序排列数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DescSortFun2(UINT16_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT16_T j = 0;
	UINT16_T k = length - 1;
	UINT16_T tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < (k - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (pVal[j] < pVal[j + 1])
			{
				tmp = pVal[j + 1];
				pVal[j + 1] = pVal[j];
				pVal[j] = tmp;
			}
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T CalcAvgFun1(UINT16_T *pVal, UINT16_T length, UINT16_T index)
{
	double sum = 0;
	UINT16_T i = 0;
	for (i = index; i < length; i++)
	{
		sum += pVal[i];
	}
	return (UINT16_T)(sum / (length - index));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T CalcAvgFun2(UINT16_T *pVal, UINT16_T length)
{
	double sum = 0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		sum += pVal[i];
	}
	return (UINT16_T)(sum / length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T CalcAvgFun3(UINT8_T *pVal, UINT16_T length, UINT16_T index)
{
	double sum = 0;
	UINT16_T i = 0;
	for (i = index; i < length; i++)
	{
		sum += pVal[i];
	}
	return (UINT8_T)(sum / (length - index));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T CalcAvgFun4(UINT8_T *pVal, UINT16_T length)
{
	double sum = 0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		sum += pVal[i];
	}
	return (UINT8_T)(sum / length);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T CompareFun1(UINT8_T *p1, UINT8_T *p2, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明： 指定比较数据的起始位置
//////////////////////////////////////////////////////////////////////////////
UINT8_T CompareFun2(UINT8_T *p1, UINT8_T *p2, UINT16_T index, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = index; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T CompareFun3(UINT16_T *p1, UINT16_T *p2, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明： 指定比较数据的起始位置
//////////////////////////////////////////////////////////////////////////////
UINT8_T CompareFun4(UINT16_T *p1, UINT16_T *p2, UINT16_T index, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = index; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}