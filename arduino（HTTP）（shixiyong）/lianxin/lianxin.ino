void setup()
{
pinMode(12,OUTPUT);  
  Serial.begin(9600);
String returnValue= "\"switch\":1";
char string[100] ;
for (int i = 0; i < returnValue.length() + 1; i++)
 {
 string[i] = returnValue[i];
 }

char seps[]   = ":";
char *token;
token = strtok( string, seps );
while( token != NULL )
   {
//     if(token == "string"){
//       token = strtok( NULL, seps );
//       if(token == "of"){
//         digitalWrite(12,HIGH);
//       }
//     }
    Serial.println(token);
    String a = token ;
    if(a == "\"switch\""){
      digitalWrite(12,HIGH);
    } 
     a = "";
    token = strtok( NULL, seps ); 
   }
}

void loop()
{
}


