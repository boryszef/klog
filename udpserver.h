#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QNetworkInterface>
#include <QUdpSocket>
#include <QObject>
#include <QHostAddress>
#include <QDataStream>
#include "utilities.h"

enum Type
    {
      Heartbeat,
      Status,
      Decode,
      Clear,
      Reply,
      QSOLogged,
      Close,
      Replay,
      HaltTx,
      FreeText,
      WSPRDecode,
      Location,
      LoggedADIF,
      HighlightCallsign,
      SwitchConfiguration,
      Configure,
      maximum_message_type_     // ONLY add new message types
                                // immediately before here
};

class UDPServer : public QObject
{
    Q_OBJECT

public:
    explicit UDPServer(QObject *parent = nullptr);
    bool start();

    bool stop();
    bool isStarted();
    void setLogging(const bool _t);
    void setRealTimeUpdate(const bool _t);
    //void setAddress(const QString _address);
    void setPort(const int _port);
    void setNetworkInterface(const QString &_t);

private:
    void readPendingDatagrams();
    void parse(const QByteArray &msg);
    void adifParse(QByteArray &msg);
    void leaveMultiCastGroup();
    void joinMultiCastGroup();
    bool startNow(quint16 _port, QHostAddress const& _multicast_group_address);

    QNetworkInterface networkInterface;
    QUdpSocket *socketServer;    
    QHostAddress groupAddress;

    //QString address;
    int port;
    bool logging, realtime;
    bool haveNetworkInterface;

    Utilities *util;

#if QT_VERSION >= 0x050400
    static quint32 constexpr schema_number {3};
#elif QT_VERSION >= 0x050200
    static quint32 constexpr schema_number {2};
#else
    // Schema 1 (Qt_5_0) is broken
#error "Qt version 5.2 or greater required"
#endif

signals:
    void status_update (const int _type, const QString _dxcall, const double _freq, const QString _mode,
                        const QString report, const QString de_call, const QString de_grid,
                        const QString dx_grid, const QString sub_mode);

    //void logged_qso (const int _type, const QString _dxcall, const double _freq, const QString _mode,
    //                 const QString _dx_grid, const QString _time_off, const QString _report_sent, const QString _report_rec,
    //                 const QString _tx_power, const QString _comments, const QString _name, const QString _time_on, const QString _de_call, const QString _de_grid);

    void logged_qso (const QString &_dxcall, const QString &_mode, const QString &_band, const double _freq,
                     const QString &_mygrid, const QString &_dxgrid, const QString &rstTX, const QString &rstRX,
                     const QString &comment, const QString &stationcallsign, const QString &name,
                     const QString &_operator, const QDateTime datetime, const QDateTime datetime_off,
                     const QString &_exchangeTX, const QString &_exchangeRX, const QString &_txpwr);
    void clearSignal();

private slots:
    void slotReadPendingDatagrams();


};

#endif // UDPSERVER_H
