## WORKSHOP "UN ARDUINO IN ZUCCA" 
###### opendot - 25.10.2014
* * *
**CODICE:** <https://github.com/dot-dot-dot/arduino-in-zucca>

### COMPONENTI
**INPUT:**

* Sensore Infrarosso (IR) di distanza, analogico  
<http://www.sharpsma.com/webfm_send/1489>

**OUTPUT:**

* 2 Strip LED bianchi (PWM) modulati con 2 MOSFET IRF540N  
<http://www.irf.com/product-info/datasheets/data/irf540n.pdf>
* 1 buzzer piezoelettrico, PWM

### COMPORTAMENTO  
**STANDBY (distanza > 80cm):**

* Pulsazione del LED
* Risata casuale tra 1 e 3 minuti, durata 3 secondi


**AZIONE (distanza < 80cm):**

* Pulsazione dei LED invertiti in base alla distanza
* Risata con velocità in base alla distanza


### SCHEMA
![schema](https://raw.githubusercontent.com/dot-dot-dot/arduino-in-zucca/master/schema_bb.png)
