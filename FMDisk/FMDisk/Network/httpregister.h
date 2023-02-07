#ifndef HTTPREGISTER_H
#define HTTPREGISTER_H

#include <QObject>
#include "IHttpReqRes.h"
#include "Utils/HttpStructData.h"


class HttpRegister : public IHttpReqRes
{
    Q_OBJECT

public:
    explicit HttpRegister(RegisterInfo registerInfo, InterfaceInputHead header);
    ~HttpRegister();

protected:
    void processResponse(QByteArray strResult);
    void processError();

private:
    QByteArray createRegisterJson(RegisterInfo registerInfo, InterfaceInputHead header);

};

#endif // HTTPREGISTER_H
