/*
  mail.hpp

  Author: Zoren Dela Cruz
  Description: Sending emails and alerts to personal gmails
               using ESP32 via SMTP Server
  Date: 5/11/2023
*/
#pragma once

#ifndef EmailSender_hpp
#define EmailSender_hpp

#include <Arduino.h>
#include <ESP_Mail_Client.h>

class EmailSender {
public:
    EmailSender(const char* ssid, const char* password, const char* smtpHost, int smtpPort, const char* authorEmail, const char* authorPassword, const char* recipientEmail);
    void sendEmail(const char* subject, const char* message);

private:
    SMTPSession smtp;
    void connectToWiFi(const char* ssid, const char* password);
    void configureSMTPSession(const char* smtpHost, int smtpPort, const char* authorEmail, const char* authorPassword);
    void setupSMTPSession();
};

#endif
