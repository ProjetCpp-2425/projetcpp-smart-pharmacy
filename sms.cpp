#include <QtNetwork>
#include "sms.h"


QString twilio_phone_number = "+12512610816";   // t7ott num elli me twilio




sms::sms(){

}
void sms::sendSMS(const QString &to, const QString &message) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/AC4da285a7f39250cc5498a027132a1edd/Messages.json"); // hne fi 3outh l we7dt7ott SID te3 compte twilio
    QNetworkRequest request(url);

    //  /// ////////////////////////////////////////////////////////////////////// fi 3oth 1 t7ot SID w 2 t7ot Token
    QString credentials = "AC4da285a7f39250cc5498a027132a1edd:7cbf0479432bfcc8021f9252cd521f6e";
    QByteArray base64Credentials = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64Credentials);


    QByteArray postData;
    postData.append("From="+twilio_phone_number.toUtf8());
    postData.append("&To=" + to.toUtf8());
    postData.append("&Body=" + message.toUtf8());


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Make the request
    QNetworkReply *reply = manager->post(request, postData);


    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully";
        } else {
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }


        reply->deleteLater();
        manager->deleteLater();
    });
}
