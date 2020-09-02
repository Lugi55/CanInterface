## SensorHub

### MCP2562
|Pin|Funktion|
|:---:|:----:|
|1|T<sub>XD</sub>|
|2|V<sub>SS</sub>|
|3|V<sub>DD</sub>|
|4|R<sub>XD</sub>|
|5|V<sub>IO</sub>|
|6|CANL|
|7|CANH|
|8|STBY|

### SUB D9
|Pin|Funktion|
|:---:|:----:|
|1||
|2|CANL|
|3||
|4||
|5||
|6|GND|
|7|CANH|
|8||
|9||

### aentron Stecker
|Pin|Funktion|
|:---:|:----:|
|1|CANL|
|2|CANH|
|3|GND|
|4|12V|
|5||
|6||
|7|E-Switch|
|8|Charge-Switch|


### Json Tx Frame
```json
{"MsgData":"number","MsgID":"number","MsgIDMask":"number"}
```


### Topics
CAN/TX   
CAN/Voltage1
CAN/Voltage2
CAN/Voltage3
CAN/Temperature1
CAN/Temperature2
CAN/Temperature3
