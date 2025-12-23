# PROTOCOL DRAFT

```
 0       7 8    12   16        19 20 23
+---------+----+----+------------+-----+
| PT 0x21 | N1 | N2 | abs(O1-O2) | ICR |
+---------+----+----+------------+-----+

 0       7 8     15  16      X
+---------+--------+----------+
| PT 0x9. |  LEN   |   NAME   |
+---------+--------+----------+

 0       7 8    12   16   20
+---------+----+----+----+----+
| PT 0xB1 | N1 | O1 | N2 | O2 |
+---------+----+----+----+----+

 0       7 8     15
+---------+--------+
| PT 0xA. |  CGRD  |
+---------+--------+
```

## PT - Packet Type

0x01-0x2F: client->server communication  
0x30-0x7F: reserved  
0x80-0xAF: server->client communication  
0xC0-0xFF: reserved  

* 0x0.: control messages tbd
* 0x1.: answer messages tbd
* 0x21: Interval Challenge Response
* 0x8.: control messages tbd
* 0x90: Assigned Name (self)
* 0x91-9F: Assigned Name (Player 1-17)
* 0xA0: Current Grade (self)
* 0xA1-AF: Current Grade (Player 1-17)
* 0xB1: Interval Challenge

## N - Note
* 0x1 - 0xC: C,C♯,D,D♯,E,F,F♯,G,G♯,A,A♯,H

## O - Octave
* 0x0 - 0x8: Octave 0-8

## ICR - Interval Challenge Response
* 0x0 - 0xF: Interval between (N1, O1) and (N2, O2)

## LEN - Length
* 0x01 - 0xFF: Name Length

## NAME - Name
* 0x\*: UTF-8 Name

## CGRD - Current Grade
* 0x00-64: Current Grade from 0-100
