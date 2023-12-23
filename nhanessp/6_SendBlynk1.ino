void senBlynk() {
  
  Blynk.virtualWrite(0, nhietdo1);
  Blynk.virtualWrite(1, doam1);
 
 
  Blynk.virtualWrite(2, nhietdo2);
  Blynk.virtualWrite(3, doam2);
  

  Blynk.virtualWrite(8, String(day()) + "/" + month() + "/" + year());
  Blynk.virtualWrite(9, String(hour()) + ":" + minute() + ":" + second());
}
