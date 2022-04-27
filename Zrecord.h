#pragma once

#define MAX_RECORDS 50 // Make it less than 50... if you change something you have to test max again

class Record{
  public:

  String timeStamp;
  float airTemperature;
  float humidity;
  float temperature4;
  float temperature5;
  float weight4;
  float weight5;


  Record() = default;

  Record(const String timeStamp, const float airTemperature, const float humidity, const float temperature4, const float temperature5, const float weight4, const float weight5):
    timeStamp{timeStamp},
    airTemperature{airTemperature},
    humidity{humidity},
    temperature4{temperature4},
    temperature5{temperature5},
    weight4{weight4},
    weight5{weight5}
    {
  }


  String toString() const {
    return String("[\"") + timeStamp + "\", " + 
          airTemperature + ", " +
          humidity + ", " +
          temperature4 + ", " +
          temperature5 + ", " +
          weight4 + ", " +
          weight5 + "]"; 
  }
};

class Records{
  public:
  
  Record toSendRecords[MAX_RECORDS];
  int toSend = 0;

  bool addRecord(Record record){
    if (toSend >= MAX_RECORDS) return false;
    toSendRecords[toSend++] = record;
    return true;
  }

  String toString() const {
    String s = "[";
    for (int i=0; i<toSend; i++){
      s += toSendRecords[i].toString();
      if (!(i+1 == toSend)) s += ",";
    }
    s += "]";
    return s;
  }

  void clear(){toSend = 0;}
};