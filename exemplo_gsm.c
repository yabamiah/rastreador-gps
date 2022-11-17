// Exemplo de recebimento de dados via GSM
String comp = "";
  if (gsm.available() > 0) {

    String msggsm = "";
    while (gsm.available() > 0)
    {
      char letra = gsm.read();
      if (isAlphaNumeric(letra)) msggsm += letra;
    }
    int tam = msggsm.length();


    comp += msggsm[tam - 2];
    comp += msggsm[tam - 1];

    Serial.print("MSG1: ");
    Serial.println(msggsm);

    Serial.print("comp: ");
    Serial.println(comp);


  lcd.setCursor(12,1);
     lcd.print(comp);


    if (comp == "L1")
    {
      digitalWrite(11, 0);
      Serial.println("Ligou1");
    }
    else if (comp == "D1")
    {
      digitalWrite(11, 1);
      Serial.println("Desligou1");
    }
    else if (comp == "L2")
    {
      digitalWrite(12, 0);
      Serial.println("ligou2");
    }
    else if (comp == "D2")
    {
      digitalWrite(12, 1);
      Serial.println("Desligou2");
    }