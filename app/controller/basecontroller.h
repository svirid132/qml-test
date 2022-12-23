#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QJSValue>
#include <QObject>

class BaseController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJSValue onAccess READ onAccess WRITE setOnAccess NOTIFY onAccessChanged)
    Q_PROPERTY(QJSValue onError READ onError WRITE setOnError NOTIFY onErrorChanged)

public:
    explicit BaseController(QObject *parent = nullptr);

    void setOnAccess(const QJSValue& onAccess) {
        m_onAccess = onAccess;
        emit onAccessChanged();
    }
    void setOnError(const QJSValue& onError) {
        m_onError = onError;
        emit onErrorChanged();
    }

    QJSValue onAccess() {
        return m_onAccess;
    }
    QJSValue onError() {
        return m_onError;
    }

signals:
    void onAccessChanged();
    void onErrorChanged();

protected:
    void execOnAccess() {
        if(m_onAccess.isCallable()) {
            m_onAccess.call();
        }
    }
    void execOnError() {
        if(m_onError.isCallable()) {
            m_onError.call();
        }
    }
    QJSValue m_onAccess;
    QJSValue m_onError;
};

#endif // BASECONTROLLER_H
