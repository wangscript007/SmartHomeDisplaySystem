/*
 * ClassName: SerialPortProtocol
 * Description: 串口协议类
 *
 * Author: Albert
 * Version: V0.1
 * Date: 2018.09.20
 * Version Description:
 *          【2018.09.27】 V0.1
 *              1.创建该类。
 *              2.更改该类为单例类。
 */
#ifndef SERIALPORTPROTOCOL_H
#define SERIALPORTPROTOCOL_H

#include <QObject>
#define FRAMEDATAMAXLEN 1024

typedef struct
{
    quint8 head[2];
    quint8 retain[3];
    quint8 len;
    quint8 deviceID;
    quint8 data[FRAMEDATAMAXLEN];
    quint8 foot;
}Frame;

class SerialPortProtocol : public QObject
{
    Q_OBJECT
private:
    explicit SerialPortProtocol(QObject *parent = nullptr);

public:
    static SerialPortProtocol * getObject();

    double te1 = 0;
    double hu1 = 0;
    int light1 = 0;
    int uv1 = 0;
    int co21 = 0;
    int pm251 = 0;
    int pm101 = 0;
    int atmospheric1 = 0;
    int iReserve1 = 0;
    int iReserve2 = 0;

    bool fire1 = false;
    bool mq51 = false;
    bool mq21 = false;
    bool os1 = false;
    bool re1 = false;
    bool bReserve1 = false;
    bool bReserve2 = false;
    bool bReserve3 = false;
    bool bReserve4 = false;
    bool bReserve5 = false;

signals:
    void newAirConditionerControl(int index,int model,int te,int fun);
    void newLedControl(int index,int b);
    void newHeaterControl(int index,int te);
    void newCurtainsControl(int index,int pos);

protected slots:
    void readFromSerialSlot(const QByteArray &data);

protected:
    void sendDataToSerialPort();
    void oneFrameReadData();
    void handleReadData();
    //向网关发送数据
    //浮点
    void sendTemperatureSensorData(double temperature);

    void sendHumiditySensorData(double humidity);
    //int 2Byte
    void sendLightIntensitySensorData(int intensity);
    //int 1Byte
    void sendUltravioletSensorData(int ultraviolet);
    void sendCo2ConcentrationSensorData(int concentration);
    void sendPm25ConcentrationSensorData(int concentration);
    void sendPm10ConcentrationSensorData(int concentration);
    void sendAtmosphereSensorData(int atmosphere);
    void sendIntReserve1SensorData(int value);
    void sendIntReserve2SensorData(int value);

    //bool 1Byte
    void sendFire1SensorData(bool isAbnormal);
    void sendMq51SensorData(bool isAbnormal);
    void sendMq21SensorData(bool isAbnormal);
    void sendOs1SensorData(bool isAbnormal);
    void sendRe1SensorData(bool isAbnormal);
    void sendBoolReserve1SensorData(bool isAbnormal);
    void sendBoolReserve2SensorData(bool isAbnormal);
    void sendBoolReserve3SensorData(bool isAbnormal);
    void sendBoolReserve4SensorData(bool isAbnormal);
    void sendBoolReserve5SensorData(bool isAbnormal);

    Frame sendData;
    Frame readData;
    quint8 tempData[FRAMEDATAMAXLEN+8];
    int readLen = 0;

};

#endif // SERIALPORTPROTOCOL_H
