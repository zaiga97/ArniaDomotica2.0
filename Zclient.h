#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

class Zclient{
  public:
  Zclient() = default;

  const String host = "script.google.com";
  const int port = 443;
  WiFiClientSecure client;

  String newPostData(const Records& records, const String& sheetName) const {
    return String("{\"action\": \"append\", ") +
           "\"sheetName\": \"" + sheetName + "\"," +
           "\"records\": " + records.toString() + "}";
  }

  String newAppendRequest(const Records& records, const String& sheetName) const {
    String postData = newPostData(records, sheetName);
    return String("POST ") + googleAppUrl + " HTTP/1.1\r\n" +
          "Host: " + host + "\r\n" +
          "User-Agent: Arduino/1.0\r\n" +
          "Connection: close\r\n" +
          "Content-Type: application/json;\r\n" +
          "Content-Length: " + postData.length() + "\r\n\r\n" +
          postData + "\r\n\r\n";
  }

  void send(const Records& records, const String& sheetName) {
    client.println(newAppendRequest(records, sheetName));
  }

  void setup(){
    client.setInsecure();
  }

  bool connect(){
    return client.connect(host, port);
  }

  String getResponse(){
    String response = "";
    char c;
    while(client.available()){
      c = client.read();
      response += c; 
    }
    return response;
  }
};