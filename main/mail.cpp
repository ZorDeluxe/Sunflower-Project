#include "mail.hpp"

EmailSender::EmailSender(const char* ssid, const char* password, const char* smtpHost, int smtpPort, const char* authorEmail, const char* authorPassword, const char* recipientEmail) {
    connectToWiFi(ssid, password);
    configureSMTPSession(smtpHost, smtpPort, authorEmail, authorPassword);
    setupSMTPSession();
}

void EmailSender::connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
    }
}

void EmailSender::configureSMTPSession(const char* smtpHost, int smtpPort, const char* authorEmail, const char* authorPassword) {
    Session_Config config;
    config.server.host_name = smtpHost;
    config.server.port = smtpPort;
    config.login.email = authorEmail;
    config.login.password = authorPassword;
    config.login.user_domain = F("127.0.0.1");

    // Set other session config parameters here

    smtp.debug(1);
    smtp.callback(smtpStatusCallback);
}

void EmailSender::setupSMTPSession() {
    if (!smtp.connect(&config)) {
        Serial.printf("Connection error, Status Code: %d, Error Code: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
        return;
    }
}

void EmailSender::sendEmail(const char* subject, const char* message) {
    SMTP_Message email;
    email.subject = subject;
    email.addRecipient(F("Someone"), recipientEmail);
    email.text.content = message;
    email.text.charSet = F("us-ascii");

    if (!MailClient.sendMail(&smtp, &email)) {
        MailClient.printf("Error, Status Code: %d, Error Code: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    }

    smtp.sendingResult.clear();
}

void smtpCallback(SMTP_Status status) {
    Serial.println(status.info());

    if (status.success()) {
        Serial.println("----------------");
        MailClient.printf("Message sent success: %d\n", status.completedCount());
        MailClient.printf("Message sent failed: %d\n", status.failedCount());
        Serial.println("----------------\n");

        for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
            SMTP_Result result = smtp.sendingResult.getItem(i);
            MailClient.printf("Message No: %d\n", i + 1);
            MailClient.printf("Status: %s\n", result.completed ? "success" : "failed");
            MailClient.printf("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
            MailClient.printf("Recipient: %s\n", result.recipients.c_str());
            MailClient.printf("Subject: %s\n", result.subject.c_str());
        }
        Serial.println("----------------\n");

        smtp.sendingResult.clear();
    }
}
