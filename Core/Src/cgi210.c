#include "cgi210.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include <stdio.h>

/* GPS Datas */
float AccRaw[3];
float GyoRaw[3];
float AngleRaw[3];
Longtitude_And_Latitude_Data_Type Longtitude_Data;
Longtitude_And_Latitude_Data_Type Latitude_Data;
double Altitude;
float SpeedValue[4];
uint8_t NSV[2];

/* Data records */
uint8_t Data_Record_Frame_CNT = 0;
CGI_Data_Record_Frame_Type CGI_Data_Record_Freme[10] = {{
    {0},
    {0},
    {0},
    {
        0,
        0,
        0.0,
        0x2D,
    },
    {
        0,
        0,
        0.0,
        0x2D,
    },
    {0},
    {0},
}};
//��buf����õ���cx���������ڵ�λ��
//����ֵ:0~0XFE,����������λ�õ�ƫ��.
//       0XFF,�������ڵ�cx������
uint8_t NMEA_Comma_Pos(uint8_t *GPS_Data, uint8_t cx) {
  uint8_t *p = GPS_Data;
  while (cx) {
    /* code */
    if (*GPS_Data == '*' || *GPS_Data < ' ' || *GPS_Data > 'z') {
      //����'*'���߷Ƿ��ַ����򲻴��ڵ�cx������
      return 0xFF;
    }
    if (*GPS_Data == ',') {
      cx--;
    }
    GPS_Data++;
  }
  return GPS_Data - p;
}

// m^n����
//����ֵ:m^n�η�.
uint32_t NMEA_Pow(uint8_t m, uint8_t n) {
  uint32_t result = 1;
  while (n--)
    result *= m;
  return result;
}

// strת��Ϊ����,��','����'*'����
// buf:���ִ洢��
// dx:С����λ��,���ظ����ú���
//����ֵ:ת�������ֵ
int NMEA_Str2num(uint8_t *buf, uint8_t *dx) {
  uint8_t *p = buf;
  uint32_t ires = 0, fres = 0;
  uint8_t ilen = 0, flen = 0;
  uint8_t mask = 0;
  int res;
  while (1) //�õ�������С���ĳ���
  {
    if (*p == '-') { //����
      mask |= 0x02;
      p++;
    }

    if ((*p == ',') || (*p == '*')) { //����
      break;
    }

    if (*p == '.') { //����С����
      mask |= 0x01;
      p++;
    } else if ((*p > '9') || (*p < '0')) { //�Ƿ��ַ�
      ilen = 0;
      flen = 0;
      break;
    }

    if (mask & 0x01) {
      flen++;
    } else {
      ilen++;
    }
    p++;
  }

  if (mask & 0x02) {
    buf++; //ȥ������
  }
  for (uint8_t i = 0; i < ilen; i++) //�õ�������������
  {
    ires += NMEA_Pow(10, ilen - 1 - i) * (buf[i] - '0');
  }

  if (flen > 5) {
    flen = 5; //���ȡ��λС��
  }
  *dx = flen; //�õ�С����λ��
  for (uint8_t i = 0; i < flen; i++) {
    //�õ�С�����ֵ�����
    fres += NMEA_Pow(10, flen - 1 - i) * (buf[ilen + 1 + i] - '0');
  }
  res = ires * NMEA_Pow(10, flen) + fres;
  if (mask & 0x02) {
    res = -res;
  }
  return res;
}

/* ����CGI210��Ϲߵ����ݽ��� */
void NMEA_GPCHC_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  int32_t temp = 0;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPCHC");

  posx = NMEA_Comma_Pos(p1, 3); //�õ�ƫ����
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 4); //�õ�������
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 5); //�õ������
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 6); //�õ�����X��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 7); //�õ�����Y��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 8); //�õ�����Z��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 9); //�õ��ӱ�X��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 10); //�õ��ӱ�Y��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 11); //�õ��ӱ�Z��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[2] = temp * 1.0 / NMEA_Pow(10, 2);
  }

  posx = NMEA_Comma_Pos(p1, 14); //�õ��߶�
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Altitude = temp / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 15); //�õ������ٶ�
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 16); //�õ������ٶ�
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 17); //�õ������ٶ�
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 18); //�õ������ٶ�
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[3] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 19); //�õ�������1��������
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    NSV[0] = temp / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 20); //�õ�������2��������
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    NSV[1] = temp / NMEA_Pow(10, dx);
  }
}

/* ����CGI210 ͨ�����ݽ��� GPGGA */
void NMEA_GPGGA_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  uint32_t temp;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPGGA");
  posx = NMEA_Comma_Pos(p1, 2); //�õ�γ��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Latitude_Data.Degrees = temp / NMEA_Pow(10, dx + 2); //�õ���
    Latitude_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //�õ�'
    Latitude_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 3); //�õ���γ���Ǳ�γ
  if (posx != 0xFF) {
    Latitude_Data.Hemisphere = *(p1 + posx);
  }

  posx = NMEA_Comma_Pos(p1, 4); //�õ�����
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Longtitude_Data.Degrees = temp / NMEA_Pow(10, dx + 2); //�õ���
    Longtitude_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //�õ���
    Longtitude_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 5); //�õ�������������
  if (posx != 0xFF) {
    Longtitude_Data.Hemisphere = *(p1 + posx);
  }
}

/* Add new frame record */
void Data_Record_Add_New_Frame(void) {
  CGI_Data_Record_Frame_Type Data_Frame;

  for (uint8_t i = 0; i < 3; i++) {
    Data_Frame.Angle_Data[i] = AngleRaw[i];
    Data_Frame.Gyro_Data[i] = GyoRaw[i];
    Data_Frame.Acc_Data[i] = AccRaw[i];
    Data_Frame.Speed_Data[i] = SpeedValue[i];
  }
  Data_Frame.Speed_Data[3] = SpeedValue[3];

  Data_Frame.NSV_Number[0] = NSV[0];
  Data_Frame.NSV_Number[1] = NSV[1];

  Data_Frame.Lat_Data = Latitude_Data;
  Data_Frame.Long_Data = Longtitude_Data;

  /* A simple FIFO algorithm */
  if (Data_Record_Frame_CNT <= 9) {
    CGI_Data_Record_Freme[Data_Record_Frame_CNT] = Data_Frame;
    Data_Record_Frame_CNT++;
  } else {
    for (uint8_t i = 0; i < 9; i++) {
      CGI_Data_Record_Freme[i] = CGI_Data_Record_Freme[i + 1];
    }
    CGI_Data_Record_Freme[9] = Data_Frame;
  }
}